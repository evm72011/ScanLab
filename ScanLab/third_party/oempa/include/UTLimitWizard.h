
#pragma once
#pragma warning( disable : 4584 )
#include <math.h>

/////////////////////////////////////////////////////////////////////////////////////////////////
class limitCUTPoint;
class UTKERNEL_API_ALIGN _limitCUTPoint
{
private:
	ULONGLONG m_ullPrivateMemory[58];
public:

};

class UTKERNEL_API_ALIGN limitCUTPoint :
	public limitCUTBaseClass,
	public _limitCUTPoint
{
public:
public:

public:
};

/////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////////

class limitCUTWizardSpecimen;
class UTKERNEL_API_ALIGN _limitCUTWizardSpecimen
{
private:
	ULONGLONG m_ullPrivateMemory[126];
public:

};

class UTKERNEL_API_ALIGN limitCUTWizardSpecimen :
	public limitCUTBaseClass,
	public _limitCUTWizardSpecimen
{
public:
public:

public:
};

class limitCUTWizardWedge;
class UTKERNEL_API_ALIGN _limitCUTWizardWedge
{
private:
	ULONGLONG m_ullPrivateMemory[301];
public:

};

class UTKERNEL_API_ALIGN limitCUTWizardWedge :
	/*virtual*/ public limitCUTBaseClass,
	public _limitCUTWizardWedge
{
public:
public:

public:
};

class limitCUTWizardProbe;
class UTKERNEL_API_ALIGN _limitCUTWizardProbe
{
private:
	ULONGLONG m_ullPrivateMemory[619];
public:

};

class UTKERNEL_API_ALIGN limitCUTWizardProbe :
	/*virtual*/ public limitCUTBaseClass,
	public limitCUTWizardWedge,
	public _limitCUTWizardProbe
{
public:
public:

public:
};



class limitCUTWizardSystem;
class UTKERNEL_API_ALIGN _limitCUTWizardSystem
{
private:
	ULONGLONG m_ullPrivateMemory[1116];
public:

};

class UTKERNEL_API_ALIGN limitCUTWizardSystem :
	public limitCUTKernelRoot,
	public _limitCUTWizardSystem
{
public:
public:

public:
};

class limitCUTWizardAperture;
class UTKERNEL_API_ALIGN _limitCUTWizardAperture
{
private:
	ULONGLONG m_ullPrivateMemory[130];
public:

};

class UTKERNEL_API_ALIGN limitCUTWizardAperture :
	/*virtual*/ public limitCUTBaseClass,
	public _limitCUTWizardAperture
{
public:
public:

public:
};

class limitCUTWizardVector;
class UTKERNEL_API_ALIGN _limitCUTWizardVector
{
private:
	ULONGLONG m_ullPrivateMemory[306];
public:

};

class UTKERNEL_API_ALIGN limitCUTWizardVector :
	/*virtual*/ public limitCUTBaseClass,
	public limitCUTWizardAperture,
	public _limitCUTWizardVector
{
public:
public:

public:
};

class UTKERNEL_API_ALIGN limitCUTWizardVectorStep : public limitCUTWizardVector
{
public:
public:

public:
};

class limitCUTWizardFocalLaw;
class UTKERNEL_API_ALIGN _limitCUTWizardFocalLaw
{
private:
	ULONGLONG m_ullPrivateMemory[958];
public:

};

class UTKERNEL_API_ALIGN limitCUTWizardFocalLaw :
	public limitCUTBaseClass,
	public _limitCUTWizardFocalLaw
{
public:
public:

public:
};



class limitCUTWizardAcquisition;
class UTKERNEL_API_ALIGN _limitCUTWizardAcquisition
{
private:
	ULONGLONG m_ullPrivateMemory[221];
public:

};

class UTKERNEL_API_ALIGN limitCUTWizardAcquisition :
	public limitCUTBaseClass,
	public _limitCUTWizardAcquisition
{
public:
public:

public:
};



class limitCUTWizardScan;
class UTKERNEL_API_ALIGN _limitCUTWizardScan
{
private:
	ULONGLONG m_ullPrivateMemory[3908];
public:

};

class UTKERNEL_API_ALIGN limitCUTWizardScan :
	/*virtual*/ public limitCUTBaseClass,
	public _limitCUTWizardScan
{
public:
public:

public:
};

/////////////////////////////////////////////////////////////////////////////////////////////////
#pragma warning( default : 4584 )
