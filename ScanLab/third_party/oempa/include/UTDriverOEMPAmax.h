
#pragma once
#include "UTDriverOEMPAminiMax.h"

#ifndef DRIVER_OEMPAMAX_API
#define DRIVER_OEMPAMAX_API
using CSWDeviceOEMPAmax = CSWDeviceOEMPAminiMax;
class DRIVER_OEMPAMINIMAX_API_ALIGN CHWDeviceOEMPAmax : public CHWDeviceOEMPAminiMax
{
public:
	CHWDeviceOEMPAmax();
	CHWDeviceOEMPAmax(const wchar_t *pFlashFile);
};
#endif //DRIVER_OEMPAMAX_API
