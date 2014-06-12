#ifndef OPTIONSHELPER_HPP_
#define OPTIONSHELPER_HPP_

#include <boost/program_options/value_semantic.hpp>
#include <boost/program_options/options_description.hpp>
#include "Point.hpp"

namespace car {

template <typename T>
boost::program_options::typed_value<T>* paramWithDefaultValue(T& value) {
	return boost::program_options::value(&value)->default_value(value);
}

Point parsePoint(const std::string& param);

}

#endif /* OPTIONSHELPER_HPP_ */
