/**

    DISIT X86
	by Piotr Bania <bania.piotr@gmail.com>
	http://www.piotrbania.com

**/

#ifndef __DISASM_FUNC_H
#define __DISASM_FUNC_H

#include "disit_types.h"

#if defined( _MSC_VER ) && !defined( __cplusplus )
 # define inline __inline
 # define bool BOOL
 # define false FALSE
 # define true TRUE
#endif // defined( _MSC_VER ) && !defined( __cplusplus )



#define		D_SIZE8					1			//byte
#define		D_SIZE16				2			//word
#define		D_SIZE32				4			//dword
#define		D_SIZE48				6			//fword
#define		D_SIZE64				8			//qword
#define		D_SIZE80				10			//tbyte
#define		D_SIZE128				16

#define		D_FPU_SIZE32R			0			// 32 bit real
#define		D_FPU_SIZE32I			1			// 32 bit int
#define		D_FPU_SIZE64R			2			// 64 bit real
#define		D_FPU_SIZE16I			3			// 16 bit int


#define		D_SIBMUL_SIZE2			2
#define		D_SIBMUL_SIZE4			4
#define		D_SIBMUL_SIZE8			8

#define		D_MMX_SIZE8P			0			// 8 bit packed
#define		D_MMX_SIZE16P			1			// 16 bit packed
#define		D_MMX_SIZE32P			2			// 32 bit packed
#define		D_MMX_SIZE64P			3			// 64 bit packed


/* main defines */
#define D_GET_FIELD_EEE(x)			((x >> 3) & 0x07)
#define D_GET_FIELD_FPU_MF(x)		((x >> 1) & 0x03) 
#define D_GET_FIELD_FPU_DBIT(x)		(x & 0x04)
#define D_GET_FILE_MMX_GG(x)		(x & 0x03)
#define D_GET_SIB_SCALE(sib)		((uchar)sib >> 6)
#define D_GET_SIB_INDEX(sib)		(((uchar)sib >> 3) & 0x7)
#define D_GET_SIB_BASE(sib)			((uchar)sib & 0x07)


#define	D_MASK_FLAGS(x)				(x & ~F_ALL)
#define D_SHOW_FLAGS(x)				(x & F_ALL)


#define D_STORE_SELECTOR(sel)		(ddm->mem_imm = (ulong32)sel)




/* inline functions for setting disassembler flags*/
inline void disit_setDF_PrefixREP(ulong32 *dflags)										{ *dflags |= DF_PREFIX_REP;	}
inline void disit_setDF_PrefixLOCK(ulong32 *dflags)										{ *dflags |= DF_PREFIX_LOCK; }
inline void disit_setDF_PrefixSEG(ulong32 *dflags)										{ *dflags |= DF_PREFIX_SEG; }
inline void disit_setDF_PrefixNONE(ulong32 *dflags)										{ *dflags &= ~(DF_PREFIX_SEG|DF_PREFIX_LOCK|DF_PREFIX_REP|DF_OMODE16); }

inline void disit_setDF_OMODE16(ulong32	*dflags)										{ *dflags |= DF_OMODE16; }		// based on the 66h prefix
inline void disit_setDF_AMODE16(ulong32	*dflags)										{ *dflags |= DF_AMODE16; }		// based on the 67h prefix

inline void	disit_setDF_IMM(ulong32 *dflags)											{ *dflags |= DF_IMM; }			 // IMM
inline void disit_setDF_IMM8(ulong32 *dflags)											{ *dflags |= DF_IMM | DF_IMM8; } // IMM8
inline void disit_setDF_IMM16(ulong32 *dflags)											{ *dflags |= DF_IMM | DF_IMM16; } // IMM16

inline void	disit_setDF_MEM_IMM(ulong32 *dflags)										{ *dflags |= DF_MEM_IMM; }			 // MEM_IMM
inline void disit_setDF_MEM_IMM8(ulong32 *dflags)										{ *dflags |= DF_MEM_IMM | DF_MEM_IMM8; } // MEM_IMM8

inline void disit_setDF_MEM_REQ8(ulong32 *dflags)										{ *dflags |= DF_MEM_REQ8; }			// MEM8
inline void disit_setDF_MEM_REQ16(ulong32 *dflags)										{ *dflags |= DF_MEM_REQ16; }		// MEM16
inline void disit_setDF_MEM_REQ32(ulong32 *dflags)										{ *dflags |= DF_MEM_REQ32; }		// MEM32
inline void disit_setDF_MEM_REQ48(ulong32 *dflags)										{ *dflags |= DF_MEM_REQ48; }		// MEM48
inline void disit_setDF_MEM_REQ64(ulong32 *dflags)										{ *dflags |= DF_MEM_REQ64; }		// MEM64
inline void disit_setDF_MEM_REQ80(ulong32 *dflags)										{ *dflags |= DF_MEM_REQ80; }		// MEM80
inline void disit_setDF_MEM_REQ128(ulong32 *dflags)										{ *dflags |= DF_MEM_REQ128; }		// MEM128

inline void disit_setDF_WRITEBIT(ulong32 *dflags)										{ *dflags |= DF_WRITEBIT; } // WRITE BIT
inline void disit_setDF_SIGNEXTBIT(ulong32 *dflags)										{ *dflags |= DF_SIGNEXTBIT; } // SIGN BIT
inline void disit_setDF_USE_WRITEBIT(ulong32 *dflags)									{ *dflags |= DF_USE_WRITEBIT; } // USE WRITE BIT
inline void disit_setDF_USE_SIGNEXTBIT(ulong32 *dflags)									{ *dflags |= DF_USE_SIGNEXTBIT; } //  USE SIGN BIT

inline void disit_setDF_USE_SIB(ulong32 *dflags)										{ *dflags |= DF_USE_SIB; } // USE SIB
inline void disit_setDF_SIBMUL2(ulong32 *dflags)										{ *dflags |= DF_USE_SIB | DF_SIBMUL2; } // SIBMUL2
inline void disit_setDF_SIBMUL4(ulong32 *dflags)										{ *dflags |= DF_USE_SIB | DF_SIBMUL4; } // SIBMUL2
inline void disit_setDF_SIBMUL8(ulong32 *dflags)										{ *dflags |= DF_USE_SIB | DF_SIBMUL8; } // SIBMUL2

inline void disit_setDF_MEM_ACTDEST(ulong32 *dflags)									{ *dflags |= DF_MEM_ACTDEST; }
inline void disit_setDF_MEM_ACTSRC(ulong32 *dflags)										{ *dflags |= DF_MEM_ACTSRC; }

inline void disit_clearDF_MEM_ACT(ulong32 *dflags)										{ *dflags &= ~(DF_MEM_ACTDEST | DF_MEM_ACTSRC); }


/* questioning functions */
inline bool	disit_isDF_PrefixREP(ulong32 dflags)										{ return (dflags & DF_PREFIX_REP) == DF_PREFIX_REP; }
inline bool	disit_isDF_PrefixLOCK(ulong32 dflags)										{ return (dflags & DF_PREFIX_LOCK) == DF_PREFIX_LOCK; }
inline bool	disit_isDF_PrefixSEG(ulong32 dflags)										{ return (dflags & DF_PREFIX_SEG) == DF_PREFIX_SEG; }
inline bool disit_isDF_PrefixANY(ulong32 dflags)										{ return ((dflags & (DF_PREFIX_REP | DF_PREFIX_LOCK | DF_PREFIX_SEG)) != 0); }

inline bool	disit_isDF_OMODE16(ulong32 dflags)											{ return (dflags & DF_OMODE16) == DF_OMODE16; }
inline bool	disit_isDF_AMODE16(ulong32 dflags)											{ return (dflags & DF_AMODE16) == DF_AMODE16; }

inline bool disit_isDF_SIBMUL2(ulong32 dflags)											{ return (dflags & DF_SIBMUL2) == DF_SIBMUL2; }
inline bool disit_isDF_SIBMUL4(ulong32 dflags)											{ return (dflags & DF_SIBMUL4) == DF_SIBMUL4;  } // SIBMUL2
inline bool disit_isDF_SIBMUL8(ulong32 dflags)											{ return (dflags & DF_SIBMUL8) == DF_SIBMUL8; } // SIBMUL2
inline int  disit_getDF_size_SIBMUL(ulong32 dflags)										{ if (disit_isDF_SIBMUL4(dflags)) return D_SIBMUL_SIZE4;	\
																						  if (disit_isDF_SIBMUL8(dflags)) return D_SIBMUL_SIZE8;	\
																						  if (disit_isDF_SIBMUL2(dflags)) return D_SIBMUL_SIZE2;	\
																						  return 0;												\
																						}

inline int disit_getADDR_MODE_SIZE(ulong32 dflags)										{ if (disit_isDF_AMODE16(dflags)) { return D_SIZE16; } else return D_SIZE32; }



inline bool disit_isDF_IMM(ulong32 dflags)												{ return (dflags & DF_IMM) == DF_IMM; }
inline bool disit_isDF_IMM8(ulong32 dflags)												{ return (dflags & DF_IMM8) == DF_IMM8; }
inline bool disit_isDF_IMM16(ulong32 dflags)											{ return (dflags & DF_IMM16) == DF_IMM16; }
inline bool disit_isDF_MEM_IMM(ulong32 dflags)											{ return (dflags & DF_MEM_IMM) == DF_MEM_IMM; }
inline bool disit_isDF_MEM_IMM8(ulong32 dflags)											{ return (dflags & DF_MEM_IMM8) == DF_MEM_IMM8; }

inline bool disit_isDF_MEM_REQ8(ulong32 dflags)											{ return (dflags & DF_MEM_REQ8) == DF_MEM_REQ8; }
inline bool disit_isDF_MEM_REQ16(ulong32 dflags)										{ return (dflags & DF_MEM_REQ16) == DF_MEM_REQ16; }
inline bool disit_isDF_MEM_REQ32(ulong32 dflags)										{ return (dflags & DF_MEM_REQ32) == DF_MEM_REQ32; }
inline bool disit_isDF_MEM_REQ48(ulong32 dflags)										{ return (dflags & DF_MEM_REQ48) == DF_MEM_REQ48; }
inline bool disit_isDF_MEM_REQ64(ulong32 dflags)										{ return (dflags & DF_MEM_REQ64) == DF_MEM_REQ64; }
inline bool disit_isDF_MEM_REQ80(ulong32 dflags)										{ return (dflags & DF_MEM_REQ80) == DF_MEM_REQ80; }
inline bool disit_isDF_MEM_REQ128(ulong32 dflags)										{ return (dflags & DF_MEM_REQ128) == DF_MEM_REQ128; }


inline bool disit_isDF_WRITEBIT(ulong32 dflags)											{ return (dflags & DF_WRITEBIT) == DF_WRITEBIT; }
inline bool disit_isDF_SIGNEXTBIT(ulong32 dflags)										{ return (dflags & DF_SIGNEXTBIT) == DF_SIGNEXTBIT; }
inline bool disit_isDF_USE_WRITEBIT(ulong32 dflags)										{ return (dflags & DF_USE_WRITEBIT) == DF_USE_WRITEBIT; }
inline bool disit_isDF_USE_SIGNEXTBIT(ulong32 dflags)									{ return (dflags & DF_USE_SIGNEXTBIT) == DF_USE_SIGNEXTBIT; }
inline bool disit_is_DF_USE_SIB(ulong32 dflags)											{ return (dflags & DF_USE_SIB) == DF_USE_SIB; }


inline bool	disit_is_DF_IMM_SIGNEXT(ulong32 dflags)										{ return (disit_isDF_USE_SIGNEXTBIT(dflags) && disit_isDF_SIGNEXTBIT(dflags) && disit_isDF_WRITEBIT(dflags)); }	// // Tylko wtedy jest dest jest 16/32 bitowe(w=1) i jest sign extend.

inline bool disit_is_DF_MEM_ACTDEST(ulong32 dflags)										{ return (dflags & DF_MEM_ACTDEST) == DF_MEM_ACTDEST; }
inline bool disit_is_DF_MEM_ACTSRC(ulong32 dflags)										{ return (dflags & DF_MEM_ACTSRC) == DF_MEM_ACTSRC; }
inline bool disit_is_DF_USE_MEM(ulong32 dflags)											{ return (disit_is_DF_MEM_ACTDEST(dflags) || disit_is_DF_MEM_ACTSRC(dflags)); }



inline bool disit_is_AF_IPRIV(uint16 ad_flags)											{ return (ad_flags & IPRIV) == IPRIV; }
inline bool disit_is_AF_IRARE(uint16 ad_flags)											{ return (ad_flags & IRARE) == IRARE; }



// gets IMM object size 
inline int	disit_getDF_size_IMM(ulong32 dflags)									{	if (!disit_isDF_IMM(dflags)) return 0;				\
																						if (disit_isDF_IMM8(dflags)) return D_SIZE8;			\
																						if (disit_isDF_IMM16(dflags)) return D_SIZE16;		\
																						if (disit_isDF_OMODE16(dflags)) return D_SIZE16;		\
																						return D_SIZE32;								\
																					}

// gets MEM IMM object size
inline int	disit_getDF_size_MEM_IMM(ulong32 dflags)								{	if (!disit_isDF_MEM_IMM(dflags)) return 0;			\
																						if (disit_isDF_MEM_IMM8(dflags)) return D_SIZE8;		\
																						if (disit_isDF_AMODE16(dflags)) return D_SIZE16;		\
																						return D_SIZE32;								\
																					}





// gets default operand size by checking the write bit and 66h prefix
inline int	disit_getDF_size_data(ulong32 dflags)									{	if (disit_isDF_USE_WRITEBIT(dflags) && !disit_isDF_WRITEBIT(dflags)) return D_SIZE8;		\
																						if (disit_isDF_OMODE16(dflags)) return D_SIZE16;		\
																						return D_SIZE32;								\
																					}
inline int	disit_getsetDF_size_data(ulong32 *dflags)								{	if (disit_isDF_USE_WRITEBIT(*dflags) && !disit_isDF_WRITEBIT(*dflags)){  disit_setDF_IMM8(dflags); return D_SIZE8; }		\
																						if (disit_isDF_OMODE16(*dflags)) { disit_setDF_IMM16(dflags); return D_SIZE16; }		\
																						return D_SIZE32;								\
																					}



// sets specified IMM size flag, depends on the sign bit. If sign=1 then IMM8 is set
inline int disit_setDF_IMM_SIZE_oSIGN(ulong32 *dflags)								{	if (disit_isDF_USE_SIGNEXTBIT(*dflags) && disit_isDF_SIGNEXTBIT(*dflags))	{ disit_setDF_IMM8(dflags);	return D_SIZE8; } \
																						disit_setDF_IMM(dflags);								\
																						return disit_getsetDF_size_data(dflags);				\
																					} 




// for "int8 reserved" field decoding
inline uint16	disit_getDF_RESERVED_TYPE(uint16 reserved)								{	return ((uint16)(reserved & DF_RESERVED_TYPE_MASK)); }
inline int   disit_getDF_RESERVED_VALUE(uint16 reserved)								{	return ((int)(reserved & DF_RESERVED_VALUE_MASK)); }
inline void disit_setDF_RESERVED_TYPEVALUE(uint16 *reserved, uint16 type, uint16 value)	{	*reserved = type | value; }

inline uint8	disit_get_TTTN(uint16 reserved)												{    return (reserved & 0x0F); }


// for memory request size
inline int	disit_getDF_size_MEM_REQ(ulong32 dflags)								{	if (disit_isDF_MEM_REQ8(dflags))		return D_SIZE8;		\
																						if (disit_isDF_MEM_REQ16(dflags))		return D_SIZE16;	\
																						if (disit_isDF_MEM_REQ32(dflags))		return D_SIZE32;	\
																						if (disit_isDF_MEM_REQ64(dflags))		return D_SIZE64;	\
																						if (disit_isDF_MEM_REQ48(dflags))		return D_SIZE48;	\
																						if (disit_isDF_MEM_REQ80(dflags))		return D_SIZE80;	\
																						if (disit_isDF_MEM_REQ128(dflags))		return D_SIZE128;	\
																						return 0;											\
																					}

// optimize this later using SHL
inline void disit_setDF_size_MEM_REQ(ulong32 *dflags)			{	if (!disit_is_DF_USE_MEM(*dflags))	return;							\
																	if (*dflags & DF_MEM_REQALL) return;					\
																	if (disit_getDF_size_data(*dflags)==D_SIZE8) disit_setDF_MEM_REQ8(dflags);			\
																	else if (disit_getDF_size_data(*dflags)==D_SIZE16) disit_setDF_MEM_REQ16(dflags);	\
																	else if (disit_getDF_size_data(*dflags)==D_SIZE32) disit_setDF_MEM_REQ32(dflags);	\
																}
															


// fpu
inline void	disit_setDF_FPU_DBIT(ulong32 *dflags)											{ *dflags |= DF_FPU_DBIT; }			 // FPU D BIT SET
inline void	disit_setDF_FPU_RBIT(ulong32 *dflags)											{ *dflags |= DF_FPU_RBIT; }			 // FPU R BIT SET
inline void disit_setDF_FPU_MEM_REAL(ulong32 *dflags)										{ *dflags |= DF_FPU_MEM_REAL; }		 // FPU mem real


inline bool disit_isDF_FPU_DBIT(ulong32 dflags)												{ return (dflags & DF_FPU_DBIT) == DF_FPU_DBIT; }
inline bool disit_isDF_FPU_RBIT(ulong32 dflags)												{ return (dflags & DF_FPU_RBIT) == DF_FPU_RBIT; }
inline bool disit_isDF_FPU_MEM_REAL(ulong32 dflags)											{ return (dflags & DF_FPU_MEM_REAL) == DF_FPU_MEM_REAL; }








//disit_text.cpp
int disit_show_object(ulong64 obj, char *out);
int disit_show_itext(char *out, _dis_data *dd);
ulong64 disit_getsingleobj(ulong64 obj);


inline bool			disit_isOBJ(ulong64 obj_bits, ulong64 desired_obj)		{	return (obj_bits & desired_obj) == desired_obj; }
inline bool			disit_isOBJ32(ulong32 obj_bits, ulong32 desired_obj)	{	return (obj_bits & desired_obj) == desired_obj; }
inline void			disit_clearOBJ(ulong32 *obj_bits, ulong32 obj_to_clear)	{	*obj_bits &= ~(obj_to_clear); }


inline ulong32		disit_getDF_PREFIX(ulong32 dflags)						{	return (dflags & (DF_PREFIX_REP | DF_PREFIX_LOCK | DF_PREFIX_SEG)); }







#endif