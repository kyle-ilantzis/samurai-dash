#include "RealTimeCollisionDetection.h"

#include "Model.h"

#include <iostream>

using namespace rtcd;
using namespace glm;
using namespace std;

const char* BoundingVolumeTypeToStr[] = {
	"NIL_BV",
	// "SPHERE",
	"CAPSULE"
};

void BoundingVolume::setCapsule(rtcd::Capsule* capsule) { 
	
	deleteData(); 
	mBoundingVolumeType = CAPSULE; 
	mData = (void*)capsule; 
}

void BoundingVolume::deleteData() {

	switch (mBoundingVolumeType) {
	case CAPSULE:
		delete (Capsule*)mData;
		break;
	}
}

bool TestBoundingVolumes(Model& m1, Model& m2) {

	BoundingVolume& b1 = m1.GetBoundingVolume();
	BoundingVolume& b2 = m2.GetBoundingVolume();

	BoundingVolumeType bt1 = b1.GetBoundingVolumeType();
	BoundingVolumeType bt2 = b2.GetBoundingVolumeType();

	if (bt1 == NIL_BV || bt2 == NIL_BV) {
		return false;
	}

	if (bt1 == CAPSULE && bt2 == CAPSULE) {

		const Capsule& c1 = *((Capsule*) b1.GetData());
		const Capsule& c2 = *((Capsule*) b2.GetData());

		return TestCapsuleCapsule(c1.transform(m1.GetWorldMatrix()), c2.transform(m2.GetWorldMatrix()));
	}

	cout << "TestBoundingVolumes intersection of unsupported pairing " 
		 << BoundingVolumeTypeToStr[bt1] << " and " << BoundingVolumeTypeToStr[bt2] 
		 << endl;

	return false;
}

Capsule Capsule::transform(const mat4& M) const {

	glm::vec3 a (M * vec4(a,1));
	glm::vec3 b (M * vec4(b, 1));
	Capsule cap;
	cap.a = a;
	cap.b = b;
	cap.r = r;

	return cap;
}
	

bool rtcd::TestCapsuleCapsule(const Capsule& capsule1, const Capsule& capsule2) {

	// Compute (squared) distance between the inner structures of the capsules
	float s, t;
	vec3 c1, c2;
	
	float dist2 = ClosestPtSegmentSegment(
		capsule1.a, capsule1.b, 
		capsule2.a, capsule2.b, 
		s, t, 
		c1, c2
	);

	// If (squared) distance smaller than (squared) sum of radii, they collide
	float radius = capsule1.r + capsule2.r;
	return dist2 <= radius * radius;
}

float rtcd::ClosestPtSegmentSegment(
	const glm::vec3& p1, const glm::vec3& q1,
	const glm::vec3& p2, const glm::vec3& q2,
	float& s, float& t,
	glm::vec3& c1, glm::vec3& c2) {

	vec3 d1 = q1 - p1; // Direction vector of segment S1
	vec3 d2 = q2 - p2; // Direction vector of segment S2
	vec3 r = p1 - p2;
	float a = dot(d1, d1); // Squared length of segment S1, always nonnegative
	float e = dot(d2, d2); // Squared length of segment S2, always nonnegative
	float f = dot(d2, r);

	// Check if either or both segments degenerate into points
	if (a <= EPSILON && e <= EPSILON) {
		// Both segments degenerate into points
		s = t = 0.0f;
		c1 = p1;
		c2 = p2;
		return dot(c1 - c2, c1 - c2);
	}
	if (a <= EPSILON) {
		// First segment degenerates into a point
		s = 0.0f;
		t = f / e; // s = 0 => t = (b*s + f) / e = f / e
		t = clamp(t, 0.0f, 1.0f);
	}
	else {
		float c = dot(d1, r);
		if (e <= EPSILON) {
			// Second segment degenerates into a point
			t = 0.0f;
			s = clamp(-c / a, 0.0f, 1.0f); // t = 0 => s = (b*t - c) / a = -c / a
		}
		else {
			// The general nondegenerate case starts here
			float b = dot(d1, d2);
			float denom = a*e - b*b; // Always nonnegative

			// If segments not parallel, compute closest point on L1 to L2 and
			// clamp to segment S1. Else pick arbitrary s (here 0)
			if (denom != 0.0f) {
				s = clamp((b*f - c*e) / denom, 0.0f, 1.0f);
			}
			else s = 0.0f;
			// Compute point on L2 closest to S1(s) using
			// t = Dot((P1 + D1*s) - P2,D2) / Dot(D2,D2) = (b*s + f) / e
			t = (b*s + f) / e;

			// If t in [0,1] done. Else clamp t, recompute s for the new value
			// of t using s = Dot((P2 + D2*t) - P1,D1) / Dot(D1,D1)= (t*b - c) / a
			// and clamp s to [0, 1]
			if (t < 0.0f) {
				t = 0.0f;
				s = clamp(-c / a, 0.0f, 1.0f);
			}
			else if (t > 1.0f) {
				t = 1.0f;
				s = clamp((b - c) / a, 0.0f, 1.0f);
			}
		}
	}

	c1 = p1 + d1 * s;
	c2 = p2 + d2 * t;
	return dot(c1 - c2, c1 - c2);
}