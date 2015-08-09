#include <iostream>

#include "SplineFactory.h"

using namespace std;
using namespace glm;

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

	return splineModel;
}

const vec2 SplineFactory::controlPointsCount = vec2(20, 30);
const vec2 SplineFactory::deltaMinControlPoint = vec2(20.0f, -10.0f);
const vec2 SplineFactory::deltaMaxControlPoint = vec2(21.0f, 10.0f);

const glm::vec4 SplineFactory::controlPointsColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);

void SplineFactory::makeControlPoints(SplineModel& spline) {

	std::vector<SplineModel::Vertex> controlPoints;

	int N = controlPointsCount.x + rand() % (int) (controlPointsCount.y - controlPointsCount.x);

	SplineModel::Vertex ver;
	ver.position=vec3(0, 0, deltaMinControlPoint.x);
	ver.color=controlPointsColor;

	controlPoints.push_back(ver);

	for (int i = 1; i < N; i++) {

		SplineModel::Vertex prev = controlPoints[i - 1];
		
		int dz = deltaMinControlPoint.x + rand() % (int) (deltaMaxControlPoint.x - deltaMinControlPoint.x);
		int dy = deltaMinControlPoint.y + rand() % (int) (deltaMaxControlPoint.y - deltaMinControlPoint.y);

		SplineModel::Vertex next;
		next.position = prev.position + vec3(0, dy, -dz);
		next.color = controlPointsColor;

		controlPoints.push_back(next);
	}

	spline.SetControlPoints(controlPoints);
}

const int SplineFactory::triangleStripSegmentCount = 5;
const float SplineFactory::trackWidth = 20.0f;
SplineFactoryPlaneDelegate SplineFactory::splinePlaneDelegate;

void SplineFactory::makeTriangleStrip(SplineModel& spline) {

	std::vector<SplineModel::Vertex> points;

	vec4 red = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	vec4 green = vec4(0.0f, 1.0f, 0.0f, 1.0f);
	vec4 blue = vec4(0.0f, 1.0f, 0.0f, 1.0f);

	vec3 shift = vec3(trackWidth / 2, 0, 0);
	float timeStep = 1.0f / triangleStripSegmentCount;

	vec3 point = spline.At(0);

	SplineModel::Vertex ver;
	ver.position=point + shift;
	ver.color=red;

	points.push_back(ver);

	SplineModel::Vertex ver2;
	ver.position=point - shift;
	ver.color=green;
	points.push_back(ver2);

	int shiftDirection = 1;
	int colorChoice = 2 ;
	for (float t = timeStep; t <= spline.MaxTime(); t += timeStep) {

		vec3 point = spline.At(t);

		point += (shiftDirection ? 1.0f : -1.0f) * shift;


		SplineModel::Vertex ver3;
		ver3.position=point;
		ver3.color=colorChoice == 0 ? red : colorChoice == 1 ? green : blue;
		points.push_back(ver3);

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

	SplineModel::Plane p = {position, tangent, normal};
	return p;
}

void SplineFactory::makeOscullatingPlanes(SplineModel& spline) {

	std::vector<SplineModel::Vertex> points;
	
	vec4 color(1); // white

	for (float t = 0; t < spline.MaxTime(); t += 0.5f) {

		SplineModel::Plane p = spline.PlaneAt(t);
		vec3 B = normalize(cross(p.tangent, p.normal));

		vec3 translation = 2.0f * B;

		SplineModel::Vertex v;
		v.position = translation + p.position;
		v.color = color;

		SplineModel::Vertex v1;
		v1.position = translation + p.position + p.tangent;
		v1.color = color;

		SplineModel::Vertex v2;
		v2.position = translation + p.position;
		v2.color = color;

		SplineModel::Vertex v3;
		v3.position = translation + p.position + p.normal;
		v3.color = color;

		SplineModel::Vertex v4;
		v4.position = translation + p.position;
		v4.color = color;

		SplineModel::Vertex v5;
		v5.position = translation + p.position + B;
		v5.color = color;


		points.push_back(v);
		points.push_back(v1);
		points.push_back(v2);
		points.push_back(v3);
		points.push_back(v4);
		points.push_back(v5);
	}

	spline.SetOscullatingPlanes(points);
}
