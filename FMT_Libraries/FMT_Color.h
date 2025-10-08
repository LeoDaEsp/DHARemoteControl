// =====================================================================================
/**
 * @file					FMT_Color.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					11/09/2021
 * @brief					RGB Color item
 *
 * @version	Project:		Formatech C++ Core Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][11/09/2021]
 */
// =====================================================================================



#ifndef FMTDEF_COLOR_H
#define FMTDEF_COLOR_H

// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_GLOBAL_H
#include "FMT_Global.h"
#endif

#ifndef FMTDEF_OBJECT_H
#include "FMT_Object.h"
#endif

#ifndef FMTDEF_EXCEPTION_H
#include "FMT_Exception.h"
#endif

#ifndef FMTDEF_BUFFER_H
#include "FMT_Buffer.h"
#endif

using namespace FMT;


// =====================================================================================
//	DEFINES
// =====================================================================================



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_Color
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_Color : public CFMT_Object
{
// =====================================================================================
//	TYPES
// =====================================================================================

protected:
public:


    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:

	//! Unsigned color
	t_FMT_Uint32		m_uiColor;

public:

// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Empty constructor
    CFMT_Color();

    //! Constructor with format
    CFMT_Color(const t_FMT_Uint32& uiColor);

    //! Copy constructor
    CFMT_Color(const CFMT_Color& op);

    //! Construct from RGB
    CFMT_Color(t_FMT_Uint8 ucRed, t_FMT_Uint8 ucGreen, t_FMT_Uint8 ucBlu);

	//! Destructor
    virtual ~CFMT_Color();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

private:

	//! Helpful to SetHLS
	t_FMT_Int32		HueToRGB(t_FMT_Int32 n1, t_FMT_Int32 n2, t_FMT_Int32 hue);

protected:

public:

	//! Assignment operator from homogeneous object
	CFMT_Color& operator=(CFMT_Color& But);

	//! Assignment operator from unsigned
	CFMT_Color& operator=(t_FMT_Uint32 col);

	//! Unsigned Cast operator
	operator t_FMT_Uint32() const
		{ return m_uiColor; };

	
	//! Set color by means of RGB components
	CFMT_Color&			SetRGB(t_FMT_Uint8 ucRed, t_FMT_Uint8 ucGreen, t_FMT_Uint8 ucBlu);

	//! Change Red component of the color
	CFMT_Color&			SetR(t_FMT_Uint8 ucNewR);

	//! Change Green component of the color
	CFMT_Color&			SetG(t_FMT_Uint8 ucNewG);

	//! Change Blu component of the color
	CFMT_Color&			SetB(t_FMT_Uint8 ucNewB);


	//! Return RGB component of the color
	void				GetRGB(t_FMT_Uint8& ucRed, t_FMT_Uint8& ucGreen, t_FMT_Uint8& ucBlu);

	//! Return Red component of the color
	t_FMT_Uint8			GetR();	

	//! Return Green component of the color
	t_FMT_Uint8			GetG();

	//! Return Blu component of the color
	t_FMT_Uint8			GetB();


	//! Return unsigned color
	t_FMT_Uint32		GetUnsignedColor()
		{	return m_uiColor;	};

	//! Return Hue, Luminance and Saturation coordinates of the color
	void				GetHLS(t_FMT_Uint8& ucH, t_FMT_Uint8& ucL, t_FMT_Uint8& ucS);

	//! Return Hue of the color
	t_FMT_Uint8			GetHue();

	//! Return Luminosity of the color
	t_FMT_Uint8			GetLuminosity();

	//! Return Saturation of the color
	t_FMT_Uint8			GetSaturation();


	//! Set color by means of Hue, Saturation and Luminosity components
	CFMT_Color&			SetHLS(t_FMT_Uint16 hue, t_FMT_Uint16 lum, t_FMT_Uint16 sat);

	//! Change Hue of the color
	CFMT_Color&			SetHue(t_FMT_Uint8 ucNewH);

	//! Change Luminosity of the color
	CFMT_Color&			SetLuminosity(t_FMT_Uint8 ucNewL);

	//! Change Saturation of the color
	CFMT_Color&			SetSaturation(t_FMT_Uint8 ucNewS);



	/*CFMT_Color ChangeHue(t_FMT_Uint8 btNewH);
	CFMT_Color ChangeLuminosity(t_FMT_Uint8 btNewL);
	CFMT_Color ChangeSaturation(t_FMT_Uint8 btNewS);*/


    // Serialization ---------------------------------------------------------

    //! Serializes a string into the buffer
    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator<<(CFMT_Buffer& buf, CFMT_Color& s);

    //! Serializes a string from the buffer
    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator>>(CFMT_Buffer& buf, CFMT_Color& s);

};



#endif







