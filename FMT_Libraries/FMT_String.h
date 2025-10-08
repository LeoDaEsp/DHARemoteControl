// =====================================================================================
/**
 * @file					FMT_String.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					09/03/2018
 * @brief					High level string management
 *
 * @version	Project:		Formatech C++ Core Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][22/01/2018]
 */
// =====================================================================================



#ifndef FMTDEF_STRING_H
#define FMTDEF_STRING_H

// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_GLOBAL_H
#include "FMT_Global.h"
#endif

#ifndef FMTDEF_OBJECT_H
#include "FMT_Object.h"
#endif

#ifndef FMTDEF_LIST_H
#include "FMT_List.h"
#endif

#ifndef FMTDEF_VECTOR_H
#include "FMT_Vector.h"
#endif

#ifndef FMTDEF_BUFFER_H
#include "FMT_Buffer.h"
#endif

using namespace FMT;


// =====================================================================================
//	DEFINES
// =====================================================================================




class CFMT_StringVector;
class CFMT_StringList;

// *************************************************************************************
// *************************************************************************************
//	Class CFMT_String
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_String : public CFMT_Object
{
    // =====================================================================================
    //	TYPES
    // =====================================================================================

public:

    //! Direction modes
    enum t_Direction
    {
        e_Direction_FromBegin		= 0x01,
        e_Direction_FromEnd			= 0x02,
        e_Direction_All				= 0x03
    };

    //! Case Modes
    enum t_Case
    {
        e_CaseLower	= 0,
        e_CaseUpper = 1
    };

    //! Alignment modes
    enum t_Align
    {
        e_Align_Left	= 0,
        e_Align_Right   = 1,
        e_Align_Center  = 2
    };

    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:

    //! C-String buffer
    t_FMT_Char		*m_pchBuf;

    //! C-String length
    t_FMT_Uint32	m_uiLength;

public:


// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Empty constructor
    CFMT_String();

    //! Copy constructor
    CFMT_String(const CFMT_String& op);

    //! Constructor from a C-style string
    CFMT_String(const t_FMT_Char* op);

    //! Constructor from a char buffer of predefined length
    CFMT_String(const t_FMT_Char* op, t_FMT_Uint32 uiLen);

    //! Constructor from a single char
    CFMT_String(const t_FMT_Char op);

    //! Constructor of a fixed size and fill
    CFMT_String(t_FMT_Uint32 uiLength, t_FMT_Char chFill = ' ');

    //! Destructor
    virtual ~CFMT_String();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

    //! Copy from an homogeneous object
    void				DataCopy(const CFMT_String& op);

    //! Destroy the string buffer and build a new one of uiNewSize
    void				NewBuffer(t_FMT_Uint32 uiNewSize);

    //! Destroy the char buffer
    void				DeleteBuffer();

    //! Clear the char buffer setting an empty string
    void				ClearBuffer();

    //! Check if two chars are equal
    t_FMT_Bool          IsCharsEqual(const t_FMT_Char& c1, const t_FMT_Char& c2, t_FMT_Bool bMatchCase) const;



public:

    // Properties ------------------------------------

    //! Return the length of a C-Style string
    static t_FMT_Uint32	CS_GetLength(const t_FMT_Char *pString);

    //! Return the length of the string
    t_FMT_Uint32		GetLength() const;

    //! Resize the string to uiSize chars, filling the new ones with chNew
    CFMT_String&		SetLength(t_FMT_Uint32 uiSize, t_FMT_Char chNew=' ');


    // Assignment ------------------------------------

    //! Assignment operator from homogeneous object
    CFMT_String&		operator=(const CFMT_String& op);

    //! Assignment operator from C-Style string
    CFMT_String&		operator=(const t_FMT_Char* op);

    //! Assignment operator from single char
    CFMT_String&		operator=(const t_FMT_Char op);



    //! Concatenation operator from homogeneous object
    CFMT_String			operator+(const CFMT_String& op);

    //! Concatenation operator from C-Style string
    CFMT_String			operator+(const t_FMT_Char* op);

    //! Concatenation operator from C-Style string
    FMTDEF_LIB_DLLSPEC friend CFMT_String  operator+(const t_FMT_Char* op1, const CFMT_String& op2);

    //! Concatenation operator from single char
    CFMT_String			operator+(const t_FMT_Char op);

    //! Concatenation operator from single char
    FMTDEF_LIB_DLLSPEC friend CFMT_String  operator+(t_FMT_Char op1, const CFMT_String& op2);


    //! Concatenation operator from homogeneous object with itself
    CFMT_String&		operator+=(const CFMT_String& op);

    //! Concatenation operator from C-Style string with itself
    CFMT_String&		operator+=(const t_FMT_Char* op);

    //! Concatenation operator from single char with itself
    CFMT_String&		operator+=(const t_FMT_Char op);

    //! Copy the string into C string pchDest
    void				ToStringC(t_FMT_Char* pchDest) const;

    //! Get the related C string
    t_FMT_Char*			GetStringC() const;


	// Sub-string extraction -------------------------

    //! Extracts the leftmost uiSize chars and returns the result
    CFMT_String			Left(t_FMT_Uint32 uiSize) const;

    //! Transforms the string into a string composed by the leftmost uiSize chars and returns a reference to the string.
    CFMT_String&		ResizeLeft(t_FMT_Uint32 uiSize);

    //! Extracts the rightmost uiSize chars and returns the result
    CFMT_String			Right(t_FMT_Uint32 uiSize) const;

    //! Transforms the string into a string composed by the rightmost uiSize chars and returns a reference to the string.
    CFMT_String&		ResizeRight(t_FMT_Uint32 uiSize);

    //! Extracts the rightmost string starting from uiPos and returns the result
    CFMT_String			RightFromPos(t_FMT_Uint32 uiPos) const;

    //! Transforms the string into a string composed by the rightmost string starting from uiPos and returns a reference to the string.
    CFMT_String&		ResizeRightFromPos(t_FMT_Uint32 uiPos);

    //! Extracts a substring of length uiStart chars, starting at position uiStart and returns the result
    CFMT_String			Mid(t_FMT_Uint32 uiStart,t_FMT_Uint32 uiSize) const;

    //! Transforms the string in the substring of length uiStart chars, starting at position uiStart and returns a reference to the string.
    CFMT_String&		ResizeMid(t_FMT_Uint32 uiStart, t_FMT_Uint32 uiSize);

    //! Removes the substring starting from uiStart of uiSize chars and returns a reference to the string.
    CFMT_String&		RemoveChars(t_FMT_Uint32 uiStart, t_FMT_Uint32 uiSize);

    //! Removes the indicated char from the string and returns a reference to the string.
    CFMT_String&		RemoveChar(t_FMT_Char chItem);

	// Comparison -------------------------------------

    //! Compare two C-Style strings
    static t_FMT_Int8	CS_Compare(const t_FMT_Char* op1, const t_FMT_Char* op2);

    //! Compare two objects matching the case
    static t_FMT_Int8   CompareMatchingCase(const CFMT_String& op1, const CFMT_String& op2);

    //! Compare two objects without matching the case
    static t_FMT_Int8   CompareNoMatchingCase(const CFMT_String& op1, const CFMT_String& op2);

    //! Compare the object to another string matching the case
    t_FMT_Int8			CompareMatchingCase(const CFMT_String& op) const;

    //! Compare the object to another string without matching the case
    t_FMT_Int8			CompareNoMatchingCase(const CFMT_String& op) const;

    //! Check if the object is equal to op
    t_FMT_Bool          operator==(const CFMT_String& op);

    //! Check if a C-string is equal to op
    FMTDEF_LIB_DLLSPEC friend t_FMT_Bool   operator==(const t_FMT_Char* op1, const CFMT_String& op2);

    //! Check if the object is not equal to op
    t_FMT_Bool          operator!=(const CFMT_String& op);

    //! Check if a C-string is not equal to op
    FMTDEF_LIB_DLLSPEC friend t_FMT_Bool   operator!=(const t_FMT_Char* op1, const CFMT_String& op2);

    //! Check if the object is greater or equal to op
    t_FMT_Bool          operator>=(const CFMT_String& op);

    //! Check if a C-string is greater or equal to op
    FMTDEF_LIB_DLLSPEC friend t_FMT_Bool   operator>=(const t_FMT_Char* op1, const CFMT_String& op2);

    //! Check if the object is greater to op
    t_FMT_Bool          operator>(const CFMT_String& op);

    //! Check if a C-string is greater to op
    FMTDEF_LIB_DLLSPEC friend t_FMT_Bool   operator>(const t_FMT_Char* op1, const CFMT_String& op2);

    //! Check if the object is less or equal to op
    t_FMT_Bool          operator<=(const CFMT_String& op);

    //! Check if a C-string is less or equal to op
    FMTDEF_LIB_DLLSPEC friend t_FMT_Bool   operator<=(const t_FMT_Char* op1, const CFMT_String& op2);

    //! Check if the object is less to op
    t_FMT_Bool          operator<(const CFMT_String& op);

    //! Check if a C-string is less to op
    FMTDEF_LIB_DLLSPEC friend t_FMT_Bool   operator<(const t_FMT_Char* op1, const CFMT_String& op2);


	// Indexing ---------------------------------------

    //! Set the char of index uiPos to ch
    void				SetChar(t_FMT_Uint32 uiPos, t_FMT_Char ch);

    //! Get the char of index uiPos
    t_FMT_Char			GetChar(t_FMT_Uint32 uiPos) const;


	// Searching --------------------------------------

    //! Searches this string for the first match of chx, starting for leftmost uiStart char
    t_FMT_Bool			FindFromBegin(t_FMT_Char chx, t_FMT_Uint32 *puiPos, t_FMT_Uint32 uiStart=0) const;

    //! Searches this string for the first match of sx, starting for leftmost uiStart char.
    t_FMT_Bool			FindFromBegin(const CFMT_String& sx, t_FMT_Uint32 *puiPos, t_FMT_Bool bMatchCase=FMTDEF_TRUE, t_FMT_Uint32 uiStart=0) const;
		
    //! Searches this string for the first match of chx, starting for rightmost uiStart char
    t_FMT_Bool			FindFromEnd(t_FMT_Char chx, t_FMT_Uint32 *puiPos, t_FMT_Uint32 uiStart=0xFFFFFFFF) const;

    //! Searches this string for the first match of sx, starting for rightmost uiStart char
    t_FMT_Bool			FindFromEnd(const CFMT_String& sx, t_FMT_Uint32 *puiPos, t_FMT_Bool bMatchCase=FMTDEF_TRUE, t_FMT_Uint32 uiStart=0xFFFFFFFF) const;


	// Copy -------------------------------------------

    //! Copies the C string pointed by source into the array pointed by destination, including the terminating null character
    static t_FMT_Char*  CS_Copy(t_FMT_Char *pDst, const t_FMT_Char *pSrc);

    //! Insert a char at leftmost position uiPos and returns a reference to the string
    CFMT_String&		Insert(t_FMT_Char src, t_FMT_Uint32 uiPos);

    //! Insert uiSize chars from leftmost uiStart of the string pchSrc, at leftmost position uiPos and returns a reference to the string.
    CFMT_String&		Insert(const CFMT_String& src, t_FMT_Uint32 uiPos, t_FMT_Uint32 uiStart = 0, t_FMT_Uint32 uiSize=0xFFFFFFFF);

    //! Copy uiSize chars of the string op, starting from uiStart, at uiPos position of current object and returns a reference to the string.
    CFMT_String&		ReplaceChars(const CFMT_String& op, t_FMT_Uint32 uiPos, t_FMT_Uint32 uiStart=0, t_FMT_Uint32 uiSize=0xFFFFFFFF);

    //! Replace uiDstSize chars starting from uiStart of current object, with uiSrcSize of the string op and returns a reference to the string.
    CFMT_String&		ReplaceString(const CFMT_String& op, t_FMT_Uint32 uiPos, t_FMT_Uint32 uiDstSize, t_FMT_Uint32 uiStart=0, t_FMT_Uint32 uiSrcSize=0xFFFFFFFF);

    //! Replace all chars chOld with chNew
    CFMT_String&        ReplaceChar(t_FMT_Char chOld, t_FMT_Char chNew);


	// Formatting ------------------------------------

    //! Call this member function to write formatted data in the same way that sprintf and returns a reference to the string. 
    CFMT_String&        Format(const t_FMT_Char *pchFormat, ...);

    //! Trim leading/trailing whitespace characters ch from the string and returns a reference to the string.
    CFMT_String&		Trim(t_FMT_Char ch=' ', t_FMT_Uint32 uiDir=e_Direction_All);

    //! Convert object applying the uiNewCase case (t_Case) and returns a reference to the string.
    CFMT_String&		SetCase(t_FMT_Uint32 uiNewCase);


    // Numbers ----------------------------------------

    //! Sets the string to the printed value of iNum in 10-base and returns the result
    static CFMT_String  FromNumber(t_FMT_Int64 qiNum);

    //! Sets the string to the printed value of dNum according to the given format and precision and returns the result
    static CFMT_String  FromNumber(t_FMT_Double dNum, t_FMT_Char format, t_FMT_Int32 precision);

    //! Sets the string to the printed value of iNum in the specified base and returns the result
    static CFMT_String  FromNumber(t_FMT_Uint64 quiNum, t_FMT_Uint32 uiBase, t_FMT_Uint32 uiSepStep = 0, t_FMT_Char ucSep = '.');

    //! Sets the string to the printed value of qiNum in the 10-base and returns a reference of the result
    CFMT_String&        SetFromNumber(t_FMT_Int64 qiNum);

    //! Sets the string to the printed value of dNum according to the given format and precision and returns a reference of the result
    CFMT_String&        SetFromNumber(t_FMT_Double dNum, t_FMT_Char format, t_FMT_Int32 precision = 6);

    //!	Sets the string to the printed value of iNum in the specified base and returns a reference of the result
    CFMT_String&        SetFromNumber(t_FMT_Uint64 quiNum, t_FMT_Uint32 uiBase, t_FMT_Uint32 uiSepStep = 0, t_FMT_Char ucSep = '.');

    //! Convert the string into a unsigned number in the specified base
    t_FMT_Uint64		ToUnsigned(t_FMT_Uint32 radix);

    //! Convert the string into a signed number in 10-base
    t_FMT_Int64			ToSigned();

    //! Convert the string into a floating point number
    t_FMT_Double		ToDouble();

    //! Convert the string into a 64-bit unsigned where the radix is provided by the string itself
    t_FMT_Uint64		ToUnsignedAutoRadix(t_FMT_Uint32 uiDelPos = e_Direction_FromBegin);

    //!	Format the string with provided alignment and fill char and return a reference of the result
    CFMT_String&        SetFormatted(t_FMT_Uint32 uiNumChars, t_Align align, t_FMT_Char chFillChar = ' ');

    //! Build a the string of uiSize chars, filling the with chFillChar
    CFMT_String&		Build(t_FMT_Uint32 uiSize, t_FMT_Char chFillChar=' ');


    // Substrings ------------------------------------------------------------

    //! Extract the strings by means of char separator and return a vector
    void                ExtractTags(t_FMT_Char chSeparator, CFMT_StringVector& v) const;

    //! Extract the strings by means of char separator and return a list
    void                ExtractTags(t_FMT_Char chSeparator, CFMT_StringList& sl) const;

    //! Extract the string encapsulated between two separators
    t_FMT_Uint32        ExtractEncapsulatedString(t_FMT_Char chLeftSeparator, t_FMT_Char chRightSeparator, CFMT_String& sSubString) const;


    // Serialization ---------------------------------------------------------

    //! Serializes a string into the buffer
    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator<<(CFMT_Buffer& buf, CFMT_String& s);

    //! Serializes a string from the buffer
    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator>>(CFMT_Buffer& buf, CFMT_String& s);


};





// *************************************************************************************
// *************************************************************************************
//	Class CFMT_StringList
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_StringList : public CFMT_List<CFMT_String>
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
public:


// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Empty constructor
    CFMT_StringList() {}

    //! Build a list of uiLength items with initialization value tValue
    CFMT_StringList(t_FMT_Uint32 uiLength, const CFMT_String& tValue) : CFMT_List(uiLength, tValue) {}

    //! Copy constructor
    CFMT_StringList(const CFMT_StringList& list) : CFMT_List(list) {}

    //! Build the list from an array
    CFMT_StringList(CFMT_String* pVet, t_FMT_Uint32 uiLength) : CFMT_List(pVet, uiLength) {}




// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

public:

    //! Sort the list
    CFMT_StringList&    Sort(t_FMT_Bool bOrder, t_FMT_Bool bMatchCase);

	//! Assignment from an homogeneous list
    CFMT_StringList& operator=(const CFMT_StringList& op);
    CFMT_StringList& operator=(const CFMT_List<CFMT_String>& op);

	//! Assignment from an homogeneous vector
    CFMT_StringList& operator=(CFMT_Vector<CFMT_String>& op);
    CFMT_StringList& operator=(CFMT_StringVector& op);
	
};




// *************************************************************************************
// *************************************************************************************
//	Class CFMT_StringVector
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_StringVector : public CFMT_Vector<CFMT_String>
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
public:


// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Empty constructor
    CFMT_StringVector() {}

    //! Build an array of uiLength without intializing
    CFMT_StringVector(t_FMT_Uint32 uiLength) : CFMT_Vector(uiLength) {}

    //! Copy constructor
    CFMT_StringVector(const CFMT_StringVector& op) : CFMT_Vector(op) {}

    //! Build an array of uiLength initializing with value
    CFMT_StringVector(t_FMT_Uint32 uiLength, const CFMT_String& value) : CFMT_Vector(uiLength, value) {}

    //! Build the object from an array of uiLength items
    CFMT_StringVector(CFMT_String* pVet, t_FMT_Uint32 uiLength) : CFMT_Vector(pVet, uiLength) {}


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

public:

    //! Sort the list
    CFMT_StringVector&		Sort(t_FMT_Bool bOrder, t_FMT_Bool bMatchCase);

	//! Assignment from an homogeneous list
    CFMT_StringVector& operator=(CFMT_StringList& op);
    CFMT_StringVector& operator=(CFMT_List<CFMT_String>& op);

	//! Assignment from an homogeneous vector
    CFMT_StringVector& operator=(const CFMT_Vector<CFMT_String>& op);
    CFMT_StringVector& operator=(const CFMT_StringVector& op);

};


#endif







