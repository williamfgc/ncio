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

void DataDescriptor::Execute(const int threadID) {}

std::future<void> DataDescriptor::ExecuteAsync(const std::launch mode,
                                               const int threadID)
{
    CheckImpl("ExecuteAsync");
    return m_ImplDataDescriptor->ExecuteAsync(mode, threadID);
}

void DataDescriptor::Close()
{
    CheckImpl("Close");
    m_ImplDataDescriptor->Close();
    m_ImplDataDescriptor = nullptr;
}

DataDescriptor::DataDescriptor(core::DataDescriptor &implDataDescriptor)
: m_ImplDataDescriptor(&implDataDescriptor)
{
}

void DataDescriptor::CheckImpl(const std::string &functionName) const
{
    if (!*this)
    {
        throw std::logic_error(
            "ncio ERROR: invalid DataDescriptor object in call to " +
            functionName +
            ". Please modify your code and pass a valid DataDescriptor created "
            "with NCIO::open that has not been previously closed\n");
    }
}

} // end namespace ncio::py11
