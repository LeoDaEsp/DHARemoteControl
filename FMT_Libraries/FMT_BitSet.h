// =====================================================================================
/**
 * @file					FMT_BitSet.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					09/03/2018
 * @brief					Set of bits object
 *
 * @version	Project:		Formatech C++ Core Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][09/03/2018]
 */
// =====================================================================================



#ifndef FMTDEF_BITSET_H
#define FMTDEF_BITSET_H

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

#ifndef FMTDEF_STRING_H
#include "FMT_String.h"
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



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_BitSet
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_BitSet : public CFMT_Object
{
    // =====================================================================================
    //	TYPES
    // =====================================================================================

public:

    //! Bit management
    class FMTDEF_LIB_DLLSPEC CBit
    {
    public:

        //! Bit position
        t_FMT_Uint32			m_uiBit;

        //! Related object
        CFMT_BitSet             *m_pInt;

        //! Empty constructor
        CBit();

        //! Copy constructor
        CBit(const CBit& op);

        //! t_FMT_Bool casting operator
        operator		t_FMT_Bool() const;

        //! Assignment operator from t_FMT_Bool
        const CBit&     operator=(const t_FMT_Bool& bOp);

        //! Assignment operator from CBit
        CBit&			operator=(const CBit& op);
    };


    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:

    //! Number of bits
    t_FMT_Uint32			m_uiNumBits;

    //! Number of words
    t_FMT_Uint32			m_uiNumWords;

    //! Data words
    t_FMT_Uint64			*m_pquiWords;


public:


// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Empty constructor
    CFMT_BitSet();

    //! Constructor with provided size
    CFMT_BitSet(t_FMT_Uint32 uiNumBits, t_FMT_Bool bValue);

    //! Copy constructor
    CFMT_BitSet(const CFMT_BitSet& op);

    //! Destructor
    virtual ~CFMT_BitSet();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

    //! Copy from an homogeneous object
    void                    DataCopy(const CFMT_BitSet& op);

    //! Create object word buffer of size uiWords
    static t_FMT_Uint32     GetNumWords(t_FMT_Uint32 uiBits);

    //! Return the number of words to manage uiBits
    void                    CreateWords(t_FMT_Uint32 uiWords);

    //! Destroy the object
    void                    Destroy();

    //! Set all words to 0
    void                    Reset();

    //! Set the bit of position uiIdx with bValue without checking
    inline void				UnsafeSetBit(const t_FMT_Uint32 uiIdx,t_FMT_Bool bValue);

    //! Return the bit of uiIdx position without checking
    inline t_FMT_Bool		UnsafeGetBit(const t_FMT_Uint32 uiIdx) const;

public:

    // Properties ------------------------------------

    //! Return FMTDEF_TRUE if the object is valid
    t_FMT_Bool              IsValid() const;

    //! Get number of bits
    t_FMT_Uint32			GetNumBits() const;

    // Building --------------------------------------

    //! Set number of bits
    void					SetNumBits(t_FMT_Uint32 uiNumBits);

    // Assignment ------------------------------------

    //! Assignment operator from homogeneous object
    CFMT_BitSet&            operator=(const CFMT_BitSet& op);

    //! Assignment operator from unsigned integer
    CFMT_BitSet&            operator=(const t_FMT_Uint64& op);

    //! Fill the set with the same value and return a reference to it
    CFMT_BitSet&            Fill(t_FMT_Bool bValue);

    //! Fill uiSize bits with b value from uiStart bit and return a reference to it
    CFMT_BitSet&			Fill(t_FMT_Uint32 uiStart, t_FMT_Uint32 uiSize, t_FMT_Bool b);

    //! Join the object with another bit set to the left
    CFMT_BitSet             Join(const CFMT_BitSet& op);

    //! Merge the object with another bit set to the left or to the right
    CFMT_BitSet&            Merge(const CFMT_BitSet& op, t_FMT_Bool bFromLeft = FMTDEF_FALSE);

    // Data access ------------------------------------------------

    //! Return/Set the bit of uiIdx position
    CBit                    operator[](const t_FMT_Uint32& uiIdx);

    //! Set the bit of position uiIdx with bValue
    void					SetBit(const t_FMT_Uint32 uiIdx, t_FMT_Bool bValue);

    //! Return the bit of uiIdx position
    t_FMT_Bool				GetBit(const t_FMT_Uint32 uiIdx);

    //! Set the raw buffer of object with the buffer pucData of size uiSize and order uiByteOrder and return a reference to it
    CFMT_BitSet&			SetRawByteBuffer(t_FMT_Uint8* pbtData, t_FMT_Uint32 uiSize, FMT::t_ByteOrdering uiByteOrder = FMT::e_ByteOrdering_LittleEndian);

    //! Extract the raw buffer of object to the buffer pucData of size uiSize and order uiByteOrder
    void					GetRawByteBuffer(t_FMT_Uint8* pbtData, t_FMT_Uint32 uiSize, FMT::t_ByteOrdering uiByteOrder = FMT::e_ByteOrdering_LittleEndian);

    //! Extract a subset of bits from uiStart bit of size uiSize
    CFMT_BitSet             GetField(t_FMT_Uint32 uiStart, t_FMT_Uint32 uiSize);

    //! Extract a subset of bits from uiStart bit of size uiSize as unsigned integer
    t_FMT_Uint64            GetFieldUnsigned(t_FMT_Uint32 uiStart, t_FMT_Uint32 uiSize);

    //! Return value into unsigned integer
    t_FMT_Uint64            ToUnsigned();

    //! Set a subset of bits from uiStart bit of size uiSize from a homogeneous object and return a reference to it
    CFMT_BitSet&            SetField(t_FMT_Uint32 uiPos, t_FMT_Uint32 uiSize, const CFMT_BitSet& field);

    //! Set a subset of bits from uiStart bit of size uiSize from unsigned and return a reference to it
    CFMT_BitSet&            SetFieldUnsigned(t_FMT_Uint32 uiPos, t_FMT_Uint32 uiSize, const t_FMT_Uint64& field);


    // Boolean operators ----------------------------------------------

    //! Unary complement
    CFMT_BitSet             operator~();

    //! Bitwise AND
    CFMT_BitSet             operator&(const CFMT_BitSet& op);

    //! Bitwise AND
    CFMT_BitSet&            operator&=(const CFMT_BitSet& op);

    //! Bitwise OR
    CFMT_BitSet             operator|(const CFMT_BitSet& op);

    //! Bitwise OR
    CFMT_BitSet&            operator|=(const CFMT_BitSet& op);

    //! Bitwise XOR
    CFMT_BitSet             operator^(const CFMT_BitSet& op);

    //! Bitwise XOR
    CFMT_BitSet&            operator^=(const CFMT_BitSet& op);

    //! Compute the XOR of all bits
    t_FMT_Bool              Xor();

    //! Compute the OR of all bits
    t_FMT_Bool              Or();

    // Compute the AND of all bits
    t_FMT_Bool              And();

    //! Left shift of uiBits bits
    CFMT_BitSet             operator<<(const t_FMT_Uint32& uiBits);

    //! Left shift of uiBits bits
    CFMT_BitSet&			operator<<=(const t_FMT_Uint32& uiBits);

    //! Right shift of uiBits bits
    CFMT_BitSet             operator>>(const t_FMT_Uint32& uiBits);

    //! Right shift of uiBits bits
    CFMT_BitSet&    		operator>>=(const t_FMT_Uint32& uiBits);


	// Comparison -------------------------------------

    //! Compare two bitsets
    static t_FMT_Int8       Compare(const CFMT_BitSet& op1, const CFMT_BitSet& op2);

    //! Compare the object to another
    t_FMT_Int8              Compare(const CFMT_BitSet& op) const;

    //! Check if the object is equal to bit set op
    t_FMT_Bool              operator==(const CFMT_BitSet& op);

    //! Check if the object is equal to unsigned op
    t_FMT_Bool              operator==(const t_FMT_Uint64& op);

    //! Check if the object is not equal to bit set op
    t_FMT_Bool              operator!=(const CFMT_BitSet& op);

    //! Check if the object is not equal to unsigned op
    t_FMT_Bool              operator!=(const t_FMT_Uint64& op);

    //! Check if the object is greater or equal to bit set op
    t_FMT_Bool              operator>=(const CFMT_BitSet& op);

    //! Check if the object is greater or equal to unsigned op
    t_FMT_Bool              operator>=(const t_FMT_Uint64& op);

    //! Check if the object is greater to bit set op
    t_FMT_Bool              operator>(const CFMT_BitSet& op);

    //! Check if the object is greater to unsigned op
    t_FMT_Bool              operator>(const t_FMT_Uint64& op);

    //! Check if the object is less or equal to bit set op
    t_FMT_Bool              operator<=(const CFMT_BitSet& op);

    //! Check if the object is less or equal to unsigned op
    t_FMT_Bool              operator<=(const t_FMT_Uint64& op);

    //! Check if the object is less to bit set op
    t_FMT_Bool              operator<(const CFMT_BitSet& op);

    //! Check if the object is less to unsigned op
    t_FMT_Bool              operator<(const t_FMT_Uint64& op);


    // Conversion -------------------------------------

    //!	Converts the set to a string in the specified base
    CFMT_String             ToString(t_FMT_Uint32 uiBase, t_FMT_Uint32 uiSepStep = 0, t_FMT_Char ucSep = '.');


    // Serialization ----------------------------------

    //! Serializes a bit set into the buffer
    friend CFMT_Buffer&     operator<<(CFMT_Buffer& buf, CFMT_BitSet& bs);

    //! Serializes a bit set from the buffer
    friend CFMT_Buffer&     operator>>(CFMT_Buffer& buf, CFMT_BitSet& bs);

};



class CFMT_BitSetVector;

// *************************************************************************************
// *************************************************************************************
//	Class CFMT_BitSetList
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_BitSetList : public CFMT_List<CFMT_BitSet>
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
    CFMT_BitSetList() {}

    //! Build a list of uiLength items with initialization value tValue
    CFMT_BitSetList(t_FMT_Uint32 uiLength, const CFMT_BitSet& tValue) : CFMT_List(uiLength, tValue) {}

    //! Copy constructor
    CFMT_BitSetList(const CFMT_BitSetList& list) : CFMT_List(list) {}

    //! Build the list from an array
    CFMT_BitSetList(CFMT_BitSet* pVet, t_FMT_Uint32 uiLength) : CFMT_List(pVet, uiLength) {}


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

public:

    //! Sort the list
    CFMT_BitSetList&        Sort(t_FMT_Bool bOrder);

	//! Assignment from an homogeneous list
    CFMT_BitSetList& operator=(const CFMT_BitSetList& op);
    CFMT_BitSetList& operator=(const CFMT_List<CFMT_BitSet>& op);

	//! Assignment from an homogeneous vector
    CFMT_BitSetList& operator=(CFMT_Vector<CFMT_BitSet>& op);
    CFMT_BitSetList& operator=(CFMT_BitSetVector& op);
};




// *************************************************************************************
// *************************************************************************************
//	Class CFMT_BitSetVector
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_BitSetVector : public CFMT_Vector<CFMT_BitSet>
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
    CFMT_BitSetVector() {}

    //! Build an array of uiLength without intializing
    CFMT_BitSetVector(t_FMT_Uint32 uiLength) : CFMT_Vector(uiLength) {}

    //! Copy constructor
    CFMT_BitSetVector(const CFMT_BitSetVector& op) : CFMT_Vector(op) {}

    //! Build an array of uiLength initializing with value
    CFMT_BitSetVector(t_FMT_Uint32 uiLength, const CFMT_BitSet& value) : CFMT_Vector(uiLength, value) {}

    //! Build the object from an array of uiLength items
    CFMT_BitSetVector(CFMT_BitSet* pVet, t_FMT_Uint32 uiLength) : CFMT_Vector(pVet, uiLength) {}



// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

public:

    //! Sort the vector
    CFMT_BitSetVector&    Sort(t_FMT_Bool bOrder);

	//! Assignment from an homogeneous list
    CFMT_BitSetVector& operator=(CFMT_BitSetList& op);
    CFMT_BitSetVector& operator=(CFMT_List<CFMT_BitSet>& op);

	//! Assignment from an homogeneous vector
    CFMT_BitSetVector& operator=(const CFMT_Vector<CFMT_BitSet>& op);
    CFMT_BitSetVector& operator=(const CFMT_BitSetVector& op);


};



#endif







