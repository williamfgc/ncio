/**
 * py11DataDescriptor.h
 *
 *  Created on: Jun 16, 2021
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include "ncio/common/ncioTypes.h"
#include "ncio/core/DataDescriptor.h"

#include <any>
#include <future>
#include <vector>

#include <pybind11/numpy.h>

namespace ncio::py11
{

/// forward declaring friend factory class to avoid cross reference
class NCIO;

class DataDescriptor
{
    friend class NCIO; // to allow access to private constructor

public:
    DataDescriptor() = default;

    ~DataDescriptor() = default;

    explicit operator bool() const noexcept;

    template <auto entry>
    void Put(const pybind11::array &data, const Dimensions &dimensions,
             const int threadID = 0);

    template <auto entry, class T>
    void Get(pybind11::array &data, const Box &box, const int threadID = 0);

    template <auto entry>
    Shape GetShape() const;

    template <auto indexModel, class T>
    T GetMetadata(const Parameters &parameters = Parameters());

    void Execute(const int threadID = 0);

    std::future<void> ExecuteAsync(const std::launch mode,
                                   const int threadID = 0);

    void Close();

private:
    DataDescriptor(core::DataDescriptor &implDataDescriptor);

    void CheckImpl(const std::string &functionName) const;

    core::DataDescriptor *m_ImplDataDescriptor = nullptr;
};

} // end namespace ncio::py11
