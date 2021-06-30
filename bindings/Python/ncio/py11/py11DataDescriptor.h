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

    void Put(const std::string &entryName, const pybind11::array &data,
             const Dimensions &dimensions, const int threadID = 0);

    void Get(const std::string &entryName, pybind11::array &data,
             const Box &box, const int threadID = 0);

    Shape GetShape(const std::string &entryName) const;

    // here be explicit about indices?
    template <auto indexModel, class T>
    T GetMetadata(const Parameters &parameters = Parameters());

    void Execute(const int threadID = 0);

    void Close();

private:
    DataDescriptor(core::DataDescriptor &implDataDescriptor);

    void CheckImpl(const std::string &functionName) const;

    core::DataDescriptor *m_ImplDataDescriptor = nullptr;
};

} // end namespace ncio::py11
