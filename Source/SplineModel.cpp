#include <vector>
#include <algorithm>

#include "SplineModel.h"

#include "World.h"
#include "Camera.h"
#include "RendererHelper.h"
#include "Obstacles.h"
//#include "ParsingHelper.h"

#include <glm/gtc/type_ptr.hpp>

using namespace glm;

SplineModel::SplineModel() : Model(), mControlPoints(), mSplineModelPlaneDelegate(nullptr), mArray(), mControlPointsBuffer(), mPointsBuffer(), mOscullatingPlanesBuffer()
{
}

SplineModel::~SplineModel()
{
}

void SplineModel::Draw()
{
	Shader shader = RendererHelper::GetShader(SHADER_SPLINE);
	shader.Bind();

	shader.SetMatrix("ViewProjectonTransform", World::GetInstance()->GetCamera()->GetViewProjectionMatrix());
	shader.SetMatrix("WorldTransform", mat4(1));

	mArray.Bind();

	int stride = sizeof(Vertex);

	shader.SetVertexAttrib(mPointsBuffer, 0, 3, stride, 0);
	shader.SetVertexAttrib(mPointsBuffer, 2, 3, stride, (void*)sizeof(vec3));
	glDrawArrays(GL_TRIANGLE_STRIP, 0, mPointsBuffer.GetSize() / sizeof(Vertex));
	shader.DisableVertexAttrib(0);

	shader.SetVertexAttrib(mOscullatingPlanesBuffer, 0, 3, stride, 0);
	shader.SetVertexAttrib(mOscullatingPlanesBuffer, 2, 3, stride, (void*)sizeof(vec3));
	glDrawArrays(GL_LINES, 0, mOscullatingPlanesBuffer.GetSize() / sizeof(Vertex));
	shader.DisableVertexAttrib(0);
}

vec3 SplineModel::At(float t) {

	int segment = (int)t;
	
	float u = t - segment;
	float u2 = u * u;
	float u3 = u * u * u;
	
	const vec3& p1 = mControlPoints[segment].position;
	const vec3& p2 = mControlPoints[segment + 1].position;
	const vec3& p3 = mControlPoints[segment + 2].position;
	const vec3& p4 = mControlPoints[segment + 3].position;

	float sixth = 1.0f / 6.0f;

	float b0 = sixth * (-u3 + 3*u2 - 3*u + 1);
	float b1 = sixth * (3*u3 - 6*u2 + 4);
	float b2 = sixth * (-3*u3 + 3*u2 + 3*u + 1);
	float b3 = sixth * (u3);

	vec3 position = vec3(
		b0 * p1.x + b1 * p2.x + b2 * p3.x + b3 * p4.x,
		b0 * p1.y + b1 * p2.y + b2 * p3.y + b3 * p4.y,
		b0 * p1.z + b1 * p2.z + b2 * p3.z + b3 * p4.z
	);

	return position;
}

SplineModel::Plane SplineModel::PlaneAt(float t) {

	return mSplineModelPlaneDelegate->At(*this, t);
}

void SplineModel::SetControlPoints(std::vector<Vertex>& controlPoints) {

	mControlPoints.resize(controlPoints.size());
	copy(controlPoints.begin(), controlPoints.end(), mControlPoints.begin());

	mControlPointsBuffer.SetData(&mControlPoints[0], mControlPoints.size() * sizeof(Vertex));
}

void SplineModel::SetPoints(std::vector<Vertex>& points, SplineModelPlaneDelegate& splinePlaneDelegate) {

	mPointsBuffer.SetData(&points[0], points.size() * sizeof(Vertex));

	mSplineModelPlaneDelegate = &splinePlaneDelegate;
}

void SplineModel::SetOscullatingPlanes(std::vector<Vertex>& oscullatingPlanes) {

	mOscullatingPlanesBuffer.SetData(&oscullatingPlanes[0], oscullatingPlanes.size() * sizeof(Vertex));
}

bool SplineModel::ParseLine(const std::vector<ci_string> &token)
{
	if (token.empty())
	{
		return true;
	}
	else
	{
		return Model::ParseLine(token);
	}
}