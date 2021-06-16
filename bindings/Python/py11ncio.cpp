/**
 * py11ncio.cpp
 *
 *  Created on: Jun 15, 2021
 *      Author: William F Godoy godoywf@ornl.gov
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "ncio/ncioConfig.h"

#include "ncio/py11/py11NCIO.h"

PYBIND11_MODULE(ncio, m)
{
    pybind11::enum_<ncio::OpenMode>(m, "OpenMode")
        .value("write", ncio::OpenMode::write)
        .value("read", ncio::OpenMode::read)
        .export_values();

    // NCIO class
    pybind11::class_<ncio::py11::NCIO>(m, "NCIO")

        .def(pybind11::init<const std::optional<std::string> &>(),
             "ncio module starting point, constructs a NCIO class object",
             pybind11::arg("configFile"))

        .def("get_config_file", &ncio::py11::NCIO::GetConfigFile,
             pybind11::return_value_policy::move,
             R"md(
                     Gets configuration file passes to NCIO constructor.
             )md")

        .def("set_parameter", &ncio::py11::NCIO::SetParameter,
             pybind11::arg("key"), pybind11::arg("value"),
             R"md(
		             Sets a single parameter. Overwrites value if key exists.

		             Parameters
		                 key 
		                     input parameter key

		                 value
		                     parameter value
		     )md")

        .def("get_parameter", &ncio::py11::NCIO::GetParameter,
             pybind11::return_value_policy::move, pybind11::arg("key"),
             R"md(
    		        Get a single parameter.

    		        Parameters
    		            key 
    		            input parameter key
                         
                    Returns
                        optional[value]
                                 
             )md");
}
