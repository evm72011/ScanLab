
#pragma once
#include "UTDriverOEMPAminiMax.h"

#ifndef DRIVER_OEMPAMINI_API
#define DRIVER_OEMPAMINI_API
using CSWDeviceOEMPAmax = CSWDeviceOEMPAminiMax;
class DRIVER_OEMPAMINIMAX_API_ALIGN CHWDeviceOEMPAmini : public CHWDeviceOEMPAminiMax
{
public:
	CHWDeviceOEMPAmini();
	CHWDeviceOEMPAmini(bool bTCP);
	CHWDeviceOEMPAmini(const wchar_t *pFlashFile);
};
#endif //DRIVER_OEMPAMINI_API
