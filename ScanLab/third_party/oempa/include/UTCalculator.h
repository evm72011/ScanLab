
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the UTCALCULATOR_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// UTCALCULATOR_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#ifdef UTCALCULATOR_EXPORTS
#ifdef _WIN32
#define UTCALCULATOR_API __declspec(dllexport)
#define UTCALCULATOR_API_ALIGN __declspec(dllexport) __declspec(align(8))
#elif defined __linux__
#define UTCALCULATOR_API __attribute__((visibility ("default")))
#define UTCALCULATOR_API_ALIGN __attribute__((visibility ("default"))) __attribute__((aligned(8)))
#endif // __linux__
#else
#ifdef _WIN32
#define UTCALCULATOR_API __declspec(dllimport)
#define UTCALCULATOR_API_ALIGN __declspec(dllimport) __declspec(align(8))
#elif defined __linux__
#define UTCALCULATOR_API
#define UTCALCULATOR_API_ALIGN __attribute__((aligned(8)))
#endif // __linux__
#endif

typedef struct structCoordinate
{
	double m_dCoordinates[3];
	bool m_bPoint;//if true this is a point, if false this is a vector
	double m_dPrecision;
}structCoordinate;

class UTCALCULATOR_API_ALIGN CCoordinate : protected structCoordinate
{
public:
	CCoordinate();

	CCoordinate(bool bPoint);
	CCoordinate(const structCoordinate &a);
	CCoordinate(const CCoordinate &a);
	CCoordinate(bool bPoint,double dX,double dY,double dZ);
	const CCoordinate& operator=(const CCoordinate &a);
	const CCoordinate& operator+=(const CCoordinate &a);
	const CCoordinate& operator-=(const CCoordinate &a);
	const CCoordinate& operator*=(const double a);
	const CCoordinate& operator/=(const double a);
	const CCoordinate operator+(const CCoordinate &a) const;
	const CCoordinate operator-(const CCoordinate &a) const;
	const CCoordinate operator^(const CCoordinate &a) const;//Cross()
	const CCoordinate operator*(double a) const;
	const CCoordinate operator/(double a) const;
	bool operator==(const CCoordinate &a) const;
	bool operator!=(const CCoordinate &a) const;

	double GetX() const;
	double GetY() const;
	double GetZ() const;

	void SetX(double dData);
	void SetY(double dData);
	void SetZ(double dData);

	void SetPrecision(double dValue);
	double GetPrecision() const;

	void EnablePoint();
	bool IsPoint() const;
	void EnableVector();
	bool IsVector() const;

	double angle();//polar system, result is between -PI and PI.
	double norm() const;//polar system.
	double norm2() const;
	void reset();

	double ProductScalar(const CCoordinate &a) const;
	CCoordinate Cross(const CCoordinate& other) const;
	CCoordinate Normalize() const;
	CCoordinate ProductMatrix3x3(double rot[3][3]) const;
	CCoordinate Rotate(int iAxisIndex,double dAngle) const;
	CCoordinate transpXY();
	CCoordinate rotXY(double dAngle);
	CCoordinate rotYZ(double dAngle);
	CCoordinate rotXZ(double dAngle);
	void PolarToCartesian();//polar system to cartesian system.
friend UTCALCULATOR_API double Prod(const CCoordinate &A,const CCoordinate &B);
};

namespace FocalCalculator
{


	class UTCALCULATOR_API_ALIGN _Probe
	{
	private:
		ULONGLONG m_ullPrivateMemory[1];
	protected:

	};

	class UTCALCULATOR_API_ALIGN Probe : public _Probe
	{
	public:
		// Empty Probe
		Probe();

		// linear probe
		Probe(int iElementCount, double dPitch, double dFrequency);

		// 2D Rectangular Matrix Probe
		Probe(int iElementCountX, int iElementCountY, double dPitchX, double dPitchY, bool bFirstElementBottom, bool bFirstElementLeft, bool incrementXFirst, double dFrequency);

		// Arbitrary Probe Def
		Probe(int iElementCount, double dXPos[], double dYPos[], double dZPos[], double dFrequency);

		~Probe();
		Probe(const Probe& other);
		Probe(Probe&& other) noexcept;
		Probe& operator=(const Probe& other);
		Probe& operator=(Probe&& other) noexcept;

		bool GetPositions(int iElementCountMax, int& iElementCount, CCoordinate probePositions[]) const;
		int GetElementCount() const;
		double GetPulseWidth() const;
		// bXAxis == false returns YAxis pitch, if probe is matrix
		// if probe is custom this will return meaningless results
		double GetPitch(bool bXAxis = true) const;

		// Create Probe from probe def file
		static Probe CreateProbeFromFile(const wchar_t* pFileName, double dFrequency, double dUnitMultiplier = 1.0e-3);
	};

	class UTCALCULATOR_API_ALIGN _Wedge
	{
	private:
		ULONGLONG m_ullPrivateMemory[10];
	protected:

	};

	class UTCALCULATOR_API_ALIGN Wedge : public _Wedge
	{
	public:
		// Empty wedge def means no wedge
		Wedge();
		// Standard wedge def
		Wedge(double dVelocity, double dTiltAngleDeg, double dRoofAngleDeg, double dSkewAngleDeg, double dElem1X, double dElem1Y, double dElem1Z);

		bool ElementPositionsOnWedge(int iElementCountMax, const Probe& probe, CCoordinate positionsOnWedge[]) const;
		bool IsContact() const;
		double GetVelocity() const;
	};

	/**
	 * @brief Calculates the focal and emergence points based on the beam emission angle and inspection setup.
	 *
	 * This function determines the emergence point and focal point relative to the center of the probe,
	 * given a specific beam emission angle, part velocity, and radius. Useful for ultrasonic beam modeling.
	 *
	 * @param focusType Type of focus calculation (e.g., fixed depth, true depth, sound path).
	 * @param probe The probe used in the inspection.
	 * @param iApertureElementCount Number of elements in the aperture.
	 * @param iApertureElements Array of element indices in the aperture.
	 * @param wedge The wedge associated with the probe.
	 * @param dPartVelocity Acoustic velocity in the part material (m/s).
	 * @param dPartRadius Radius of the part (0 for flat parts).
	 * @param dPrimaryAxisAngleDeg Beam steering angle in the primary axis (degrees).
	 * @param dSecondaryAxisAngleDeg Beam steering angle in the secondary axis (degrees).
	 * @param dFocalDistance Desired focal distance from the probe center.
	 * @param FocalPoint Output coordinate of the focal point.
	 * @param EmergencePoint Output coordinate of the beam emergence point.
	 * @param dCylinderSkewAngle Skew angle in degrees defining the orientation of the cylindrical part's axis in the XY plane (0° = Y-axis curvature, 90° = X-axis curvature). Defaults to 0° (curvature in YZ plane). Ignored if dPartRadius = 0.
	 *
	 * @return True if the calculation succeeded, false otherwise.
	 */
	UTCALCULATOR_API bool GetFocusAndEmergencePointFromBeamAngle(enumDepthMode focusType, const Probe& probe, int iApertureElementCount, int iApertureElements[], const Wedge& wedge,
		double dPartVelocity, double dPartRadius, double dPrimaryAxisAngleDeg, double dSecondaryAxisAngleDeg, double dFocalDistance,
		CCoordinate& FocalPoint, CCoordinate& EmergencePoint, double dCylinderSkewAngle = 0.0);

	/**
	 * @brief Calculates delay law and emergence point based on a given focal point.
	 *
	 * This function computes the delay values required to focus at a specified point and also returns
	 * the beam emergence point. Useful for beamforming in phased array inspections.
	 *
	 * @param probe The probe used in the inspection.
	 * @param iApertureElementCount Number of elements in the aperture.
	 * @param iApertureElements Array of element indices in the aperture.
	 * @param wedge The wedge associated with the probe.
	 * @param focalPoint Desired focal point in 3D space.
	 * @param dPartVelocity Acoustic velocity in the part material (m/s).
	 * @param dPartRadius Radius of the part (0 for flat parts).
	 * @param iDelayCountMax Maximum number of delay values to store.
	 * @param fDelays Output array of delay values per element (in microseconds).
	 * @param dWedgeDelay Output total delay introduced by the wedge.
	 * @param dCenterDelay Output delay for the center element (for reference or calibration).
	 * @param emergencePoint Output coordinate of the beam emergence point.
	 * @param dCylinderSkewAngle Skew angle in degrees defining the orientation of the cylindrical part's axis in the XY plane (0° = Y-axis curvature, 90° = X-axis curvature). Defaults to 0° (curvature in XZ plane). Ignored if dPartRadius = 0.
	 *
	 * @return True if the calculation succeeded, false otherwise.
	 */
	UTCALCULATOR_API bool GetDelayLawAndEmergencePointFromFocus(const Probe& probe, int iApertureElementCount, int iApertureElements[], const Wedge& wedge, const CCoordinate& focalPoint, double dPartVelocity, double dPartRadius,
		int iDelayCountMax, float fDelays[], double& dWedgeDelay, double& dCenterDelay, CCoordinate& emergencePoint, double dCylinderSkewAngle = 0.0);
}
