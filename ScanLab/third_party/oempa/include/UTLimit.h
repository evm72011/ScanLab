
#pragma once

#include <limits.h>
#include <float.h>
#pragma warning( disable : 4584 )


const COLORREF colorCursorDefault=RGB(0xff,0,0);
const COLORREF colorZoomDefault=RGB(0,0,0xff);
const COLORREF colorTitleDefault=RGB(0,0xff,0);
class limitCUTData;
class UTKERNEL_API_ALIGN _limitCUTData
{
private:
	ULONGLONG m_ullPrivateMemory[32];
public:

};

class UTKERNEL_API_ALIGN limitCUTData :
	/*virtual*/ public limitCUTBaseClass,
	public _limitCUTData
{
public:
public:

public:
};

///////////////////////////////////////////////////////////////////////////////////////
// LIMIT CLASSES
///////////////////////////////////////////////////////////////////////////////////////
class limitCUTFocalLaw;
class UTKERNEL_API_ALIGN _limitCUTFocalLaw
{
private:
	ULONGLONG m_ullPrivateMemory[815];
public:

};

class UTKERNEL_API_ALIGN limitCUTFocalLaw :
	/*virtual*/ public limitCUTBaseClass,
	public _limitCUTFocalLaw
{
public:
public:

public:
};

class limitCUTPulser;
class UTKERNEL_API_ALIGN _limitCUTPulser
{
private:
	ULONGLONG m_ullPrivateMemory[99];
public:

};

class UTKERNEL_API_ALIGN limitCUTPulser :
	/*virtual*/ public limitCUTBaseClass,
	public limitCUTFocalLaw,
	public _limitCUTPulser
{
public:
public:

public:
};

class limitCUTAcquisitionInfo;
class UTKERNEL_API_ALIGN _limitCUTAcquisitionInfo
{
private:
	ULONGLONG m_ullPrivateMemory[236];
public:

};

class UTKERNEL_API_ALIGN limitCUTAcquisitionInfo :
	public limitCUTBaseClass,
	public _limitCUTAcquisitionInfo
{
public:
public:
protected:
public:

public:
};

class limitCUTGate;
class UTKERNEL_API_ALIGN _limitCUTGate
{
private:
	ULONGLONG m_ullPrivateMemory[931];
public:

};

class UTKERNEL_API_ALIGN limitCUTGate :
	/*virtual*/ public limitCUTBaseClass,
	public _limitCUTGate
{
public:
public:

public:
};



class limitCUTReceiver;
class UTKERNEL_API_ALIGN _limitCUTReceiver
{
private:
	ULONGLONG m_ullPrivateMemory[1013];
public:

};

class UTKERNEL_API_ALIGN limitCUTReceiver :
	/*virtual*/ public limitCUTBaseClass,
	public limitCUTFocalLaw,
	public limitCUTGate,
	public _limitCUTReceiver
{
public:
public:

public:
};



class limitCUTPulserReceiver;
class UTKERNEL_API_ALIGN _limitCUTPulserReceiver
{
private:
	ULONGLONG m_ullPrivateMemory[3001];
public:

};

class UTKERNEL_API_ALIGN limitCUTPulserReceiver :
	/*virtual*/ public limitCUTBaseClass,
	public limitCUTPulser,
	public _limitCUTPulserReceiver
{
public:
public:

public:
};



class limitCUTScan;
class UTKERNEL_API_ALIGN _limitCUTScan
{
private:
	ULONGLONG m_ullPrivateMemory[4081];
public:

};

class UTKERNEL_API_ALIGN limitCUTScan :
	/*virtual*/ public limitCUTBaseClass,
	public limitCUTWizardScan,//for pulse/echo
	public _limitCUTScan
{
public:
public:

public:
};



class limitCUTProbe;
class UTKERNEL_API_ALIGN _limitCUTProbe
{
private:
	ULONGLONG m_ullPrivateMemory[8294];
public:

};

class UTKERNEL_API_ALIGN limitCUTProbe :
	public limitCUTBaseClass,
	public _limitCUTProbe
{
public:
public:

public:
};



class limitCUTChannelsSimulator;
class UTKERNEL_API_ALIGN _limitCUTChannelsSimulator
{
private:
	ULONGLONG m_ullPrivateMemory[66];
public:

};

class UTKERNEL_API_ALIGN limitCUTChannelsSimulator :
	public limitCUTBaseClass,
	public _limitCUTChannelsSimulator
{
public:
public:

public:
};

///////////////////////////////////////////////////////////////////

class limitCUTFilterOEMPA;
class UTKERNEL_API_ALIGN _limitCUTFilterOEMPA
{
private:
	ULONGLONG m_ullPrivateMemory[120];
public:

};

class UTKERNEL_API_ALIGN limitCUTFilterOEMPA :
	public limitCUTBaseClass,
	public _limitCUTFilterOEMPA
{
public:
public:

public:
};



class limitCUTDeviceOEMPA;
class UTKERNEL_API_ALIGN _limitCUTDeviceOEMPA
{
private:
	ULONGLONG m_ullPrivateMemory[914];
public:

};

class UTKERNEL_API_ALIGN limitCUTDeviceOEMPA :
	public limitCUTBaseClass,
	public _limitCUTDeviceOEMPA
{
public:
public:

public:
};



class limitCUTChannels;
class UTKERNEL_API_ALIGN _limitCUTChannels
{
private:
	ULONGLONG m_ullPrivateMemory[8604];
public:

};

class UTKERNEL_API_ALIGN limitCUTChannels :
	public limitCUTKernelRoot,
	public limitCUTData,
	public _limitCUTChannels
{
public:
public:

public:
};

class limitCUTModule;
class UTKERNEL_API_ALIGN _limitCUTModule
{
private:
	ULONGLONG m_ullPrivateMemory[98];
public:

};

class UTKERNEL_API_ALIGN limitCUTModule :
	public limitCUTBaseClass,
	public _limitCUTModule
{
public:
public:

public:
};



class limitCUTPreference;
class UTKERNEL_API_ALIGN _limitCUTPreference
{
private:
	ULONGLONG m_ullPrivateMemory[397];
public:

};

class UTKERNEL_API_ALIGN limitCUTPreference :
	public limitCUTKernelRoot,
	public _limitCUTPreference
{
public:
public:

public:
};



/////////////////////////////////////////////////////////////////////////////////////

class limitCUTEncoder;
class UTKERNEL_API_ALIGN _limitCUTEncoder
{
private:
	ULONGLONG m_ullPrivateMemory[341];
public:

};

class UTKERNEL_API_ALIGN limitCUTEncoder :
	public limitCUTKernelRoot,
	public _limitCUTEncoder
{
public:
public:

public:
};

class limitCUTAxis;
class UTKERNEL_API_ALIGN _limitCUTAxis
{
private:
	ULONGLONG m_ullPrivateMemory[333];
public:

};

class UTKERNEL_API_ALIGN limitCUTAxis :
	public limitCUTKernelRoot,
	public _limitCUTAxis
{
public:
public:

public:
};

class limitCUTAcquisitionData;
class UTKERNEL_API_ALIGN _limitCUTAcquisitionData
{
private:
	ULONGLONG m_ullPrivateMemory[466];
public:

};

class UTKERNEL_API_ALIGN limitCUTAcquisitionData :
	public limitCUTKernelRoot,
	public limitCUTData,
	public _limitCUTAcquisitionData
{
public:
public:

public:
};

class limitCUTDisplayCursor;
class UTKERNEL_API_ALIGN _limitCUTDisplayCursor
{
private:
	ULONGLONG m_ullPrivateMemory[126];
public:

};

class UTKERNEL_API_ALIGN limitCUTDisplayCursor :
	public limitCUTKernelRoot,
	public _limitCUTDisplayCursor
{
public:
public:

public:
};

class limitCUTDisplayZoom;
class UTKERNEL_API_ALIGN _limitCUTDisplayZoom
{
private:
	ULONGLONG m_ullPrivateMemory[145];
public:

};

class UTKERNEL_API_ALIGN limitCUTDisplayZoom :
	public limitCUTKernelRoot,
	public _limitCUTDisplayZoom
{
public:
public:

public:
};

class limitCUTDisplayScreen;
class UTKERNEL_API_ALIGN _limitCUTDisplayScreen
{
private:
	ULONGLONG m_ullPrivateMemory[302];
public:

};

class UTKERNEL_API_ALIGN limitCUTDisplayScreen :
	/*virtual*/ public limitCUTBaseClass,
	public _limitCUTDisplayScreen
{
public:
public:

public:
};

class limitCUTDisplayView;
class UTKERNEL_API_ALIGN _limitCUTDisplayView
{
private:
	ULONGLONG m_ullPrivateMemory[918];
public:

};

class UTKERNEL_API_ALIGN limitCUTDisplayView :
	/*virtual*/ public limitCUTBaseClass,
	public limitCUTDisplayScreen,
	public _limitCUTDisplayView
{
public:
public:

public:
};



class limitCUTDisplayWindow;
class UTKERNEL_API_ALIGN _limitCUTDisplayWindow
{
private:
	ULONGLONG m_ullPrivateMemory[1308];
public:

};

class UTKERNEL_API_ALIGN limitCUTDisplayWindow :
	/*virtual*/ public limitCUTBaseClass,
	public limitCUTDisplayScreen,
	public _limitCUTDisplayWindow
{
public:
public:

public:
};



class limitCUTDisplayLayout;
class UTKERNEL_API_ALIGN _limitCUTDisplayLayout
{
private:
	ULONGLONG m_ullPrivateMemory[1996];
public:

};

class UTKERNEL_API_ALIGN limitCUTDisplayLayout :
	public limitCUTKernelRoot,
	public _limitCUTDisplayLayout
{
public:
public:

public:
};
