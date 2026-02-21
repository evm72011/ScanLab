#include <iostream>
#include"UTKernelDriver.h"//low level API used by the customized API
#include"UTKernelDriverOEMPA.h"//low level API used by the customized API
#include"OEMPACustomizedAPI.h"//to use the driver customized API
#include"OEMPACustomizedWizardAPI.h"//to use the kernel customized API
#include"UTKernelAPI.h"//to use high level API (Kernel Wizard)

int main() {
    CHWDeviceOEMPA* m_pHWDeviceOEMPA;
    std::cout << "Hello, OEMPA." << std::endl;
}
