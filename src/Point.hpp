#ifndef SRC_POINT_HPP
#define SRC_POINT_HPP

#include <SFML/System/Vector2.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/register/point.hpp>

namespace car {

using Point = sf::Vector2f;

}

BOOST_GEOMETRY_REGISTER_POINT_2D(car::Point, float, cs::cartesian, x, y)

#endif /* SRC_POINT_HPP */
