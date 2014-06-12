
#include "Telemetry.hpp"

#include <algorithm>

#include "drawUtil.hpp"

namespace car {

float Telemetry::horizontalScaling = 10.f;
float Telemetry::horizontalResolution = 0.02f;
std::size_t Telemetry::maxNumberOfPoints = 10000;

void Telemetry::addDataPoint(const Point& point) {
	if (!dataPoints.empty() && std::abs(point.x - dataPoints.back().x) < horizontalResolution) {
		return;
	}
	dataPoints.push_back(point);
	while (dataPoints.size() > maxNumberOfPoints) {
		dataPoints.pop_front();
	}
}


void Telemetry::drawAsGraph(sf::RenderWindow& window, const sf::FloatRect& position, const sf::Color& color) {

	if (dataPoints.size() < 2) {
		return;
	}

	float maxUp = position.top; //d
	float minUp = position.top + position.height; //c
	float leftSide = position.left;

	float maxData = maxBound; //b
	float minData = minBound; //a

   	if (automaticBoundsDetection) {
		minData = std::min_element(dataPoints.begin(), dataPoints.end(),
			[](const Point& lhs, const Point& rhs) { return lhs.y < rhs.y; })->y;
		maxData = std::max_element(dataPoints.begin(), dataPoints.end(),
			[](const Point& lhs, const Point& rhs) { return lhs.y < rhs.y; })->y;
	}

	if ( minData - maxData == 0.0 ) {
		return;
	}

	auto it = dataPoints.begin();

	if (scrolling) {
		auto firstPositionToDraw = dataPoints.back().x - position.width / horizontalScaling;
		it = std::find_if(dataPoints.begin(), dataPoints.end(),
				[firstPositionToDraw](const Point& value)
				{ return value.x >= firstPositionToDraw; });
		if (it == dataPoints.end()) {
			// this should never happen
			return;
		}
	}

	auto startingPoint = it->x;

	Point lastPoint(leftSide,
			(-maxData*minUp + minData*maxUp + (minUp - maxUp)*it->y) / (minData - maxData));

	for ( ++it; it != dataPoints.end(); ++it ) {
		Point currentPoint(
				leftSide + (it->x - startingPoint) * horizontalScaling,
				(-maxData*minUp + minData*maxUp + (minUp - maxUp)*it->y) / (minData - maxData));
		drawLine(window, lastPoint, currentPoint, color);
		lastPoint = currentPoint;
	}
}

void Telemetry::setAutomaticBoundsDetection(bool value) {
	automaticBoundsDetection = value;
}

void Telemetry::setScrolling(bool value) {
	scrolling = value;
}

void Telemetry::setBounds(float min, float max) {
	minBound = min;
	maxBound = max;
}

}

