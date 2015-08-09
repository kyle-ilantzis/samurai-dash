#ifndef SPLINEFACTORY_H
#define SPLINEFACTORY_H

#include <glm/glm.hpp>
#include "ParsingHelper.h"
#include "SplineModel.h"

class SplineFactoryPlaneDelegate : public SplineModelPlaneDelegate {

	virtual SplineModel::Plane At(SplineModel& spline, float t);
};

class SplineFactory {

public:
	/**
	 * The name of the loaded spline model
	 */
	static const ci_string splineName;

	/***
	 * The width of the spline track.
	 */
	static const float trackWidth;

	static SplineModel* LoadSpline();

private:

	/**
	 * Random control points count variation of y (used as max) - x (used as min)
	 */
	static const glm::vec2 controlPointsCount;

	/**
	 * Random control points minimum x and y variation
	 */
	static const glm::vec2 deltaMinControlPoint;
	
	/**
	 * Random control points maximum x and y variation
	 */
	static const glm::vec2 deltaMaxControlPoint;

	/**
	 *
	 */
	static const glm::vec4 controlPointsColor;

	/**
	 * Create random control points for the spline
	 */
	static void makeControlPoints(SplineModel& spline);

	/**
	 * The number of triangle strips per segment.
	 *
	 * A segment is control points i,i+1,..,i+3 and variable t
	 * where 0 <= t <= 1.
	 */
	static const int triangleStripSegmentCount;

	/**
	 *
	 */
	static SplineFactoryPlaneDelegate splinePlaneDelegate;

	/**
	 * Create the triangle strip for the spline.
	 */
	static void makeTriangleStrip(SplineModel& spline);

	/**
	 *
	 */
	static void makeOscullatingPlanes(SplineModel& spline);
};

#endif