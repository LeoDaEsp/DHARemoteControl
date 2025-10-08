// =====================================================================================
/**
 * @file					FMT_BasicContainers.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					24/03/2018
 * @brief					Basic containers
 *
 * @version	Project:		Formatech C++ Core Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][24/03/2018]
 */
// =====================================================================================



#ifndef FMTDEF_BASICCONTAINERS_H
#define FMTDEF_BASICCONTAINERS_H

// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_GLOBAL_H
#include "FMT_Global.h"
#endif

#ifndef FMTDEF_LIST_H
#include "FMT_List.h"
#endif

#ifndef FMTDEF_VECTOR_H
#include "FMT_Vector.h"
#endif

#ifndef FMTDEF_MATRIX_H
#include "FMT_Matrix.h"
#endif

#ifndef FMTDEF_TREE_H
#include "FMT_Tree.h"
#endif

// =====================================================================================
//	DEFINES
// =====================================================================================


class CFMT_Uint8Vector;
class CFMT_Uint16Vector;
class CFMT_Uint32Vector;
class CFMT_Uint64Vector;
class CFMT_Int8Vector;
class CFMT_Int16Vector;
class CFMT_Int32Vector;
class CFMT_Int64Vector;
class CFMT_FloatVector;
class CFMT_DoubleVector;

// *************************************************************************************
// *************************************************************************************
//	Class CFMT_Uint8List
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_Uint8List : public CFMT_OrderedList<t_FMT_Uint8>
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
	CFMT_Uint8List() {}

	//! Build a list of uiLength items with initialization value tValue
	CFMT_Uint8List(t_FMT_Uint32 uiLength, const t_FMT_Uint8& tValue) : CFMT_OrderedList(uiLength, tValue) {}

	//! Copy constructor
	CFMT_Uint8List(const CFMT_Uint8List& list) : CFMT_OrderedList(list) {}

	//! Build the list from an array
	CFMT_Uint8List(t_FMT_Uint8* pVet, t_FMT_Uint32 uiLength) : CFMT_OrderedList(pVet, uiLength) {}


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

public:

	//! Assignment from an homogeneous list
    CFMT_Uint8List& operator=(const CFMT_Uint8List& op);
    CFMT_Uint8List& operator=(const CFMT_List<t_FMT_Uint8>& op);

	//! Assignment from an homogeneous vector
    CFMT_Uint8List& operator=(CFMT_Vector<t_FMT_Uint8>& op);
    CFMT_Uint8List& operator=(CFMT_Uint8Vector& op);
};


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_Uint16List
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_Uint16List : public CFMT_OrderedList<t_FMT_Uint16>
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
	CFMT_Uint16List() {}

	//! Build a list of uiLength items with initialization value tValue
	CFMT_Uint16List(t_FMT_Uint32 uiLength, const t_FMT_Uint16& tValue) : CFMT_OrderedList(uiLength, tValue) {}

	//! Copy constructor
	CFMT_Uint16List(const CFMT_Uint16List& list) : CFMT_OrderedList(list) {}

	//! Build the list from an array
	CFMT_Uint16List(t_FMT_Uint16* pVet, t_FMT_Uint32 uiLength) : CFMT_OrderedList(pVet, uiLength) {}


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

public:

	//! Assignment from an homogeneous list
    CFMT_Uint16List& operator=(const CFMT_Uint16List& op);
    CFMT_Uint16List& operator=(const CFMT_List<t_FMT_Uint16>& op);

	//! Assignment from an homogeneous vector
    CFMT_Uint16List& operator=(CFMT_Vector<t_FMT_Uint16>& op);
    CFMT_Uint16List& operator=(CFMT_Uint16Vector& op);

};


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_Uint32List
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_Uint32List : public CFMT_OrderedList<t_FMT_Uint32>
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
	CFMT_Uint32List() {}

	//! Build a list of uiLength items with initialization value tValue
	CFMT_Uint32List(t_FMT_Uint32 uiLength, const t_FMT_Uint32& tValue) : CFMT_OrderedList(uiLength, tValue) {}

	//! Copy constructor
	CFMT_Uint32List(const CFMT_Uint32List& list) : CFMT_OrderedList(list) {}

	//! Build the list from an array
	CFMT_Uint32List(t_FMT_Uint32* pVet, t_FMT_Uint32 uiLength) : CFMT_OrderedList(pVet, uiLength) {}


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

public:

	//! Assignment from an homogeneous list
    CFMT_Uint32List& operator=(const CFMT_Uint32List& op);
    CFMT_Uint32List& operator=(const CFMT_List<t_FMT_Uint32>& op);

	//! Assignment from an homogeneous vector
    CFMT_Uint32List& operator=(CFMT_Vector<t_FMT_Uint32>& op);
    CFMT_Uint32List& operator=(CFMT_Uint32Vector& op);

};


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_Uint64List
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_Uint64List : public CFMT_OrderedList<t_FMT_Uint64>
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
	CFMT_Uint64List() {}

	//! Build a list of uiLength items with initialization value tValue
	CFMT_Uint64List(t_FMT_Uint32 uiLength, const t_FMT_Uint64& tValue) : CFMT_OrderedList(uiLength, tValue) {}

	//! Copy constructor
	CFMT_Uint64List(const CFMT_Uint64List& list) : CFMT_OrderedList(list) {}

	//! Build the list from an array
	CFMT_Uint64List(t_FMT_Uint64* pVet, t_FMT_Uint32 uiLength) : CFMT_OrderedList(pVet, uiLength) {}


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

public:

	//! Assignment from an homogeneous list
    CFMT_Uint64List& operator=(const CFMT_Uint64List& op);
    CFMT_Uint64List& operator=(const CFMT_List<t_FMT_Uint64>& op);

	//! Assignment from an homogeneous vector
    CFMT_Uint64List& operator=(CFMT_Vector<t_FMT_Uint64>& op);
    CFMT_Uint64List& operator=(CFMT_Uint64Vector& op);

};


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_Int8List
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_Int8List : public CFMT_OrderedList<t_FMT_Int8>
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
	CFMT_Int8List() {}

	//! Build a list of uiLength items with initialization value tValue
	CFMT_Int8List(t_FMT_Uint32 uiLength, const t_FMT_Int8& tValue) : CFMT_OrderedList(uiLength, tValue) {}

	//! Copy constructor
	CFMT_Int8List(const CFMT_Int8List& list) : CFMT_OrderedList(list) {}

	//! Build the list from an array
	CFMT_Int8List(t_FMT_Int8* pVet, t_FMT_Uint32 uiLength) : CFMT_OrderedList(pVet, uiLength) {}


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

public:

	//! Assignment from an homogeneous list
    CFMT_Int8List& operator=(const CFMT_Int8List& op);
    CFMT_Int8List& operator=(const CFMT_List<t_FMT_Int8>& op);

	//! Assignment from an homogeneous vector
    CFMT_Int8List& operator=(CFMT_Vector<t_FMT_Int8>& op);
    CFMT_Int8List& operator=(CFMT_Int8Vector& op);

};


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_Int16List
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_Int16List : public CFMT_OrderedList<t_FMT_Int16>
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
	CFMT_Int16List() {}

	//! Build a list of uiLength items with initialization value tValue
	CFMT_Int16List(t_FMT_Uint32 uiLength, const t_FMT_Int16& tValue) : CFMT_OrderedList(uiLength, tValue) {}

	//! Copy constructor
	CFMT_Int16List(const CFMT_Int16List& list) : CFMT_OrderedList(list) {}

	//! Build the list from an array
	CFMT_Int16List(t_FMT_Int16* pVet, t_FMT_Uint32 uiLength) : CFMT_OrderedList(pVet, uiLength) {}


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

public:

	//! Assignment from an homogeneous list
    CFMT_Int16List& operator=(const CFMT_Int16List& op);
    CFMT_Int16List& operator=(const CFMT_List<t_FMT_Int16>& op);

	//! Assignment from an homogeneous vector
    CFMT_Int16List& operator=(CFMT_Vector<t_FMT_Int16>& op);
    CFMT_Int16List& operator=(CFMT_Int16Vector& op);
};


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_Int32List
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_Int32List : public CFMT_OrderedList<t_FMT_Int32>
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
	CFMT_Int32List() {}

	//! Build a list of uiLength items with initialization value tValue
	CFMT_Int32List(t_FMT_Uint32 uiLength, const t_FMT_Int32& tValue) : CFMT_OrderedList(uiLength, tValue) {}

	//! Copy constructor
	CFMT_Int32List(const CFMT_Int32List& list) : CFMT_OrderedList(list) {}

	//! Build the list from an array
	CFMT_Int32List(t_FMT_Int32* pVet, t_FMT_Uint32 uiLength) : CFMT_OrderedList(pVet, uiLength) {}


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

public:

	//! Assignment from an homogeneous list
    CFMT_Int32List& operator=(const CFMT_Int32List& op);
    CFMT_Int32List& operator=(const CFMT_List<t_FMT_Int32>& op);

	//! Assignment from an homogeneous vector
    CFMT_Int32List& operator=(CFMT_Vector<t_FMT_Int32>& op);
    CFMT_Int32List& operator=(CFMT_Int32Vector& op);

};


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_Int64List
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_Int64List : public CFMT_OrderedList<t_FMT_Int64>
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
	CFMT_Int64List() {}

	//! Build a list of uiLength items with initialization value tValue
	CFMT_Int64List(t_FMT_Uint32 uiLength, const t_FMT_Int64& tValue) : CFMT_OrderedList(uiLength, tValue) {}

	//! Copy constructor
	CFMT_Int64List(const CFMT_Int64List& list) : CFMT_OrderedList(list) {}

	//! Build the list from an array
	CFMT_Int64List(t_FMT_Int64* pVet, t_FMT_Uint32 uiLength) : CFMT_OrderedList(pVet, uiLength) {}


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

public:

	//! Assignment from an homogeneous list
    CFMT_Int64List& operator=(const CFMT_Int64List& op);
    CFMT_Int64List& operator=(const CFMT_List<t_FMT_Int64>& op);

	//! Assignment from an homogeneous vector
    CFMT_Int64List& operator=(CFMT_Vector<t_FMT_Int64>& op);
    CFMT_Int64List& operator=(CFMT_Int64Vector& op);

};


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_FloatList
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_FloatList : public CFMT_OrderedList<t_FMT_Float>
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
	CFMT_FloatList() {}

	//! Build a list of uiLength items with initialization value tValue
	CFMT_FloatList(t_FMT_Uint32 uiLength, const t_FMT_Float& tValue) : CFMT_OrderedList(uiLength, tValue) {}

	//! Copy constructor
	CFMT_FloatList(const CFMT_FloatList& list) : CFMT_OrderedList(list) {}

	//! Build the list from an array
	CFMT_FloatList(t_FMT_Float* pVet, t_FMT_Uint32 uiLength) : CFMT_OrderedList(pVet, uiLength) {}


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

public:

	//! Assignment from an homogeneous list
    CFMT_FloatList& operator=(const CFMT_FloatList& op);
    CFMT_FloatList& operator=(const CFMT_List<t_FMT_Float>& op);

	//! Assignment from an homogeneous vector
    CFMT_FloatList& operator=(CFMT_Vector<t_FMT_Float>& op);
    CFMT_FloatList& operator=(CFMT_FloatVector& op);

};


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_DoubleList
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_DoubleList : public CFMT_OrderedList<t_FMT_Double>
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
	CFMT_DoubleList() {}

	//! Build a list of uiLength items with initialization value tValue
	CFMT_DoubleList(t_FMT_Uint32 uiLength, const t_FMT_Double& tValue) : CFMT_OrderedList(uiLength, tValue) {}

	//! Copy constructor
	CFMT_DoubleList(const CFMT_DoubleList& list) : CFMT_OrderedList(list) {}

	//! Build the list from an array
	CFMT_DoubleList(t_FMT_Double* pVet, t_FMT_Uint32 uiLength) : CFMT_OrderedList(pVet, uiLength) {}


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

public:

	//! Assignment from an homogeneous list
    CFMT_DoubleList& operator=(const CFMT_DoubleList& op);
    CFMT_DoubleList& operator=(const CFMT_List<t_FMT_Double>& op);

	//! Assignment from an homogeneous vector
    CFMT_DoubleList& operator=(CFMT_Vector<t_FMT_Double>& op);
    CFMT_DoubleList& operator=(CFMT_DoubleVector& op);

};





// *************************************************************************************
// *************************************************************************************
//	Class CFMT_Uint8Vector
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_Uint8Vector : public CFMT_OrderedVector<t_FMT_Uint8>
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
	CFMT_Uint8Vector() {}

	//! Build an array of uiLength without intializing
	CFMT_Uint8Vector(t_FMT_Uint32 uiLength) : CFMT_OrderedVector(uiLength) {}

	//! Copy constructor
	CFMT_Uint8Vector(const CFMT_Uint8Vector& op) : CFMT_OrderedVector(op) {}

	//! Build an array of uiLength initializing with value
	CFMT_Uint8Vector(t_FMT_Uint32 uiLength, const t_FMT_Uint8& value) : CFMT_OrderedVector(uiLength, value) {}

	//! Build the object from an array of uiLength items
	CFMT_Uint8Vector(t_FMT_Uint8* pVet, t_FMT_Uint32 uiLength) : CFMT_OrderedVector(pVet, uiLength) {}



// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:


    //! Get a 16-bit unsigned integer from uiPos, according set byte ordering
    t_FMT_Uint16    GetUint16(t_FMT_Uint32 uiPos, t_ByteOrdering bo = e_ByteOrdering_LittleEndian);

    //! Get a 32-bit unsigned integer from uiPos, according set byte ordering
    t_FMT_Uint32    GetUint32(t_FMT_Uint32 uiPos, t_ByteOrdering bo = e_ByteOrdering_LittleEndian);

    //! Get a 64-bit unsigned integer from uiPos, according set byte ordering
    t_FMT_Uint64    GetUint64(t_FMT_Uint32 uiPos, t_ByteOrdering bo = e_ByteOrdering_LittleEndian);

    //! Get a 16-bit signed integer from uiPos, according set byte ordering
    t_FMT_Int16     GetInt16(t_FMT_Uint32 uiPos, t_ByteOrdering bo = e_ByteOrdering_LittleEndian);

    //! Get a 32-bit signed integer from uiPos, according set byte ordering
    t_FMT_Int32     GetInt32(t_FMT_Uint32 uiPos, t_ByteOrdering bo = e_ByteOrdering_LittleEndian);

    //! Get a 64-bit signed integer from uiPos, according set byte ordering
    t_FMT_Int64     GetInt64(t_FMT_Uint32 uiPos, t_ByteOrdering bo = e_ByteOrdering_LittleEndian);

    //! Get a single precision float number from uiPos, according set byte ordering
    t_FMT_Float     GetFloat(t_FMT_Uint32 uiPos, t_ByteOrdering bo = e_ByteOrdering_LittleEndian);

    //! Get a double precision float number from uiPos, according set byte ordering
    t_FMT_Double    GetDouble(t_FMT_Uint32 uiPos, t_ByteOrdering bo = e_ByteOrdering_LittleEndian);


    //! Set a 16-bit unsigned integer to uiPos,  according set byte ordering
    void            SetUint16(const t_FMT_Uint16& usSrc, t_FMT_Uint32 uiPos, t_ByteOrdering bo = e_ByteOrdering_LittleEndian);

    //! Set a 32-bit unsigned integer to uiPos,  according set byte ordering
    void            SetUint32(const t_FMT_Uint32& uiSrc, t_FMT_Uint32 uiPos, t_ByteOrdering bo = e_ByteOrdering_LittleEndian);

    //! Set a 64-bit unsigned integer to uiPos,  according set byte ordering
    void            SetUint64(const t_FMT_Uint64& quiSrc, t_FMT_Uint32 uiPos, t_ByteOrdering bo = e_ByteOrdering_LittleEndian);

    //! Set a 16-bit signed integer to uiPos,  according set byte ordering
    void            SetInt16(const t_FMT_Int16& shSrc, t_FMT_Uint32 uiPos, t_ByteOrdering bo = e_ByteOrdering_LittleEndian);

    //! Set a 32-bit signed integer to uiPos,  according set byte ordering
    void            SetInt32(const t_FMT_Int32& iSrc, t_FMT_Uint32 uiPos, t_ByteOrdering bo = e_ByteOrdering_LittleEndian);

    //! Set a 64-bit signed integer to uiPos,  according set byte ordering
    void            SetInt64(const t_FMT_Int64& qiSrc, t_FMT_Uint32 uiPos, t_ByteOrdering bo = e_ByteOrdering_LittleEndian);

    //! Set a single precision float number to uiPos,  according set byte ordering
    void            SetFloat(const t_FMT_Float& fSrc, t_FMT_Uint32 uiPos, t_ByteOrdering bo = e_ByteOrdering_LittleEndian);

    //! Set a double precision float number to uiPos,  according set byte ordering
    void            SetDouble(const t_FMT_Double& dSrc, t_FMT_Uint32 uiPos, t_ByteOrdering bo = e_ByteOrdering_LittleEndian);


	//! Assignment from an homogeneous list
    CFMT_Uint8Vector& operator=(CFMT_Uint8List& op);
    CFMT_Uint8Vector& operator=(CFMT_List<t_FMT_Uint8>& op);

	//! Assignment from an homogeneous vector
    CFMT_Uint8Vector& operator=(const CFMT_Vector<t_FMT_Uint8>& op);
    CFMT_Uint8Vector& operator=(const CFMT_Uint8Vector& op);
};


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_Uint16Vector
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_Uint16Vector : public CFMT_OrderedVector<t_FMT_Uint16>
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
	CFMT_Uint16Vector() {}

	//! Build an array of uiLength without intializing
	CFMT_Uint16Vector(t_FMT_Uint32 uiLength) : CFMT_OrderedVector(uiLength) {}

	//! Copy constructor
	CFMT_Uint16Vector(const CFMT_Uint16Vector& op) : CFMT_OrderedVector(op) {}

	//! Build an array of uiLength initializing with value
	CFMT_Uint16Vector(t_FMT_Uint32 uiLength, const t_FMT_Uint16& value) : CFMT_OrderedVector(uiLength, value) {}

	//! Build the object from an array of uiLength items
	CFMT_Uint16Vector(t_FMT_Uint16* pVet, t_FMT_Uint32 uiLength) : CFMT_OrderedVector(pVet, uiLength) {}



// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:

	//! Assignment from an homogeneous list
    CFMT_Uint16Vector& operator=(CFMT_Uint16List& op);
    CFMT_Uint16Vector& operator=(CFMT_List<t_FMT_Uint16>& op);

	//! Assignment from an homogeneous vector
    CFMT_Uint16Vector& operator=(const CFMT_Vector<t_FMT_Uint16>& op);
    CFMT_Uint16Vector& operator=(const CFMT_Uint16Vector& op);

};


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_Uint32Vector
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_Uint32Vector : public CFMT_OrderedVector<t_FMT_Uint32>
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
	CFMT_Uint32Vector() {}

	//! Build an array of uiLength without intializing
	CFMT_Uint32Vector(t_FMT_Uint32 uiLength) : CFMT_OrderedVector(uiLength) {}

	//! Copy constructor
	CFMT_Uint32Vector(const CFMT_Uint32Vector& op) : CFMT_OrderedVector(op) {}

	//! Build an array of uiLength initializing with value
	CFMT_Uint32Vector(t_FMT_Uint32 uiLength, const t_FMT_Uint32& value) : CFMT_OrderedVector(uiLength, value) {}

	//! Build the object from an array of uiLength items
	CFMT_Uint32Vector(t_FMT_Uint32* pVet, t_FMT_Uint32 uiLength) : CFMT_OrderedVector(pVet, uiLength) {}


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:

	//! Assignment from an homogeneous list
    CFMT_Uint32Vector& operator=(CFMT_Uint32List& op);
    CFMT_Uint32Vector& operator=(CFMT_List<t_FMT_Uint32>& op);

	//! Assignment from an homogeneous vector
    CFMT_Uint32Vector& operator=(const CFMT_Vector<t_FMT_Uint32>& op);
    CFMT_Uint32Vector& operator=(const CFMT_Uint32Vector& op);
};


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_Uint64Vector
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_Uint64Vector : public CFMT_OrderedVector<t_FMT_Uint64>
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
	CFMT_Uint64Vector() {}

	//! Build an array of uiLength without intializing
	CFMT_Uint64Vector(t_FMT_Uint32 uiLength) : CFMT_OrderedVector(uiLength) {}

	//! Copy constructor
	CFMT_Uint64Vector(const CFMT_Uint64Vector& op) : CFMT_OrderedVector(op) {}

	//! Build an array of uiLength initializing with value
	CFMT_Uint64Vector(t_FMT_Uint32 uiLength, const t_FMT_Uint64& value) : CFMT_OrderedVector(uiLength, value) {}

	//! Build the object from an array of uiLength items
	CFMT_Uint64Vector(t_FMT_Uint64* pVet, t_FMT_Uint32 uiLength) : CFMT_OrderedVector(pVet, uiLength) {}


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:

	//! Assignment from an homogeneous list
    CFMT_Uint64Vector& operator=(CFMT_Uint64List& op);
    CFMT_Uint64Vector& operator=(CFMT_List<t_FMT_Uint64>& op);

	//! Assignment from an homogeneous vector
    CFMT_Uint64Vector& operator=(const CFMT_Vector<t_FMT_Uint64>& op);
    CFMT_Uint64Vector& operator=(const CFMT_Uint64Vector& op);


};




// *************************************************************************************
// *************************************************************************************
//	Class CFMT_Int8Vector
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_Int8Vector : public CFMT_OrderedVector<t_FMT_Int8>
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
	CFMT_Int8Vector() {}

	//! Build an array of uiLength without intializing
	CFMT_Int8Vector(t_FMT_Uint32 uiLength) : CFMT_OrderedVector(uiLength) {}

	//! Copy constructor
	CFMT_Int8Vector(const CFMT_Int8Vector& op) : CFMT_OrderedVector(op) {}

	//! Build an array of uiLength initializing with value
	CFMT_Int8Vector(t_FMT_Uint32 uiLength, const t_FMT_Int8& value) : CFMT_OrderedVector(uiLength, value) {}

	//! Build the object from an array of uiLength items
	CFMT_Int8Vector(t_FMT_Int8* pVet, t_FMT_Uint32 uiLength) : CFMT_OrderedVector(pVet, uiLength) {}



// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:

	//! Assignment from an homogeneous list
    CFMT_Int8Vector& operator=(CFMT_Int8List& op);
    CFMT_Int8Vector& operator=(CFMT_List<t_FMT_Int8>& op);

	//! Assignment from an homogeneous vector
    CFMT_Int8Vector& operator=(const CFMT_Vector<t_FMT_Int8>& op);
    CFMT_Int8Vector& operator=(const CFMT_Int8Vector& op);

};


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_Int16Vector
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_Int16Vector : public CFMT_OrderedVector<t_FMT_Int16>
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
	CFMT_Int16Vector() {}

	//! Build an array of uiLength without intializing
	CFMT_Int16Vector(t_FMT_Uint32 uiLength) : CFMT_OrderedVector(uiLength) {}

	//! Copy constructor
	CFMT_Int16Vector(const CFMT_Int16Vector& op) : CFMT_OrderedVector(op) {}

	//! Build an array of uiLength initializing with value
	CFMT_Int16Vector(t_FMT_Uint32 uiLength, const t_FMT_Int16& value) : CFMT_OrderedVector(uiLength, value) {}

	//! Build the object from an array of uiLength items
	CFMT_Int16Vector(t_FMT_Int16* pVet, t_FMT_Uint32 uiLength) : CFMT_OrderedVector(pVet, uiLength) {}



// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:

	//! Assignment from an homogeneous list
    CFMT_Int16Vector& operator=(CFMT_Int16List& op);
    CFMT_Int16Vector& operator=(CFMT_List<t_FMT_Int16>& op);

	//! Assignment from an homogeneous vector
    CFMT_Int16Vector& operator=(const CFMT_Vector<t_FMT_Int16>& op);
    CFMT_Int16Vector& operator=(const CFMT_Int16Vector& op);

};


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_Int32Vector
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_Int32Vector : public CFMT_OrderedVector<t_FMT_Int32>
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
	CFMT_Int32Vector() {}

	//! Build an array of uiLength without intializing
	CFMT_Int32Vector(t_FMT_Uint32 uiLength) : CFMT_OrderedVector(uiLength) {}

	//! Copy constructor
	CFMT_Int32Vector(const CFMT_Int32Vector& op) : CFMT_OrderedVector(op) {}

	//! Build an array of uiLength initializing with value
	CFMT_Int32Vector(t_FMT_Uint32 uiLength, const t_FMT_Int32& value) : CFMT_OrderedVector(uiLength, value) {}

	//! Build the object from an array of uiLength items
	CFMT_Int32Vector(t_FMT_Int32* pVet, t_FMT_Uint32 uiLength) : CFMT_OrderedVector(pVet, uiLength) {}



// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:

	//! Assignment from an homogeneous list
    CFMT_Int32Vector& operator=(CFMT_Int32List& op);
    CFMT_Int32Vector& operator=(CFMT_List<t_FMT_Int32>& op);

	//! Assignment from an homogeneous vector
    CFMT_Int32Vector& operator=(const CFMT_Vector<t_FMT_Int32>& op);
    CFMT_Int32Vector& operator=(const CFMT_Int32Vector& op);
};


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_Int64Vector
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_Int64Vector : public CFMT_OrderedVector<t_FMT_Int64>
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
	CFMT_Int64Vector() {}

	//! Build an array of uiLength without intializing
	CFMT_Int64Vector(t_FMT_Uint32 uiLength) : CFMT_OrderedVector(uiLength) {}

	//! Copy constructor
	CFMT_Int64Vector(const CFMT_Int64Vector& op) : CFMT_OrderedVector(op) {}

	//! Build an array of uiLength initializing with value
	CFMT_Int64Vector(t_FMT_Uint32 uiLength, const t_FMT_Int64& value) : CFMT_OrderedVector(uiLength, value) {}

	//! Build the object from an array of uiLength items
	CFMT_Int64Vector(t_FMT_Int64* pVet, t_FMT_Uint32 uiLength) : CFMT_OrderedVector(pVet, uiLength) {}



// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:

	//! Assignment from an homogeneous list
    CFMT_Int64Vector& operator=(CFMT_Int64List& op);
    CFMT_Int64Vector& operator=(CFMT_List<t_FMT_Int64>& op);

	//! Assignment from an homogeneous vector
    CFMT_Int64Vector& operator=(const CFMT_Vector<t_FMT_Int64>& op);
    CFMT_Int64Vector& operator=(const CFMT_Int64Vector& op);

};



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_FloatVector
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_FloatVector : public CFMT_OrderedVector<t_FMT_Float>
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
    CFMT_FloatVector() {}

    //! Build an array of uiLength without intializing
    CFMT_FloatVector(t_FMT_Uint32 uiLength) : CFMT_OrderedVector(uiLength) {}

    //! Copy constructor
    CFMT_FloatVector(const CFMT_FloatVector& op) : CFMT_OrderedVector(op) {}

    //! Build an array of uiLength initializing with value
    CFMT_FloatVector(t_FMT_Uint32 uiLength, const t_FMT_Float& value) : CFMT_OrderedVector(uiLength, value) {}

    //! Build the object from an array of uiLength items
    CFMT_FloatVector(t_FMT_Float* pVet, t_FMT_Uint32 uiLength) : CFMT_OrderedVector(pVet, uiLength) {}



// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:

	//! Assignment from an homogeneous list
    CFMT_FloatVector& operator=(CFMT_FloatList& op);
    CFMT_FloatVector& operator=(CFMT_List<t_FMT_Float>& op);

	//! Assignment from an homogeneous vector
    CFMT_FloatVector& operator=(const CFMT_Vector<t_FMT_Float>& op);
    CFMT_FloatVector& operator=(const CFMT_FloatVector& op);

};


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_DoubleVector
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_DoubleVector : public CFMT_OrderedVector<t_FMT_Double>
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
    CFMT_DoubleVector() {}

    //! Build an array of uiLength without intializing
    CFMT_DoubleVector(t_FMT_Uint32 uiLength) : CFMT_OrderedVector(uiLength) {}

    //! Copy constructor
    CFMT_DoubleVector(const CFMT_DoubleVector& op) : CFMT_OrderedVector(op) {}

    //! Build an array of uiLength initializing with value
    CFMT_DoubleVector(t_FMT_Uint32 uiLength, const t_FMT_Double& value) : CFMT_OrderedVector(uiLength, value) {}

    //! Build the object from an array of uiLength items
    CFMT_DoubleVector(t_FMT_Double* pVet, t_FMT_Uint32 uiLength) : CFMT_OrderedVector(pVet, uiLength) {}



// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:

    //! Compute the true RMS of the vector
    t_FMT_Double        GetRMS();

	//! Assignment from an homogeneous list
    CFMT_DoubleVector& operator=(CFMT_DoubleList& op);
    CFMT_DoubleVector& operator=(CFMT_List<t_FMT_Double>& op);

	//! Assignment from an homogeneous vector
    CFMT_DoubleVector& operator=(const CFMT_Vector<t_FMT_Double>& op);
    CFMT_DoubleVector& operator=(const CFMT_DoubleVector& op);
};

#endif







