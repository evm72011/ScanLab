#include "scanlab/config/file_loader.h"

#include <CustomizedDriverOEMPA.h>


namespace sd = scanlab::device;

namespace scanlab::config {

FileLoader::FileLoader(sd::Device& device)
    : device_(device)
{
}

std::expected<void, ConfigFileError>
FileLoader::load(const std::filesystem::path& filePath) const
{
    if (!std::filesystem::exists(filePath)) {
        return std::unexpected(ConfigFileErrorKind::FileNotFound);
    }

    auto* hw = device_.get();
    if (hw == nullptr) {
        return std::unexpected(sd::HardwareError::HardwareNotSet);
    }

    if (hw->GetSWDeviceOEMPA() == nullptr) {
        return std::unexpected(sd::HardwareError::OempaInterfaceUnavailable);
    }

    const std::wstring path = filePath.wstring();

    if (!OEMPA_ReadFileWriteHW(hw,path.c_str())) {
        return std::unexpected(ConfigFileErrorKind::LoadFailed);
    }

    return {};
}

} // namespace scanlab::config