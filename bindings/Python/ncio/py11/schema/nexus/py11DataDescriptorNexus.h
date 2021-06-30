/**
 * py11DataDescriptorNexus.h
 *
 *  Created on: Jun 30, 2021
 *      Author: William F Godoy godoywf@ornl.gov
 */

#define xstr(s) str(s)
#define str(s) #s

#include "ncio/schema/nexus/ncioTypesSchemaNexus.h"

auto schema = m.def_submodule("schema");
auto nexus = schema.def_submodule("nexus");
auto entry = nexus.def_submodule("entry");

// py::module bank##T##_events = entry.def_submodule("bank"xstr(T)"_events");
// m, "schema.nexus.entry.bank" xstr(T) "_events")
#define declare_ncio_types(T)                                                  \
    pybind11::enum_<ncio::schema::nexus::entry::bank##T##_events>(             \
        entry, "bank" xstr(T) "_events")                                       \
        .value("event_id",                                                     \
               ncio::schema::nexus::entry::bank##T##_events::event_id)         \
        .value("event_index",                                                  \
               ncio::schema::nexus::entry::bank##T##_events::event_index)      \
        .export_values();

NCIO_MACRO_NEXUS_FOREACH_BANK_ID(declare_ncio_types)
#undef declare_ncio_types
