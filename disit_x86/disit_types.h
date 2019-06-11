/**

    DISIT X86
	by Piotr Bania <bania.piotr@gmail.com>
	http://www.piotrbania.com

**/


#ifndef __DISASM_TYPES_H
#define __DISASM_TYPES_H

#define inline __inline

//#ifndef _NO_PARENT_
typedef	unsigned	__int8		uint8, uchar;
typedef				char		int8;
//#endif

typedef	unsigned	__int16		uint16, uword;
typedef	signed		__int16		int16;
typedef unsigned	__int32		ulong32;
typedef signed		__int32		long32, int32;
typedef unsigned	__int64		ulong64;
typedef signed		__int64		long64, int64;


// Special flags for "uint16		reserved" field (TTTN, SREG) entries
// First 4 bits are reserved for TTTN's etc. etc.
#define DF_RESERVED_TTTN		(1 << 4)
#define DF_RESERVED_SREG3		(2 << 4)
#define DF_RESERVED_SREG2		(2 << 4)
#define	DF_RESERVED_REG_CL		(3 << 4)
#define DF_RESERVED_REG_CRX		(4 << 4)		// mutinstruction is using the CRx registers
#define DF_RESERVED_REG_DRX		(5 << 4)		// mutinstruction is using the DRx registers
#define DF_RESERVED_SEG_ES		(6 << 4)	
#define DF_RESERVED_SEG_CS		(7 << 4)	
#define DF_RESERVED_SEG_SS		(8 << 4)	
#define DF_RESERVED_SEG_DS		(9 << 4)	
#define DF_RESERVED_SEG_FS		(10 << 4)	
#define DF_RESERVED_SEG_GS		(10 << 4)	
#define DF_RESERVED_SELECTOR	(11 << 4)		// the 16bit selector is written in mem_imm
#define DF_RESERVED_SELECTOR8	(11 << 4)		// the 8bit selector is written in mem_imm
#define DF_RESERVED_JTTTN		(12 << 4)	
#define DF_RESERVED_MMX_GG		(13 << 4)		// MMX GG bit value for name uncoding

#define DF_RESERVED_TYPE_MASK	(int8)0xFFF0
#define	DF_RESERVED_VALUE_MASK	(int8)0x000F



// Special disassembler flags
#define	DF_SIBMUL2		(ulong)0x00000001
#define	DF_SIBMUL4		(ulong)0x00000002
#define DF_SIBMUL8		(ulong)0x00000004
#define DF_USE_SIB		(ulong)0x00000008

#define	DF_MEM_ACTDEST	(ulong)0x00000010		// [mem] is dest
#define DF_MEM_ACTSRC	(ulong)0x00000020		// [mem] is src
												// remember if both of those ACT modes are set the ACTDEST is has the priority (it means the [mem] is the first arg)

#define	DF_OMODE16		(ulong)0x00000040		// operand 16bit mode? relies on 66h prefix
#define	DF_AMODE16		(ulong)0x00000080		// addressing 16 bit mode? relies on 67h prefix

#define DF_MEM_IMM		(ulong)0x00000100		// there is an mem IMM i.e [IMM]
#define DF_MEM_IMM8		(ulong)0x00000200		// there is mem IMM which is 8bit long (commes together with the upper flag)

												// memory request size mov reg,byte ptr [] etc. etc.
#define DF_MEM_REQ8		(ulong)0x00000400		// byte
#define DF_MEM_REQ16	(ulong)0x00000800		// word
#define DF_MEM_REQ32	(ulong)0x00001000		// dword
#define DF_MEM_REQ48	(ulong)0x00002000		// fword
#define DF_MEM_REQ64	(ulong)0x00004000		// qword
#define DF_MEM_REQ80	(ulong)0x00008000		// tbyte
#define DF_MEM_REQ128	(ulong)0x00010000		// 
#define	DF_MEM_REQALL	(ulong)(DF_MEM_REQ8|DF_MEM_REQ16|DF_MEM_REQ32|DF_MEM_REQ48|DF_MEM_REQ64|DF_MEM_REQ80|DF_MEM_REQ128)

#define	DF_IMM			(ulong)0x00020000		// there is an IMM (16bit or 32bit) depends on 66h prefix
#define DF_IMM8			(ulong)0x00040000		// there is an IMM which is 8bits long (overwrides the prev. one)
#define DF_IMM16		(ulong)0x00080000		// there is an IMM which is 16bit long (!SPECIAL!)


//#define DF_IMM8			(ulong)0x00000200		// there is a normal IMM - 8 bit size
//#define DF_IMM16		(ulong)0x00000400		// there is a normal IMM - 16bit size  ---those two could be marked as one and decoded appending to the DF_MODE16
//#define DF_IMM32		(ulong)0x00000800		// there is a normal IMM - 32bit size  -/

#define DF_PREFIX_REP		(ulong)0x00100000		// REP prefix found
#define	DF_PREFIX_LOCK		(ulong)0x00200000		// LOCK prefix found
#define	DF_PREFIX_SEG		(ulong)0x00400000		// SEG prefix found

#define	DF_SIGNEXTBIT		(ulong)0x00800000		// sign extension (relies on S bit), if ON 8bit is extended to 16or32
#define DF_WRITEBIT			(ulong)0x01000000		// write bit if 0, ((8bit->16bit) | (8bit->32bit))
#define DF_USE_SIGNEXTBIT	(ulong)0x02000000		// are we allowed to use it
#define DF_USE_WRITEBIT		(ulong)0x04000000		// are we allowed to use it

#define	DF_FPU_DBIT			(ulong)0x08000000		// destination bit set for FPU mutinstruction 
#define DF_FPU_RBIT			(ulong)0x10000000		// R bit set for FPU mutinstruction
#define	DF_FPU_MEM_REAL		(ulong)0x20000000		// Memory as REAL if set/ Memory as INT if not set



// X86 REGISTERS 
#define R_AL			(ulong64)0x00000001
#define R_AH			(ulong64)0x00000002
#define R_AX			(ulong64)0x00000003
#define R_EAX			(ulong64)0x0000000F
#define R_CL			(ulong64)0x00000010
#define R_CH			(ulong64)0x00000020
#define R_CX			(ulong64)0x00000030
#define R_ECX			(ulong64)0x000000F0
#define R_DL			(ulong64)0x00000100
#define R_DH			(ulong64)0x00000200
#define R_DX			(ulong64)0x00000300
#define R_EDX			(ulong64)0x00000F00
#define R_BL			(ulong64)0x00001000
#define R_BH			(ulong64)0x00002000
#define R_BX			(ulong64)0x00003000
#define R_EBX			(ulong64)0x0000F000
#define R_SP			(ulong64)0x00010000
#define R_ESP			(ulong64)0x00030000
#define R_BP			(ulong64)0x00100000
#define R_EBP			(ulong64)0x00300000
#define R_SI			(ulong64)0x01000000
#define R_ESI			(ulong64)0x03000000
#define R_DI			(ulong64)0x10000000
#define R_EDI			(ulong64)0x30000000
#define R_ALL16			(ulong64)0x11113333
#define R_ALL32			(ulong64)0x3333FFFF

//X86 XMM 128bit MEDIA REGISTERS
#define	R_XMM0			(ulong64)0x0000000100000000
#define	R_XMM1			(ulong64)0x0000000200000000
#define	R_XMM2			(ulong64)0x0000000400000000
#define	R_XMM3			(ulong64)0x0000000800000000
#define	R_XMM4			(ulong64)0x0000001000000000
#define	R_XMM5			(ulong64)0x0000002000000000
#define	R_XMM6			(ulong64)0x0000004000000000
#define	R_XMM7			(ulong64)0x0000008000000000

// assume: MMX0=FPR0 etc.
#define	R_MMX0			(ulong64)0x0000010000000000
#define	R_MMX1			(ulong64)0x0000020000000000
#define	R_MMX2			(ulong64)0x0000040000000000
#define	R_MMX3			(ulong64)0x0000080000000000
#define	R_MMX4			(ulong64)0x0000100000000000
#define	R_MMX5			(ulong64)0x0000200000000000
#define	R_MMX6			(ulong64)0x0000400000000000
#define	R_MMX7			(ulong64)0x0000800000000000

#define	R_ST0			R_MMX0
#define	R_ST1			R_MMX1
#define	R_ST2			R_MMX2
#define	R_ST3			R_MMX3
#define	R_ST4			R_MMX4
#define	R_ST5			R_MMX5
#define	R_ST6			R_MMX6
#define	R_ST7			R_MMX7

#define R_ALL_ST		(R_ST0 | R_ST1 | R_ST2 | R_ST3 | R_ST4 | R_ST5 | R_ST6 | R_ST7)
#define R_ALL_MMX		(R_MMX0 | R_MMX1 | R_MMX2 | R_MMX3 | R_MMX4 | R_MMX5 | R_MMX6 | R_MMX7)
#define R_ALL_XMM		(R_XMM0 | R_XMM1 | R_XMM2 | R_XMM3 | R_XMM4 | R_XMM5 | R_XMM6 | R_XMM7)

//CR0-DR0 are not needed for the future tracing process anyway
//because DR4/DR5/CR5/CR6/CR7 are reserved the actuall name
//decoding will be done by using also the reserved field
//which will have the 3bits describin the EEE field.

#define	R_DR0			(ulong64)0x0001000000000000			
#define	R_DR1			(ulong64)0x0002000000000000
#define	R_DR2			(ulong64)0x0004000000000000
#define	R_DR3			(ulong64)0x0008000000000000
#define	R_DR6			(ulong64)0x0010000000000000
#define	R_DR7			(ulong64)0x0020000000000000
#define	R_CR0			(ulong64)0x0040000000000000
#define	R_CR2			(ulong64)0x0080000000000000
#define	R_CR3			(ulong64)0x0100000000000000
#define	R_CR4			(ulong64)0x0200000000000000

// flags, only Status Flags and Control flags will be written (no System Flags)
#define F_DIRECTION		(ulong64)0x0000000000040000
#define F_CARRY			(ulong64)0x0000000000080000
#define F_PARITY		(ulong64)0x0000000000400000
#define F_AUXILIARY		(ulong64)0x0000000000800000
#define F_ZERO			(ulong64)0x0000000004000000
#define F_SIGN			(ulong64)0x0000000008000000
#define F_OVERFLOW		(ulong64)0x0000000040000000


#define	F_TRAP			(ulong64)0x0400000000000000
#define	F_INTERRUPT		(ulong64)0x0800000000000000
#define	F_IOPL			(ulong64)0x1000000000000000
#define	F_NT			(ulong64)0x2000000000000000
#define	F_RESUME		(ulong64)0x4000000000000000
#define	F_VM			(ulong64)0x8000000000000000



#define F_ALL			(ulong64)(F_CARRY | F_PARITY | F_AUXILIARY | F_ZERO | F_SIGN | F_OVERFLOW | F_DIRECTION | \
								  F_TRAP | F_INTERRUPT | F_IOPL | F_NT | F_RESUME | F_VM)

#define	F_ALL_UM		(ulong64)(F_CARRY | F_PARITY | F_AUXILIARY | F_ZERO | F_SIGN | F_OVERFLOW | F_DIRECTION)


// just a copy

#define AF			F_AUXILIARY
#define CF			F_CARRY
#define OF			F_OVERFLOW
#define SF			F_SIGN	
#define ZF			F_ZERO
#define PF			F_PARITY
#define DF			F_DIRECTION
#define IF			F_INTERRUPT
#define RF			F_RESUME
#define TF			F_TRAP
#define NTF			F_NT
#define IOPLF		F_IOPL
#define VMF			F_VM
#define ALL_FLAGS	F_ALL
#define ALL_FLAGS_UM F_ALL_UM



// ------------------------------

#define		SEG_ES 0
#define		SEG_CS 1
#define		SEG_SS 2
#define		SEG_DS 3
#define		SEG_FS 4
#define		SEG_GS 5



#define RR_AL		0
#define RR_CL		1
#define RR_DL		2
#define RR_BL		3
#define RR_AH		4
#define RR_CH		5
#define RR_DH		6
#define RR_BH		7
#define RR_AX		0
#define RR_CX		1
#define RR_DX		2
#define RR_BX		3
#define RR_SP		4
#define RR_BP		5
#define RR_SI		6
#define RR_DI		7
#define RR_EAX		0
#define RR_ECX		1
#define RR_EDX		2
#define RR_EBX		3
#define RR_ESP		4
#define RR_EBP		5
#define RR_ESI		6
#define RR_EDI		7





#endif