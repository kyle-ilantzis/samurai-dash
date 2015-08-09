#include "CapsuleModel.h"
#include "Math.h"
#include "RendererHelper.h"

#include <glm/gtc/constants.hpp>
#include <glm/gtx/transform.hpp>

#include <vector>

using namespace std;
using namespace glm;

CapsuleModel::CapsuleModel(const rtcd::Capsule& capsule) : mArray(), mBuffer() {

	vector<Vertex> vertexes;

	makeCapsuleLineSegments(vertexes, capsule);

	mBuffer.SetData(&vertexes[0], vertexes.size() * sizeof(Vertex));
}

void CapsuleModel::Draw() {

	Shader shader = RendererHelper::GetShader(SHADER_PATH_LINES);

	shader.Bind();
	shader.SetViewProjectionMatrix();
	shader.SetMatrix("WorldTransform", GetWorldMatrix());

	mArray.Bind();

	shader.SetVertexAttrib(mBuffer, 0, 3, sizeof(Vertex), (void*)0);

	glDrawArrays(GL_LINES, 0, mBuffer.GetSize() / sizeof(Vertex));
	
	shader.DisableVertexAttrib(0);
}

void CapsuleModel::makeCapsuleLineSegments(std::vector<Vertex>& vertexes, const rtcd::Capsule& capsule) {

	vec3 ba = normalize(capsule.b - capsule.a);
	vec3 n = capsule.r * normalize(math::anyOrthogonalVector(ba));

	float Pi = pi<float>();

	vec3 prevR = n;
	vec3 prevTopLeft = capsule.a + prevR;
	vec3 prevTopRight = capsule.a - prevR;
	vec3 prevBottomLeft = capsule.b + prevR;
	vec3 prevBottomRight = capsule.b - prevR;

	for (float d = 0; d <= 180; d += 180 / CYLINDER_SEGMENTS) {

		vec3 r = vec3(rotate(d, ba) * vec4(n, 1));
		vec3 topLeft = capsule.a + r;
		vec3 topRight = capsule.a - r;
		vec3 bottomLeft = capsule.b + r;
		vec3 bottomRight = capsule.b - r;

		Vertex v;
		v.position = prevTopLeft;

		Vertex v1;
		v1.position = topLeft;

		Vertex v2;
		v2.position = prevTopRight;

		Vertex v3;
		v3.position = prevBottomLeft;

		Vertex v4;
		v4.position = bottomLeft;

		Vertex v5;
		v5.position = prevBottomRight;

		Vertex v6;
		v6.position = bottomRight;

		Vertex v7;
		v7.position = topRight;

		vertexes.push_back(v);
		vertexes.push_back(v1);
		vertexes.push_back(v2);
		vertexes.push_back(v7);
		vertexes.push_back(v3);
		vertexes.push_back(v4);
		vertexes.push_back(v5);
		vertexes.push_back(v6);
		vertexes.push_back(v1);
		vertexes.push_back(v4);
		vertexes.push_back(v7);
		vertexes.push_back(v6);

		makeHalfCircleLineSegments(vertexes, topLeft, topRight, -ba);
		makeHalfCircleLineSegments(vertexes, bottomLeft, bottomRight, ba);

		prevR = r;
		prevTopLeft = capsule.a + prevR;
		prevTopRight = capsule.a - prevR;
		prevBottomLeft = capsule.b + prevR;
		prevBottomRight = capsule.b - prevR;
	}

	if (CYLINDER_SEGMENTS % 180 != 0) {

		vec3 firstTopLeft = vertexes[0].position;
		vec3 firstTopRight = vertexes[0 + 2].position;
		vec3 firstBottomLeft = vertexes[0 + 4].position;
		vec3 firstBottomRight = vertexes[0 + 4 + 2].position;

		Vertex v;
		v.position = prevTopLeft;

		Vertex v1;
		v1.position = firstTopRight;

		Vertex v2;
		v2.position = prevTopRight;

		Vertex v3;
		v3.position = prevBottomLeft;

		Vertex v4;
		v4.position = firstTopLeft;

		Vertex v5;
		v5.position = prevBottomRight;

		Vertex v6;
		v6.position = firstBottomRight;

		Vertex v7;
		v7.position = prevBottomLeft;

		Vertex v8;
		v8.position = firstBottomLeft;
		
		vertexes.push_back(v);
		vertexes.push_back(v1);
		vertexes.push_back(v2);
		vertexes.push_back(v4);
		vertexes.push_back(v7);
		vertexes.push_back(v6);
		vertexes.push_back(v5);
		vertexes.push_back(v8);
	}
}

void CapsuleModel::makeHalfCircleLineSegments(std::vector<Vertex>& vertexes, vec3 p, vec3 q, vec3 direction) {

	vec3 qpCenter = 0.5f * (p + q);
	float r = 0.5f * length(q - p);
	vec3 midDestination = qpCenter + r * direction;
	
	makeQuarterCircleLineSegments(vertexes, p, midDestination, qpCenter, r);
	makeQuarterCircleLineSegments(vertexes, q, midDestination, qpCenter, r);
}

void CapsuleModel::makeQuarterCircleLineSegments(std::vector<Vertex>& vertexes, glm::vec3 p, glm::vec3 q, glm::vec3 center, float radius) {

	vec3 prevU = p;
	for (int i = 0; i <= SPHERE_SEGMENTS; i++) {

		float t = i / (float)SPHERE_SEGMENTS;
		vec3 v = p + t * (q - p);
		vec3 u = radius * normalize(v - center);

		Vertex v1;
		v1.position = prevU;

		Vertex v2;
		v2.position = center + u ;
		
		vertexes.push_back(v1);
		vertexes.push_back(v2);

		prevU = center + u;
	}
}
