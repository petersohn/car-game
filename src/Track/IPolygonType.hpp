#ifndef IPOLYGONTYPE_HPP_
#define IPOLYGONTYPE_HPP_

#include <functional>
#include <string>
#include <vector>
#include <memory>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include "Point.hpp"

namespace car { namespace track {

class Track;

class IPolygonType {
public:
	virtual std::function<Track(const std::vector<Point>)> getTrackCreator(
			const boost::program_options::variables_map& variablesMap) = 0;
	virtual std::string getHelpString() = 0;
	virtual std::string getArgumentName() = 0;
	virtual boost::program_options::options_description getOptions() = 0;
	virtual ~IPolygonType() {}
};

}} /* namespace car::track */



#endif /* IPOLYGONTYPE_HPP_ */
