/**
 * py11DataDescriptor.cpp
 *
 *  Created on: Jun 16, 2021
 *      Author: William F Godoy godoywf@ornl.gov
 */

#include "py11DataDescriptor.h"

namespace ncio::py11
{

DataDescriptor::operator bool() const noexcept
{
    return m_ImplDataDescriptor != nullptr ? true : false;
}

void DataDescriptor::Put(const std::string &entryName,
                         const pybind11::array &data,
                         const Dimensions &dimensions, const int threadID)
{
    CheckImpl("Put");
    // TODO loop to find type of data.data()
    // m_ImplDataDescriptor->Put(entryName, data.data(), dimensions,
    //                                 threadID);
}

void DataDescriptor::Get(const std::string &entryName, pybind11::array &data,
                         const Box &box, const int threadID)
{
    CheckImpl("Get");
    // TODO loop to find type of data.data()
    // m_ImplDataDescriptor->Get(entryName, data.data(), box, threadID);
}

Shape DataDescriptor::GetShape(const std::string &entryName) const
{
    CheckImpl("GetShape");
    return m_ImplDataDescriptor->GetShape(entryName);
}

void DataDescriptor::Execute(const int threadID)
{
    CheckImpl("Execute");
    return m_ImplDataDescriptor->Execute(threadID);
}

void DataDescriptor::Close()
{
    CheckImpl("Close");
    m_ImplDataDescriptor->Close();
    m_ImplDataDescriptor = nullptr;
}

// PRIVATE
DataDescriptor::DataDescriptor(core::DataDescriptor &implDataDescriptor)
: m_ImplDataDescriptor(&implDataDescriptor)
{
}

void DataDescriptor::CheckImpl(const std::string &functionName) const
{
    if (!*this)
    {
        throw std::logic_error(
            "ncio ERROR: Python bindings invalid DataDescriptor object in call "
            "to " +
            functionName +
            ". Please modify your code and pass a valid DataDescriptor created "
            "with NCIO::open that has not been previously closed\n");
    }
}

} // end namespace ncio::py11
