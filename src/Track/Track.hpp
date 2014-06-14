#ifndef TRACK_HPP
#define TRACK_HPP

#include <vector>
#include <stdexcept>
#include <functional>

#include <boost/optional.hpp>

#include <SFML/Graphics.hpp>

#include "Line2.hpp"
#include "Box.hpp"
#include <boost/geometry/index/rtree.hpp>

namespace car {

class Car;

namespace track {

struct TrackError: std::logic_error {
	TrackError(const std::string& what_arg):
		std::logic_error{what_arg}
	{}
};

class Track {
public:
	using LineIndices = std::vector<std::size_t>;

	Track() = default;

	Track(const Track& other):
			lines(other.lines),
			checkpoints(other.checkpoints),
			startingPoint(other.startingPoint),
			startingDirection(other.startingDirection)
	{}

	Track& operator=(const Track& other) {
		lines = other.lines;
		checkpoints = other.checkpoints;
		startingPoint = other.startingPoint;
		startingDirection = other.startingDirection;

		return *this;
	}

	void addLine(const Line2f& line);
	void addCheckpoint(const Line2f& line);

	Point collideWithRay(const Point& origin, const Point& direction,
			float maxViewDistance) const;

	bool collidesWith(const Line2f& line) const;
	bool collidesWith(const Line2f& line, const LineIndices& lineIndices) const;
	bool collidesWithCheckpoint(const Line2f& line, std::size_t checkpointId) const;

	std::size_t getNumberOfCheckpoints() const;
	const Line2f& getCheckpoint(std::size_t n) const;
	void check() const;

	sf::FloatRect getDimensions() const;

	void drawBoundary(sf::RenderWindow& window) const;
	void drawCheckpoints(sf::RenderWindow& window, int highlightCheckpoint = -1) const;

	void setOrigin(const Point& point, float direction);
	Car createCar() const;

	LineIndices getLineIndices(const Box& geometry) const {
		namespace bgi = boost::geometry::index;
		std::vector<RtreeValue> values;
		if (!rtree) {
			createRtree();
		}
		rtree->query(bgi::intersects(geometry), std::back_inserter(values));

		LineIndices result;
		result.reserve(values.size());
		for (const auto& value: values) {
			result.push_back(value.second);
		}
		return result;
	}
private:
	typedef std::vector<Line2f> Lines;
	Lines lines;
	Lines checkpoints;
	Point startingPoint;
	float startingDirection = 0.f;

	using RtreeValue = std::pair<Box, std::size_t>;
	using Rtree = boost::geometry::index::rtree<RtreeValue, boost::geometry::index::rstar<16>>;
	mutable std::unique_ptr<Rtree> rtree;

	void createRtree() const;
};

}} /* namespace car::track */

#endif /* !TRACK_HPP */
