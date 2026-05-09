#include "scanlab/config/file_saver.h"

#include <CustomizedDriverOEMPA.h>

#include <fstream>

namespace sd = scanlab::device;

namespace scanlab::config
{

FileSaver::FileSaver(sd::Device& device)
    : device_(device)
{
}

std::expected<void, ConfigFileError> FileSaver::save(const std::filesystem::path& filePath) const
{
    {
        std::ofstream test(filePath);
        if (!test.is_open())
        {
            return std::unexpected(ConfigFileErrorKind::FileCreationFailed);
        }
    }

    auto* hw = device_.get();
    if (hw == nullptr)
    {
        return std::unexpected(sd::HardwareError::HardwareNotSet);
    }

    if (hw->GetSWDeviceOEMPA() == nullptr)
    {
        return std::unexpected(sd::HardwareError::OempaInterfaceUnavailable);
    }

    if (!hw->LockDevice(eAcqContinue))
    {
        return std::unexpected(sd::HardwareError::DeviceLockFailed);
    }

    const std::wstring path = filePath.wstring();

    const bool ok = OEMPA_ReadHWWriteFile2(hw, path.c_str());

    const bool unlockOk = hw->UnlockDevice(eAcqContinue);

    if (!ok || !unlockOk)
    {
        return std::unexpected(ConfigFileErrorKind::SaveFailed);
    }

    return {};
}

} // namespace scanlab::config