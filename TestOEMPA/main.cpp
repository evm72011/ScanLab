#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <Windows.h>

#include <iostream>
#include <memory>

#include <UTDriverOEMPA.h>
#include <UTDriverOEMPAExport.h>
#include <UTDriverOEMPAmax.h>

//#include"UTKernelDriver.h"//low level API used by the customized API
//#include"UTKernelDriverOEMPA.h"//low level API used by the customized API
//#include"OEMPACustomizedAPI.h"//to use the driver customized API
//#include"OEMPACustomizedWizardAPI.h"//to use the kernel customized API
//#include"UTKernelAPI.h"//to use high level API (Kernel Wizard)

int main() {
    std::cout << "[1] start" << std::endl;

    // создаём на куче (важно!)
    auto hw = std::make_unique<CHWDeviceOEMPAmax>();
    std::cout << "[2] device created" << std::endl;

    const wchar_t* addr = L"192.168.0.10";      // Ethernet
    // const wchar_t* addr = L"pcie://device=0"; // PCIe

    // OEMPA-слой — установка адреса
    auto* swOempa = hw->GetSWDeviceOEMPA();
    if (!swOempa || !swOempa->SetAddress(addr)) {
        std::cout << "[E] SetAddress failed" << std::endl;
        return 1;
    }
    std::cout << "[3] address set" << std::endl;

    // базовый слой — подключение
    auto* swBase = hw->GetSWDevice();
    if (!swBase || !swBase->SetConnectionState(eConnected, true)) {
        std::cout << "[E] Connect failed" << std::endl;
        return 2;
    }

    std::cout << "[4] connected" << std::endl;

    return 0;
}
