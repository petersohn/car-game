#include "PointAdderRandomPolygonGenerator.hpp"
#include <boost/random/uniform_real_distribution.hpp>


namespace car { namespace track {

namespace {

std::size_t findNearestLine(const std::vector<Point>& points, const Point& referencePoint) {
	std::size_t n = points.size();

	std::vector<float> distanceSquares(n);

	for (std::size_t i = 0; i < n; ++i) {
		std::size_t j = (i + 1) % n;

		auto nearest = nearestPoint(referencePoint, {points[i], points[j]});
		distanceSquares[i] = getDistanceSQ(referencePoint, nearest);
	}

	return std::min_element(distanceSquares.begin(), distanceSquares.end()) -
			distanceSquares.begin();
}

}

std::vector<Point> PointAdderRandomPolygonGenerator::operator()(
		RandomGenerator& rng) const {

	Point startEdge1 = params.corner1 * params.inset +
			params.corner2 * (1.f - params.inset);
	Point startEdge2 = params.corner2 * params.inset +
			params.corner1 * (1.f - params.inset);

	std::vector<Point> points{
		startEdge1, {startEdge2.x, startEdge1.y},
		startEdge2, {startEdge1.x, startEdge2.y}
	};

	using Distribution = boost::random::uniform_real_distribution<float>;
	Distribution distX{std::min(params.corner1.x, params.corner2.x),
			std::max(params.corner1.x, params.corner2.x)};
	Distribution distY{std::min(params.corner1.y, params.corner2.y),
			std::max(params.corner1.y, params.corner2.y)};

	for (int i = 4; i < params.numberOfPoints; ++i) {
		Point newPoint{distX(rng), distY(rng)};

		int index = findNearestLine(points, newPoint) + 1;

		points.insert(points.begin() + index, newPoint);
	}

	return points;
}



}} /* namespace car::track */




