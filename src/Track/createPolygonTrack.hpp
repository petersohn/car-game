#ifndef POLYGONTRACKBUILDER_HPP_
#define POLYGONTRACKBUILDER_HPP_

#include <vector>
#include "Point.hpp"
#include "Track.hpp"

namespace car { namespace track {

Track createPolygonTrack(float checkpointDistance, float trackWidth, const std::vector<Point>& points);

}} /* namespace car::track */

#endif /* POLYGONTRACKBUILDER_HPP_ */
