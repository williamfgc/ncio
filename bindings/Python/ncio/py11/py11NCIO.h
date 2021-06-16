/**
 * py11NCIO.h
 *
 *  Created on: Jun 16, 2021
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include <memory> //std::unique_ptr
#include <optional>
#include <string>

#include "ncio/common/ncioTypes.h"
#include "ncio/core/NCIO.h"
#include "ncio/py11/py11DataDescriptor.h"

namespace ncio::py11
{

class NCIO
{
public:
    NCIO(const std::optional<std::string> &configFile = std::nullopt);

    ~NCIO() = default;

    std::optional<std::string> GetConfigFile() const noexcept;

    void SetParameter(const std::string key, const std::string value) noexcept;

    std::optional<std::string>
    GetParameter(const std::string key) const noexcept;

    DataDescriptor Open(const std::string &name, const OpenMode mode);

private:
    /** private implementation pointer owned by this class */
    std::unique_ptr<ncio::core::NCIO> m_ImplNCIO;
};

} // end namespace
