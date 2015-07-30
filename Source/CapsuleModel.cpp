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
	vec3 n = math::anyOrthogonalVector(ba);

	int N = 18;
	float Pi = pi<float>();

	vec3 prevR = n;
	vec3 prevTopLeft = capsule.a + prevR;
	vec3 prevTopRight = capsule.a - prevR;
	vec3 prevBottomLeft = capsule.b + prevR;
	vec3 prevBottomRight = capsule.b - prevR;

	for (float d = 0; d <= 180; d += 180 / N) {

		vec3 r = vec3(rotate(d, ba) * vec4(n, 1));
		vec3 topLeft = capsule.a + r;
		vec3 topRight = capsule.a - r;
		vec3 bottomLeft = capsule.b + r;
		vec3 bottomRight = capsule.b - r;

		vertexes.push_back({ prevTopLeft });
		vertexes.push_back({ topLeft });
		vertexes.push_back({ prevTopRight });
		vertexes.push_back({ topRight });
		vertexes.push_back({ prevBottomLeft });
		vertexes.push_back({ bottomLeft });
		vertexes.push_back({ prevBottomRight });
		vertexes.push_back({ bottomRight });
		vertexes.push_back({ topLeft });
		vertexes.push_back({ bottomLeft });
		vertexes.push_back({ topRight });
		vertexes.push_back({ bottomRight });

		makeHalfCircleLineSegments(vertexes, topLeft, topRight, -ba);
		makeHalfCircleLineSegments(vertexes, bottomLeft, bottomRight, ba);

		prevR = r;
		prevTopLeft = capsule.a + prevR;
		prevTopRight = capsule.a - prevR;
		prevBottomLeft = capsule.b + prevR;
		prevBottomRight = capsule.b - prevR;
	}

	if (N % 180 != 0) {

		vec3 firstTopLeft = vertexes[0].position;
		vec3 firstTopRight = vertexes[0 + 2].position;
		vec3 firstBottomLeft = vertexes[0 + 4].position;
		vec3 firstBottomRight = vertexes[0 + 4 + 2].position;

		vertexes.push_back({ prevTopLeft });
		vertexes.push_back({ firstTopRight });
		vertexes.push_back({ prevTopRight });
		vertexes.push_back({ firstTopLeft });
		vertexes.push_back({ prevBottomLeft });
		vertexes.push_back({ firstBottomRight });
		vertexes.push_back({ prevBottomRight });
		vertexes.push_back({ firstBottomLeft });
	}
}

void CapsuleModel::makeHalfCircleLineSegments(std::vector<Vertex>& vertexes, vec3 p, vec3 q, vec3 direction) {

	vec3 qpCenter = 0.5f * (p + q);
	vec3 midDestination = qpCenter + direction;
	float r = 0.5f * length(q - p);

	makeQuarterCircleLineSegments(vertexes, p, midDestination, qpCenter, r);
	makeQuarterCircleLineSegments(vertexes, q, midDestination, qpCenter, r);
}

void CapsuleModel::makeQuarterCircleLineSegments(std::vector<Vertex>& vertexes, glm::vec3 p, glm::vec3 q, glm::vec3 center, float radius) {

	int M = 10;

	vec3 prevU = p;
	for (int i = 0; i < M; i++) {

		float t = i / (float)M;
		vec3 v = p + t * (q - p);
		vec3 u = radius * normalize(v - center);

		vertexes.push_back({ prevU });
		vertexes.push_back({ center + u });

		prevU = center + u;
	}
}
