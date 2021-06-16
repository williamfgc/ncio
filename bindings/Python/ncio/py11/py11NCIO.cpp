/**
 * py11NCIO.cpp
 *
 *  Created on: Jun 16, 2021
 *      Author: William F Godoy godoywf@ornl.gov
 */

#include "py11NCIO.h"

#include "ncio/core/NCIO.h"

namespace ncio::py11
{

NCIO::NCIO(const std::optional<std::string> &configFile)
: m_ImplNCIO(std::make_unique<core::NCIO>(configFile))
{
}

std::optional<std::string> NCIO::GetConfigFile() const noexcept
{
    return m_ImplNCIO->GetConfigFile();
}

void NCIO::SetParameter(const std::string key, const std::string value) noexcept
{
    m_ImplNCIO->SetParameter(key, value);
}

std::optional<std::string>
NCIO::GetParameter(const std::string key) const noexcept
{
    return m_ImplNCIO->GetParameter(key);
}

DataDescriptor NCIO::Open(const std::string &name, const OpenMode openMode)
{
    return DataDescriptor(m_ImplNCIO->Open(name, openMode));
}

} // end namespace ncio::py11
