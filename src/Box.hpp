#ifndef SRC_BOX_HPP
#define SRC_BOX_HPP

#include "Point.hpp"
#include <boost/geometry/geometries/box.hpp>

namespace car {

using Box = boost::geometry::model::box<Point>;

}


#endif /* SRC_BOX_HPP */
