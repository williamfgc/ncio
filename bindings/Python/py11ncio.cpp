/**
 * py11ncio.cpp
 *
 *  Created on: Jun 15, 2021
 *      Author: William F Godoy godoywf@ornl.gov
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "ncio/ncioConfig.h"

#include "ncio/py11/py11DataDescriptor.h"
#include "ncio/py11/py11NCIO.h"

PYBIND11_MODULE(ncio, m)
{
    pybind11::enum_<ncio::OpenMode>(m, "openmode")
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
             )md")

        .def("open", &ncio::py11::NCIO::Open, pybind11::arg("name"),
             pybind11::arg("openmode"),
             R"md(
	    		    Open a DataDescriptor for communication

	    		    Parameters
	    		         name 
	    		         unique identifier of the DataDescriptor to be returned
                         
                         openmode
                         from enum: ncio.openmode.write or ncio.openmode.read
	                         
	                Returns
	                     DataDescriptor object
	             )md");

    pybind11::class_<ncio::py11::DataDescriptor>(m, "DataDescriptor")

        .def("get_shape",
             (ncio::Shape(ncio::py11::DataDescriptor::*)(const std::string &)) &
                 ncio::py11::DataDescriptor::GetShape,
             pybind11::return_value_policy::move, pybind11::arg("entry_name"),
             R"md(
		           Gets shape of an entry.
		         )md")

        // overload Put
        .def("put",
             (void (ncio::py11::DataDescriptor::*)(
                 const std::string &, const pybind11::array &,
                 const ncio::Dimensions &, const int)) &
                 ncio::py11::DataDescriptor::Put,
             pybind11::arg("entry_name"), pybind11::arg("data"),
             pybind11::arg("dimensions"), pybind11::arg("thread_id") = 0,
             R"md(
				   Puts an entry into the DataDescriptor using lazy evaluation.
				 )md")

        .def("get",
             (void (ncio::py11::DataDescriptor::*)(
                 const std::string &, pybind11::array &, const ncio::Box &,
                 const int)) &
                 ncio::py11::DataDescriptor::Get,
             pybind11::arg("entry_name"), pybind11::arg("data"),
             pybind11::arg("box"), pybind11::arg("thread_id") = 0,
             R"md(
				 	Gets an entry data from a DataDescriptor using lazy evaluation.
				 )md")

        .def("execute", &ncio::py11::DataDescriptor::Execute,
             pybind11::arg("thread_id") = 0)

        .def("close", &ncio::py11::DataDescriptor::Close);

#ifdef NCIO_HAVE_SCHEMA_NEXUS
#include "ncio/py11/schema/nexus/py11DataDescriptorNexus.h"
#endif
}
