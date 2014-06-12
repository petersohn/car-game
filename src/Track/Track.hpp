#ifndef TRACK_HPP
#define TRACK_HPP

#include <vector>
#include <stdexcept>
#include <functional>

#include <boost/optional.hpp>

#include <SFML/Graphics.hpp>

#include "Line2.hpp"

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
	void addLine(const Line2f& line);
	void addCheckpoint(const Line2f& line);

	Point collideWithRay(const Point& origin, const Point& direction,
			float maxViewDistance) const;

	bool collidesWith(const Line2f& line) const;
	bool collidesWithCheckpoint(const Line2f& line, std::size_t checkpointId) const;

	std::size_t getNumberOfCheckpoints() const;
	const Line2f& getCheckpoint(std::size_t n) const;
	void check() const;

	sf::FloatRect getDimensions() const;

	void drawBoundary(sf::RenderWindow& window) const;
	void drawCheckpoints(sf::RenderWindow& window, int highlightCheckpoint = -1) const;

	void setOrigin(const Point& point, float direction);
	Car createCar() const;
private:
	typedef std::vector<Line2f> Lines;
	Lines lines;
	Lines checkpoints;
	Point startingPoint;
	float startingDirection = 0.f;
};

}} /* namespace car::track */

#endif /* !TRACK_HPP */
