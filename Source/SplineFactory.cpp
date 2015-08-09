#include <iostream>

#include "SplineFactory.h"

using namespace std;
using namespace glm;
using namespace rtcd;

const ci_string SplineFactory::splineName = "Spline";

SplineModel* SplineFactory::LoadSpline() {
	
	SplineModel* splineModel = new SplineModel();
	SplineModel& spline = *splineModel;

	ci_stringstream outName;
	outName << "name = \"" << splineName << "\"";
	ci_istringstream inName(outName.str());

	spline.Load(inName);

	if (!spline.HasControlPoints()) {
		makeControlPoints(spline);
	}

	makeTriangleStrip(spline);

	makeOscullatingPlanes(spline);

	makeEndOfTrackBoundingVolume(spline);

	return splineModel;
}

const vec2 SplineFactory::controlPointsCount = vec2(20, 30);
const vec2 SplineFactory::deltaMinControlPoint = vec2(20.0f, -10.0f);
const vec2 SplineFactory::deltaMaxControlPoint = vec2(21.0f, 10.0f);

const glm::vec4 SplineFactory::controlPointsColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);

void SplineFactory::makeControlPoints(SplineModel& spline) {

	std::vector<SplineModel::Vertex> controlPoints;

	int N = controlPointsCount.x + rand() % (int) (controlPointsCount.y - controlPointsCount.x);

	controlPoints.push_back({
		vec3(0, 0, deltaMinControlPoint.x),
		controlPointsColor
	});

	for (int i = 1; i < N; i++) {

		SplineModel::Vertex prev = controlPoints[i - 1];
		
		int dz = deltaMinControlPoint.x + rand() % (int) (deltaMaxControlPoint.x - deltaMinControlPoint.x);
		int dy = deltaMinControlPoint.y + rand() % (int) (deltaMaxControlPoint.y - deltaMinControlPoint.y);

		SplineModel::Vertex next = {
			prev.position + vec3(0, dy, -dz),
			controlPointsColor
		};
		controlPoints.push_back(next);
	}

	spline.SetControlPoints(controlPoints);
}

const int SplineFactory::triangleStripSegmentCount = 5;
const float SplineFactory::trackWidth = 20.0f;
SplineFactoryPlaneDelegate SplineFactory::splinePlaneDelegate;

void SplineFactory::makeTriangleStrip(SplineModel& spline) {

	std::vector<SplineModel::Vertex> points;

	vec4 red =	vec4(1.0f, 0.0f, 0.0f, 1.0f);
	vec4 green=	vec4(0.0f, 1.0f, 0.0f, 1.0f);
	vec4 blue = vec4(0.0f, 0.0f, 1.0f, 1.0f);

	vec3 shift = vec3(trackWidth / 2, 0, 0);
	float timeStep = 1.0f / triangleStripSegmentCount;

	vec3 point = spline.At(0);
	points.push_back({
		point + shift,
		red
	});
	points.push_back({
		point - shift,
		green
	});

	int shiftDirection = 1;
	int colorChoice = 2;
	for (float t = timeStep; t <= spline.MaxTime(); t += timeStep) {

		vec3 point = spline.At(t);

		point += (shiftDirection ? 1.0f : -1.0f) * shift;

		points.push_back({
			point,
			colorChoice == 0 ? red : colorChoice == 1 ? green : blue
		});

		shiftDirection = (shiftDirection + 1) % 2;
		colorChoice = (colorChoice + 1) % 3;
	}

	spline.SetPoints(points, splinePlaneDelegate);
}

SplineModel::Plane SplineFactoryPlaneDelegate::At(SplineModel& spline, float t) {
	
	vec3 position = spline.At(t);
	vec3 next = spline.At(t + 0.05f);

	vec3 tangent = normalize(next - position);
	
	vec3 normal = vec3(-1.0f, 0.0f, 0.0f);

	return { position, tangent, normal };
}

bool SplineFactory::MAKE_OSCULATTING_PLANES = true;

void SplineFactory::makeOscullatingPlanes(SplineModel& spline) {

	if (!MAKE_OSCULATTING_PLANES) { return; }

	std::vector<SplineModel::Vertex> points;
	
	vec4 color(1,1,1,1); // white

	for (float t = 0; t < spline.MaxTime(); t += 0.5f) {

		SplineModel::Plane p = spline.PlaneAt(t);
		vec3 B = normalize(cross(p.tangent, p.normal));

		vec3 translation = 2.0f * B;

		points.push_back({ translation + p.position, color });
		points.push_back({ translation + p.position + p.tangent, color });

		points.push_back({ translation + p.position, color });
		points.push_back({ translation + p.position + p.normal, color });

		points.push_back({ translation + p.position, color });
		points.push_back({ translation + p.position + B, color });
	}

	spline.SetOscullatingPlanes(points);
}

float SplineFactory::endOfTrackCapsuleTimeOffset = 0.5f;
float SplineFactory::endOfTrackCapsuleRadius = 3;

void SplineFactory::makeEndOfTrackBoundingVolume(SplineModel& spline) {

	float maxTime = spline.MaxTime() - endOfTrackCapsuleTimeOffset;

	SplineModel::Plane p = spline.PlaneAt(maxTime);

	vec3 a = p.position + p.normal * trackWidth * 0.5f;
	vec3 b = p.position - p.normal * trackWidth * 0.5f;
	float r = endOfTrackCapsuleRadius;

	spline.setCapsuleBoundingVolume(new Capsule(a, b, r));
}
