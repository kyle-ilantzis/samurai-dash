#ifndef SPLINEMODEL_H
#define SPLINEMODEL_H

#include <vector>

#include "Model.h"
#include "Vertexes.h"

class SplineModelPlaneDelegate;

enum Track { TRACK_LEFT, TRACK_MIDDLE, TRACK_RIGHT };
class SplineModel : public Model {

public:
	struct Vertex {
		glm::vec3 position;
		glm::vec4 color;
	};

	struct Plane {
		glm::vec3 position;
		glm::vec3 tangent;
		glm::vec3 normal;
	};

	SplineModel();
	virtual ~SplineModel();

	virtual void Update(float dt) {};

	virtual void Draw();

	glm::vec3 At(float t);
	glm::vec3 TrackShiftDir(Track dir, float t);

	Plane PlaneAt(float t);
	float MaxTime() { return mControlPoints.size() - 4; }
	bool HasControlPoints() { return !mControlPoints.empty(); }
	std::vector<Vertex>& GetControlPoints() { return mControlPoints; }

	void SetControlPoints(std::vector<Vertex>& controlPoints);

	void SetPoints(std::vector<Vertex>& points, SplineModelPlaneDelegate& splinePlaneDelegate);

	void SetOscullatingPlanes(std::vector<Vertex>& oscullatingPlanes);

protected:
	virtual bool ParseLine(const std::vector<ci_string> &token);

private:

	std::vector<Vertex> mControlPoints;
	SplineModelPlaneDelegate* mSplineModelPlaneDelegate;

	VertexArray mArray;
	VertexBuffer mControlPointsBuffer;
	VertexBuffer mPointsBuffer;

	VertexBuffer mOscullatingPlanesBuffer;
};

class SplineModelPlaneDelegate {

public:
	virtual SplineModel::Plane At(SplineModel& spline, float t) = 0;
};

#endif
