/**
 * cxx17ncioNexusDataDescriptor.tcc : implements DataDescriptor specific
 * functionality to the Nexus schema for Put and Get
 *
 *  Created on: Jun 15, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include "ncio/schema/nexus/ncioTypesSchemaNexus.h"

namespace ncio
{
// TODO implement array data with dimensions

#define declare_ncio_types(T)                                                  \
    template void DataDescriptor::Put<schema::nexus::bank##T::event_id>(       \
        const std::uint64_t &, const int);                                     \
    template void DataDescriptor::Put<schema::nexus::bank##T::event_index>(    \
        const std::uint64_t *, const Dimensions &, const int);                 \
    template void                                                              \
    DataDescriptor::Put<schema::nexus::bank##T::event_time_offset>(            \
        const float *, const Dimensions &, const int);                         \
    template void                                                              \
    DataDescriptor::Put<schema::nexus::bank##T::event_time_zero>(              \
        const double &, const int);                                            \
    template void DataDescriptor::Put<schema::nexus::bank##T::total_counts>(   \
        const float &, const int);

NCIO_MACRO_NEXUS_FOREACH_BANK_ID(declare_ncio_types)
#undef declare_ncio_types

#define declare_ncio_types(T)                                                  \
    template void DataDescriptor::Get<schema::nexus::bank##T::event_id>(       \
        std::uint64_t &, const int);                                           \
    template void DataDescriptor::Get<schema::nexus::bank##T::event_index>(    \
        std::uint64_t *, const Box &box, const int);                           \
                                                                               \
    template void                                                              \
    DataDescriptor::Get<schema::nexus::bank##T::event_time_offset>(            \
        float *, const Box &box, const int);                                   \
                                                                               \
    template void                                                              \
    DataDescriptor::Get<schema::nexus::bank##T::event_time_zero>(double &,     \
                                                                 const int);   \
    template void DataDescriptor::Get<schema::nexus::bank##T::total_counts>(   \
        float &, const int);

NCIO_MACRO_NEXUS_FOREACH_BANK_ID(declare_ncio_types)
#undef declare_ncio_types

}
