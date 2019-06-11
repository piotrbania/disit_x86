/**

    DISIT X86
	by Piotr Bania <bania.piotr@gmail.com>
	http://www.piotrbania.com

**/


#ifndef __DISASM_H
#define __DISASM_H

#include "disit_types.h"


#define	MAX_PREFIXES  4


#define USE_CRS       1
#define USE_DRS       2
#define USE_SREG      3


#define	D_TTTN_JO		0
#define	D_TTTN_JNO		1
#define	D_TTTN_JB		2
#define	D_TTTN_JNB		3
#define	D_TTTN_JE		4
#define	D_TTTN_JNE		5
#define	D_TTTN_JBE		6
#define	D_TTTN_JNBE		7
#define	D_TTTN_JS		8
#define	D_TTTN_JNS		9
#define	D_TTTN_JP		10
#define	D_TTTN_JNP		11
#define	D_TTTN_JL		12
#define	D_TTTN_JNL		13
#define	D_TTTN_JLE		14
#define	D_TTTN_JNLE		15




/* flags - AF | CF | OF | SF | ZF | PF | DF | IF*/

/*
#define NNN	0
#define EX_FLAGS	0			// not supported (ring0)
#define AF			0x01
#define CF			0x02
#define OF			0x04
#define SF			0x08
#define ZF			0x10
#define PF			0x20
#define DF			0x40
#define IF			0x80
#define ALL_FLAGS	AF | CF | OF | SF | ZF | PF | DF | IF | EX_FLAGS
*/


/* special bits */
// dont change the values
#define WW				0x0001            // Bit W
#define SS				0x0002            // Bit S
#define WS				0x0003            // Bits W and S
#define NA				0x0004            // Name depends on size
#define W3				0x0008            // Bit W at position 3
#define BM				0x0010			   // The mem operand which is DEST, should be considered also as SRC
									   // for mutinstruction like or [mem]/and [mem]/xor [mem] but not mov [mem]
#define	EX_DIV			0x0020				// special flag for I/DIV
#define EX_MUL			0x0040				// special flag for I/MUL

#define	FPU_DBIT		0x0080				// FPU D BIT present
#define	FPU_RBIT		0x0100				// FPU D BIT present
#define MMX_GG			0x0200				// MMX Granularity

#define IPRIV			0x0400				// Requires priviledges
#define IRARE			0x0800				// Rare mutinstructions
#define ISSE			0x1000 
#define ISSE4			0x2000

//#define DD             0x02			   // Operation Direction Bit

#define NNN            0               // No operand
#define MDR1           1			   // Register in field 1
#define MDR2           2               // Register in field 2 
#define MDR1R          3               // Register in field 1 (now source)
#define MDR2R          4               // Register in field 2 (now dest)
#define ACC            5               // Accumulator
#define IMM            6               // Immediate data
#define MM1            7               // Memory as dest
#define MM2            8               // Memory as src
#define IMMS		   9               // IMM after SIB (possible)
#define IMMC           10              // Immediate directly after op
#define MDR1R_16       11			   // Register in field 1 (16 bit super mode)
#define MDR2R_16       12              // Register in field 2 (16 bit super mode)
#define MM1_16		   13              // Memory (16 bit request)
#define MM2_E          14              // Extended mem (BOUND etc.)
#define IMM8           15              // 8 Bit Immediate
#define IMM16          16              // 16 Bit Immediate
#define IMM8S          17              // 8 Bit Immediate possible after SIB
#define IMM32C         18              // 32 Bit Immediate for call
#define IMM_SEL        19              // Selector (calls etc.)
#define MM2CE          20              // Memory source extended (CALLs)
#define MDR2_A         21              // Reg in field 2 (alternate)
#define IMM8E          22              // 8 Bit Immediate (ENTER style)
#define IMM_SEL_E      23              // Selector (ENTER)
#define IMMI           24              // Special for IMMuls
#define IMM8C          25              // 8 Bit Immediate directly after op
#define REG_DX         26              // REG EDX
#define JTTTN          27              // Jump decoding (tttn fields)
#define IMM32          28              // Immediate 32 bits (FULL)
#define IMM8CN         29              // 8 Bit immediate directly after op
#define MM2_EF         30              // Memory extended (LSF)
#define MDR1_16        31              // 16 bit reg
#define MDR2_16        32              // 16 bit reg
#define ACCR           33              // Acumulator as dest
#define MM1_FD         34              // Mem Full disp
#define MM2_FD         35              // Mem Full disp
#define CRX            36              // CR register
#define DRX            37              // DR register
#define SREG3          38              // SREG3 field
#define SREG2          39              // SREG2 field
#define IMM1           40              // Immediate - value = 1
#define REG_CL         41              // CL register
#define IMM16C         42              // 16 Bit immediate directly after op
#define MDR2R_8        43              // 8 Bit REG
#define JTTTNS         44              // JTTTNS for SETXX
#define MM2R_8         45              // 8 Bit MEM
#define IMMI8          46              // Immediate 8 (special)
#define REG_CL_I       47              // CL (flags update required, SHLD etc.)
#define MDR2_8		   48              // 8 Bit reg
#define MM_8		   49              // byte ptr [mem]
#define MM_16		   50			   // word ptr [mem]
#define MDR2_AA		   51			   // alternate register encoding (XCHG)
#define	DRXR		   52			   // DR register as source
#define CRXR		   53			   // CR register as dest
#define FPU_MEM		   54			   // FPU MEMORY
#define	FPU_REG		   55			   // FPU REGISTER
#define FPU_MEM80S	   56			   // 80 bit mem request as source
#define FPU_MEM80D	   57			   // 80 bit mem request as dest
#define FPU_MEM16S	   59			   // 
#define FPU_MEM32S	   60			   // 
#define FPU_MEM64S	   61			   // 
#define FPU_MEM16D	   62			   // 
#define FPU_MEM32D	   63			   // 
#define FPU_MEM64D	   64			   // 
#define MMX_MEMS	   65			   // MMX memory as source, size based on GG
#define MMX_MEMD	   66			   // MMX memory as dest, size based on GG
#define MMX_REG1S	   67			   // MMX register source
#define MMX_REG1D	   68			   // MMX register dest
#define MMX_REG2S	   69			  
#define MMX_REG2D	   70			  
#define MMX_MEM64S	   FPU_MEM64S	   // MMX mem 64 as source



#define XMM_REG1S	   71			   // XMM reg as source
#define XMM_REG1D	   72			   // XMM reg as dest
#define XMM_REG2S	   73			   // XMM reg as src
#define XMM_REG2D	   74			   // XMM reg as dest
#define XMM_MEM128S	   75			   // 128 bit mem source
#define XMM_MEM128D	   76			   // 128 bit mem dest
#define C_MMX_CMP	   77				// no dest, src|=old_dest


/* special flags */ 

#define   C_NNN        0            // Ordinary mutinstruction
#define   C_D2S        1            // Dest regs are Src regs
#define   C_S2D        2            // Src regs are Dest regs
#define   C_D2SN       3            // Dest to Source, then Dest = 0
#define   C_D2S_DEAX   4            // Src|=Dest, Dest|=EAX
#define	  C_D2S_NN     5           // Src |= Dest, Dest unchagned
#define   C_DS_ESP_N   6           // Dest |= ESP | Src |= old_DEST | ESP
#define   C_S_CL_N     7           // SRC: CL | Src |= Dest
#define	  C_SND_MEM	   8			// MEM is only source / NO MEM as DEST
#define	  C_FPU_CMP    9			// no dest
#define	  C_S_MEM	   10			// mem is source too
#define	  C_DOS		   11			// dest|=src; src|=dest; for XCHG
#define	  C_DOSM	   12			// dest|=src; MEM is dest and source for XCHG

/* some str flags */
#define F_CALL			1			// call flag
#define F_JMP			2			// jump flag
#define F_ENTER         3           // enter flag
#define F_SETXX         4           // set flag
#define F_SHL3          5           // shls (3 params)


#define MEM_ACT_DEST	0			// mem is dest
#define MEM_ACT_SOURCE	1			// mem is source

typedef unsigned char  uchar;          // Unsigned character (byte)
typedef unsigned	__int16 ushort;         // Unsigned short
typedef unsigned	__int32  uint;           // Unsigned integer
typedef unsigned	long ulong;          // Unsigned long
typedef unsigned	__int16	uword;



// this struct is pretty similiar to the one Oleh used, anyway that's
// the end of similiarities in the engine.


int disit_show_object(ulong64 obj, char *out);


#define DISIT_MAX_ARGS		3
typedef struct _g_ddata {
  ulong32			mask;                 
  ulong32			code;                 
  uint8				len;                  
  uint16			bits;                 
  uint8				arg1;
  uint8				arg2;
  uint8				arg3;   

  //char			 in_flags;
  //char			 out_flags;

  ulong64			static_obj_src;
  ulong64			static_obj_dest;
 
  uint8				s_flag;                 
 
  
  ulong64			status_obj_undefined;
  char				*name;                
} g_ddata;




typedef struct __dis_data {
	int8		prefix_len;
	int8		len;									// len of the mutinstruction
	ulong32		dflags;									// main flags DF_XXX
	ulong32		mem_imm;								// immediate for mem
	uint16		reserved;								// reserved for TTTN fields
	

	uint8		tttn;									// for jumps

	ulong64		obj_src;								// all src objectes
	ulong64		obj_dest;								// all dest objects

	ulong64		i_obj_src;								// src object mutinstruction style (register)
	ulong64		i_obj_dest;								// dst object mutinstruction style (register)


	ulong32		mem_regs;								// memory registers (32bits are enough)
	ulong32		sib_mul_reg;							// multipled register (32bit are enough)

	ulong32		imm_data;								// imm data

	
	uint8		opcode;							// opcode value
	uint8		opcode2;						// second opcode value
	uint8		modrm;							// modrm value
	uint8		sib;							// sib value

	uint16		additional_flags;				// IPRIV/IRARE etc.
	int			emul_int;

//only for SPIDERPIG
#ifdef _NO_PARENT_
	uint8		modrm_offset;
#endif

// only for emulator
#ifdef ASLAN_EMU
	int			seg;
#endif

} _dis_data;




#ifdef DISIT_NO_ASCII
#define      SK(x) NULL
#else
#define      SK(x) x
#endif


const g_ddata i_data[] = {


	{ 0x00FFFF, 0x00320F, 2, IPRIV|IRARE,  NNN,		NNN,		NNN, R_ECX,						R_EDX | R_EAX,												NNN,         NNN,     SK("RDMSR")},				// RDMSR -> 0000 1111: 0011 0010
	{ 0x00FFFF, 0x00330F, 2, IRARE,  NNN,		NNN,		NNN, R_ECX,						R_EDX | R_EAX,												NNN,         NNN,     SK("RDPMC")},		// RDPMC -> 0000 1111: 0011 0011
	{ 0x00FFFF, 0x00310F, 2, 0,  NNN,		NNN,		NNN, NNN,						R_EDX | R_EAX,												NNN,         NNN,     SK("RDTSC")},		// RDTSC -> 0000 1111: 0011 0001
	{ 0x00FFFF, 0x00AA0F, 2, 0,  NNN,		NNN,		NNN, NNN,						F_ALL,														NNN,         NNN,     SK("RSM")},			// RSM -> 0000 1111: 1010 1010
	{ 0x0000FF, 0x00009E, 1, IRARE,  NNN,		NNN,		NNN, R_AH,						SF | ZF | AF | PF | CF,										NNN,         NNN,     SK("SAHF")},		// SAHF -> 1001110
	{ 0x38FFFF, 0x00010F, 2, IRARE,  MM2CE,		NNN,		NNN, NNN,						NNN,														NNN,	     NNN,     SK("SGDT")},		// SGDT -> 0000 1111: 0000 0001: mod^A 0000 r/m
	
	
	//{ 0xF8F0FF, 0xC0900F, 2, 0,   JTTTNS,	MDR2R_8,	NNN, NNN,				NNN,														C_NNN,				     NNN,     SK("SETcc")},		// SETcc r1 -> 0000 1111: 1001 NNN: 11 000 r1
	// changed 12.09.2011 - because even the upper one was the only form listed by Intel it seems like Adobe Flash and other crap
	// use them anyway.
	{ 0xC0F0FF, 0xC0900F, 2, 0,   JTTTNS,	MDR2R_8,	NNN, NNN,				NNN,														C_NNN,				     NNN,     SK("SETcc")},		// SETcc r1 -> 0000 1111: 1001 NNN: 11 000 r1
	
	{ 0x38F0FF, 0x00900F, 2, 0,   JTTTNS,	MM2R_8,		NNN, NNN,				NNN,														C_NNN,				     NNN,     SK("SETcc")},		// SETcc MM -> 0000 1111: 1001 NNN: mod 000 r/m



	{ 0x0000FF, 0x000037, 1, 0,  NNN,		NNN,		NNN, R_AX | AF,					R_AX | DF | IF | TF | SF | ZF | PF | CF | OF,				NNN,         OF|SF|ZF|PF,     SK("AAA")},			// AAA -> 0011 0111
	{ 0x0000FF, 0x00003F, 1, 0,  NNN,		NNN,		NNN, R_AX | AF,					R_AX | DF | IF | TF | SF | ZF | PF | CF | OF,				NNN,         OF|SF|ZF|PF,     SK("AAS")},			// AAS -> 0011 1111
	
	{ 0x00C0FE, 0x00C010, 1, WW, MDR1R,		MDR2R,		NNN, CF,						OF | SF | ZF | AF | CF | PF,								C_D2S_NN,			     NNN,     SK("ADC")},			// r1,r2 -> 0001 000w: 11 r1 r2
	{ 0x00C0FE, 0x00C012, 1, WW, MDR1,		MDR2,		NNN, CF,						OF | SF | ZF | AF | CF | PF,								C_D2S_NN,			     NNN,     SK("ADC")},			// r2,r1 -> 0001 001w: 11 r1 r2
    { 0x0000FE, 0x000012, 1, WW, MDR1,		MM2,		NNN, CF,						OF | SF | ZF | AF | CF | PF,								C_D2S_NN,			     NNN,     SK("ADC")},			// r1,MM -> 0001 001w: mod reg r/m
	{ 0x0000FE, 0x000010, 1, WW|BM, MDR1R,	MM1,		NNN, CF,						OF | SF | ZF | AF | CF | PF,								C_S_MEM,			     NNN,     SK("ADC")},			// MM,r1 -> 0001 000w: mod reg r/m        *crap*
	{ 0x00F8FC, 0x00D080, 1, WS, MDR2R,		IMM,		NNN, CF,						OF | SF | ZF | AF | CF | PF,								C_D2S_NN,			     NNN,     SK("ADC")},			// r1,IM -> 1000 00sw: 11 010 reg : IM
	{ 0x0000FE, 0x000014, 1, WW, ACC,		IMMC,		NNN, CF,						OF | SF | ZF | AF | CF | PF,								C_D2S_NN,			     NNN,     SK("ADC")},			// AC,IM -> 0001 010w: IM
	{ 0x0038FC, 0x001080, 1, WS|BM, MM1,	IMMS,		NNN, CF,						OF | SF | ZF | AF | CF | PF,								C_S_MEM,			     NNN,     SK("ADC")},			// MM,IM -> 1000 00sw: mod 010 r/m : IM	  *crap*
	
	
	{ 0x00C0FE, 0x00C000, 1, WW, MDR1R,		MDR2R,		NNN, NNN,						OF | SF | ZF | AF | CF | PF,								C_D2S_NN,			     NNN,     SK("ADD")},			// r1,r2 -> 0000 000w: 11 reg1 reg2
	{ 0x00C0FE, 0x00C002, 1, WW, MDR1,		MDR2,		NNN, NNN,						OF | SF | ZF | AF | CF | PF,								C_D2S_NN,			     NNN,     SK("ADD")},			// r2,r1 -> 0000 001w: 11 reg1 reg2
	{ 0x0000FE, 0x000002, 1, WW, MDR1,		MM2,		NNN, NNN,						OF | SF | ZF | AF | CF | PF,								C_D2S_NN,			     NNN,     SK("ADD")},			// r1,MM -> 0000 001w: mod reg r/m
	{ 0x0000FE, 0x000000, 1, WW|BM, MDR1R,	MM1,		NNN, NNN,						OF | SF | ZF | AF | CF | PF,								C_S_MEM,			     NNN,     SK("ADD")},			// MM,r1 -> 0000 000w: mod reg r/m			*crap*
	{ 0x00F8FC, 0x00C080, 1, WS, MDR2R,		IMM,		NNN, NNN,						OF | SF | ZF | AF | CF | PF,								C_D2S_NN,			     NNN,     SK("ADD")},			// r1,IM -> 1000 00sw: 11 000 reg : 
	{ 0x0000FE, 0x000004, 1, WW, ACC,		IMMC,		NNN, NNN,						OF | SF | ZF | AF | CF | PF,								C_D2S_NN,			     NNN,     SK("ADD")},			// AC,IM -> 0000 010w: IM
	{ 0x0038FC, 0x000080, 1, WS|BM, MM1,	IMMS,		NNN, NNN,						OF | SF | ZF | AF | CF | PF,								C_S_MEM,			     NNN,     SK("ADD")},			// MM,IM -> 1000 00sw: mod 000 r/m : IM		*crap*

	{ 0x00C0FE, 0x00C020, 1, WW, MDR1R,		MDR2R,		NNN, NNN,						OF | CF | SF | ZF | PF | AF,								C_D2S_NN,			     AF,     SK("AND")},			// r1,r2 -> 0010 000w: 11 r1 r2
	{ 0x00C0FE, 0x00C022, 1, WW, MDR1,		MDR2,		NNN, NNN,						OF | CF | SF | ZF | PF | AF,								C_D2S_NN,			     AF,     SK("AND")},			// r2,r1 -> 0010 001w: 11 r1 r2
	{ 0x0000FE, 0x000022, 1, WW, MDR1,		MM2,		NNN, NNN,						OF | CF | SF | ZF | PF | AF,								C_D2S_NN,			     AF,     SK("AND")},			// r1,MM -> 0010 001w: mod reg r/m
	{ 0x0000FE, 0x000020, 1, WW|BM, MDR1R,	MM1,		NNN, NNN,						OF | CF | SF | ZF | PF | AF,								C_S_MEM,			     AF,     SK("AND")},			// MM,r1 -> 0010 000w: mod reg r/m			*crap*
	{ 0x00F8FC, 0x00E080, 1, WS, MDR2R,		IMM,		NNN, NNN,						OF | CF | SF | ZF | PF | AF,								C_D2S_NN,			     AF,     SK("AND")},			// r1,IM -> 1000 00sw: 11 100 reg
	{ 0x0000FE, 0x000024, 1, WW, ACC,		IMMC,		NNN, NNN,						OF | CF | SF | ZF | PF | AF,								C_D2S_NN,			     AF,     SK("AND")},			// AC,IM -> 0010 010w: IM
	{ 0x0038FC, 0x002080, 1, WS|BM, MM1,	IMMS,		NNN, NNN,						OF | CF | SF | ZF | PF | AF,								C_S_MEM,			     AF,     SK("AND")},			// MM,IM -> 1000 00sw: mod 100 r/m: IM		*crap*
	
	{ 0x00C0FF, 0x00C063, 1, IPRIV|IRARE,  MDR1R_16,	MDR2R_16,	NNN, NNN,						ZF,															NNN,				     NNN,     SK("ARPL")},		// f.reg -> 0110 0011: 11 reg1 reg2
	{ 0x0000FF, 0x000063, 1, IPRIV|IRARE,  MDR1R_16,	MM1_16,		NNN, NNN,						ZF,															NNN,				     NNN,     SK("ARPL")},		// f.mem -> 0110 0011: mod reg r/m

	{ 0x0000FF, 0x000062, 1, IRARE,  MDR1,		MM2_E,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("BOUND")},		// bound -> 0110 0010: mod^a reg r/m

	{ 0xC0FFFF, 0xC0BC0F, 2, 0,  MDR1,		MDR2,		NNN, NNN,						ZF | CF | OF | SF | AF | PF,								NNN,				     CF|OF|SF|AF|PF,     SK("BSF")},			// r1,r2 -> 0000 1111: 1011 1100: 11 reg1 reg2
	{ 0x00FFFF, 0x00BC0F, 2, 0,  MDR1,		MM2,		NNN, NNN,						ZF | CF | OF | SF | AF | PF,								NNN,				     CF|OF|SF|AF|PF,     SK("BSF")},			// r1,MM -> 0000 1111: 1011 1100: mod reg r/m

	{ 0xC0FFFF, 0xC0BD0F, 2, 0,  MDR1,		MDR2,		NNN, NNN,						ZF | CF | OF | SF | AF | PF,								NNN,				     CF|OF|SF|AF|PF,     SK("BSR")},			// r1,r2 -> 0000 1111: 1011 1101: 11 reg1 reg2
	{ 0x00FFFF, 0x00BD0F, 2, 0,  MDR1,		MM2,		NNN, NNN,						ZF | CF | OF | SF | AF | PF,								NNN,				     CF|OF|SF|AF|PF,     SK("BSR")},			// r1,MM -> 0000 1111: 1011 1101: mod reg r/m



	{ 0xF8FFFF, 0xE0BA0F, 2, 0,  MDR2R,		IMM8,		NNN, NNN,						CF | OF | SF | ZF | AF | PF,								NNN,				     OF|SF|AF|PF|ZF,     SK("BT")},			// r1,IM -> 0000 1111: 1011 1010: 11 100 reg: IMM8 DATA
	{ 0x38FFFF, 0x20BA0F, 2, BM,  MM1,		IMM8S,		NNN, NNN,						CF | OF | SF | ZF | AF | PF,								NNN,				     OF|SF|AF|PF|ZF,     SK("BT")},			// MM,IM -> 0000 1111: 1011 1010: mod 100 r/m
	{ 0xC0FFFF, 0xC0A30F, 2, 0,  MDR1R,		MDR2R,		NNN, NNN,						CF | OF | SF | ZF | AF | PF,								NNN,				     OF|SF|AF|PF|ZF,     SK("BT")},			// r1,r2 -> 0000 1111: 1010 0011: 11 reg2 reg1
	{ 0x00FFFF,	0x00A30F, 2, BM,  MM1,		MDR1R,		NNN, NNN,						CF | OF | SF | ZF | AF | PF,								NNN,				     OF|SF|AF|PF|ZF,     SK("BT")},			// MM,r1 -> 0000 1111: 1010 0011: mod reg r/m

  
	{ 0xF8FFFF, 0xF8BA0F, 2, 0,  MDR2R,		IMM8,		NNN, NNN,						CF | OF | SF | ZF | AF | PF,								NNN,				     OF|SF|AF|PF|ZF,     SK("BTC")},			// r1,IM -> 0000 1111: 1011 1010: 11 111 reg: NNN DATA
	{ 0x38FFFF, 0x38BA0F, 2, BM,  MM1,		IMM8S,		NNN, NNN,						CF | OF | SF | ZF | AF | PF,								NNN,				     OF|SF|AF|PF|ZF,     SK("BTC")},			// MM,IM -> 0000 1111: 1011 1010: mod 111 r/m: NNN DATA
	{ 0xC0FFFF, 0xC0BB0F, 2, 0,  MDR1R,		MDR2R,		NNN, NNN,						CF | OF | SF | ZF | AF | PF,								NNN,				     OF|SF|AF|PF|ZF,     SK("BTC")},			// r1,r2 -> 0000 1111: 1011 1011: 11 reg2 reg1
	{ 0x00FFFF, 0x00BB0F, 2, BM,  MM1,		MDR1R,		NNN, NNN,						CF | OF | SF | ZF | AF | PF,								NNN,				     OF|SF|AF|PF|ZF,     SK("BTC")},			// MM,r1 -> 0000 1111: 1011 1011: mod reg r/m

	{ 0xF8FFFF, 0xF0BA0F, 2, 0,  MDR2R,		IMM8,		NNN, NNN,						CF | OF | SF | ZF | AF | PF,								NNN,				     OF|SF|AF|PF|ZF,     SK("BTR")},			// r1,IM -> 0000 1111: 1011 1010: 11 110 reg: NNN DATA
	{ 0x38FFFF, 0x30BA0F, 2, BM,  MM1,		IMM8S,		NNN, NNN,						CF | OF | SF | ZF | AF | PF,								NNN,				     OF|SF|AF|PF|ZF,     SK("BTR")},			// MM,IM -> 0000 1111: 1011 1010: mod 110 r/m: NNN data
	{ 0xC0FFFF, 0xC0B30F, 2, 0,  MDR1R,		MDR2R,		NNN, NNN,						CF | OF | SF | ZF | AF | PF,								NNN,				     OF|SF|AF|PF|ZF,     SK("BTR")},			// r1,r2 -> 0000 1111: 1011 0011: 11 reg2 reg1
	{ 0x00FFFF, 0x00B30F, 2, BM,  MM1,		MDR1R,		NNN, NNN,						CF | OF | SF | ZF | AF | PF,								NNN,				     OF|SF|AF|PF|ZF,     SK("BTR")},			// MM,r1 -> 0000 1111: 1011 0011: mod reg r/m

	{ 0xF8FFFF, 0xE8BA0F, 2, 0,  MDR2R,		IMM8,		NNN, NNN,						CF | OF | SF | ZF | AF | PF,								NNN,				     OF|SF|AF|PF|ZF,     SK("BTS")},			// r1,IM -> 0000 1111: 1011 1010: 11 101 reg: NNN DATA
	{ 0x38FFFF, 0x28BA0F, 2, BM,  MM1,		IMM8S,		NNN, NNN,						CF | OF | SF | ZF | AF | PF,								NNN,				     OF|SF|AF|PF|ZF,     SK("BTS")},			// MM,IM -> 0000 1111: 1011 1010: mod 101 r/m: NNN data
	{ 0xC0FFFF, 0xC0AB0F, 2, 0,  MDR1R,		MDR2R,		NNN, NNN,						CF | OF | SF | ZF | AF | PF,								NNN,				     OF|SF|AF|PF|ZF,     SK("BTS")},			// r1,r2 -> 0000 1111: 1010 1011: 11 reg2 reg1
	{ 0x00FFFF, 0x00AB0F, 2, BM,  MM1,		MDR1R,		NNN, NNN,						CF | OF | SF | ZF | AF | PF,								NNN,				     OF|SF|AF|PF|ZF,     SK("BTS")},			// MM,r1 -> 0000 1111: 1010 1011: mod reg r/m


	/* add reg_dst = ESP for every call */
																																														// in the same segment
	{ 0x0000FF, 0x0000E8, 1, 0,  IMM32C,	NNN,		NNN, R_ESP,						R_ESP,														NNN,				     NNN,     SK("CALL")},		// call direct -> 1110 1000: full displacement
	{ 0x00F8FF, 0x00D0FF, 1, 0,  MDR2,		NNN,		NNN, R_ESP,						R_ESP,														NNN,				     NNN,     SK("CALL")},		// call register indirect -> 1111 1111: 11 010 reg
	{ 0x0038FF, 0x0010FF, 1, 0,  MM2,		NNN,		NNN, R_ESP,						R_ESP,														NNN,				     NNN,     SK("CALL")},		// call memory indirect -> 1111 1111: mod 010 r/m
																																														// in other segment
	{ 0x0000FF, 0x00009A, 1, 0,  IMM32C,	IMM_SEL,	NNN, R_ESP,						R_ESP,														NNN,				     NNN,     SK("CALL FAR")},	// call direct -> 1001 1010: unsigned full offset, selector
	{ 0x0038FF, 0x0018FF, 1, 0,  MM2CE,		NNN,		NNN, R_ESP,						R_ESP,														NNN,				     NNN,     SK("CALL FAR")},	// call indirect -> 1111 1111: mod 010 r/m



	{ 0x0000FF, 0x000098, 1, NA, NNN,		NNN,		NNN, NNN,						R_EAX,														NNN,				     NNN,     SK("CBW*")},	    // CBW/CWDE: 1001 1000
	{ 0x0000FF, 0x000099, 1, NA, NNN,		NNN,		NNN, R_EAX,						R_EDX,														NNN,				     NNN,     SK("CD*")},			// CDQ/CWD: 1001 1001
	{ 0x0000FF, 0x0000F8, 1, 0,  NNN,		NNN,		NNN, NNN,						CF,															NNN,				     NNN,     SK("CLC")},			// CLC: 1111 1000
	{ 0x0000FF, 0x0000FC, 1, 0,  NNN,		NNN,		NNN, NNN,						DF,															NNN,				     NNN,     SK("CLD")},			// CBW: 1111 1100
	{ 0x0000FF, 0x0000FA, 1, 0,  NNN,		NNN,		NNN, NNN,						IF,															NNN,				     NNN,     SK("CLI")},			// CLI: 1111 1010
	{ 0x00FFFF, 0x00060F, 2, IPRIV|IRARE,  NNN,		NNN,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("CLTS")},		// CLTS: 0000 1111: 0000 0110
	{ 0x0000FF, 0x0000F5, 1, 0,  NNN,		NNN,		NNN, NNN,						CF,															NNN,				     NNN,     SK("CMC")},			// CMC: 1111 0101

	{ 0x00C0FE, 0x00C038, 1, WW, MDR1R,		MDR2R,		NNN, NNN,						CF | OF | SF | ZF | AF | PF,								C_D2SN,				     NNN,     SK("CMP")},			// r1,r2: 0011 100w: 11 reg1 reg2
	{ 0x00C0FE, 0x00C03A, 1, WW, MDR1,		MDR2,		NNN, NNN,						CF | OF | SF | ZF | AF | PF,								C_D2SN,				     NNN,     SK("CMP")},			// r2,r1: 0011 101w: 11 reg1 reg2
	{ 0x0000FE, 0x000038, 1, WW, MM1,		MDR1R,		NNN, NNN,						CF | OF | SF | ZF | AF | PF,								C_SND_MEM,			     NNN,     SK("CMP")},			// MM,r1 -> 0011 100w: mod reg r/m			*crap*
	{ 0x0000FE, 0x00003A, 1, WW, MDR1,		MM2,		NNN, NNN,						CF | OF | SF | ZF | AF | PF,								C_D2SN,				     NNN,     SK("CMP")},			// r1,MM -> 0011 101w: mod reg r/m
	{ 0x00F8FC, 0x00F880, 1, WS, MDR2R,		IMM,		NNN, NNN,						CF | OF | SF | ZF | AF | PF,								C_D2SN,				     NNN,     SK("CMP")},			// r1,IM -> 1000 00sw: 11 111 reg
	{ 0x0000FE, 0x00003C, 1, WW, ACC,		IMMC,		NNN, NNN,						CF | OF | SF | ZF | AF | PF,								C_D2SN,				     NNN,     SK("CMP")},			// AC,IM -> 0011 110w: IM
	{ 0x0038FC, 0x003880, 1, WS, MM1,		IMMS,		NNN, NNN,						CF | OF | SF | ZF | AF | PF,								C_SND_MEM,		         NNN,     SK("CMP")},			// MM,IM -> 1000 00sw: mod 111 r/m: IM		*crap*

	{ 0x0000FE, 0x0000A6, 1, WW|NA,NNN,		NNN,		NNN, R_ESI | R_EDI | DF,		R_ESI | R_EDI | CF | OF | SF | ZF | AF | PF,				C_SND_MEM,				     NNN,     SK("CMPS*")},		// CMPS(X) -> 1010 011w

	{ 0xC0FEFF, 0xC0B00F, 2, WW, MDR1R,		MDR2R,		NNN, R_EAX,						R_EAX | ZF | CF | PF | AF | SF | OF,						NNN,				     NNN,     SK("CMPXCHG")},		// r1,r2 -> 0000 1111: 1011 000w: 11 reg2 reg1
	{ 0x00FEFF, 0x00B00F, 2, WW, MM1,		MDR1R,		NNN, R_EAX,						R_EAX |ZF | CF | PF | AF | SF | OF,							NNN,				     NNN,     SK("CMPXCHG")},		// MM,r1 -> 0000 1111: 1011 000w: mod reg r/m

	{ 0x00FFFF, 0x00A20F, 2, IRARE,  NNN,		NNN,		NNN, NNN,						R_EAX | R_EBX | R_ECX | R_EDX,								NNN,				     NNN,     SK("CPUID")},		// CPUID -> 0000 1111: 1010 0010 

	{ 0x0000FF, 0x000027, 1, 0,  NNN,		NNN,		NNN, R_AL | CF | AF,			CF | AF | SF | ZF | PF | OF,								NNN,				     OF,     SK("DAA")},			// DAA -> 0010 0111
	{ 0x0000FF, 0x00002F, 1, 0,  NNN,		NNN,		NNN, R_AL | CF | AF,			CF | AF | SF | ZF | PF | OF,								NNN,				     OF,     SK("DAS")},			// DAS -> 0010 1111

	{ 0x00F8FE, 0x00C8FE, 1, WW, MDR2R,		NNN,		NNN, NNN,						OF | SF | ZF | AF | PF,										C_D2S,				     NNN,     SK("DEC")},			// dec r1 -> 1111 111w: 11 001 reg
	{ 0x0000F8, 0x000048, 1, 0,  MDR2_A,	NNN,		NNN, NNN,						OF | SF | ZF | AF | PF,										C_D2S,				     NNN,     SK("DEC")},			// dec r1 -> 0100 1 reg
	{ 0x0038FE, 0x0008FE, 1, WW|BM, MM1,	NNN,		NNN, NNN,						OF | SF | ZF | AF | PF,										NNN,				     NNN,     SK("DEC")},			// dec MM -> 1111 111w: mod 0001 r/m

																	     
	{ 0x00F8FE, 0x00F0F6, 1, WW|EX_DIV,  MDR2,	NNN,	NNN, R_EAX | R_EDX,				R_EAX | R_EDX | CF | OF | SF | ZF | AF | PF,				NNN,				     CF|OF|SF|ZF|AF|PF,     SK("DIV")},			// AC,r1 -> 1111 011w: 11 111 reg
	{ 0x0038FE, 0x0030F6, 1, WW|EX_DIV,  MM2,	NNN,	NNN, R_EAX | R_EDX,				R_EAX | R_EDX | CF | OF | SF | ZF | AF | PF,				NNN,				     CF|OF|SF|ZF|AF|PF,     SK("DIV")},			// AC,MM -> 1111 011w: mod 110 r/m

	{ 0x0000FF, 0x0000C8, 1, 0,   IMM_SEL_E,IMM8E,		NNN, R_ESP,						R_ESP,														NNN,				     NNN,     SK("ENTER")},		// ENTER -> 1100 1000: 16 bit displacment: 8bit level(L)

	{ 0x0000FF, 0x0000F4, 1, IPRIV|IRARE,   NNN,		NNN,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("HLT")},			// HLT ->	1111 0100

	{ 0x00F8FE, 0x00F8F6, 1, WW|EX_DIV,  MDR2,	NNN,	NNN, R_EAX | R_EDX,				R_EAX | R_EDX | CF | OF | SF | ZF | AF | PF,				NNN,				     CF|OF|SF|ZF|AF|PF,     SK("IDIV")},		// AC,r1 ->	1111 011w: 11 111 reg
	{ 0x0038FE, 0x0038F6, 1, WW|EX_DIV,  MM2,	NNN,	NNN, R_EAX | R_EDX,				R_EAX | R_EDX | CF | OF | SF | ZF | AF | PF,				NNN,				     CF|OF|SF|ZF|AF|PF,     SK("IDIV")},		// AC,MM ->	1111 011w: mod 111 r/m

	{ 0x00F8FE, 0x00E8F6, 1, WW|EX_MUL,  MDR2,		NNN,		NNN, R_EAX,						R_EAX | R_EDX | CF | OF | SF | ZF | AF | PF,				NNN,				     SF|ZF|AF|PF,     SK("IMUL")},		// AC,r1 -> 1111 011w: 11 101 reg
	{ 0x0038FE, 0x0028F6, 1, WW|EX_MUL,  MM2,		NNN,		NNN, R_EAX,						R_EAX | R_EDX | CF | OF | SF | ZF | AF | PF,				NNN,				     SF|ZF|AF|PF,     SK("IMUL")},		// AC,MM -> 1111 011w: mod 101 reg
	{ 0xC0FFFF, 0xC0AF0F, 2, EX_MUL,   MDR1,		MDR2,		NNN, R_EAX,						R_EAX | R_EDX | CF | OF | SF | ZF | AF | PF,				NNN,				     SF|ZF|AF|PF,     SK("IMUL")},		// r1,r2 -> 0000 1111: 1010 1111: 11: reg1 reg2
	{ 0x00FFFF, 0x00AF0F, 2, EX_MUL,   MDR1,		MM2,		NNN, R_EAX,						R_EAX | R_EDX | CF | OF | SF | ZF | AF | PF,				NNN,				     SF|ZF|AF|PF,     SK("IMUL")},		// r1,MM -> 0000 1111: 1010 1111: mod reg r/m
	{ 0x0080FD, 0x008069, 1, SS|EX_MUL,  MDR1,		MDR2,		IMM, R_EAX,						R_EAX | R_EDX | CF | OF | SF | ZF | AF | PF,				NNN,				     SF|ZF|AF|PF,     SK("IMUL")},		// r1,IM2r2 -> 0110 10s1: 11 reg1 reg2: IMM DATA
	{ 0x0000FD, 0x000069, 1, SS|EX_MUL,  MDR1,		MM2,		IMMI,R_EAX,						R_EAX | R_EDX | CF | OF | SF | ZF | AF | PF,				C_S_MEM,			     SF|ZF|AF|PF,     SK("IMUL")},		// MM,IM2reg -> 0110 10s1: mod reg r/m: IMM DATA
	

	{ 0x0000FE, 0x0000E4, 1, WW|IPRIV|IRARE,  ACC,		IMM8C,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("IN")},			// fixed port -> 1110 010w: port number
	{ 0x0000FE, 0x0000EC, 1, WW|IPRIV|IRARE,  ACC,		REG_DX,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("IN")},			// variable port -> 1110 110w

	{ 0x00F8FE, 0x00C0FE, 1, WW,  MDR2R,	NNN,		NNN, NNN,						OF | SF | ZF | AF | PF,										C_D2S,				     NNN,     SK("INC")},			// r1 -> 1111 111w -> 11 000 reg
	{ 0x0000F8, 0x000040, 1, 0,   MDR2_A,	NNN,		NNN, NNN,						OF | SF | ZF | AF | PF,										C_D2S,				     NNN,     SK("INC")},			// r1 (a.e) -> 0100 0 reg
	{ 0x0038FE, 0x0000FE, 1, WW|BM,  MM1,	NNN,		NNN, NNN,						OF | SF | ZF | AF | PF,										C_S_MEM,			     NNN,     SK("INC")},			// MM -> 1111 111w: mod 000 r/m *crap*
	
	{ 0x0000FE, 0x00006C, 1, WW|NA|IPRIV|IRARE,NNN,		NNN,		NNN, R_DX | R_ESI | R_EDI,		R_ESI | R_EDI,												NNN,				     NNN,     SK("INSS*")},       // from DX port -> 0110 110w

	{ 0x0000FF, 0x0000CD, 1, IRARE,   IMM8CN,	NNN,		NNN, R_ESP,						R_ESP | IF | TF | NTF | RF | VMF,							NNN,				     NNN,     SK("INT")},			// INT N -> 1100 1101: n(type)
	{ 0x0000FF, 0x0000CC, 1, IRARE,   NNN,		NNN,		NNN, NNN,						IF | TF | NTF | RF | VMF,									NNN,				     NNN,     SK("INT 0x3")},		// INT 3 -> 1100 1100
	{ 0x0000FF, 0x0000CE, 1, 0,   NNN,		NNN,		NNN, R_ESP,						R_ESP | IF | TF | NTF | RF | VMF,							NNN,				     NNN,     SK("INTO")},		// INTO -> 1100 1110
	{ 0x00FFFF, 0x00080F, 2, IPRIV|IRARE,   NNN,		NNN,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("INVD")},		// INVD -> 0000 1111: 0000 1000
	{ 0x38FFFF, 0x38010F, 2, IPRIV|IRARE,   MM1,		NNN,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("INVLPG")},		// INVLPG -> 0000 1111: 0000 0001: mod 111 /rm
	{ 0x0000FF, 0x0000CF, 1, IRARE,   NNN,		NNN,		NNN, R_ESP,						R_ESP | ALL_FLAGS,											NNN,				     NNN,     SK("IRET/IRETD")},	// IRET -> 1100 1111

	{ 0x0000F0, 0x000070, 1, NA,  JTTTN,	IMM8C,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("JCC")},			// JCC -> 0111 tttn: 8 bit displacement
	{ 0x00F0FF, 0x00800F, 2, NA,  JTTTN,	IMM32C,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("JCC")},			// JCC -> 0000 1111: 1000 tttn: full displacement
	{ 0x0000FF, 0x0000E3, 1, 0,   NNN,		IMM8C,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("JECXZ")},		// JCXZ -> 1110 0011: 8 bit displacement

																																														// JMP - same segment
	{ 0x0000FF, 0x0000EB, 1, 0,   IMM8C,	NNN,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("JMP SHORT")},	// JMP SHORT -> 1110 1011: 8 bit displacement
	{ 0x0000FF, 0x0000E9, 1, 0,   IMM32C,	NNN,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("JMP")},			// JMP DIRECT -> 1110 1001: full displacement
	{ 0x00F8FF, 0x00E0FF, 1, 0,   MDR2,		NNN,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("JMP")},			// JMP R.INDIRECT -> 1111 1111: 11 100 reg
	{ 0x0038FF, 0x0020FF, 1, 0,   MM2,		NNN,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("JMP")},			// JMP M.INDIRECT -> 1111 1111: mod 100 r/m

																																					// JMP - other segment
	{ 0x0000FF, 0x0000EA, 1, 0,   IMM32C,	IMM_SEL,	NNN, NNN,						NNN,														NNN,				     NNN,     SK("JMP")},			// JMP DIRECT ISEG -> 1110 1010: unsigned full offset, selector
	{ 0x0038FF, 0x0028FF, 1, 0,   MM2CE,	NNN,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("JMP")},			// JMP INDIRECT ISEG -> 1111 1111: mod 101 r/m 

	{ 0x0000FF, 0x00009F, 1, IRARE,   NNN,		NNN,		NNN, SF | ZF | AF | PF | CF,	R_AH,														NNN,				     NNN,     SK("LAHF")},		// LAHF -> 1001 1111

	{ 0xC0FFFF, 0xC0020F, 2, IPRIV|IRARE,   MDR1,		MDR2,		NNN, NNN,						ZF,															NNN,				     NNN,     SK("LAR")},			// LAR from reg -> 0000 1111: 0000 0010: 11 reg1 reg2
	{ 0x00FFFF, 0x00020F, 2, IPRIV|IRARE,   MDR1,		MM2,		NNN, NNN,						ZF,															NNN,				     NNN,     SK("LAR")},			// LAR from mem -> 0000 1111: 0000 0010: mod reg r/m

	{ 0x0000FF, 0x0000C5, 1, IRARE,   MDR1,		MM2_EF,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("LDS")},			// LDS -> 1100 0101: mod^A reg r/m
	{ 0x0000FF, 0x00008D, 1, 0,   MDR1,		MM2,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("LEA")},			// LEA -> 1000 1101: mod^A reg r/m
	{ 0x0000FF, 0x0000C9, 1, 0,   NNN,		NNN,		NNN, R_EBP,						R_EBP | R_ESP,												NNN,				     NNN,     SK("LEAVE")},		// LEAVE -> 1100 1001
	{ 0x0000FF, 0x0000C4, 1, IRARE,   MDR1,		MM2_EF,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("LES")},			// LES -> 1100 0100: mod^A reg r/m
	{ 0x00FFFF, 0x00B40F, 2, IRARE,   MDR1,		MM2_EF,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("LFS")},			// LFS -> 0000 1111: 1011 0100: mod^A reg r/m


	//added 13.04.2011
	{ 0xFFFFFF, 0xD0010F, 3, 0,   NNN,  NNN, NNN, R_ECX,						R_EDX|R_EAX,														NNN,			     NNN,     SK("XGETBV")},
	{ 0xFFFFFF, 0xD1010F, 3, 0,   NNN,  NNN, NNN, R_EDX|R_EAX,						R_ECX,														NNN,			     NNN,     SK("XSETBV")},
	
	//end added 13.04.2011

	{ 0x38FFFF, 0x10010F, 2, IPRIV|IRARE,   MM2CE,	NNN,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("LGDT")},		// LGDT -> 0000 1111: 0000 0001: mod^A 010 r/m
	{ 0x00FFFF, 0x00B50F, 2, IRARE,   MDR1,		MM2_EF,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("LGS")},			// LGS -> 0000 1111: 1011 0101: mod^A reg r/m
	{ 0x38FFFF, 0x18010F, 2, IPRIV|IRARE,   MM2CE,	NNN,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("LIDT")},		// LIDT -> 0000 1111: 0000 0001: mod^A 011 r/m

	{ 0xF8FFFF, 0xD0000F, 2, IPRIV|IRARE,   MDR2R_16,	NNN,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("LLDT")},		// LLDT from reg -> 0000 1111: 0000 0000: 11 010 reg
	{ 0x38FFFF, 0x10000F, 2, IPRIV|IRARE|BM,  MM1_16,	NNN,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("LLDT")},		// LLDT from mem -> 0000 1111: 0000 0000: mod 010 r/m

	{ 0xF8FFFF, 0xF0010F, 2, IPRIV|IRARE,   MDR2R_16,	NNN,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("LMSW")},		// LMSW from reg -> 0000 1111: 0000 0001: 11 110 reg
	{ 0x38FFFF, 0x30010F, 2, BM|IPRIV|IRARE,   MM1_16,	NNN,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("LMSW")},		// LMSW from mem -> 0000 1111: 0000 0001: mod 110 r/m

	{ 0x0000FE, 0x0000AC, 1, WW|NA,NNN,		NNN,		NNN, R_ESI | DF,				R_ESI | R_EAX,												NNN,				     NNN,     SK("LODS*")},		// LODS(X) -> 1010 110w

	{ 0x0000FF, 0x0000E2, 1, 0,   IMM8C,	NNN,		NNN, R_ECX | ZF,				R_ECX | ZF,													NNN,				     NNN,     SK("LOOP")},		// LOOP -> 1110 0010: 8 bit displacement
	{ 0x0000FF, 0x0000E1, 1, 0,   IMM8C,	NNN,		NNN, R_ECX | ZF,				R_ECX | ZF,													NNN,				     NNN,     SK("LOOPE")},		// LOOPE/Z -> 1110 0001: 8 bit displacement
	{ 0x0000FF, 0x0000E0, 1, 0,   IMM8C,	NNN,		NNN, R_ECX | ZF,				R_ECX | ZF,													NNN,				     NNN,     SK("LOOPNE")},		// LOOPNE/NZ -> 1110 0000: 8 bit displacement

	{ 0xC0FFFF, 0xC0030F, 2, IPRIV|IRARE,   MDR1,		MDR2,		NNN, NNN,						ZF,															NNN,				     NNN,     SK("LSL")},			// LSL from reg -> 0000 1111: 0000 0011: 11 reg1 reg2
	{ 0x00FFFF, 0x00030F, 2, IPRIV|IRARE,   MDR1,		MM2,		NNN, NNN,						ZF,															NNN,				     NNN,     SK("LSL")},			// LSL from mem -> 0000 1111: 0000 0011: mod reg r/m

	{ 0x00FFFF, 0x00B20F, 2, IRARE,   MDR1,		MM2_EF,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("LSS")},			// LSS -> 0000 1111: 1011 0010: mod^A reg r/m

	{ 0xF8FFFF, 0xD8000F, 2, IPRIV|IRARE,   MDR2R_16,	NNN,		NNN, NNN,						NNN,														C_D2SN,				     NNN,     SK("LTR")},			// LTR from reg -> 0000 1111: 0000 0000: 11 0111 reg
	{ 0x38FFFF, 0x18000F, 2, IPRIV|IRARE,   MM1_16,	NNN,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("LTR")},			// LTR from mem -> 0000 1111: 0000 0000: mod 011 r/m

	{ 0x00C0FE, 0x00C088, 1, WW,  MDR1R,	MDR2R,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("MOV")},			// MOV r1, r2  -> 1000 100w: 11 r1 r2
	{ 0x00C0FE, 0x00C08A, 1, WW,  MDR1,		MDR2,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("MOV")},			// MOV r2, r1  -> 1000 101w: 11 r1 r2
	{ 0x0000FE, 0x00008A, 1, WW,  MDR1,		MM2,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("MOV")},			// MOV reg, MM -> 1000 101w: mod reg r/m
	{ 0x0000FE, 0x000088, 1, WW,  MDR1R,	MM1,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("MOV")},			// MOV MM, reg -> 1000 100w: mod reg r/m
	{ 0x00F8FE, 0x00C0C6, 1, WW,  MDR2R,	IMM,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("MOV")},			// MOV reg, IM -> 1100 011w: 11 000 reg: IM
	{ 0x0000F0, 0x0000B0, 1, W3,  MDR2_A,	IMMC,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("MOV")},			// MOV reg, IM -> 1011 w reg: IM
	{ 0x0038FE, 0x0000C6, 1, WW,  MM1,		IMMS,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("MOV")},			// MOV MM, IM  -> 1100 011w: mod 000 r/m: IM
	{ 0x0000FE, 0x0000A0, 1, WW,  ACC,		MM2_FD,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("MOV")},			// MOV AC, MM  -> 1010 000w: FULL DISP
	{ 0x0000FE, 0x0000A2, 1, WW,  ACCR,		MM1_FD,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("MOV")},			// MOV MM, AC  -> 1010 001w: FULL DISP
	
	{ 0xF8FFFF, 0xC0220F, 2, IPRIV|IRARE,   CRX,		MDR2,		NNN, NNN,						OF | SF | ZF | AF | PF | CF,								NNN,				     NNN,     SK("MOV")},			// MOV CR0, r1 -> 0000 1111: 0010 0010: 11 000 r1
	{ 0xF8FFFF, 0xD0220F, 2, IPRIV|IRARE,   CRX,		MDR2,		NNN, NNN,						OF | SF | ZF | AF | PF | CF,								NNN,				     NNN,     SK("MOV")},			// MOV CR2, r1 -> 0000 1111: 0010 0010: 11 010 r1
	{ 0xF8FFFF, 0xD8220F, 2, IPRIV|IRARE,   CRX,		MDR2,		NNN, NNN,						OF | SF | ZF | AF | PF | CF,								NNN,				     NNN,     SK("MOV")},			// MOV CR3, r1 -> 0000 1111: 0010 0010: 11 011 r1
	{ 0xF8FFFF, 0xE0220F, 2, IPRIV|IRARE,   CRX,		MDR2,		NNN, NNN,						OF | SF | ZF | AF | PF | CF,								NNN,				     NNN,     SK("MOV")},			// MOV CR4, r1 -> 0000 1111: 0010 0010: 11 100 r1
	{ 0xC0FFFF, 0xC0200F, 2, IPRIV|IRARE,   CRXR,		MDR2R,		NNN, NNN,						OF | SF | ZF | AF | PF | CF,								NNN,				     NNN,     SK("MOV")},			// MOV r1, CRX -> 0000 1111: 0010 0000: 11 eee r1

	{ 0xC0FFFF, 0xC0230F, 2, IPRIV|IRARE,   DRX,		MDR2,		NNN, NNN,						OF | SF | ZF | AF | PF | CF,								NNN,				     NNN,     SK("MOV")},		// MOV D0/7,r1 -> 0000 1111: 0010 0011: 11 eee r1
	{ 0xC0FFFF, 0xC0210F, 2, IPRIV|IRARE,   DRXR,		MDR2R,		NNN, NNN,						OF | SF | ZF | AF | PF | CF,								NNN,				     NNN,     SK("MOV")},		// MOV r1,D0/7 -> 0000 1111: 0010 0001: 11 eee r1

	{ 0x00C0FF, 0x00C08E, 1, 0,   SREG3,	MDR2,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("MOV")},			// MOV sR1, r2 -> 1000 1110: 11 sreg3 r2
	{ 0x0000FF, 0x00008E, 1, 0,   SREG3,	MM2,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("MOV")},			// MOV sR1, MM -> 1000 1110: mod sreg3 r/m
	{ 0x00C0FF, 0x00C08C, 1, 0,   MDR2R,	SREG3,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("MOV")},			// MOV r2, sR1 -> 1000 1100: 11 sreg3 r2
	{ 0x0000FF, 0x00008C, 1, 0,   MM1,		SREG3,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("MOV")},			// MOV MM, sR1 -> 1000 1100: mod sreg3 r/m


	{ 0x0000FE, 0x0000A4, 1, WW|NA,NNN,		NNN,		NNN, R_EDI | R_ESI | DF,		R_EDI | R_ESI,												NNN,				     NNN,     SK("MOVS*")},		// MOVS(B) -> 1010 010w


	{ 0xC0FFFF, 0xC0BE0F, 2, 0,    MDR1,	MDR2_8,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("MOVSX")},		// MOVSX r1, r2 -> 0000 1111: 1011 111w: 11 r1 r2
	{ 0xC0FEFF, 0xC0BE0F, 2, WW,   MDR1,	MDR2_16,	NNN, NNN,						NNN,														NNN,				     NNN,     SK("MOVSX")},		// MOVSX r1, r2 -> 0000 1111: 1011 111w: 11 r1 r2
	{ 0x00FFFF, 0x00BE0F, 2, 0,    MDR1,	MM_8,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("MOVSX")},		// MOVSX r1, MM -> 0000 1111: 1011 111w: mod reg r/m
	{ 0x00FEFF, 0x00BE0F, 2, WW,   MDR1,	MM_16,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("MOVSX")},		// MOVSX r1, MM -> 0000 1111: 1011 111w: mod reg r/m

	{ 0xC0FFFF, 0xC0B60F, 2, 0,    MDR1,	MDR2_8,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("MOVZX")},		// MOVZX r1, r2 -> 0000 1111: 1011 011w: 11 r1 r2
	{ 0xC0FEFF, 0xC0B60F, 2, WW,   MDR1,	MDR2_16,	NNN, NNN,						NNN,														NNN,				     NNN,     SK("MOVZX")},		// MOVZX r1, r2 -> 0000 1111: 1011 011w: 11 r1 r2
	{ 0x00FFFF, 0x00B60F, 2, 0,    MDR1,	MM_8,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("MOVZX")},		// MOVZX r1, MM -> 0000 1111: 1011 011w: mod reg r/m
	{ 0x00FEFF, 0x00B60F, 2, WW,   MDR1,	MM_16,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("MOVZX")},		// MOVZX r1, MM -> 0000 1111: 1011 011w: mod reg r/m

	{ 0x00F8FE, 0x00E0F6, 1, WW|EX_MUL,  MDR2,		NNN,		NNN, R_EAX,						R_EAX | R_EDX | OF | CF | SF | ZF | AF | PF,				NNN,				     SF|ZF|AF|PF,     SK("MUL")},			// MUL AC with r1 -> 1111 011w: 11 100 r1
	{ 0x0038FE, 0x0020F6, 1, WW|EX_MUL,  MM2,		NNN,		NNN, R_EAX,						R_EAX | R_EDX | OF | CF | SF | ZF | AF | PF,				NNN,				     SF|ZF|AF|PF,     SK("MUL")},			// MUL AC with MM -> 1111 011w: mod 100 r1

	{ 0x00F8FE, 0x00D8F6, 1, WW,  MDR2R,	NNN,		NNN, NNN,						CF | OF | SF | ZF | AF | PF,								C_D2S,				     NNN,     SK("NEG")},			// NEG r1 -> 1111 011w: 11 011 r1
	{ 0x0038FE, 0x0018F6, 1, WW|BM,MM1,		NNN,		NNN, NNN,						CF | OF | SF | ZF | AF | PF,								NNN,				     NNN,     SK("NEG")},			// NEG MM -> 1111 011w: mod 011 r/m


	{ 0x0000FF, 0x000090, 1, 0,   NNN,		NNN,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("NOP")},			// NOP -> 1001 0000
	{ 0x00F8FE, 0x00D0F6, 1, WW,  MDR2R,	NNN,		NNN, NNN,						NNN,														C_D2S,				     NNN,     SK("NOT")},			// NOT r1 -> 1111 011w: 11 010 r1
	{ 0x0038FE, 0x0010F6, 1, WW|BM,  MM1,	NNN,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("NOT")},			// NOT MM -> 1111 011w: mod 010 r/m

	{ 0x00C0FE, 0x00C008, 1, WW,  MDR1R,	MDR2R,		NNN, NNN,						OF | CF | SF | ZF | PF | AF,								C_D2S_NN,			     AF,     SK("OR")},			// OR r1, r2 -> 0000 100w: 11 r1 r2
	{ 0x00C0FE, 0x00C00A, 1, WW,  MDR1,		MDR2,		NNN, NNN,						OF | CF | SF | ZF | PF | AF,								C_D2S_NN,			     AF,     SK("OR")},			// OR r2, r1 -> 0000 101w: 11 r2 r2
	{ 0x0000FE, 0x00000A, 1, WW,  MDR1,		MM2,		NNN, NNN,						OF | CF | SF | ZF | PF | AF,								C_D2S_NN,			     AF,     SK("OR")},			// OR r1, MM -> 0000 101w: mod reg r/m
	{ 0x0000FE, 0x000008, 1, WW|BM,MDR1R,	MM1,		NNN, NNN,						OF | CF | SF | ZF | PF | AF,								C_S_MEM,			     AF,     SK("OR")},			// OR MM, r1 -> 0000 100w: mod reg r/m			*crap*
	{ 0x00F8FC, 0x00C880, 1, WS,  MDR2R,	IMM,		NNN, NNN,						OF | CF | SF | ZF | PF | AF,								C_D2S_NN,			     AF,     SK("OR")},			// OR r1, IM -> 1000 00sw: 11 001 r1: IM
	{ 0x0000FE, 0x00000C, 1, WW,  ACC,		IMMC,		NNN, NNN,						OF | CF | SF | ZF | PF | AF,								C_D2S_NN,			     AF,     SK("OR")},			// OR AC, IM -> 0000 110w: IM
	{ 0x0038FC, 0x000880, 1, WS|BM,  MM1,	IMMS,		NNN, NNN,						OF | CF | SF | ZF | PF | AF,								C_S_MEM,			     AF,     SK("OR")},			// OR MM, IM -> 1000 00sw: mod 001 r/m: IM		*crap*

	{ 0x0000FE, 0x0000E6, 1, WW|IPRIV|IRARE,  ACC,		IMM8C,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("OUT")},			// OUT fixed port -> 1110 011w: PORT NR
	{ 0x0000FE, 0x0000EE, 1, WW|IPRIV|IRARE,  ACC,		REG_DX,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("OUT")},			// OUT variable port -> 1110 111w
	{ 0x0000FE, 0x00006E, 1, WW|NA|IPRIV|IRARE,NNN,		NNN,		NNN, R_EDX | R_ESI | DF,		R_ESI,														NNN,				     NNN,     SK("OUTS*")},		// OUTS to DX -> 0110 111w

	{ 0x00F8FF, 0x00C08F, 1, 0,   MDR2R,	NNN,		NNN, R_ESP,						R_ESP,														NNN,				     NNN,     SK("POP")},			// POP r1 -> 1000 1111: 11 000 reg
	{ 0x0000F8, 0x000058, 1, 0,   MDR2_A,	NNN,		NNN, R_ESP,						R_ESP,														NNN,				     NNN,     SK("POP")},			// POP r1 -> 0101 1 reg
	{ 0x0038FF, 0x00008F, 1, 0,   MM1,		NNN,		NNN, R_ESP,						R_ESP,														NNN,				     NNN,     SK("POP")},			// POP MM -> 1000 1111: mod 000 r/m
	{ 0x00C7FF, 0x00810F, 1, IRARE,   SREG3,	NNN,		NNN, R_ESP,						R_ESP,														NNN,				     NNN,     SK("POP")},			// POP FS/GS -> 0000 1111: 10 sreg3 001

    { 0x0000FF, 0x000061, 1, 0,   NNN,		NNN,		NNN, R_ESP,						R_ESP | R_ALL32,											NNN,				     NNN,     SK("POPAD")},		// POPAD -> 0110 0001
	{ 0x0000FF, 0x00009D, 1, IRARE,   NNN,		NNN,		NNN, R_ESP | ALL_FLAGS,			R_ESP | ALL_FLAGS,											NNN,				     NNN,     SK("POPFD")},		// POPFD -> 1001 1101

	{ 0x00F8FF, 0x00F0FF, 1, 0,   MDR2R,	NNN,		NNN, NNN,						NNN,														C_DS_ESP_N,			     NNN,     SK("PUSH")},		// PUSH r1 -> 1111 1111: 11 110 r1
	{ 0x0000F8, 0x000050, 1, 0,   MDR2_A,	NNN,		NNN, NNN,						NNN,														C_DS_ESP_N,			     NNN,     SK("PUSH")},		// PUSH r1 -> 0101 0 reg
	{ 0x0038FF, 0x0030FF, 1, 0,   MM1,		NNN,		NNN, R_ESP,						R_ESP,														C_SND_MEM,			     NNN,     SK("PUSH")},		// PUSH MM -> 1111 1111: mod 110 r/m
	{ 0x0000FD, 0x000068, 1, SS,  IMMC,		NNN,		NNN, R_ESP,						R_ESP,														NNN,				     NNN,     SK("PUSH")},		// PUSH IM -> 0110 10s0: IM
	{ 0x0000E7, 0x000006, 1, IRARE,   SREG2,	NNN,		NNN, R_ESP,						R_ESP,														NNN,				     NNN,     SK("PUSH")},		// PUSH CS/DS/ES/SS -> 000 sreg2 110
	{ 0x00C7FF, 0x00800F, 1, IRARE,   SREG3,	NNN,		NNN, R_ESP,						R_ESP,														NNN,				     NNN,     SK("PUSH")},		// PUSH FS/GS -> 0000 1111: 10 sreg3 000

	{ 0x0000FF, 0x000060, 1, 0,   NNN,		NNN,		NNN, R_ESP | R_ALL32,			R_ESP,														NNN,				     NNN,     SK("PUSHAD")},		// PUSHAD -> 0110 0000
	{ 0x0000FF, 0x00009C, 1, 0,   NNN,		NNN,		NNN, R_ESP | ALL_FLAGS,			R_ESP | ALL_FLAGS,											NNN,				     NNN,     SK("PUSHFD")},		// PUSHFD -> 1001 1100


	{ 0x00F8FE, 0x00D0D0, 1, WW,  MDR2R,	IMM1,		NNN, NNN,						CF | OF,													C_D2S_NN,			     OF,     SK("RCL")},			// RCL r1,1 -> 1101 000w: 11 010 r1
	{ 0x0038FE, 0x0010D0, 1, WW|BM,  MM1,	IMM1,		NNN, NNN,						CF | OF,													NNN,				     OF,     SK("RCL")},			// RCL MM, 1 -> 1101 000w: mod 010 r/m
	{ 0x00F8FE, 0x00D0D2, 1, WW,  MDR2R,	REG_CL,		NNN, NNN,						CF | OF,													C_D2S_NN,			     OF,     SK("RCL")},			// RCL r1,cl -> 1101 001w: 11 010 reg
	{ 0x0038FE, 0x0010D2, 1, WW|BM,  MM1,	REG_CL,		NNN, NNN,						CF | OF,													C_S_MEM,			     OF,     SK("RCL")},			// RCL MM,cl -> 1101 001w: mod 010 r/m
	{ 0x00F8FE, 0x00D0C0, 1, WW,  MDR2R,	IMM8,		NNN, NNN,						CF | OF,													C_D2S_NN,			     OF,     SK("RCL")},			// RCL r1,IM -> 1100 000w: 11 010 reg: NNN
	{ 0x0038FE, 0x0010C0, 1, WW|BM,  MM1,	IMM8S,		NNN, NNN,						CF | OF,													C_S_MEM,			     OF,     SK("RCL")},			// RCL MM,IM -> 1100 000w: mod 010 r/m: NNN

	{ 0x00F8FE, 0x00D8D0, 1, WW,  MDR2R,	IMM1,		NNN, NNN,						CF | OF,													C_D2S_NN,			     OF,     SK("RCR")},			// RCR r1,1 -> 1101 000w: 11 011 r1
	{ 0x0038FE, 0x0018D0, 1, WW|BM,  MM1,	IMM1,		NNN, NNN,						CF | OF,													C_S_MEM,			     OF,     SK("RCR")},			// RCR MM,1 -> 1101 000w: mod 011 r/m
	{ 0x00F8FE, 0x00D8D2, 1, WW,  MDR2R,	REG_CL,		NNN, NNN,						CF | OF,													C_D2S_NN,			     OF,     SK("RCR")},			// RCR r1,cl -> 1101 001w: 11 011 r1
	{ 0x0038FE, 0x0018D2, 1, WW|BM,  MM1,	REG_CL,		NNN, NNN,						CF | OF,													C_S_MEM,			     OF,     SK("RCR")},			// RCR MM,cl -> 1101 001w: mod 011 r/m
	{ 0x00F8FE, 0x00D8C0, 1, WW,  MDR2R,	IMM8,		NNN, NNN,						CF | OF,													C_D2S_NN,			     OF,     SK("RCR")},			// RCR r1,IM -> 1100 000w: 11 011 reg: NNN
	{ 0x0038FE, 0x0018C0, 1, WW|BM,  MM1,	IMM8S,		NNN, NNN,						CF | OF,													C_S_MEM,			     OF,     SK("RCR")},			// RCR MM,IM -> 1100 000w: mod 011 r/m: NNN


	{ 0x0000FF, 0x0000C3, 1, 0,   NNN,		NNN,		NNN, R_ESP,						R_ESP,														NNN,				     NNN,     SK("RET")},			// RET (same seg)-> 1100 1011
	{ 0x0000FF, 0x0000C2, 1, 0,   IMM16C,	NNN,		NNN, R_ESP,						R_ESP,														NNN,				     NNN,     SK("RET")},			// RET ARG (same seg) -> 1100 0010: 16-bit DISP
	{ 0x0000FF, 0x0000CB, 1, 0,   NNN,		NNN,		NNN, R_ESP,						R_ESP,														NNN,				     NNN,     SK("RET FAR")},		// RET (other seg) -> 1100 1011
	{ 0x0000FF, 0x0000CA, 1, 0,   IMM16C,	NNN,		NNN, R_ESP,						R_ESP,														NNN,				     NNN,     SK("RET FAR")},		// RET ARG (other seg) -> 1100 1010: 16-bit DISP


	{ 0x00F8FE, 0x00C0D0, 1, WW,  MDR2R,	IMM1,		NNN, NNN,						CF | OF,													C_D2S_NN,			     OF,     SK("ROL")},			// ROL r1,1 -> 1101 000w: 11 000 r1
	{ 0x0038FE, 0x0000D0, 1, WW|BM,  MM1,	IMM1,		NNN, NNN,						CF | OF,													C_S_MEM,			     OF,     SK("ROL")},			// ROL MM,1 -> 1101 000w: mod 000 r/m
	{ 0x00F8FE, 0x00C0D2, 1, WW,  MDR2R,	REG_CL,		NNN, NNN,						CF | OF,													C_D2S_NN,			     OF,     SK("ROL")},			// ROL r1,cl -> 1101 001w: 11 000 r1
	{ 0x0038FE, 0x0000D2, 1, WW|BM,  MM1,	REG_CL,		NNN, NNN,						CF | OF,													C_S_MEM,			     OF,     SK("ROL")},			// ROL MM,cl -> 1101 001w: mod 000 r/m
	{ 0x00F8FE, 0x00C0C0, 1, WW,  MDR2R,	IMM8,		NNN, NNN,						CF | OF,													C_D2S_NN,			     OF,     SK("ROL")},			// ROL r1,IM -> 1100 000w: 11 000 r1: NNN
	{ 0x0038FE, 0x0000C0, 1, WW|BM,  MM1,	IMM8S,		NNN, NNN,						CF | OF,													C_S_MEM,			     OF,     SK("ROL")},			// ROL MM,IM -> 11000 000w: mod 000 r/m: NNN

	{ 0x00F8FE, 0x00C8D0, 1, WW,  MDR2R,	IMM1,		NNN, NNN,						CF | OF,													C_D2S_NN,			     OF,     SK("ROR")},			// ROR r1,1 -> 1101 000w: 11 001 r1
	{ 0x0038FE, 0x0008D0, 1, WW|BM,  MM1,	IMM1,		NNN, NNN,						CF | OF,													C_S_MEM,			     OF,     SK("ROR")},			// ROR MM,1 -> 1101 000W: mod 001 r/m
	{ 0x00F8FE, 0x00C8D2, 1, WW,  MDR2R,	REG_CL,		NNN, NNN,						CF | OF,													C_D2S_NN,			     OF,     SK("ROR")},			// ROR r1,cl -> 1101 001w: 11 001 r1
	{ 0x0038FE, 0x0008D2, 1, WW|BM,  MM1,	REG_CL,		NNN, NNN,						CF | OF,													C_S_MEM,			     OF,     SK("ROR")},			// ROR MM,cl -> 1101 001w: mod 001 r/m
	{ 0x00F8FE, 0x00C8C0, 1, WW,  MDR2R,	IMM8,		NNN, NNN,						CF | OF,													C_D2S_NN,			     OF,     SK("ROR")},			// ROR r1,IM -> 1100 000w: 11 001 r1: NNN
	{ 0x0038FE, 0x0008C0, 1, WW|BM,  MM1,	IMM8S,		NNN, NNN,						CF | OF,													C_S_MEM,			     OF,     SK("ROR")},			// ROR MM,IM -> 1100 000w: mod 001 r/m: NNN

	{ 0x00F8FE, 0x00F8D0, 1, WW,  MDR2R,	IMM1,		NNN, NNN,						CF | OF | SF | ZF | PF | AF,								C_D2S_NN,			     NNN,     SK("SAR")},			// SAR r1,1 -> 1101 000w: 11 111 r1
	{ 0x0038FE, 0x0038D0, 1, WW|BM,  MM1,	IMM1,		NNN, NNN,						CF | OF | SF | ZF | PF | AF,								C_S_MEM,			     NNN,     SK("SAR")},			// SAR MM,1 -> 1101 000w: mod 111 r/m
	{ 0x00F8FE, 0x00F8D2, 1, WW,  MDR2R,	REG_CL,		NNN, NNN,						CF | OF | SF | ZF | PF | AF,								C_D2S_NN,			     NNN,     SK("SAR")},			// SAR r1,cl -> 1101 001w: 11 111 r1
	{ 0x0038FE, 0x0038D2, 1, WW|BM,  MM1,	REG_CL,		NNN, NNN,						CF | OF | SF | ZF | PF | AF,								C_S_MEM,			     NNN,     SK("SAR")},			// SAR MM,cl -> 1101 001w: mod 111 r/m
	{ 0x00F8FE, 0x00F8C0, 1, WW,  MDR2R,	IMM8,		NNN, NNN,						CF | OF | SF | ZF | PF | AF,								C_D2S_NN,			     NNN,     SK("SAR")},			// SAR r1,IM -> 1100 000w: 11 111 reg: NNN
	{ 0x0038FE, 0x0038C0, 1, WW|BM,  MM1,	IMM8S,		NNN, NNN,						CF | OF | SF | ZF | PF | AF,								C_S_MEM,			     NNN,     SK("SAR")},			// SAR MM,IM -> 1100 000w: mod 111 r/m: NNN

	
	

	{ 0x00C0FE, 0x00C018, 1, WW,  MDR1R,	MDR2R,		NNN, NNN,						OF | SF | ZF | AF | PF | CF,								C_D2S_NN,			     NNN,     SK("SBB")},			// SBB r1,r2 -> 0001 100w: 11 r1 r2
	{ 0x00C0FE, 0x00C01A, 1, WW,  MDR1,		MDR2,		NNN, NNN,						OF | SF | ZF | AF | PF | CF,								C_D2S_NN,			     NNN,     SK("SBB")},			// SBB r2,r1 -> 0001 101w: 11 r2 r2
	{ 0x0000FE, 0x00001A, 1, WW,  MDR1,		MM2,		NNN, NNN,						OF | SF | ZF | AF | PF | CF,								C_D2S_NN,			     NNN,     SK("SBB")},			// SBB r1,MM -> 0001 101w: mod reg r/m
	{ 0x0000FE, 0x000018, 1, WW|BM,  MDR1R,	MM1,		NNN, NNN,						OF | SF | ZF | AF | PF | CF,								C_S_MEM,			     NNN,     SK("SBB")},			// SBB MM,r1 -> 0001 100w: mod reg r/m
	{ 0x00F8FC, 0x00D880, 1, WS,  MDR2R,	IMM,		NNN, NNN,						OF | SF | ZF | AF | PF | CF,								C_D2S_NN,			     NNN,     SK("SBB")},			// SBB r1,IM -> 100000sw: 11 011 reg: NNN
	{ 0x0000FE, 0x00001C, 1, WW,  ACC,		IMMC,		NNN, NNN,						OF | SF | ZF | AF | PF | CF,								C_D2S_NN,			     NNN,     SK("SBB")},			// SBB AC,IM -> 0001 110w: NNN
	{ 0x0038FC, 0x001880, 1, WS|BM, MM1,	IMMS,		NNN, NNN,						OF | SF | ZF | AF | PF | CF,								C_S_MEM,			     NNN,     SK("SBB")},			// SBB MM,IM -> 1000 00sw: mod 011 r/m: NNN

	{ 0x0000FE, 0x0000AE, 1, WW|NA,NNN,		NNN,		NNN, R_EAX | R_EDI | DF,		R_EDI | OF | SF | ZF | AF | PF | CF,						NNN,				     NNN,     SK("SCAS*")},		// SCASB -> 1010 111w

	{ 0x00F8FE, 0x00E0D0, 1, WW,  MDR2R,	IMM1,		NNN, NNN,						CF | OF | SF | ZF | PF | AF,								C_D2S_NN,			     NNN,     SK("SHL")},			// SHL r1,1 -> 1101 000w: 11 100 r1
	{ 0x0038FE, 0x0020D0, 1, WW|BM,  MM1,	IMM1,		NNN, NNN,						CF | OF | SF | ZF | PF | AF,								C_S_MEM,			     NNN,     SK("SHL")},			// SHL MM,1 -> 1101 000w: mod 1000 r/m
	{ 0x00F8FE, 0x00E0D2, 1, WW,  MDR2R,	REG_CL,		NNN, NNN,						CF | OF | SF | ZF | PF | AF,								C_D2S_NN,			     NNN,     SK("SHL")},			// SHL r1,cl -> 1101 001w: 11 100 r1
	{ 0x0038FE, 0x0020D2, 1, WW|BM,  MM1,	REG_CL,		NNN, NNN,						CF | OF | SF | ZF | PF | AF,								C_S_MEM,			     NNN,     SK("SHL")},			// SHL MM,cl -> 1101 001w: mod 100 r/m
	{ 0x00F8FE, 0x00E0C0, 1, WW,  MDR2R,	IMM8,		NNN, NNN,						CF | OF | SF | ZF | PF | AF,								C_D2S_NN,			     NNN,     SK("SHL")},			// SHL r1,IM -> 1100 000w: 11 100 reg: NNN
	{ 0x0038FE, 0x0020C0, 1, WW|BM,  MM1,	IMM8S,		NNN, NNN,						CF | OF | SF | ZF | PF | AF,								C_S_MEM,			     NNN,     SK("SHL")},			// SHL MM,IM -> 1100 000w: mod 100 r/m: NNN

	{ 0x0038FE, 0x0030C0, 1, WW|BM,  MM1,	IMM8S,		NNN, NNN,						CF | OF | SF | ZF | PF | AF,								C_S_MEM,			     AF,     SK("SAL")},			// ??? SAL MM,IM -> 1100 000w: mod 100 r/m: NNN
	{ 0x00F8FE, 0x00F0D0, 1, WW,  MDR2R,	IMM1,		NNN, NNN,						CF | OF | SF | ZF | PF | AF,								C_D2S_NN,			     AF,     SK("SAL")},			// SAL r1,1


	{ 0xC0FFFF, 0xC0A40F, 2, 0,   MDR1R,	MDR2R,		IMMI8,NNN,						CF | SF | ZF | PF | OF | AF,								C_D2S_NN,			     AF|OF,     SK("SHLD")},		// SHLD r1,IM ->0000 1111: 1010 0100: 11 r2 r1: NNN
	{ 0x00FFFF, 0x00A40F, 2, BM,   MM1,		MDR1R,		IMMI8,NNN,						CF | SF | ZF | PF | OF | AF,								C_S_MEM,			     AF|OF,     SK("SHLD")},		// SHLD MM,IM ->0000 1111: 1010 0100:mod reg r/m:IM8
	{ 0xC0FFFF, 0xC0A50F, 2, 0,   MDR1R,	MDR2R,		REG_CL_I,NNN,					CF | SF | ZF | PF | OF | AF,								C_S_CL_N,			     AF|OF,     SK("SHLD")},		// SHLD r1,cl ->0000 1111: 1010 0101: 11 r2 r2
	{ 0x00FFFF, 0x00A50F, 2, BM,   MM1,		MDR1R,		REG_CL_I,R_CL,					CF | SF | ZF | PF | OF | AF,								C_S_MEM,			     AF|OF,     SK("SHLD")},		// SHLD MM,cl ->0000 1111: 1010 0101: mod reg r/m

	
	{ 0x00F8FE, 0x00E8D0, 1, WW,  MDR2R,	IMM1,		NNN, NNN,						CF | OF | SF | ZF | PF | AF,								C_D2S_NN,			     AF,     SK("SHR")},			// SHR r1,1 -> 1101 000w: 11 101 reg
	{ 0x0038FE, 0x0028D0, 1, WW|BM,  MM1,	IMM1,		NNN, NNN,						CF | OF | SF | ZF | PF | AF,								C_S_MEM,			     AF,     SK("SHR")},			// SHR MM,1 -> 1101 000w: mod 101 r/m
	{ 0x00F8FE, 0x00E8D2, 1, WW,  MDR2R,	REG_CL,		NNN, NNN,						CF | OF | SF | ZF | PF | AF,								C_D2S_NN,			     AF,     SK("SHR")},			// SHR r1,cl -> 1101 001w: 11 101 reg
	{ 0x0038FE, 0x0028D2, 1, WW|BM,  MM1,	REG_CL,		NNN, NNN,						CF | OF | SF | ZF | PF | AF,								C_S_MEM,			     AF,     SK("SHR")},			// SHR MM,cl -> 1101 001w: mod 101 r/m
	{ 0x00F8FE, 0x00E8C0, 1, WW,  MDR2R,	IMM8,		NNN, NNN,						CF | OF | SF | ZF | PF | AF,								C_D2S_NN,			     AF,     SK("SHR")},			// SHR r1,IM -> 1100 000w: 11 101 XXX: NNN
	{ 0x0038FE, 0x0028C0, 1, WW|BM,  MM1,	IMM8S,		NNN, NNN,						CF | OF | SF | ZF | PF | AF,								C_S_MEM,			     AF,     SK("SHR")},			// SHR MM,IM -> 1100 000w: mod 101 r/m: NNN

	{ 0xC0FFFF, 0xC0AC0F, 2, 0,   MDR1R,	MDR2R,		IMMI8,NNN,						CF | SF | ZF | PF | OF | AF,								C_D2S_NN,			     AF|OF,     SK("SHRD")},		// SHRD r1,IM->0000 1111: 1010 1100: 11 r2 r1: NNN
	{ 0x00FFFF, 0x00AC0F, 2, BM,   MM1,		MDR1R,		IMMI8,NNN,						CF | SF | ZF | PF | OF | AF,								C_S_MEM,			     AF|OF,     SK("SHRD")},		// SHRD MM,IM->0000 1111: 1010 1100:mod reg r/m:NNN
	{ 0xC0FFFF, 0xC0AD0F, 2, 0,   MDR1R,	MDR2R,		REG_CL_I,R_CL,					CF | SF | ZF | PF | OF | AF,								NNN,				     AF|OF,     SK("SHRD")},		// SHRD r1,cl->00001111: 1010 1101: 11 r2 r1 *TEST*C_S_CL_N
	{ 0x00FFFF, 0x00AD0F, 2, BM,   MM1,		MDR1R,		REG_CL_I,R_CL,					CF | SF | ZF | PF | OF | AF,								C_S_MEM,			     AF|OF,     SK("SHRD")},		// SHRD MM,cl->00001111:1010 1101: mod reg r/m

	{ 0xF8FFFF, 0xE0010F, 2, IPRIV|IRARE,   MDR2R_16,	NNN,		NNN, NNN,						NNN,														C_NNN,				     NNN,     SK("SMSW")},		// SMSW to r1 -> 0000 1111: 0000 0001: 11 100 r1
	{ 0x38FFFF, 0x20010F, 2, IPRIV|IRARE,   MM1_16,	NNN,		NNN, NNN,						NNN,														C_NNN,				     NNN,     SK("SMSW")},		// SMSW to MM -> 0000 1111: 0000 0001: mod 100 r/m
	{ 0x0000FF, 0x0000F9, 1, 0,   NNN,		NNN,		NNN, NNN,						CF,															C_NNN,				     NNN,     SK("STC")},			// STC -> 1111 1001
	{ 0x0000FF, 0x0000FD, 1, 0,   NNN,		NNN,		NNN, NNN,						DF,															C_NNN,				     NNN,     SK("STD")},			// STD -> 1111 1101
	{ 0x0000FF, 0x0000FB, 1, 0,   NNN,		NNN,		NNN, NNN,						IF,															C_NNN,				     NNN,     SK("STI")},			// STI -> 1111 1011
	{ 0x0000FE, 0x0000AA, 1, WW|NA,NNN,		NNN,		NNN, DF | R_EAX | R_EDI,		R_EDI,														NNN,			     NNN,     SK("STOS*")},		// STOSB -> 1010 101w
	{ 0xF8FFFF, 0xC8000F, 2, IPRIV|IRARE,   MDR2R_16, NNN,		NNN, NNN,						NNN,														C_D2SN,				     NNN,     SK("STR")},			// STR to r1 -> 0000 1111: 0000 0000: 11 001 reg
	{ 0x38FFFF, 0x08000F, 2, IPRIV|IRARE,   MM1_16,	NNN,		NNN, NNN,						NNN,														C_NNN,				     NNN,     SK("STR")},			// STR to MM -> 0000 1111: 0000 0000: mod 001 r/m

	{ 0x00C0FE, 0x00C028, 1, WW,  MDR1R,	MDR2R,		NNN, NNN,						OF | SF | ZF | AF| PF | CF,									C_D2S_NN,			     NNN,     SK("SUB")},			// SUB r1,r2 -> 0010 100w: 11 r1 r2
	{ 0x00C0FE, 0x00C02A, 1, WW,  MDR1,		MDR2,		NNN, NNN,						OF | SF | ZF | AF| PF | CF,									C_D2S_NN,			     NNN,     SK("SUB")},			// SUB r2,r1 -> 0010 101w: 11 r1 r2
	{ 0x0000FE, 0x00002A, 1, WW|BM,  MDR1,	MM2,		NNN, NNN,						OF | SF | ZF | AF| PF | CF,									C_S_MEM,			     NNN,     SK("SUB")},			// SUB MM,r1 -> 0010 101w: mod reg r/m
	{ 0x0000FE, 0x000028, 1, WW,  MDR1R,	MM1,		NNN, NNN,						OF | SF | ZF | AF| PF | CF,									C_NNN,				     NNN,     SK("SUB")},			// SUB r1,MM -> 0010 100w: mod reg r/m
	{ 0x00F8FC, 0x00E880, 1, WS,  MDR2R,	IMM,		NNN, NNN,						OF | SF | ZF | AF| PF | CF,									C_D2S_NN,			     NNN,     SK("SUB")},			// SUB r1,IM -> 1000 00sw: 11 101 r1: NNN
	{ 0x0000FE, 0x00002C, 1, WW,  ACC,		IMMC,		NNN, NNN,						OF | SF | ZF | AF| PF | CF,									C_D2S_NN,			     NNN,     SK("SUB")},			// SUB AC,IM -> 0010 110w: NNN
	{ 0x0038FC, 0x002880, 1, WS|BM,  MM1,	IMMS,		NNN, NNN,						OF | SF | ZF | AF| PF | CF,									C_S_MEM,			     NNN,     SK("SUB")},			// SUB MM,IM -> 1000 00sw: mod 101 r/m: NNN


	{ 0x00C0FE, 0x00C084, 1, WW,  MDR1,		MDR2,		NNN, NNN,						OF | CF | SF | ZF | PF | AF,								C_D2SN,				     AF,     SK("TEST")},		// TEST r1,r2 -> 1000 010w: 11 r1 r2
	{ 0x0000FE, 0x000084, 1, WW,  MM1,		MDR1R,		NNN, NNN,						OF | CF | SF | ZF | PF | AF,								C_SND_MEM,			     AF,     SK("TEST")},		// TEST MM,r1 -> 1000 010w: mod reg r/m
	{ 0x00F8FE, 0x00C0F6, 1, WW,  MDR2R,	IMM,		NNN, NNN,						OF | CF | SF | ZF | PF | AF,								C_D2SN,				     AF,     SK("TEST")},		// TEST r1,IM -> 1111 011w: 11 000 r1: NNN
	{ 0x0000FE, 0x0000A8, 1, WW,  ACC,		IMMC,		NNN, NNN,						OF | CF | SF | ZF | PF | AF,								C_D2SN,				     AF,     SK("TEST")},		// TEST AC,IM -> 1010 100w: NNN
	{ 0x0038FE, 0x0000F6, 1, WW,  MM1,		IMMS,		NNN, NNN,						OF | CF | SF | ZF | PF | AF,								C_SND_MEM,			     AF,     SK("TEST")},		// TEST MM,IM -> 1111 011w: mod 000 r/m: NNN

	{ 0x00FFF0, 0x000B00, 2, IRARE,   NNN,		NNN,		NNN, NNN,						NNN,														C_NNN,				     NNN,     SK("UD2")},			// UD2 -> 0000 FFFF: 0000 1011
	{ 0xF8FFFF, 0xE0000F, 2, IPRIV|IRARE,   MDR2R_16,	NNN,		NNN, NNN,						ZF,															C_NNN,				     NNN,     SK("VERR")},		// VERR r1 -> 0000 1111: 0000 0000: 11 100 r1
	{ 0x38FFFF, 0x20000F, 2, IPRIV|IRARE,   MM1_16,	NNN,		NNN, NNN,						ZF,															C_NNN,				     NNN,     SK("VERR")},		// VERR MM -> 0000 1111: 0000 0000: mod 100 r/m
	{ 0xF8FFFF, 0xE8000F, 2, IPRIV|IRARE,   MDR2R_16,	NNN,		NNN, NNN,						ZF,															C_NNN,				     NNN,     SK("VERW")},		// VERW r1 -> 0000 1111: 0000 0000: 11 101 reg
	{ 0x38FFFF, 0x28000F, 2, IPRIV|IRARE,   MM1_16,	NNN,		NNN, NNN,						ZF,															C_NNN,				     NNN,     SK("VERW")},		// VERW MM -> 0000 1111: 0000 0000: mod 101 r/m


	
	{ 0x00FFFF, 0x00090F, 2, IPRIV|IRARE,   NNN,		NNN,		NNN, NNN,						NNN,														C_NNN,				     NNN,     SK("WBINVD")},		// WBINVD -> 0000 1111: 0000 1001
	{ 0x00FFFF, 0x00300F, 2, IPRIV|IRARE,   NNN,		NNN,		NNN, R_EAX | R_EDX | R_ECX,		NNN,														C_NNN,				     NNN,     SK("WRMSR")},		// WRMSR -> 0000 1111: 0011 0000

	{ 0xC0FEFF, 0xC0C00F, 2, WW,  MDR1R,	MDR2R,		NNN, NNN,						CF | PF | AF | SF | ZF | OF,								C_D2S_NN,			     NNN,     SK("XADD")},		// XADD r1,r2 -> 0000 1111: 1100 000w: 11 r2 r2
	{ 0x00FEFF, 0x00C00F, 2, WW,  MM1,		MDR1R,		NNN, NNN,						CF | PF | AF | SF | ZF | OF,								C_S_MEM,			     NNN,     SK("XADD")},		// XADD MM,r1 -> 0000 1111: 1100 000w: mod reg r/m
	{ 0x00C0FE, 0x00C086, 1, WW,  MDR1,		MDR2,		NNN, NNN,						NNN,														C_DOS,				     NNN,     SK("XCHG")},		// XCHG r1,r2 -> 1000 011w: 11 r2 r2
	{ 0x0000F8, 0x000090, 1, 0,   ACC,		MDR2_AA,	NNN, NNN,						NNN,														C_DOS,				     NNN,     SK("XCHG")},		// XCHG AC,r1 -> 1001 0 reg
	{ 0x0000FE, 0x000086, 1, WW,  MM1,		MDR1R,		NNN, NNN,						NNN,														C_DOSM,				     NNN,     SK("XCHG")},		// XCHG MM,r1 -> 1000 011w: mod reg r/m
	{ 0x0000FF, 0x0000D7, 1, 0,   NNN,		NNN,		NNN, R_AL | R_EBX,				R_AL,														C_NNN,				     NNN,     SK("XLAT")},		// XLAT -> 1101 0111

	{ 0x00C0FE, 0x00C030, 1, WW,  MDR1R,	MDR2R,		NNN, NNN,						OF | CF | SF | ZF | PF | AF,								C_D2S_NN,			     AF,     SK("XOR")},			// XOR r1,r2 -> 0011 000w: 11 r1 r2
	{ 0x00C0FE, 0x00C032, 1, WW,  MDR1,		MDR2,		NNN, NNN,						OF | CF | SF | ZF | PF | AF,								C_D2S_NN,			     AF,     SK("XOR")},			// XOR r2,r1 -> 0011 001w: 11 r2 r2
	{ 0x0000FE, 0x000032, 1, WW|BM,MDR1,	MM2,		NNN, NNN,						OF | CF | SF | ZF | PF | AF,								C_S_MEM,			     AF,     SK("XOR")},			// XOR MM,r1 -> 0011 001w: mod reg r/m
	{ 0x0000FE, 0x000030, 1, WW,  MDR1R,	MM1,		NNN, NNN,						OF | CF | SF | ZF | PF | AF,								C_NNN,				     AF,     SK("XOR")},			// XOR r1,MM -> 0011 000w: mod reg r/m
	{ 0x00F8FC, 0x00F080, 1, WS,  MDR2R,	IMM,		NNN, NNN,						OF | CF | SF | ZF | PF | AF,								C_D2S_NN,			     AF,     SK("XOR")},			// XOR r1,IM -> 1000 00sw: 11 110 r1: NNN
	{ 0x0000FE, 0x000034, 1, WW,  ACC,		IMMC,		NNN, NNN,						OF | CF | SF | ZF | PF | AF,								C_D2S_NN,			     AF,     SK("XOR")},			// XOR AC,IM -> 0011 010w: NNN
	{ 0x0038FC, 0x003080, 1, WS|BM,MM1,		IMMS,		NNN, NNN,						OF | CF | SF | ZF | PF | AF,								C_S_MEM,			     AF,     SK("XOR")},			// XOR MM,IM -> 1000 00sw: mod 110 r/m: IM  *crap*
	{ 0x38FFFF, 0x08C70F, 2, BM,   MM1,		MDR1R,		NNN, R_EDX | R_EAX | R_ECX | R_EBX,	R_EDX | R_EAX | ZF | CF | PF | AF | SF | OF,			C_NNN,				     NNN,     SK("CMPXCHG8B")},	// CMPXCHG8B MM,r1 -> 0000 1111: 1100 0111: mod 0001 r/m

	{ 0x00FFFF, 0x00340F, 2, 0,		NNN,	NNN,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("SYSENTER")},	// SYSENTER
	{ 0x00FFFF, 0x00350F, 2, IPRIV|IRARE,		NNN,	NNN,		NNN, NNN,						NNN,														NNN,				     NNN,     SK("SYSEXIT")},	// SYSEXIT


	{ 0xC0F0FF, 0xC0400F, 2, 0,	  JTTTN,    MDR1,		MDR2, NNN,						NNN,														NNN,			     NNN,     SK("CMOVcc")},
	{ 0x00F0FF, 0x00400F, 2, 0,	  JTTTN,    MDR1,		MM2, NNN,						NNN,														NNN,			     NNN,     SK("CMOVcc")},



	


	// fpu mutinstructions 
    // wait + fpu exceptions

	/*
	{ 0x00FFFFFF, 0x00E2DB9B, 3, 0,	  NNN,		NNN,		NNN, NNN,						NNN,														NNN,			     NNN,     SK("FCLEX")},		// FCLEX
	{ 0x0038FFFF, 0x0030DD9B, 2, 0,	  FPU_MEM80D,	NNN,	NNN, R_ALL_ST | R_ALL_MMX | R_ALL_XMM,	NNN,												NNN,			     NNN,     SK("FSAVE")},		// it should be 108byte mem
	{ 0x0038FFFF, 0x0030D99B, 2, 0,	  FPU_MEM80D,	NNN,	NNN, NNN,						NNN,														NNN,			     NNN,     SK("FSTENV")},		// it should be 28byte mem
	{ 0x0038FFFF, 0x0038D99B, 2, 0,	  FPU_MEM16D,	NNN,	NNN, NNN,						NNN,														NNN,			     NNN,     SK("FSTCW")},
	{ 0x0038FFFF, 0x0038DD9B, 2, 0,	  FPU_MEM16D,	NNN,	NNN, NNN,						NNN,														NNN,			     NNN,     SK("FSTSW")},
	{ 0x00FFFFFF, 0x00E0DF9B, 3, 0,	  NNN,		NNN,		NNN, NNN,						R_AX,														NNN,			     NNN,     SK("FSTSW")},		// 
*/



	// normal
	{ 0x00FFFF, 0x00E8D9, 2, 0,	  NNN,		NNN,		NNN, NNN,						R_ST0,														NNN,			     NNN,     SK("FLD1")},		// FLD1
	{ 0x00FFFF, 0x00EAD9, 2, 0,	  NNN,		NNN,		NNN, NNN,						R_ST0,														NNN,			     NNN,     SK("FLDL2E")},		// 
	{ 0x00FFFF, 0x00E9D9, 2, 0,	  NNN,		NNN,		NNN, NNN,						R_ST0,														NNN,			     NNN,     SK("FLDL2T")},		// 
	{ 0x00FFFF, 0x00E8D9, 2, 0,	  NNN,		NNN,		NNN, NNN,						R_ST0,														NNN,			     NNN,     SK("FLDLG2")},		// 
	{ 0x00FFFF, 0x00ECD9, 2, 0,	  NNN,		NNN,		NNN, NNN,						R_ST0,														NNN,			     NNN,     SK("FLDLN2")},		//
	{ 0x00FFFF, 0x00EBD9, 2, 0,	  NNN,		NNN,		NNN, NNN,						R_ST0,														NNN,			     NNN,     SK("FLDPI")},		// 
	{ 0x00FFFF, 0x00EED9, 2, 0,	  NNN,		NNN,		NNN, NNN,						R_ST0,														NNN,			     NNN,     SK("FLDZ")},		// 

	{ 0x00FFFF, 0x00EED9, 2, 0,	  NNN,		NNN,		NNN, NNN,						R_ST0,														NNN,			     NNN,     SK("FNOP")},		// 
	{ 0x00FFFF, 0x00D0D9, 2, 0,	  NNN,		NNN,		NNN, NNN,						R_ST0,														NNN,			     NNN,     SK("FPATAN")},		// 
	{ 0x00FFFF, 0x00F3D9, 2, 0,	  NNN,		NNN,		NNN, NNN,						R_ST0,														NNN,			     NNN,     SK("FPREM")},		// 
	{ 0x00FFFF, 0x00F5D9, 2, 0,	  NNN,		NNN,		NNN, NNN,						R_ST0,														NNN,			     NNN,     SK("FPREM1")},		// 
	{ 0x00FFFF, 0x00F2D9, 2, 0,	  NNN,		NNN,		NNN, NNN,						R_ST0,														NNN,			     NNN,     SK("FPTAN")},		// 
	{ 0x00FFFF, 0x00FCD9, 2, 0,	  NNN,		NNN,		NNN, NNN,						R_ST0,														NNN,			     NNN,     SK("FRNDINT")},		//  
	{ 0x00FFFF, 0x00FDD9, 2, 0,	  NNN,		NNN,		NNN, NNN,						R_ST0,														NNN,			     NNN,     SK("FSCALE")},		// 
	{ 0x00FFFF, 0x00FED9, 2, 0,	  NNN,		NNN,		NNN, NNN,						R_ST0,														NNN,			     NNN,     SK("FSIN")},		// 
	{ 0x00FFFF, 0x00FBD9, 2, 0,	  NNN,		NNN,		NNN, NNN,						R_ST0,														NNN,			     NNN,     SK("FSINCOS")},		// 
	{ 0x00FFFF, 0x00FBD9, 2, 0,	  NNN,		NNN,		NNN, NNN,						R_ST0,														NNN,			     NNN,     SK("FSQRT")},		// 
	{ 0x00FFFF, 0x00E4D9, 2, 0,	  NNN,		NNN,		NNN, NNN,						R_ST0,														NNN,			     NNN,     SK("FTST")},		// 
	{ 0x00FFFF, 0x00E0DF, 2, 0,	  NNN,		NNN,		NNN, NNN,						R_AX,														NNN,			     NNN,     SK("FSTSW")},		// 

	{ 0x00F8FF,	0x00C0DA, 1, 0,   FPU_REG,		NNN,	NNN, CF,						NNN,														NNN,			     NNN,     SK("FCMOVB")},
	{ 0x00F8FF,	0x00C8DA, 1, 0,   FPU_REG,		NNN,	NNN, ZF,						NNN,														NNN,			     NNN,     SK("FCMOVE")},
	{ 0x00F8FF,	0x00D0DA, 1, 0,   FPU_REG,		NNN,	NNN, CF | ZF,					NNN,														NNN,			     NNN,     SK("FCMOVBE")},
	{ 0x00F8FF,	0x00D8DA, 1, 0,   FPU_REG,		NNN,	NNN, PF,						NNN,														NNN,			     NNN,     SK("FCMOVU")},
	{ 0x00F8FF,	0x00C0DB, 1, 0,   FPU_REG,		NNN,	NNN, CF,						NNN,														NNN,			     NNN,     SK("FCMOVNB")},
	{ 0x00F8FF,	0x00C8DB, 1, 0,   FPU_REG,		NNN,	NNN, ZF,						NNN,														NNN,			     NNN,     SK("FCMOVNE")},
	{ 0x00F8FF,	0x00D8DB, 1, 0,   FPU_REG,		NNN,	NNN, CF | ZF,					NNN,														NNN,			     NNN,     SK("FCMOVNBE")},
	{ 0x00F8FF,	0x00D8DB, 1, 0,   FPU_REG,		NNN,	NNN, PF,						NNN,														NNN,			     NNN,     SK("FCMOVNU")},

	{ 0x00FFFF, 0x00F0D9, 2, 0,	  NNN,		NNN,		NNN, R_ST0,						R_ST0,														NNN,			     NNN,     SK("F2XM1")},		// F2XM1
	{ 0x00FFFF, 0x00E1D9, 2, 0,	  NNN,		NNN,		NNN, R_ST0,						R_ST0,														NNN,			     NNN,     SK("FABS")},		// FABS
	{ 0x00F8FF, 0x00C0DE, 1, FPU_DBIT,FPU_REG,NNN,		NNN, R_ST0,						NNN,														C_D2S_NN,		     NNN,     SK("FADDP")},		// FADDP	(pseudo DBIT)
	{ 0x00F8FB, 0x00C0D8, 1, FPU_DBIT,FPU_REG,NNN,		NNN, R_ST0,						NNN,														C_D2S_NN,		     NNN,     SK("FADD")},		// FADD(d)		
	{ 0x0038F9, 0x0000D8, 1, 0,	  FPU_MEM,	NNN,		NNN, R_ST0,						R_ST0,														NNN,			     NNN,     SK("FADDMEM")},		// FADD
	{ 0x00F8FF, 0x00F0DF, 1, 0,	  FPU_REG,	NNN,		NNN, R_ST0,						ZF | CF | PF,												C_FPU_CMP,		     NNN,     SK("FCOMIP")},
	{ 0x00F8FF, 0x00F0DB, 1, 0,	  FPU_REG,	NNN,		NNN, R_ST0,						ZF | CF | PF,												C_FPU_CMP,		     NNN,     SK("FCOMI")},

	{ 0x0038FF, 0x0020DF, 1, 0,	  FPU_MEM80S,NNN,		NNN, NNN,						R_ST0,														NNN,			     NNN,     SK("FBLD")},		// FBLD
	{ 0x0038FF, 0x0030DF, 1, 0,	  FPU_MEM80D,NNN,		NNN, R_ST0,						NNN,														NNN,			     NNN,     SK("FBSTP")},		// FBSTP	
	{ 0x00FFFF, 0x00E0D9, 2, 0,	  NNN,		NNN,		NNN, R_ST0,						R_ST0,														NNN,			     NNN,     SK("FCHS")},		// FCHS
	{ 0x00FFFF, 0x00E2DB, 2, 0,	  NNN,		NNN,		NNN, NNN,						NNN,														NNN,			     NNN,     SK("FCLEX")},		// FCLEX
	{ 0x00FFFF, 0x00FFD9, 2, 0,	  NNN,		NNN,		NNN, R_ST0,						R_ST0,														NNN,			     NNN,     SK("FCOS")},		// FCOS
	{ 0x00FFFF, 0x00F6D9, 2, 0,	  NNN,		NNN,		NNN, NNN,						NNN,														NNN,			     NNN,     SK("FDECSTP")},		// FDECSTP
	{ 0x00FFFF, 0x00E9DA, 2, 0,	  0,		NNN,		NNN, R_ST0 | R_ST1,				NNN,														C_FPU_CMP,		     NNN,     SK("FUCOMPP")},	

	{ 0x00FFFF, 0x00E5D9, 2, 0,	  0,		NNN,		NNN, R_ST0,						R_ST0,														NNN,			     NNN,     SK("FXAM")},	
	{ 0x00FFFF, 0x00F4D9, 2, 0,	  0,		NNN,		NNN, R_ST0,						R_ST0,														NNN,			     NNN,     SK("FXTRACT")},	
	{ 0x00FFFF, 0x00F1D9, 2, 0,	  0,		NNN,		NNN, R_ST0,						R_ST0,														NNN,			     NNN,     SK("FYL2X")},	
	{ 0x00FFFF, 0x00F9D9, 2, 0,	  0,		NNN,		NNN, R_ST0,						R_ST0,														NNN,			     NNN,     SK("FYL2XP1")},	
	
	{ 0x00F8FF, 0x00C8D9, 1, 0,   FPU_REG,  NNN,        NNN, R_ST0,                     R_ST0,                                                      NNN,                 NNN,     SK("FXCH")},

	

	{ 0x00F8FF, 0x00D0D8, 1, 0,	  FPU_REG,	NNN,		NNN, R_ST0,						NNN,														C_FPU_CMP,		     NNN,     SK("FCOM")},
	{ 0x0038F9, 0x0010D8, 1, 0,	  FPU_MEM,	NNN,		NNN, R_ST0,						NNN,														NNN,			     NNN,     SK("FCOM")},

	{ 0x00FFFF, 0x00D9DE, 2, 0,	  NNN,	NNN,			NNN, R_ST0 | R_ST1,				NNN,														C_FPU_CMP,		     NNN,     SK("FCOMPP")},
	{ 0x00F8FF, 0x00D8D8, 1, 0,	  FPU_REG,	NNN,		NNN, R_ST0,						NNN,														C_FPU_CMP,		     NNN,     SK("FCOMP")},
	{ 0x0038F9, 0x0018D8, 1, 0,	  FPU_MEM,	NNN,		NNN, R_ST0,						NNN,														NNN,			     NNN,     SK("FCOMP")},
	{ 0x00F8FF, 0x00E8DB, 1, 0,	  FPU_REG,	NNN,		NNN, R_ST0,						ZF | CF | PF,												C_FPU_CMP,		     NNN,     SK("FUCOMI")},
	{ 0x00F8FF, 0x00E8DF, 1, 0,	  FPU_REG,	NNN,		NNN, R_ST0,						ZF | CF | PF,												C_FPU_CMP,		     NNN,     SK("FUCOMIP")},
	

	{ 0x00F8FF, 0x00F0DE, 1, 0,	  FPU_REG,  NNN,		NNN, R_ST0,						R_ST0,														NNN,			     NNN,     SK("FDIVRP")},
	{ 0x00F8FB, 0x00F8D8, 1, FPU_DBIT,	  FPU_REG,	NNN,	NNN, R_ST0,		NNN,																	C_D2S_NN,		     NNN,     SK("FDIV")},
	{ 0x00F8FB, 0x00F0D8, 1, FPU_DBIT,	  FPU_REG,	NNN,NNN, R_ST0,						NNN,														C_D2S_NN,		     NNN,     SK("FDIVR")},
	{ 0x0038F9, 0x0038D8, 1, 0,	  FPU_MEM,	NNN,		NNN, R_ST0,						R_ST0,														NNN,			     NNN,     SK("FDIVRMEM")},
	{ 0x0038F9, 0x0030D8, 1, 0,	  FPU_MEM,	NNN,		NNN, R_ST0,						R_ST0,														NNN,			     NNN,     SK("FDIVMEM")},
	
	{ 0x00F8FF, 0x00F8DE, 1, 0,	  FPU_REG,  NNN,		NNN, R_ST0,						R_ST0,														NNN,			     NNN,     SK("FDIVP")},

	{ 0x00F8FF, 0x00C0DD, 1, 0,	  FPU_REG,	NNN,		NNN, NNN,						NNN,														C_FPU_CMP,			     NNN,     SK("FFREE")},
	

	{ 0x00F8FF, 0x00C8DE, 1, FPU_DBIT,FPU_REG,	NNN,	NNN, R_ST0,						NNN,														C_D2S_NN,			     NNN,     SK("FMULP")},		
	{ 0x00F8FB, 0x00C8D8, 1, FPU_DBIT,FPU_REG,	NNN,	NNN, R_ST0,						NNN,														C_D2S_NN,			     NNN,     SK("FMUL")},	
	{ 0x0038F9, 0x0008D8, 1, 0,	  FPU_MEM,	NNN,		NNN, R_ST0,						R_ST0,														C_D2S_NN,			     NNN,     SK("FMULMEM")},
	
	{ 0x00F8FF, 0x00E8DE, 1, FPU_DBIT,FPU_REG,	NNN,	NNN, R_ST0,						NNN,														C_D2S_NN,			     NNN,     SK("FSUBP")},	
	{ 0x00F8FF, 0x00E0DE, 1, FPU_DBIT,FPU_REG,	NNN,	NNN, R_ST0,						NNN,														C_D2S_NN,			     NNN,     SK("FSUBRP")},	
	

	{ 0x00F8FB, 0x00E0D8, 1, FPU_DBIT,FPU_REG,	NNN,	NNN, R_ST0,						NNN,														C_D2S_NN,			     NNN,     SK("FSUB")},	
	{ 0x0038F9, 0x0020D8, 1, 0,	  FPU_MEM,	NNN,		NNN, R_ST0,						R_ST0,														C_D2S_NN,			     NNN,     SK("FSUBMEM")},
	
	{ 0x00F8FB, 0x00E8D8, 1, FPU_DBIT,FPU_REG,	NNN,	NNN, R_ST0,						NNN,														C_D2S_NN,			     NNN,     SK("FSUBR")},	
	{ 0x0038F9, 0x0028D8, 1, 0,	  FPU_MEM,	NNN,		NNN, R_ST0,						R_ST0,														C_D2S_NN,			     NNN,     SK("FSUBRMEM")},


	{ 0x0038FF, 0x0028DF, 1, 0,	  FPU_MEM64S,	NNN,	NNN, NNN,						R_ST0,														NNN,			     NNN,     SK("FILDM64")}, // 64
	{ 0x0038FF, 0x0000DF, 1, 0,	  FPU_MEM16S,	NNN,	NNN, NNN,						R_ST0,														NNN,			     NNN,     SK("FILDM16")}, // 16
	{ 0x0038FF, 0x0000DB, 1, 0,	  FPU_MEM32S,	NNN,	NNN, NNN,						R_ST0,														NNN,			     NNN,     SK("FILDM32")}, // 32
	
	{ 0x00FFFF, 0x00F7D9, 2, 0,	  NNN,		NNN,		NNN, NNN,						NNN,														NNN,			     NNN,     SK("FINCSTP")},
	{ 0x00FFFF, 0x00E3DB, 2, 0,	  NNN,		NNN,		NNN, NNN,						NNN,														NNN,			     NNN,     SK("FINIT")},
	
	{ 0x0038FF, 0x0038DF, 1, 0,	  FPU_MEM64D,	NNN,	NNN, R_ST0,						NNN,														NNN,			     NNN,     SK("FISTPM4")}, // 64
	{ 0x0038FF, 0x0018DF, 1, 0,	  FPU_MEM16D,	NNN,	NNN, R_ST0,						NNN,														NNN,			     NNN,     SK("FISTPM16")}, // 16
	{ 0x0038FF, 0x0018DB, 1, 0,	  FPU_MEM32D,	NNN,	NNN, R_ST0,						NNN,														NNN,			     NNN,     SK("FISTPM32")}, // 32
	
	{ 0x00F8FF, 0x00E0DD, 1, 0,	  FPU_REG,	NNN,	NNN, R_ST0,						NNN,														C_FPU_CMP,		     NNN,     SK("FUCOM")},	
	{ 0x00F8FF, 0x00E8DD, 1, 0,	  FPU_REG,	NNN,	NNN, R_ST0,						NNN,														C_FPU_CMP,		     NNN,     SK("FUCOMP")},	
	


	
	{ 0x0038FF, 0x0010DF, 1, 0,	  FPU_MEM16D,	NNN,	NNN, R_ST0,						NNN,														NNN,			     NNN,     SK("FISTM16")}, // 16
	{ 0x0038FF, 0x0010DB, 1, 0,	  FPU_MEM32D,	NNN,	NNN, R_ST0,						NNN,														NNN,			     NNN,     SK("FISTM32")}, // 32
	
	
	{ 0x00F8FF, 0x00D0DD, 1, FPU_DBIT,	  FPU_REG,		NNN,	NNN, R_ST0,				NNN,														NNN,			     NNN,     SK("FST")}, // r
	{ 0x0038FF, 0x0010D9, 1, 0,	  FPU_MEM32D,	NNN,	NNN, R_ST0,						NNN,														NNN,			     NNN,     SK("FSTM16")}, // 16
	{ 0x0038FF, 0x0010DD, 1, 0,	  FPU_MEM64D,	NNN,	NNN, R_ST0,						NNN,														NNN,			     NNN,     SK("FSTM32")}, // 32
	
	
	{ 0x00F8FF, 0x00D8DD, 1, FPU_DBIT,	  FPU_REG,		NNN,	NNN, R_ST0,				NNN,														NNN,			     NNN,     SK("FSTP")}, // r
	{ 0x0038FF, 0x0018D9, 1, 0,	  FPU_MEM32D,	NNN,	NNN, R_ST0,						NNN,														NNN,			     NNN,     SK("FSTPM16")}, // 16
	{ 0x0038FF, 0x0018DD, 1, 0,	  FPU_MEM64D,	NNN,	NNN, R_ST0,						NNN,														NNN,			     NNN,     SK("FSTPM32")}, // 32
	{ 0x0038FF, 0x0038DB, 1, 0,	  FPU_MEM80D,	NNN,	NNN, R_ST0,						NNN,														NNN,			     NNN,     SK("FSTPM80")}, // 80
	
	{ 0x0038FF, 0x0028DB, 1, 0,	  FPU_MEM80S,	NNN,	NNN, NNN,						R_ST0,														NNN,			     NNN,     SK("FLDM80")}, // 80
	{ 0x0038FF, 0x0000DD, 1, 0,	  FPU_MEM64S,	NNN,	NNN, NNN,						R_ST0,														NNN,			     NNN,     SK("FLDM64")}, // 64
	{ 0x0038FF, 0x0000D9, 1, 0,	  FPU_MEM32S,	NNN,	NNN, NNN,						R_ST0,														NNN,			     NNN,     SK("FLDM32")}, // 32
	

	{ 0x0038FF, 0x0028D9, 1, 0,	  FPU_MEM16S,	NNN,	NNN, NNN,						NNN,														NNN,			     NNN,     SK("FLDCW")}, 
	{ 0x0038FF, 0x0020D9, 1, 0,	  FPU_MEM80S,	NNN,	NNN, NNN,						NNN,														NNN,			     NNN,     SK("FLDENV")},		// it should be 28byte mem but fword it.

	{ 0x0038FF, 0x0020DD, 1, 0,	  FPU_MEM80S,	NNN,	NNN, NNN,						R_ALL_ST | R_ALL_MMX | R_ALL_XMM,							NNN,			     NNN,     SK("FRSTOR")},		// it should be 108byte mem but fword it.
	{ 0x0038FF, 0x0030DD, 1, 0,	  FPU_MEM80D,	NNN,	NNN, R_ALL_ST | R_ALL_MMX | R_ALL_XMM,	NNN,												NNN,			     NNN,     SK("FSAVE")},		// it should be 108byte mem but fword it.

	{ 0x0038FFFF, 0x008AE0F, 2, 0,	  FPU_MEM80S,	NNN,	NNN, NNN,						R_ALL_ST | R_ALL_MMX | R_ALL_XMM,							NNN,			     NNN,     SK("FXRSTOR")},		// it should be 108byte mem but fword it.
	{ 0x0038FFFF, 0x0000AE0F, 2, 0,	  FPU_MEM80D,	NNN,	NNN, R_ALL_ST | R_ALL_MMX | R_ALL_XMM,	NNN,												NNN,			     NNN,     SK("FXSAVE")},		// it should be 108byte mem but fword it.


	{ 0x0038FF, 0x0030D9, 1, 0,	  FPU_MEM80D,	NNN,	NNN, NNN,						NNN,														NNN,			     NNN,     SK("FSTENV")},		// it should be 28byte mem but fword it.
	{ 0x0038FF, 0x0038D9, 1, 0,	  FPU_MEM16D,	NNN,	NNN, NNN,						NNN,														NNN,			     NNN,     SK("FSTCW")},
	{ 0x0038FF, 0x0038DD, 1, 0,	  FPU_MEM16D,	NNN,	NNN, NNN,						NNN,														NNN,			     NNN,     SK("FSTSW_FPU")},





	// sse2

	{ 0xC0FFFFFF, 0xC0580F66, 3, ISSE,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("ADDPD")},
	{ 0x00FFFFFF, 0x00580F66, 3, ISSE,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("ADDPD")},

	{ 0xC0FFFFFF, 0xC0580FF2, 3, ISSE,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("ADDSD")},
	{ 0x00FFFFFF, 0x00580FF2, 3, ISSE,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("ADDSD")},

	{ 0xC0FFFFFF, 0xC0550F66, 3, ISSE,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("ANDNPD")},
	{ 0x00FFFFFF, 0x00550F66, 3, ISSE,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("ANDNPD")},

	{ 0xC0FFFFFF, 0xC0540F66, 3, ISSE,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("ANDPD")},
	{ 0x00FFFFFF, 0x00540F66, 3, ISSE,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("ANDPD")},

	{ 0xC0FFFF, 0xC0540F, 2, ISSE,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("ANDPS")},
	{ 0x00FFFF, 0x00540F, 2, ISSE,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("ANDPS")},


	{ 0xC0FFFFFF, 0xC0C20F66, 3, ISSE,   XMM_REG1D,    XMM_REG2S,IMM8,NNN,						NNN,														 NNN,		     NNN,     SK("CMPPD")},
	{ 0x00FFFFFF, 0x00C20F66, 3, ISSE,   XMM_REG1D,    XMM_MEM128S,IMM8S,NNN,						NNN,													 NNN,		     NNN,     SK("CMPPD")},

	{ 0xC0FFFFFF, 0xC0C20FF2, 3, ISSE,   XMM_REG1D,    XMM_REG2S,IMM8,NNN,						NNN,														 NNN,		     NNN,     SK("CMPSD")},
	{ 0x00FFFFFF, 0x00C20FF2, 3, ISSE,   XMM_REG1D,    XMM_MEM128S,IMM8S,NNN,						NNN,													 NNN,		     NNN,     SK("CMPSD")},

	{ 0xC0FFFFFF, 0xC02F0F66, 3, ISSE,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						ZF | PF | CF | OF | SF | AF,														 C_FPU_CMP,		     NNN,     SK("COMISD")},
	{ 0x00FFFFFF, 0x002F0F66, 3, ISSE,   XMM_REG1D,    MM2,NNN,NNN,					ZF | PF | CF | OF | SF | AF,														 C_FPU_CMP,		     NNN,     SK("COMISD")},


	{ 0xC0FFFFFF, 0xC02A0F66, 3, ISSE,   XMM_REG1D,    MMX_REG2S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("CVTPI2PD")},
	{ 0x00FFFFFF, 0x002A0F66, 3, ISSE,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("CVTPI2PD")},


	{ 0xC0FFFFFF, 0xC02A0FF2, 3, ISSE,   XMM_REG1D,    MDR2,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("CVTSI2SD")},
	{ 0x00FFFFFF, 0x002A0FF2, 3, ISSE,   XMM_REG1D,    FPU_MEM32S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("CVTSI2SD")},


	{ 0xC0FFFFFF, 0xC02D0FF2, 3, ISSE,   MDR1,    XMM_REG2S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("CVTSD2SI")},
	{ 0x00FFFFFF, 0x002D0FF2, 3, ISSE,   MDR1,    FPU_MEM32S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("CVTSD2SI")},

	{ 0xC0FFFFFF, 0xC02D0F66, 3, ISSE,   MMX_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("CVTPD2PI")},
	{ 0x00FFFFFF, 0x002D0F66, 3, ISSE,   MMX_REG1D,    MMX_MEM64S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("CVTPD2PI")},

	{ 0xC0FFFFFF, 0xC02C0F66, 3, ISSE,   MMX_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("CVTTPD2PI")},
	{ 0x00FFFFFF, 0x002C0F66, 3, ISSE,   MMX_REG1D,    MMX_MEM64S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("CVTTPD2PI")},

	{ 0xC0FFFFFF, 0xC02C0FF2, 3, ISSE,   MDR1,    XMM_REG2S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("CVTTSD2SI")},
	{ 0x00FFFFFF, 0x002C0FF2, 3, ISSE,   MDR1,    FPU_MEM32S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("CVTTSD2SI")},



	{ 0xC0FFFFFF,0xC0E60FF2, 3, ISSE,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("CVTPD2DQ")},
	{ 0x00FFFFFF,0x00E60FF2, 3, ISSE,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,													 NNN,		     NNN,     SK("CVTDQ2PD")},

	{ 0xC0FFFFFF,0xC0E60F66, 3, ISSE,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("CVTTPD2DQ")},
	{ 0x00FFFFFF,0x00E60F66, 3, ISSE,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,													 NNN,		     NNN,     SK("CVTTDQ2PD")},

	{ 0xC0FFFFFF,0xC05B0F66, 3, ISSE,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("CVTPS2DQ")},
	{ 0x00FFFFFF,0x005B0F66, 3, ISSE,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,													 NNN,		     NNN,     SK("CVTPS2DQ")},

	{ 0xC0FFFFFF,0xC05B0FF3, 3, ISSE,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("CVTTPS2DQ")},
	{ 0x00FFFFFF,0x005B0FF3, 3, ISSE,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,													 NNN,		     NNN,     SK("CVTTPS2DQ")},

	{ 0xC0FFFFFF,0xC05E0F66, 3, ISSE,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("DIVPD")},
	{ 0x00FFFFFF,0x005E0F66, 3, ISSE,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,													 C_D2S_NN,		     NNN,     SK("DIVPD")},

	{ 0xC0FFFFFF,0xC05E0FF2, 3, ISSE,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("DIVSD")},
	{ 0x00FFFFFF,0x005E0FF2, 3, ISSE,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,													 C_D2S_NN,		     NNN,     SK("DIVSD")},


	{ 0xC0FFFFFF,0xC05F0F66, 3, ISSE,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("MAXPD")},
	{ 0x00FFFFFF,0x005F0F66, 3, ISSE,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,													 C_D2S_NN,		     NNN,     SK("MAXPD")},

	{ 0xC0FFFFFF,0xC05F0FF2, 3, ISSE,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("MAXSD")},
	{ 0x00FFFFFF,0x005F0FF2, 3, ISSE,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,													 C_D2S_NN,		     NNN,     SK("MAXSD")},



	{ 0xC0FFFFFF,0xC05D0F66, 3, ISSE,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("MINPD")},
	{ 0x00FFFFFF,0x005D0F66, 3, ISSE,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,													 C_D2S_NN,		     NNN,     SK("MINPD")},

	{ 0xC0FFFFFF,0xC05D0FF2, 3, ISSE,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("MINSD")},
	{ 0x00FFFFFF,0x005D0FF2, 3, ISSE,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,													 C_D2S_NN,		     NNN,     SK("MINSD")},

	
	{ 0xC0FFFFFF, 0xC0290F66, 3, ISSE,	  XMM_REG1S,   XMM_REG2D,    NNN, NNN,						NNN,														NNN,			     NNN,     SK("MOVAPD")},
	{ 0x00FFFFFF, 0x00290F66, 3, ISSE,     XMM_REG1S,   XMM_MEM128D,NNN, NNN,						NNN,														NNN,			     NNN,     SK("MOVAPD")},			
	{ 0xC0FFFFFF, 0xC0280F66, 3, ISSE,	  XMM_REG1D,   XMM_REG2S,   NNN, NNN,						NNN,														NNN,			     NNN,     SK("MOVAPD")},
	{ 0x00FFFFFF, 0x00280F66, 3, ISSE,	 XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,												NNN,			     NNN,     SK("MOVAPD")},	
     
	
	{ 0x00FFFFFF,0x00170F66, 3, ISSE,   XMM_REG1S,    XMM_MEM128D,NNN,NNN,						NNN,													 NNN,		     NNN,     SK("MOVHPD")},
	{ 0x00FFFFFF,0x00160F66, 3, ISSE,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,													 NNN,		     NNN,     SK("MOVHPD")},

	{ 0x00FFFFFF,0x00130F66, 3, ISSE,   XMM_REG1S,    XMM_MEM128D,NNN,NNN,						NNN,													 NNN,		     NNN,     SK("MOVLPD")},
	{ 0x00FFFFFF,0x00120F66, 3, ISSE,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,													 NNN,		     NNN,     SK("MOVLPD")},

	{ 0xC0FFFFFF,0xC0500F66, 3, ISSE,   MDR1,    XMM_REG2S,NNN,NNN,						NNN,													 NNN,		     NNN,     SK("MOVMSKPD")},


	{ 0xC0FFFFFF, 0xC0110FF2, 3, ISSE,	  XMM_REG1S,   XMM_REG2D,    NNN, NNN,						NNN,														NNN,			     NNN,     SK("MOVSD")},
	{ 0x00FFFFFF, 0x00110FF2, 3, ISSE,     XMM_REG1S,   XMM_MEM128D,NNN, NNN,						NNN,														NNN,			     NNN,     SK("MOVSD")},			
	{ 0xC0FFFFFF, 0xC0100FF2, 3, ISSE,	  XMM_REG1D,   XMM_REG2S,   NNN, NNN,						NNN,														NNN,			     NNN,     SK("MOVSD")},
	{ 0x00FFFFFF, 0x00100FF2, 3, ISSE,	 XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,												NNN,			     NNN,     SK("MOVSD")},	
     
	{ 0xC0FFFFFF, 0xC0110F66, 3, ISSE,	  XMM_REG1S,   XMM_REG2D,    NNN, NNN,						NNN,														NNN,			     NNN,     SK("MOVUPD")},
	{ 0x00FFFFFF, 0x00110F66, 3, ISSE,     XMM_REG1S,   XMM_MEM128D,NNN, NNN,						NNN,														NNN,			     NNN,     SK("MOVUPD")},			
	{ 0xC0FFFFFF, 0xC0100F66, 3, ISSE,	  XMM_REG1D,   XMM_REG2S,   NNN, NNN,						NNN,														NNN,			     NNN,     SK("MOVUPD")},
	{ 0x00FFFFFF, 0x00100F66, 3, ISSE,	 XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,												NNN,			     NNN,     SK("MOVUPD")},	
     
	{ 0xC0FFFFFF, 0xC0590F66, 3, ISSE,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("MULPD")},
	{ 0x00FFFFFF, 0x00590F66, 3, ISSE,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,													 C_D2S_NN,		     NNN,     SK("MULPD")},

	{ 0xC0FFFFFF, 0xC0590FF2, 3, ISSE,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("MULSD")},
	{ 0x00FFFFFF, 0x00590FF2, 3, ISSE,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,													 C_D2S_NN,		     NNN,     SK("MULSD")},

	{ 0xC0FFFFFF, 0xC0560F66, 3, ISSE,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("ORPD")},
	{ 0x00FFFFFF, 0x00560F66, 3, ISSE,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,													 C_D2S_NN,		     NNN,     SK("ORPD")},


	{ 0xC0FFFFFF, 0xC0C60F66, 3, ISSE,   XMM_REG1D,    XMM_REG2S,IMM8,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("SHUFPD")},
	{ 0x00FFFFFF, 0x00C60F66, 3, ISSE,   XMM_REG1D,    XMM_MEM128S,IMM8,NNN,						NNN,													 C_D2S_NN,		     NNN,     SK("SHUFPD")},

	{ 0xC0FFFFFF, 0xC0510F66, 3, ISSE,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("SQRTPD")},
	{ 0x00FFFFFF, 0x00510F66, 3, ISSE,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,													 NNN,		     NNN,     SK("SQRTPD")},

	{ 0xC0FFFFFF, 0xC0510FF2, 3, ISSE,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("SQRTSD")},
	{ 0x00FFFFFF, 0x00510FF2, 3, ISSE,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,													 NNN,		     NNN,     SK("SQRTSD")},


	{ 0xC0FFFFFF, 0xC05C0F66, 3, ISSE,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("SUBPD")},
	{ 0x00FFFFFF, 0x005C0F66, 3, ISSE,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,													 C_D2S_NN,		     NNN,     SK("SUBPD")},


	{ 0xC0FFFFFF, 0xC05C0FF2, 3, ISSE,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("SUBSD")},
	{ 0x00FFFFFF, 0x005C0FF2, 3, ISSE,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,													 C_D2S_NN,		     NNN,     SK("SUBSD")},

	{ 0xC0FFFFFF, 0xC02E0F66, 3, ISSE,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						ZF | PF | CF | OF | SF | AF,														 C_MMX_CMP,		     NNN,     SK("UCOMISD")},
	{ 0x00FFFFFF, 0x002E0F66, 3, ISSE,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						ZF | PF | CF | OF | SF | AF,														 C_MMX_CMP,		     NNN,     SK("UCOMISD")},

	{ 0xC0FFFFFF, 0xC0150F66, 3, ISSE,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("UNPCKHPD")},
	{ 0x00FFFFFF, 0x00150F66, 3, ISSE,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,													 NNN,		     NNN,     SK("UNPCKHPD")},

	{ 0xC0FFFFFF, 0xC0140F66, 3, ISSE,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("UNPCKLPD")},
	{ 0x00FFFFFF, 0x00140F66, 3, ISSE,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,													 NNN,		     NNN,     SK("UNPCKLPD")},

	{ 0xC0FFFFFF, 0xC0570F66, 3, ISSE,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("XORPD")},
	{ 0x00FFFFFF, 0x00570F66, 3, ISSE,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,													 C_D2S_NN,		     NNN,     SK("XORPD")},

	{ 0xC0FFFFFF, 0xC06E0F66, 3, ISSE,	  XMM_REG1D,   MDR2,    NNN, NNN,						NNN,														NNN,			     NNN,     SK("MOVD")},
	{ 0xC0FFFFFF, 0xC07E0F66, 3, ISSE,     XMM_REG1S,   MDR2R,NNN, NNN,						NNN,														NNN,			     NNN,     SK("MOVD")},			
	{ 0x00FFFFFF, 0x006E0F66, 3, ISSE,	  XMM_REG1D,   XMM_MEM128S,   NNN, NNN,						NNN,														NNN,			     NNN,     SK("MOVD")},
	{ 0x00FFFFFF, 0x007E0F66, 3, ISSE,	 XMM_REG1S,   XMM_MEM128D,NNN, NNN,						NNN,												NNN,			     NNN,     SK("MOVD")},	
     
	{ 0xC0FFFFFF, 0xC06F0F66, 3, ISSE,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,														NNN,			     NNN,     SK("MOVDQA")},
	{ 0xC0FFFFFF, 0xC07F0F66, 3, ISSE,     XMM_REG1S,   XMM_REG2D,NNN, NNN,						NNN,														NNN,			     NNN,     SK("MOVDQA")},			
	{ 0x00FFFFFF, 0x006F0F66, 3, ISSE,	  XMM_REG1D,   XMM_MEM128S,   NNN, NNN,						NNN,														NNN,			     NNN,     SK("MOVDQA")},
	{ 0x00FFFFFF, 0x007F0F66, 3, ISSE,	 XMM_REG1S,   XMM_MEM128D,NNN, NNN,						NNN,												NNN,			     NNN,     SK("MOVDQA")},	

	{ 0xC0FFFFFF, 0xC06F0FF3, 3, ISSE,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,														NNN,			     NNN,     SK("MOVDQU")},
	{ 0xC0FFFFFF, 0xC07F0FF3, 3, ISSE,     XMM_REG1S,   XMM_REG2D,NNN, NNN,						NNN,														NNN,			     NNN,     SK("MOVDQU")},			
	{ 0x00FFFFFF, 0x006F0FF3, 3, ISSE,	  XMM_REG1D,   XMM_MEM128S,   NNN, NNN,						NNN,														NNN,			     NNN,     SK("MOVDQU")},
	{ 0x00FFFFFF, 0x007F0FF3, 3, ISSE,	 XMM_REG1S,   XMM_MEM128D,NNN, NNN,						NNN,												NNN,			     NNN,     SK("MOVDQU")},	

	{ 0xC0FFFFFF, 0xC0D60FF3, 3, ISSE,   XMM_REG1D,    MMX_REG2S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("MOVQ2DQ")},
	{ 0xC0FFFFFF, 0xC0D60FF2, 3, ISSE,   XMM_REG1S,    MMX_REG2D,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("MOVDQ2Q")},
		
	{ 0xC0FFFFFF, 0xC06B0F66, 3, ISSE,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,														NNN,			     NNN,     SK("PACKSSDW")},
	{ 0x00FFFFFF, 0x006B0F66, 3, ISSE,   XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														NNN,			     NNN,     SK("PACKSSDW")},			

	{ 0xC0FFFFFF, 0xC0630F66, 3, ISSE,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,														NNN,			     NNN,     SK("PACKSSWB")},
	{ 0x00FFFFFF, 0x00630F66, 3, ISSE,   XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														NNN,			     NNN,     SK("PACKSSWB")},			

	{ 0xC0FFFFFF, 0xC0670F66, 3, ISSE,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,														NNN,			     NNN,     SK("PACKUSWB")},
	{ 0x00FFFFFF, 0x00670F66, 3, ISSE,   XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														NNN,			     NNN,     SK("PACKUSWB")},			

	{ 0xC0FCFFFF, 0xC0FC0F66, 3, ISSE|MMX_GG,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PADD")},
	{ 0x00FCFFFF, 0x00FC0F66, 3, ISSE|MMX_GG,   XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PADD")},

	{ 0xC0FCFFFF, 0xC0EC0F66, 3, ISSE|MMX_GG,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PADDS")},
	{ 0x00FCFFFF, 0x00EC0F66, 3, ISSE|MMX_GG,   XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PADDS")},			

	{ 0xC0FCFFFF, 0xC0DC0F66, 3, ISSE|MMX_GG,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PADDUS")},
	{ 0x00FCFFFF, 0x00DC0F66, 3, ISSE|MMX_GG,   XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PADDUS")},			

	{ 0xC0FFFFFF, 0xC0DB0F66, 3, ISSE,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PAND")},
	{ 0x00FFFFFF, 0x00DB0F66, 3, ISSE,   XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PAND")},			

	{ 0xC0FFFFFF, 0xC0DF0F66, 3, ISSE,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PANDN")},
	{ 0x00FFFFFF, 0x00DF0F66, 3, ISSE,   XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PANDN")},			

	{ 0xC0FFFFFF, 0xC0E00F66, 3, ISSE,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,														NNN,			     NNN,     SK("PAVGB_SSE2")},
	{ 0x00FFFFFF, 0x00E00F66, 3, ISSE,   XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														NNN,			     NNN,     SK("PAVGB_SSE2")},			

	{ 0xC0FFFFFF, 0xC0E30F66, 3, ISSE,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,														NNN,			     NNN,     SK("PAVGW_SSE2")},
	{ 0x00FFFFFF, 0x00E30F66, 3, ISSE,   XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														NNN,			     NNN,     SK("PAVGW_SSE2")},			

	{ 0xC0FCFFFF, 0xC0740F66, 3, ISSE|MMX_GG,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,														C_MMX_CMP,			     NNN,     SK("PCMPEQ")},
	{ 0x00FCFFFF, 0x00740F66, 3, ISSE|MMX_GG,   XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														C_MMX_CMP,			     NNN,     SK("PCMPEQ")},			

	{ 0xC0FCFFFF, 0xC0640F66, 3, ISSE|MMX_GG,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,														C_MMX_CMP,			     NNN,     SK("PCMPGT")},
	{ 0x00FCFFFF, 0x00640F66, 3, ISSE|MMX_GG,   XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														C_MMX_CMP,			     NNN,     SK("PCMPGT")},			

	{ 0xC0FFFFFF, 0xC0C50F66, 3, ISSE,	  MDR1,   XMM_REG2S,    IMM8, NNN,						NNN,														NNN,			     NNN,     SK("PEXTRW_SSE2")},
	
	{ 0xC0FFFFFF, 0xC0C40F66, 3, ISSE,	  XMM_REG1D,   MDR2,    IMM8, NNN,						NNN,														NNN,			     NNN,     SK("PINSRW_SSE2")},
	{ 0x00FFFFFF, 0x00C40F66, 3, ISSE,	  XMM_REG1D,   FPU_MEM16S,    IMM8, NNN,						NNN,														NNN,			     NNN,     SK("PINSRW_SSE2")},
	
	{ 0xC0FFFFFF, 0xC0F50F66, 3, ISSE,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMADDWD")},
	{ 0x00FFFFFF, 0x00F50F66, 3, ISSE,   XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMADDWD")},			
	
	{ 0xC0FFFFFF, 0xC0EE0F66, 3, ISSE,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMAXSW")},
	{ 0x00FFFFFF, 0x00EE0F66, 3, ISSE,   XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMAXSW")},			

	{ 0xC0FFFFFF, 0xC0DE0F66, 3, ISSE,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMAXUB")},
	{ 0x00FFFFFF, 0x00DE0F66, 3, ISSE,   XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMAXUB")},			

	{ 0xC0FFFFFF, 0xC0EA0F66, 3, ISSE,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMINSW")},
	{ 0x00FFFFFF, 0x00EA0F66, 3, ISSE,   XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMINSW")},			

	{ 0xC0FFFFFF, 0xC0DA0F66, 3, ISSE,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMINUB")},
	{ 0x00FFFFFF, 0x00DA0F66, 3, ISSE,   XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMINUB")},			

	{ 0xC0FFFFFF, 0xC0D70F66, 3, ISSE,	  MDR1,   XMM_REG2S,    NNN, NNN,						NNN,														NNN,			     NNN,     SK("PMOVMSKB_SSE2")},

	{ 0xC0FFFFFF, 0xC0E40F66, 3, ISSE,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMULHUW")},
	{ 0x00FFFFFF, 0x00E40F66, 3, ISSE,   XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMULHUW")},			

	{ 0xC0FFFFFF, 0xC0E50F66, 3, ISSE,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMULHW")},
	{ 0x00FFFFFF, 0x00E50F66, 3, ISSE,   XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMULHW")},			

	{ 0xC0FFFFFF, 0xC0D50F66, 3, ISSE,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMULLW")},
	{ 0x00FFFFFF, 0x00D50F66, 3, ISSE,   XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMULLW")},			


	{ 0x00C0FFFF, 0x00C0F40F, 2, ISSE,	  MMX_REG1D,   MMX_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMULUDQ")},
	{ 0x0000FFFF, 0x0000F40F, 2, ISSE,   MMX_REG1D,   FPU_MEM80S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMULUDQ")},			
	{ 0xC0FFFFFF, 0xC0F40F66, 3, ISSE,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMULUDQ")},
	{ 0x00FFFFFF, 0x00F40F66, 3, ISSE,   XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMULUDQ")},			


	{ 0xC0FFFFFF, 0xC0EB0F66, 3, ISSE,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("POR")},
	{ 0x00FFFFFF, 0x00EB0F66, 3, ISSE,   XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("POR")},			

	{ 0xC0FFFFFF, 0xC0F60F66, 3, ISSE,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSADBW")},
	{ 0x00FFFFFF, 0x00F60F66, 3, ISSE,   XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSADBW")},			

	{ 0xC0FFFFFF, 0xC0700FF2, 3, ISSE,	  XMM_REG1D,   XMM_REG2S,    IMM8, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSHUFLW")},
	{ 0x00FFFFFF, 0x00700FF2, 3, ISSE,   XMM_REG1D,   XMM_MEM128S,IMM8, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSHUFLW")},			

	{ 0xC0FFFFFF, 0xC0700FF3, 3, ISSE,	  XMM_REG1D,   XMM_REG2S,    IMM8, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSHUFHW")},
	{ 0x00FFFFFF, 0x00700FF3, 3, ISSE,   XMM_REG1D,   XMM_MEM128S,IMM8, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSHUFHW")},			

	{ 0xC0FFFFFF, 0xC0700F66, 3, ISSE,	  XMM_REG1D,   XMM_REG2S,    IMM8, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSHUFD")},
	{ 0x00FFFFFF, 0x00700F66, 3, ISSE,   XMM_REG1D,   XMM_MEM128S,IMM8, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSHUFD")},			

	{ 0xF8FFFFFF, 0xF8730F66, 3, ISSE,	  XMM_REG1D,   IMM8,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSLLDQ")},
	

	{ 0xC0FCFFFF, 0xC0F00F66, 3, ISSE|MMX_GG,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSLL")},	// name changes based on GG	
	{ 0x00FCFFFF, 0x00F00F66, 3, ISSE|MMX_GG,XMM_REG1D,   MMX_MEMS,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSLL")},
	{ 0xF8FCFFFF, 0xF0700F66, 3, ISSE|MMX_GG,XMM_REG1D,   IMM8,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSLL")},

	{ 0xC0FCFFFF, 0xC0E00F66, 3, ISSE|MMX_GG,	XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSRA")},	// name changes based on GG	
	{ 0x00FCFFFF, 0x00E00F66, 3, ISSE|MMX_GG,XMM_REG1D,   MMX_MEMS,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSRA")},
	{ 0xF8FCFFFF, 0xE0700F66, 3, ISSE|MMX_GG,XMM_REG1D,   IMM8,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSRA")},

	{ 0xF8FFFFFF, 0xD8730F66, 3, ISSE,	  XMM_REG1D,   IMM8,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSRLDQ")},
	
	{ 0xC0FCFFFF, 0xC0D00F66, 3, ISSE|MMX_GG,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSRL")},	// name changes based on GG	
	{ 0x00FCFFFF, 0x00D00F66, 3, ISSE|MMX_GG,XMM_REG1D,   MMX_MEMS,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSRL")},
	{ 0xF8FCFFFF, 0xD0700F66, 3, ISSE|MMX_GG,XMM_REG1D,   IMM8,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSRL")},

	{ 0xC0FFFF, 0x00C0FB0F, 2, ISSE,   MMX_REG1D,    MMX_REG2S,NNN,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PSUBQ")},
	{ 0x00FFFF, 0x0000FB0F, 2, ISSE,   MMX_REG1D,    FPU_MEM80S,NNN,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PSUBQ")},
	{ 0xC0FFFFFF, 0xC0FB0F66, 3, ISSE,   XMM_REG1S,    XMM_REG2D,NNN,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PSUBQ")},
	{ 0x00FFFFFF, 0x00FB0F66, 3, ISSE,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("PSUBQ")},


	{ 0xC0FCFFFF, 0xC0F80F66, 3, ISSE|MMX_GG,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSUB")},	// name changes based on GG
	{ 0x00FCFFFF, 0x00F80F66, 3, ISSE|MMX_GG,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSUB")},

	{ 0xC0FCFFFF, 0xC0E80F66, 3, ISSE|MMX_GG,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSUBS")},	// name changes based on GG	
	{ 0x00FCFFFF, 0x00E80F66, 3, ISSE|MMX_GG,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSUBS")},

	{ 0xC0FCFFFF, 0xC0680F66, 3, ISSE|MMX_GG,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PUNPCKH")},	// name changes based on GG	
	{ 0x00FCFFFF, 0x00680F66, 3, ISSE|MMX_GG,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PUNPCKH")},

	{ 0xC0FCFFFF, 0xC06D0F66, 3, ISSE,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PUNPCKHQDQ")},	
	{ 0x00FCFFFF, 0x006D0F66, 3, ISSE,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PUNPCKHQDQ")},

	{ 0xC0FCFFFF, 0xC0600F66, 3, ISSE|MMX_GG,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PUNPCKL")},	// name changes based on GG	
	{ 0x00FCFFFF, 0x00600F66, 3, ISSE|MMX_GG,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PUNPCKL")},

	{ 0xC0FCFF, 0xC0600F, 2, ISSE|MMX_GG,	  MMX_REG1D,   MMX_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PUNPCKL")},	// name changes based on GG	
	{ 0x00FCFF, 0x00600F, 2, ISSE|MMX_GG,MMX_REG1D,   MMX_MEMS,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PUNPCKL")},


	{ 0xC0FCFFFF, 0xC06C0F66, 3, ISSE,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PUNPCKLQDQ")},	// name changes based on GG	
	{ 0x00FCFFFF, 0x006C0F66, 3, ISSE,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PUNPCKLQDQ")},

	{ 0xC0FFFFFF, 0xC0EF0F66, 3, ISSE,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													C_D2S_NN,			     NNN,     SK("PXOR")},	
	{ 0x00FFFFFF, 0x00EF0F66, 3, ISSE,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PXOR")},
	
	{ 0xC0FFFFFF, 0xC0F70F66, 3, ISSE,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													NNN,			     NNN,     SK("MASKMOVDQU")},	
	
	{ 0x0038FFFF, 0x0038AE0F, 2, ISSE,	  MM_8,   NNN,    NNN, NNN,						NNN,													NNN,			     NNN,     SK("CLFLUSH")},	
	
	{ 0x00FFFFFF, 0x002B0F66, 3, ISSE,XMM_REG1S,   XMM_MEM128D,NNN, NNN,						NNN,														NNN,			     NNN,     SK("MOVNTPD")},

	{ 0x00FFFFFF, 0x00E70F66, 3, ISSE,XMM_REG1S,   XMM_MEM128D,NNN, NNN,						NNN,														NNN,			     NNN,     SK("MOVNTDQ")},

	{ 0x00FFFFFF, 0x00E8AE0F, 3, ISSE, NNN,   NNN ,NNN, NNN,						NNN,														NNN,			     NNN,     SK("LFENCE")},
	{ 0x00FFFFFF, 0x00F0AE0F, 3, ISSE, NNN,   NNN ,NNN, NNN,						NNN,														NNN,			     NNN,     SK("MFENCE")},
	{ 0x0000FFFF, 0x000090F3, 2, ISSE, NNN,   NNN ,NNN, NNN,						NNN,														NNN,			     NNN,     SK("PAUSE")},

	// koniec sse2

	// sse3
	{ 0xC0FFFFFF, 0xC0D00F66, 3, ISSE,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													C_D2S_NN,			     NNN,     SK("ADDSUBPD")},	
	{ 0x00FFFFFF, 0x00D00F66, 3, ISSE,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("ADDSUBPD")},
	
	{ 0xC0FFFFFF, 0xC0D00FF2, 3, ISSE,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													C_D2S_NN,			     NNN,     SK("ADDSUBPS")},	
	{ 0x00FFFFFF, 0x00D00FF2, 3, ISSE,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("ADDSUBPS")},
	
	{ 0xC0FFFFFF, 0xC07C0F66, 3, ISSE,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													C_D2S_NN,			     NNN,     SK("HADDPD")},	
	{ 0x00FFFFFF, 0x007C0F66, 3, ISSE,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("HADDPD")},
	
	{ 0xC0FFFFFF, 0xC07C0FF2, 3, ISSE,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													C_D2S_NN,			     NNN,     SK("HADDPS")},	
	{ 0x00FFFFFF, 0x007C0FF2, 3, ISSE,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("HADDPS")},
	
	{ 0xC0FFFFFF, 0xC07D0F66, 3, ISSE,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													C_D2S_NN,			     NNN,     SK("HSUBPD")},	
	{ 0x00FFFFFF, 0x007D0F66, 3, ISSE,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("HSUBPD")},
	
	{ 0xC0FFFFFF, 0xC07D0FF2, 3, ISSE,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													C_D2S_NN,			     NNN,     SK("HSUBPS")},	
	{ 0x00FFFFFF, 0x007D0FF2, 3, ISSE,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("HSUBPS")},
	
	{ 0x00FFFFFF, 0x00C8010F, 3, ISSE, NNN,   NNN ,NNN, R_ECX|R_EAX|R_EDX,						R_ECX|R_EAX|R_EDX,														NNN,			     NNN,     SK("MONITOR")},
	{ 0x00FFFFFF, 0x00C9010F, 3, ISSE, NNN,   NNN ,NNN, R_ECX|R_EAX,						R_ECX|R_EAX,														NNN,			     NNN,     SK("MWAIT")},
	
	{ 0xC0FFFFFF, 0xC01C380F, 3, ISSE,   MMX_REG1D,    MMX_REG2S,NNN,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PABSB")},
	{ 0x00FFFFFF, 0x001C380F, 3, ISSE,   MMX_REG1D,    MMX_MEMS,NNN,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PABSB")},
	// tutaj nizej jest zle: bo sama mutinstrukcja ma 4 bajty :-(
	//{ 0xC0FFFFFF, 0xC01C380F, 3, 0,   XMM_REG1S,    XMM_REG2D,NNN,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PABSB")},
	//{ 0x00FFFFFF, 0x001C380F, 3, 0,   XMM_REG1S,    XMM_MEM128D,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("PABSB")},

	{ 0xC0FFFFFF, 0xC01E380F, 3, ISSE,   MMX_REG1D,    MMX_REG2S,NNN,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PABSD")},
	{ 0x00FFFFFF, 0x001E380F, 3, ISSE,   MMX_REG1D,    MMX_MEMS,NNN,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PABSD")},
	


	{ 0xC0FFFFFF, 0xC01D380F, 3, ISSE,   MMX_REG1D,    MMX_REG2S,NNN,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PABSW")},
	{ 0x00FFFFFF, 0x001D380F, 3, ISSE,   MMX_REG1D,    MMX_MEMS,NNN,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PABSW")},

	{ 0xC0FFFFFF, 0xC002380F, 3, ISSE,   MMX_REG1D,    MMX_REG2S,NNN,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PHADD")},
	{ 0x00FFFFFF, 0x0002380F, 3, ISSE,   MMX_REG1D,    MMX_MEMS,NNN,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PHADD")},

	{ 0xC0FFFFFF, 0xC003380F, 3, ISSE,   MMX_REG1D,    MMX_REG2S,NNN,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PHADDSW")},
	{ 0x00FFFFFF, 0x0003380F, 3, ISSE,   MMX_REG1D,    MMX_MEMS,NNN,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PHADDSW")},

	{ 0xC0FFFFFF, 0xC001380F, 3, ISSE,   MMX_REG1D,    MMX_REG2S,NNN,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PHADDW")},
	{ 0x00FFFFFF, 0x0001380F, 3, ISSE,   MMX_REG1D,    MMX_MEMS,NNN,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PHADDW")},


	{ 0xC0FFFFFF, 0xC006380F, 3, ISSE,   MMX_REG1D,    MMX_REG2S,NNN,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PHSUBD")},
	{ 0x00FFFFFF, 0x0006380F, 3, ISSE,   MMX_REG1D,    MMX_MEMS,NNN,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PHSUBD")},

	{ 0xC0FFFFFF, 0xC007380F, 3, ISSE,   MMX_REG1D,    MMX_REG2S,NNN,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PHSUBSW")},
	{ 0x00FFFFFF, 0x0007380F, 3, ISSE,   MMX_REG1D,    MMX_MEMS,NNN,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PHSUBSW")},

	{ 0xC0FFFFFF, 0xC005380F, 3, ISSE,   MMX_REG1D,    MMX_REG2S,NNN,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PHSUBW")},
	{ 0x00FFFFFF, 0x0005380F, 3, ISSE,   MMX_REG1D,    MMX_MEMS,NNN,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PHSUBW")},


	{ 0xC0FFFFFF, 0xC004380F, 3, ISSE,   MMX_REG1D,    MMX_REG2S,NNN,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PMADDUBSW")},
	{ 0x00FFFFFF, 0x0004380F, 3, ISSE,   MMX_REG1D,    MMX_MEMS,NNN,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PMADDUBSW")},

	{ 0xC0FFFFFF, 0xC00B380F, 3, ISSE,   MMX_REG1D,    MMX_REG2S,NNN,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PMULHRSW")},
	{ 0x00FFFFFF, 0x000B380F, 3, ISSE,   MMX_REG1D,    MMX_MEMS,NNN,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PMULHRSW")},


	{ 0xC0FFFFFF, 0xC000380F, 3, ISSE,   MMX_REG1D,    MMX_REG2S,NNN,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PSHUFB")},
	{ 0x00FFFFFF, 0x0000380F, 3, ISSE,   MMX_REG1D,    MMX_MEMS,NNN,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PSHUFB")},


	{ 0xC0FFFFFF,  0xC008380F, 3, ISSE,   MMX_REG1D,    MMX_REG2S,NNN,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PSIGNB")},
	{ 0x00FFFFFF,  0x0008380F, 3, ISSE,   MMX_REG1D,    MMX_MEMS,NNN,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PSIGNB")},
	

	{ 0xC0FFFFFF,  0xC00A380F, 3, ISSE,   MMX_REG1D,    MMX_REG2S,NNN,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PSIGND")},
	{ 0x00FFFFFF,  0x000A380F, 3, ISSE,   MMX_REG1D,    MMX_MEMS,NNN,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PSIGND")},
	
	{ 0xC0FFFFFF,  0xC009380F, 3, ISSE,   MMX_REG1D,    MMX_REG2S,NNN,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PSIGNW")},
	{ 0x00FFFFFF,  0x0009380F, 3, ISSE,   MMX_REG1D,    MMX_MEMS,NNN,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PSIGNW")},
	
	{ 0xC0FFFFFF,  0xC00F3A0F, 3, ISSE,   MMX_REG1D,    MMX_REG2S,IMM8,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PALIGNR")},
	{ 0x00FFFFFF,  0x000F3A0F, 3, ISSE,   MMX_REG1D,    MMX_MEMS,IMM8,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PALIGNR")},
	

	// dopisz: Table B-31. Formats and Encodings for SSE3 Integer and Move Instructions

	{ 0x0038FF, 0x0008DF, 1, 0,	  FPU_MEM16D,	NNN,	NNN, R_ST0,						NNN,														NNN,			     NNN,     SK("FISTPPM16")}, // 16
	{ 0x0038FF, 0x0008DB, 1, 0,	  FPU_MEM32D,	NNN,	NNN, R_ST0,						NNN,														NNN,			     NNN,     SK("FISTPPM32")}, // 32
	{ 0x0038FF, 0x0008DD, 1, 0,	  FPU_MEM64D,	NNN,	NNN, R_ST0,						NNN,														NNN,			     NNN,     SK("FISTPPM64")}, // 64
	
	{ 0x00FFFFFF, 0x00F00FF2, 3, 0,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,														NNN,		     NNN,     SK("LDDQU")},

	{ 0xC0FFFFFF, 0xC0120FF2, 3, 0,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													C_D2S_NN,			     NNN,     SK("MOVDDUP")},	
	{ 0x00FFFFFF, 0x00120FF2, 3, 0,XMM_REG1D,   FPU_MEM64S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("MOVDDUP")},

	{ 0xC0FFFFFF, 0xC0160FF3, 3, 0,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													C_D2S_NN,			     NNN,     SK("MOVSHDUP")},	
	{ 0x00FFFFFF, 0x00160FF3, 3, 0,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("MOVSHDUP")},

	{ 0xC0FFFFFF, 0xC0120FF3, 3, 0,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													C_D2S_NN,			     NNN,     SK("MOVSLDUP")},	
	{ 0x00FFFFFF, 0x00120FF3, 3, 0,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("MOVSLDUP")},

	// koniec sse3

	// sse mutinstructions (the ones with len=3 must be the first)
	// sse, sse

	{ 0xC0FFFFFF, 0xC0580FF3, 3, 0,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("ADDSS")},
	{ 0x00FFFFFF, 0x00580FF3, 3, 0,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("ADDSS")},

	{ 0xC0FFFFFF, 0xC02A0FF3, 3, 0,   XMM_REG1D,    MDR2,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("CVTSI2SS")},
	{ 0x00FFFFFF, 0x002A0FF3, 3, 0,   XMM_REG1D,    FPU_MEM32S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("CVTSI2SS")},

	{ 0xC0FFFFFF, 0xC02D0FF3, 3, 0,   MDR1,    XMM_REG2S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("CVTSS2SI")},
	{ 0x00FFFFFF, 0x002D0FF3, 3, 0,   MDR1,    FPU_MEM32S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("CVTSS2SI")},

	{ 0xC0FFFFFF, 0xC02C0FF3, 3, 0,   MDR1,    XMM_REG2S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("CVTTSS2SI")},
	{ 0x00FFFFFF, 0x002C0FF3, 3, 0,   MDR1,    FPU_MEM32S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("CVTTSS2SI")},

	{ 0xC0FFFFFF, 0xC0C20FF3, 3, 0,   XMM_REG1D,    XMM_REG2S,IMM8,NNN,						NNN,														 NNN,		     NNN,     SK("CMPSS")},
	{ 0x00FFFFFF, 0x00C20FF3, 3, 0,   XMM_REG1D,    XMM_MEM128S,IMM8S,NNN,						NNN,														 NNN,		     NNN,     SK("CMPSS")},

	{ 0xC0FFFFFF, 0xC05E0FF3, 3, 0,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("DIVSS")},
	{ 0x00FFFFFF, 0x005E0FF3, 3, 0,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("DIVSS")},

	{ 0xC0FFFFFF, 0xC05F0FF3, 3, 0,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("MAXSS")},
	{ 0x00FFFFFF, 0x005F0FF3, 3, 0,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("MAXSS")},

	{ 0xC0FFFFFF, 0xC05D0FF3, 3, 0,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("MINSS")},
	{ 0x00FFFFFF, 0x005D0FF3, 3, 0,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("MINSS")},


	{ 0xC0FFFF, 0xC0500F, 2, 0,   MDR1,         XMM_REG2S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("MOVMSKPS")},

	{ 0xC0FFFF, 0xC0580F, 2, 0,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("ADDPS")},
	{ 0x00FFFF, 0x00580F, 2, 0,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("ADDPS")},

	{ 0xC0FFFF, 0xC0550F, 2, 0,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("ANDNPS")},
	{ 0x00FFFF, 0x00550F, 2, 0,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("ANDNPS")},

	{ 0xC0FFFF, 0xC02F0F, 2, 0,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						ZF | PF | CF | OF | SF | AF,														 C_MMX_CMP,		     NNN,     SK("COMISS")},
	{ 0x00FFFF, 0x002F0F, 2, 0,   XMM_REG1D,    MM2,NNN,NNN,					ZF | PF | CF | OF | SF | AF,														 C_MMX_CMP,		     NNN,     SK("COMISS")},


	{ 0xC0FFFF, 0xC02D0F, 2, 0,   MMX_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("CVTPS2PI")},
	{ 0x00FFFF, 0x002D0F, 2, 0,   MMX_REG1D,    MMX_MEM64S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("CVTPS2PI")},

	{ 0xC0FFFF, 0xC02C0F, 2, 0,   MMX_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("CVTTPS2PI")},
	{ 0x00FFFF, 0x002C0F, 2, 0,   MMX_REG1D,    MMX_MEM64S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("CVTTPS2PI")},


	{ 0xC0FFFF, 0xC0C20F, 2, 0,   XMM_REG1D,    XMM_REG2S,IMM8,NNN,						NNN,														 NNN,		     NNN,     SK("CMPPS")},
	{ 0x00FFFF, 0x00C20F, 2, 0,   XMM_REG1D,    XMM_MEM128S,IMM8S,NNN,						NNN,													 NNN,		     NNN,     SK("CMPPS")},

	{ 0xC0FFFF, 0xC05E0F, 2, 0,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("DIVPS")},
	{ 0x00FFFF, 0x005E0F, 2, 0,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("DIVPS")},

	{ 0xC0FFFF, 0xC05F0F, 2, 0,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("MAXPS")},
	{ 0x00FFFF, 0x005F0F, 2, 0,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("MAXPS")},

	{ 0xC0FFFF, 0xC05D0F, 2, 0,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("MINPS")},
	{ 0x00FFFF, 0x005D0F, 2, 0,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("MINPS")},

	{ 0xC0FFFF, 0xC0120F, 2, 0,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("MOVHLPS")},


	{ 0xC0FFFF, 0xC0590F, 2, 0,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("MULPS")},
	{ 0x00FFFF, 0x00590F, 2, 0,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("MULPS")},

	{ 0xC0FFFFFF, 0xC0590FF3, 3, 0,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("MULSS")},
	{ 0x00FFFFFF, 0x00590FF3, 3, 0,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("MULSS")},

	{ 0xC0FFFF, 0xC0560F, 2, 0,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("ORPS")},
	{ 0x00FFFF, 0x00560F, 2, 0,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("ORPS")},

	{ 0xC0FFFFFF, 0xC0530FF3, 3, 0,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("RCPSS")},
	{ 0x00FFFFFF, 0x00530FF3, 3, 0,   XMM_REG1D,    FPU_MEM32S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("RCPSS")},


	{ 0xC0FFFF, 0xC0530F, 2, 0,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("RCPPS")},
	{ 0x00FFFF, 0x00530F, 2, 0,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("RCPPS")},


	
	
	{ 0xC0FFFF, 0xC0520F, 2, 0,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("RSQRTPS")},
	{ 0x00FFFF, 0x00520F, 2, 0,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("RSQRTPS")},

	{ 0xC0FFFFFF, 0xC0520FF3, 3, 0,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("RSQRTSS")},
	{ 0x00FFFFFF, 0x00520FF3, 3, 0,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("RSQRTSS")},

	{ 0xC0FFFF, 0xC0C60F, 2, 0,   XMM_REG1D,    XMM_REG2S,IMM8,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("SHUFPS")},
	{ 0x00FFFF, 0x00C60F, 2, 0,   XMM_REG1D,    XMM_MEM128S,IMM8S,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("SHUFPS")},

	{ 0xC0FFFF, 0xC0510F, 2, 0,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("SQRTPS")},
	{ 0x00FFFF, 0x00510F, 2, 0,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("SQRTPS")},

	{ 0xC0FFFFFF, 0xC0510FF3, 3, 0,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("SQRTSS")},
	{ 0x00FFFFFF, 0x00510FF3, 3, 0,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("SQRTSS")},

	{ 0xC0FFFF, 0xC05C0F, 2, 0,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("SUBPS")},
	{ 0x00FFFF, 0x005C0F, 2, 0,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("SUBPS")},

	
	{ 0x00FFFF, 0x00160F, 2, 0,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("MOVHPS")},
	{ 0x00FFFF, 0x00170F, 2, 0,   XMM_REG1S,    XMM_MEM128D,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("MOVHPS")},

	{ 0x00FFFF, 0x00120F, 2, 0,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("MOVLPS")},
	{ 0x00FFFF, 0x00130F, 2, 0,   XMM_REG1S,    XMM_MEM128D,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("MOVLPS")},

	// od
	{ 0xC0FFFFFF, 0xC05C0FF3, 3, 0,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("SUBSS")},
	{ 0x00FFFFFF, 0x005C0FF3, 3, 0,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("SUBSS")},

	{ 0xC0FFFF, 0xC02E0F, 2, 0,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_MMX_CMP,		     NNN,     SK("UCOMISS")},
	{ 0x00FFFF, 0x002E0F, 2, 0,   XMM_REG1D,    MMX_MEM64S,NNN,NNN,						NNN,													 C_MMX_CMP,		     NNN,     SK("UCOMISS")},

	{ 0xC0FFFF, 0xC0150F, 2, 0,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("UNPCKHPS")},
	{ 0x00FFFF, 0x00150F, 2, 0,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("UNPCKHPS")},

	{ 0xC0FFFF, 0xC0140F, 2, 0,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("UNPCKLPS")},
	{ 0x00FFFF, 0x00140F, 2, 0,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("UNPCKLPS")},

	{ 0xC0FFFF, 0xC0570F, 2, 0,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("XORPS")},
	{ 0x00FFFF, 0x00570F, 2, 0,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,														 C_D2S_NN,		     NNN,     SK("XORPS")},




	{ 0xC0FFFF, 0xC0280F, 2, 0,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,															 NNN,		     NNN,     SK("MOVAPS")},
	{ 0x00FFFF, 0x00280F, 2, 0,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("MOVAPS")},
	{ 0xC0FFFF, 0xC0290F, 2, 0,   XMM_REG1S,    XMM_REG2D,NNN,NNN,						NNN,															 NNN,		     NNN,     SK("MOVAPS")},
	{ 0x00FFFF, 0x00290F, 2, 0,   XMM_REG1S,    XMM_MEM128D,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("MOVAPS")},


	{ 0xC0FFFFFF, 0xC0100FF3, 3, 0,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,															 NNN,		     NNN,     SK("MOVSS")},
	{ 0x00FFFFFF, 0x00100FF3, 3, 0,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("MOVSS")},
	{ 0xC0FFFFFF, 0xC0110FF3, 3, 0,   XMM_REG1S,    XMM_REG2D,NNN,NNN,						NNN,															 NNN,		     NNN,     SK("MOVSS")},
	{ 0x00FFFFFF, 0x00110FF3, 3, 0,   XMM_REG1S,    XMM_MEM128D,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("MOVSS")},


	{ 0xC0FFFF, 0xC0100F, 2, 0,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,															 NNN,		     NNN,     SK("MOVUPS")},
	{ 0x00FFFF, 0x00100F, 2, 0,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("MOVUPS")},
	{ 0xC0FFFF, 0xC0110F, 2, 0,   XMM_REG1S,    XMM_REG2D,NNN,NNN,						NNN,															 NNN,		     NNN,     SK("MOVUPS")},
	{ 0x00FFFF, 0x00110F, 2, 0,   XMM_REG1S,    XMM_MEM128D,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("MOVUPS")},




	{ 0xC0FFFF, 0xC0160F, 2, 0,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,															 NNN,		     NNN,     SK("MOVLHPS")},


	{ 0xC0FFFF, 0xC02A0F, 2, 0,   XMM_REG1D,    MMX_REG2S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("CVTPI2PS")},
	{ 0x00FFFF, 0x002A0F, 2, 0,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("CVTPI2PS")},


		// added 13.04.2011 (the operands are wrong here but lets keep it this way for now)
	{ 0x0038FFFF, 0x20AE0F, 2, 0,	  FPU_MEM80D,	NNN,	NNN, R_ALL_ST | R_ALL_MMX | R_ALL_XMM,	NNN,												NNN,			     NNN,     SK("XSAVE")},		
	{ 0x0038FFFF, 0x28AE0F, 2, 0,	  FPU_MEM80D,	NNN,	NNN, R_ALL_ST | R_ALL_MMX | R_ALL_XMM,	NNN,												NNN,			     NNN,     SK("XRSTOR")},		
	


	// end added 13.04.2011


	{ 0x38FFFF, 0x10AE0F, 2, 0,   FPU_MEM32S,   NNN,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("LDMXCSR")},
	{ 0x38FFFF, 0x18AE0F, 2, 0,   FPU_MEM32D,   NNN,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("STMXCSR")},



	// sse int
	{ 0xC0FFFF, 0xC0E00F, 2, 0,  MMX_REG1D,    MMX_REG2S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PAVGB")},
	{ 0x00FFFF, 0x00E00F, 2, 0,  MMX_REG1D,    FPU_MEM64S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PAVGB_MEM64")},
	{ 0xC0FFFF, 0xC0E30F, 2, 0,  MMX_REG1D,    MMX_REG2S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PAVGW")},
	{ 0x00FFFF, 0x00E30F, 2, 0,  MMX_REG1D,    FPU_MEM64S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PAVGW_MEM64")},

	{ 0xC0FFFF, 0xC0C50F, 2, 0,  MDR1,		   MMX_REG2S,IMM8, NNN,						NNN,														NNN,			     NNN,     SK("PEXTRW")},

	{ 0xC0FFFF, 0xC0C40F, 2, 0,  MMX_REG1D,	   MDR2,IMM8, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PINSRW")},
	{ 0x00FFFF, 0x00C40F, 2, 0,  MMX_REG1D,	   FPU_MEM16S,IMM8S, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PINSRW")},

	{ 0xC0FFFF, 0xC0D70F, 2, 0,  MDR1,		   MMX_REG2S,NNN, NNN,						NNN,														NNN,			     NNN,     SK("PMOVMSKB")},

	{ 0xC0FFFF, 0xC0EE0F, 2, 0,  MMX_REG1D,    MMX_REG2S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMAXSW")},
	{ 0x00FFFF, 0x00EE0F, 2, 0,  MMX_REG1D,    FPU_MEM64S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMAXSW_MEM64")},

	{ 0xC0FFFF, 0xC0DE0F, 2, 0,  MMX_REG1D,    MMX_REG2S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMAXUB")},
	{ 0x00FFFF, 0x00DE0F, 2, 0,  MMX_REG1D,    FPU_MEM64S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMAXUB_MEM64")},

	{ 0xC0FFFF, 0xC0EA0F, 2, 0,  MMX_REG1D,    MMX_REG2S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMINSW")},
	{ 0x00FFFF, 0x00EA0F, 2, 0,  MMX_REG1D,    FPU_MEM64S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMINSW_MEM64")},

	{ 0xC0FFFF, 0xC0DA0F, 2, 0,  MMX_REG1D,    MMX_REG2S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMINUB")},
	{ 0x00FFFF, 0x00DA0F, 2, 0,  MMX_REG1D,    FPU_MEM64S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMINUB_MEM64")},

	{ 0xC0FFFF, 0xC0E40F, 2, 0,  MMX_REG1D,    MMX_REG2S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMULHUW")},
	{ 0x00FFFF, 0x00E40F, 2, 0,  MMX_REG1D,    FPU_MEM64S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMULHUW_MEM64")},

	{ 0xC0FFFF, 0xC0F60F, 2, 0,  MMX_REG1D,    MMX_REG2S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSADBW")},
	{ 0x00FFFF, 0x00F60F, 2, 0,  MMX_REG1D,    FPU_MEM64S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSADBW_MEM64")},

	{ 0xC0FFFF, 0xC0700F, 2, 0,  MMX_REG1D,    MMX_REG2S,IMM8, NNN,						NNN,														NNN,			     NNN,     SK("PSHUFW")},
	{ 0x00FFFF, 0x00700F, 2, 0,  MMX_REG1D,    FPU_MEM64S,IMM8S, NNN,						NNN,														NNN,			     NNN,     SK("PSHUFW_MEM64")},

	{ 0xC0FFFF, 0xC0F70F, 2, 0,  MMX_REG1D,    MMX_REG2S,NNN, NNN,						NNN,														NNN,			     NNN,     SK("MASKMOVQ")},

	{ 0x00FFFF, 0x00E70F, 2, 0,  FPU_MEM64D,   MMX_REG1S,NNN, NNN,						NNN,														NNN,			     NNN,     SK("MOVNTQ_MEM64")},

	{ 0x00FFFF, 0x002B0F, 2, 0,  XMM_MEM128D,  XMM_REG1S,NNN, NNN,						NNN,														NNN,			     NNN,     SK("MOVNTPS")},

	{ 0x38FFFF, 0x08180F, 2, 0,  MM_8,  NNN,NNN, NNN,						NNN,														NNN,			     NNN,     SK("PREFETCHT0")},
	{ 0x38FFFF, 0x10180F, 2, 0,  MM_8,  NNN,NNN, NNN,						NNN,														NNN,			     NNN,     SK("PREFETCHT1")},
	{ 0x38FFFF, 0x18180F, 2, 0,  MM_8,  NNN,NNN, NNN,						NNN,														NNN,			     NNN,     SK("PREFETCHT2")},
	{ 0x38FFFF, 0x00180F, 2, 0,  MM_8,  NNN,NNN, NNN,						NNN,														NNN,			     NNN,     SK("PREFETCHNTA")},

	{ 0xFFFFFF, 0xF8AE0F, 3, 0,  NNN,  NNN,NNN, NNN,						NNN,														NNN,			     NNN,     SK("SFENCE")},



	// some of SSE2 most used mutinstructions
	//MMX_REG2S
	{ 0xC0FFFFFF, 0xC07E0FF3, 3, ISSE,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,														NNN,			     NNN,     SK("MOVQ")},
	{ 0xC0FFFFFF, 0xC0D60F66, 3, ISSE,	  XMM_REG1S,   XMM_REG2D,   NNN, NNN,						NNN,														NNN,			     NNN,     SK("MOVQ")},
	{ 0x00FFFFFF, 0x007E0FF3, 3, ISSE,    XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														NNN,			     NNN,     SK("MOVQ")},		// MOVD mmx,[mem ]
	{ 0x00FFFFFF, 0x00D60F66, 3, ISSE,	 XMM_REG1S,   XMM_MEM128D,NNN, NNN,						NNN,												NNN,			     NNN,     SK("MOVQ")},	// MOVD [mem ],mmx
	{ 0x00FFFF,   0x00C30F,   2, ISSE, MM1, MDR1R,          NNN,NNN, NNN,						NNN,														     NNN,     SK("MOVNTI")},       
	
	{ 0xC0FFFFFF, 0xC02F0F66, 3, ISSE,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						ZF | PF | CF | OF | SF | AF,														 NNN,		     NNN,     SK("COMISD")},
	{ 0x00FFFFFF, 0x002F0F66, 3, ISSE,   XMM_REG1D,    MMX_MEM64S,NNN,NNN,					ZF | PF | CF | OF | SF | AF,														 NNN,		     NNN,     SK("COMISD")},

	{ 0xC0FFFF, 0x00C0D40F, 2, ISSE,   MMX_REG1D,    MMX_REG2S,NNN,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PADDQ")},
	{ 0x00FFFF, 0x0000D40F, 2, ISSE,   MMX_REG1D,    FPU_MEM80S,NNN,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PADDQ")},
	{ 0xC0FFFFFF, 0xC0D40F66, 3, ISSE,   XMM_REG1S,    XMM_REG2D,NNN,NNN,						NNN,															 C_D2S_NN,		     NNN,     SK("PADDQ")},
	{ 0x00FFFFFF, 0x00D40F66, 3, ISSE,   XMM_REG1S,    XMM_MEM128D,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("PADDQ")},

	//{ 0xC0FFFFFF, 0xC0580FF3, 3, 0,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("CVTPD2PS")},
	//{ 0x00FFFFFF, 0x00580FF3, 3, 0,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,													 NNN,		     NNN,     SK("CVTPD2PS")},


	{ 0xC0FFFFFF, 0xC05A0F66, 3, ISSE,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("CVTPD2PS")},
	{ 0x00FFFFFF, 0x005A0F66, 3, ISSE,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,													 NNN,		     NNN,     SK("CVTPD2PS")},


	{ 0xC0FFFF, 0x00C05A0F, 2, ISSE,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("CVTPS2PD")},
	{ 0x00FFFF, 0x00005A0F, 2, ISSE,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,													 NNN,		     NNN,     SK("CVTPS2PD")},

	{ 0xC0FFFFFF,0xC05A0FF2, 3, ISSE,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("CVTSD2SS")},
	{ 0x00FFFFFF,0x005A0FF2, 3, ISSE,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,													 NNN,		     NNN,     SK("CVTSD2SS")},

	{ 0xC0FFFFFF,0xC0E60FF3, 3, ISSE,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("CVTDQ2PD")},
	{ 0x00FFFFFF,0x00E60FF3, 3, ISSE,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,													 NNN,		     NNN,     SK("CVTDQ2PD")},

	{ 0xC0FFFF,0xC05B0F, 2, ISSE,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("CVTDQ2PS")},
	{ 0x00FFFF,0x005B0F, 2, ISSE,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,													 NNN,		     NNN,     SK("CVTDQ2PS")},


	{ 0xC0FFFFFF, 0xC05A0FF3, 3, ISSE,   XMM_REG1D,    XMM_REG2S,NNN,NNN,						NNN,														 NNN,		     NNN,     SK("CVTSS2SD")},
	{ 0x00FFFFFF, 0x005A0FF3, 3, ISSE,   XMM_REG1D,    XMM_MEM128S,NNN,NNN,						NNN,													 NNN,		     NNN,     SK("CVTSS2SD")},




	// mmx mutinstructions
	{ 0x00FFFF, 0x00770F, 2, 0,	  NNN,			NNN,	NNN, NNN,						NNN,														NNN,			     NNN,     SK("EMMS")},		// EMMS (uses fpu tag word)
	{ 0xC0FFFF, 0xC06E0F, 2, 0,	  MMX_REG1D,   MDR2,    NNN, NNN,						NNN,														NNN,			     NNN,     SK("MOVD")},
	{ 0xC0FFFF, 0xC07E0F, 2, 0,	  MMX_REG1S,   MDR2R,   NNN, NNN,						NNN,														NNN,			     NNN,     SK("MOVD")},
	{ 0x00FFFF, 0x006E0F, 2, MMX_GG,MMX_REG1D,   MMX_MEMS,NNN, NNN,						NNN,														NNN,			     NNN,     SK("MOVD")},		// MOVD mmx,[mem ]
	{ 0x00FFFF, 0x007E0F, 2, MMX_GG,	  MMX_REG1S,   MMX_MEMD,NNN, NNN,						NNN,														NNN,			     NNN,     SK("MOVD")},	// MOVD [mem ],mmx


	{ 0xC0FFFF, 0xC06F0F, 2, 0,	  MMX_REG1D,   MMX_REG2S,NNN, NNN,						NNN,														NNN,			     NNN,     SK("MOVQ")},
	{ 0xC0FFFF, 0xC07F0F, 2, 0,	  MMX_REG1S,   MMX_REG2D,   NNN, NNN,						NNN,														NNN,			     NNN,     SK("MOVQ")},
	{ 0x00FFFF, 0x006F0F, 2, MMX_GG,MMX_REG1D,   MMX_MEMS,NNN, NNN,						NNN,														NNN,			     NNN,     SK("MOVQ")},		// MOVQ mmx,[mem ]
	{ 0x00FFFF, 0x007F0F, 2, MMX_GG,MMX_REG1S,   MMX_MEMD,NNN, NNN,						NNN,														NNN,			     NNN,     SK("MOVQ")},	// MOVQ [mem ],mmx


	{ 0xC0FFFF, 0xC0EF0F, 2, 0,	  MMX_REG1D,   MMX_REG2S,    NNN, NNN,						NNN,													C_D2S_NN,			     NNN,     SK("PXOR")},	
	{ 0x00FFFF, 0x00EF0F, 2, 0,MMX_REG1D,   MMX_MEM64S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PXOR")},
	
	

	{ 0xC0FFFF, 0xC06B0F, 2, 0,	  MMX_REG1D,   MMX_REG2S,    NNN, NNN,						NNN,													C_D2S_NN,			     NNN,     SK("PACKSSDW")},
	{ 0x00FFFF, 0x006B0F, 2, MMX_GG,MMX_REG1D,   MMX_MEMS,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PACKSSDW")},	// PACKSSDW mmx,[mem ]


	{ 0xC0FFFF, 0xC0630F, 2, 0,	  MMX_REG1D,   MMX_REG2S,    NNN, NNN,						NNN,													C_D2S_NN,			     NNN,     SK("PACKSSWB")},
	{ 0x00FFFF, 0x00630F, 2, MMX_GG,MMX_REG1D,   MMX_MEMS,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PACKSSWB")},	

	{ 0xC0FFFF, 0xC0DF0F, 2, 0,	  MMX_REG1D,   MMX_REG2S,    NNN, NNN,						NNN,													C_D2S_NN,			     NNN,     SK("PANDN")},	
	{ 0x00FFFF, 0x00DF0F, 2, MMX_GG,MMX_REG1D,   MMX_MEMS,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PANDN")},


	{ 0xC0FFFF, 0xC0670F, 2, 0,	  MMX_REG1D,   MMX_REG2S,    NNN, NNN,						NNN,													C_D2S_NN,			     NNN,     SK("PACKUSWB")},
	{ 0x00FFFF, 0x00670F, 2, MMX_GG,MMX_REG1D,   MMX_MEMS,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PACKUSWB")},


	{ 0xC0FCFF, 0xC0FC0F, 2, MMX_GG,	  MMX_REG1D,   MMX_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PADD")},	// name changes based on GG
	{ 0x00FCFF, 0x00FC0F, 2, MMX_GG,MMX_REG1D,   MMX_MEMS,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PADD")},

	{ 0xC0FCFF, 0xC0EC0F, 2, NA|MMX_GG,	  MMX_REG1D,   MMX_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PADDS")},	// name changes based on GG
	{ 0x00FCFF, 0x00EC0F, 2, NA|MMX_GG,MMX_REG1D,   MMX_MEMS,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PADDS")},

	{ 0xC0FCFF, 0xC0DC0F, 2, NA|MMX_GG,	  MMX_REG1D,   MMX_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PADDUS")},	// name changes based on GG
	{ 0x00FCFF, 0x00DC0F, 2, NA|MMX_GG,MMX_REG1D,   MMX_MEMS,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PADDUS")},

	{ 0xC0FFFF, 0xC0DB0F, 2, 0,	  MMX_REG1D,   MMX_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PAND")},	
	{ 0x00FFFF, 0x00DB0F, 2, MMX_GG,MMX_REG1D,   MMX_MEMS,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PAND")},


	{ 0xC0FCFF, 0xC0740F, 2, NA|MMX_GG,	  MMX_REG1D,   MMX_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PCMPEQ")},	// name changes based on GG
	{ 0x00FCFF, 0x00740F, 2, NA|MMX_GG,MMX_REG1D,   MMX_MEMS,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PCMPEQ")},

	{ 0xC0FCFF, 0xC0640F, 2, NA|MMX_GG,	  MMX_REG1D,   MMX_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PCMPGT")},	// name changes based on GG
	{ 0x00FCFF, 0x00640F, 2, NA|MMX_GG,MMX_REG1D,   MMX_MEMS,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PCMPGT")},


	{ 0xC0FFFF, 0xC0F50F, 2, 0,	  MMX_REG1D,   MMX_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMADDWD")},	
	{ 0x00FFFF, 0x00F50F, 2, 0,MMX_REG1D,   MMX_MEM64S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMADDWD")},

//	{ 0xC0FFFF, 0xC0E40F, 2, 0,	  MMX_REG1D,   MMX_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMULHUW")},	
//	{ 0x00FFFF, 0x00E40F, 2, 0,MMX_REG1D,   MMX_MEM64S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMULHUW_MEM64")},

	{ 0xC0FFFF, 0xC0E50F, 2, 0,	  MMX_REG1D,   MMX_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMULHW")},	
	{ 0x00FFFF, 0x00E50F, 2, 0,MMX_REG1D,   MMX_MEM64S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMULHW")},

	{ 0xC0FFFF, 0xC0D50F, 2, 0,	  MMX_REG1D,   MMX_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMULLW")},	
	{ 0x00FFFF, 0x00D50F, 2, 0,MMX_REG1D,   MMX_MEM64S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PMULLW")},

	{ 0xC0FFFF, 0xC0EB0F, 2, 0,	  MMX_REG1D,   MMX_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("POR")},	
	{ 0x00FFFF, 0x00EB0F, 2, 0,MMX_REG1D,   MMX_MEM64S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("POR")},

	{ 0xC0FCFF, 0xC0F80F, 2, NA|MMX_GG,	  MMX_REG1D,   MMX_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSUB")},	// name changes based on GG
	{ 0x00FCFF, 0x00F80F, 2, NA|MMX_GG,MMX_REG1D,   MMX_MEMS,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSUB")},

	{ 0xC0FCFF, 0xC0E80F, 2, NA|MMX_GG,	  MMX_REG1D,   MMX_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSUBS")},	// name changes based on GG	
	{ 0x00FCFF, 0x00E80F, 2, NA|MMX_GG,MMX_REG1D,   MMX_MEMS,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSUBS")},

	{ 0xC0FCFF, 0xC0D80F, 2, NA|MMX_GG,	  MMX_REG1D,   MMX_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSUBUS")},	// name changes based on GG	
	{ 0x00FCFF, 0x00D80F, 2, NA|MMX_GG,MMX_REG1D,   MMX_MEMS,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSUBUS")},

	{ 0xC0FCFF, 0xC0680F, 2, NA|MMX_GG,	  MMX_REG1D,   MMX_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PUNPCHK")},	// name changes based on GG	
	{ 0x00FCFF, 0x00680F, 2, NA|MMX_GG,MMX_REG1D,   MMX_MEMS,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PUNPCHK")},


	{ 0xC0FCFF, 0xC0F00F, 2, NA|MMX_GG,	  MMX_REG1D,   MMX_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSLL")},	// name changes based on GG	
	{ 0x00FCFF, 0x00F00F, 2, NA|MMX_GG,MMX_REG1D,   MMX_MEMS,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSLL")},
	{ 0xF8FCFF, 0xF0700F, 2, NA|MMX_GG,MMX_REG1D,   IMM8,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSLL")},

	{ 0xC0FCFF, 0xC0E00F, 2, NA|MMX_GG,	  MMX_REG1D,   MMX_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSRA")},	// name changes based on GG	
	{ 0x00FCFF, 0x00E00F, 2, NA|MMX_GG,MMX_REG1D,   MMX_MEMS,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSRA")},
	{ 0xF8FCFF, 0xE0700F, 2, NA|MMX_GG,MMX_REG1D,   IMM8,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSRA")},


	{ 0xC0FCFF, 0xC0D00F, 2, NA|MMX_GG,	  MMX_REG1D,   MMX_REG2S,    NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSRL")},	// name changes based on GG	
	{ 0x00FCFF, 0x00D00F, 2, NA|MMX_GG,MMX_REG1D,   MMX_MEMS,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSRL")},
	{ 0xF8FCFF, 0xD0700F, 2, NA|MMX_GG,MMX_REG1D,   IMM8,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PSRL")},

	// sse4
	{ 0xC0FFFFFF, 0xC00D3A0F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    IMM8, NNN,						NNN,													C_D2S_NN,			     NNN,     SK("BLENDPD")},	
	{ 0x00FFFFFF, 0x000D3A0F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,IMM8S, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("BLENDPD")},

	{ 0xC0FFFFFF, 0xC00C3A0F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    IMM8, NNN,						NNN,													C_D2S_NN,			     NNN,     SK("BLENDPS")},	
	{ 0x00FFFFFF, 0x000C3A0F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,IMM8S, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("BLENDPS")},

	{ 0xC0FFFFFF, 0xC014380F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    NNN, R_XMM0,						NNN,													C_D2S_NN,			     NNN,     SK("BLENDVPS")},	
	{ 0x00FFFFFF, 0x0014380F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,NNN, R_XMM0,						NNN,														C_D2S_NN,			     NNN,     SK("BLENDVPS")},

	{ 0xC0FFFFFF, 0xC0413A0F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    IMM8, NNN,						NNN,													C_D2S_NN,			     NNN,     SK("DPPD")},	
	{ 0x00FFFFFF, 0x00413A0F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,IMM8S, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("DPPD")},


	{ 0xC0FFFFFF, 0xC0403A0F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    IMM8, NNN,						NNN,													C_D2S_NN,			     NNN,     SK("DPPS")},	
	{ 0x00FFFFFF, 0x00403A0F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,IMM8S, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("DPPS")},


	{ 0xC0FFFFFF, 0xC0173A0F, 3, ISSE|ISSE4,	  MDR2R,   XMM_REG1S,    IMM8, NNN,						NNN,													C_D2S_NN,			     NNN,     SK("EXTRACTPS")},	
	{ 0x00FFFFFF, 0x00173A0F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,IMM8S, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("EXTRACTPS")},

	{ 0xC0FFFFFF, 0xC0213A0F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    IMM8, NNN,						NNN,													C_D2S_NN,			     NNN,     SK("INSERTPS")},	
	{ 0x00FFFFFF, 0x00213A0F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,IMM8S, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("INSERTPS")},

	{ 0xC0FFFFFF, 0xC0423A0F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    IMM8, NNN,						NNN,													C_D2S_NN,			     NNN,     SK("MPSADBW")},	
	{ 0x00FFFFFF, 0x00423A0F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,IMM8S, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("MPSADBW")},

	{ 0x00FFFFFF, 0x002A380F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("MOVNTDQA")},

	{ 0xC0FFFFFF, 0xC02B380F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													C_D2S_NN,			     NNN,     SK("PACKUSDW")},	
	{ 0x00FFFFFF, 0x002B380F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PACKUSDW")},

	{ 0xC0FFFFFF, 0xC010380F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													C_D2S_NN,			     NNN,     SK("PBLENDVB")},	
	{ 0x00FFFFFF, 0x0010380F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PBLENDVB")},

	{ 0xC0FFFFFF, 0xC01E3A0F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    IMM8, NNN,						NNN,													C_D2S_NN,			     NNN,     SK("PBLENDW")},	
	{ 0x00FFFFFF, 0x001E3A0F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,IMM8S, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PBLENDW")},

	{ 0xC0FFFFFF, 0xC029380F, 3, ISSE|ISSE4|MMX_GG,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													NNN,			     NNN,     SK("PCMPEQQ")},	
	{ 0x00FFFFFF, 0x0029380F, 3, ISSE|ISSE4|MMX_GG,	  XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														NNN,			     NNN,     SK("PCMPEQQ")},


	{ 0xC0FFFFFF, 0xC0143A0F, 3, ISSE|ISSE4,	  MDR2R,   XMM_REG1S,    IMM8, NNN,						NNN,													C_D2S_NN,			     NNN,     SK("PEXTRB")},	
	{ 0x00FFFFFF, 0x00143A0F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,IMM8S, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PEXTRB")},

	{ 0xC0FFFFFF, 0xC0163A0F, 3, ISSE|ISSE4,	  MDR2R,   XMM_REG1S,    IMM8, NNN,						NNN,													C_D2S_NN,			     NNN,     SK("PEXTRD")},	
	{ 0x00FFFFFF, 0x00163A0F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,IMM8S, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PEXTRD")},


	{ 0xC0FFFFFF, 0xC0153A0F, 3, ISSE|ISSE4,	  MDR2R,   XMM_REG1S,    IMM8, NNN,						NNN,													C_D2S_NN,			     NNN,     SK("PEXTRW")},	
	{ 0x00FFFFFF, 0x00153A0F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,IMM8S, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PEXTRW")},

	{ 0xC0FFFFFF, 0xC041380F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													NNN,			     NNN,     SK("PHMINPOSUW")},	
	{ 0x00FFFFFF, 0x0041380F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														NNN,			     NNN,     SK("PHMINPOSUW")},

	{ 0xC0FFFFFF, 0xC0203A0F, 3, ISSE|ISSE4,	  MDR2,   XMM_REG1D,    IMM8, NNN,						NNN,													C_D2S_NN,			     NNN,     SK("PINSRB")},	
	{ 0x00FFFFFF, 0x00203A0F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,IMM8S, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PINSRB")},

	{ 0xC0FFFFFF, 0xC0223A0F, 3, ISSE|ISSE4,	  MDR2,   XMM_REG1D,    IMM8, NNN,						NNN,													C_D2S_NN,			     NNN,     SK("PINSRD")},	
	{ 0x00FFFFFF, 0x00223A0F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,IMM8S, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("PINSRD")},

	{ 0xC0FFFFFF, 0xC03C380F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													NNN,			     NNN,     SK("PMAXSB")},	
	{ 0x00FFFFFF, 0x003C380F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														NNN,			     NNN,     SK("PMAXSB")},

	{ 0xC0FFFFFF, 0xC03D380F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													NNN,			     NNN,     SK("PMAXSD")},	
	{ 0x00FFFFFF, 0x003D380F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														NNN,			     NNN,     SK("PMAXSD")},

	{ 0xC0FFFFFF, 0xC03F380F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													NNN,			     NNN,     SK("PMAXUD")},	
	{ 0x00FFFFFF, 0x003F380F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														NNN,			     NNN,     SK("PMAXUD")},

	{ 0xC0FFFFFF, 0xC03E380F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													NNN,			     NNN,     SK("PMAXUW")},	
	{ 0x00FFFFFF, 0x003E380F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														NNN,			     NNN,     SK("PMAXUW")},

	{ 0xC0FFFFFF, 0xC038380F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													NNN,			     NNN,     SK("PMINSB")},	
	{ 0x00FFFFFF, 0x0038380F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														NNN,			     NNN,     SK("PMINSB")},

	{ 0xC0FFFFFF, 0xC039380F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													NNN,			     NNN,     SK("PMINSD")},	
	{ 0x00FFFFFF, 0x0039380F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														NNN,			     NNN,     SK("PMINSD")},

	{ 0xC0FFFFFF, 0xC03B380F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													NNN,			     NNN,     SK("PMINUD")},	
	{ 0x00FFFFFF, 0x003B380F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														NNN,			     NNN,     SK("PMINUD")},

	{ 0xC0FFFFFF, 0xC03A380F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													NNN,			     NNN,     SK("PMINUW")},	
	{ 0x00FFFFFF, 0x003A380F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														NNN,			     NNN,     SK("PMINUW")},

	{ 0xC0FFFFFF, 0xC021380F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													NNN,			     NNN,     SK("PMOVSXBD")},	
	{ 0x00FFFFFF, 0x0021380F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														NNN,			     NNN,     SK("PMOVSXBD")},

	{ 0xC0FFFFFF, 0xC022380F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													NNN,			     NNN,     SK("PMOVSXBQ")},	
	{ 0x00FFFFFF, 0x0022380F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														NNN,			     NNN,     SK("PMOVSXBQ")},

	{ 0xC0FFFFFF, 0xC020380F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													NNN,			     NNN,     SK("PMOVSXBW")},	
	{ 0x00FFFFFF, 0x0020380F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														NNN,			     NNN,     SK("PMOVSXBW")},

	{ 0xC0FFFFFF, 0xC023380F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													NNN,			     NNN,     SK("PMOVSXWD")},	
	{ 0x00FFFFFF, 0xC023380F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														NNN,			     NNN,     SK("PMOVSXWD")},

	{ 0xC0FFFFFF, 0xC024380F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													NNN,			     NNN,     SK("PMOVSXWQ")},	
	{ 0x00FFFFFF, 0x0024380F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														NNN,			     NNN,     SK("PMOVSXWQ")},

	{ 0xC0FFFFFF, 0xC025380F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													NNN,			     NNN,     SK("PMOVSXDQ")},	
	{ 0x00FFFFFF, 0x0025380F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														NNN,			     NNN,     SK("PMOVSXDQ")},

	{ 0xC0FFFFFF, 0xC031380F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													NNN,			     NNN,     SK("PMOVZXBD")},	
	{ 0x00FFFFFF, 0x0031380F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														NNN,			     NNN,     SK("PMOVZXBD")},

	{ 0xC0FFFFFF, 0xC032380F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													NNN,			     NNN,     SK("PMOVZXBQ")},	
	{ 0x00FFFFFF, 0x0032380F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														NNN,			     NNN,     SK("PMOVZXBQ")},

	{ 0xC0FFFFFF, 0xC030380F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													NNN,			     NNN,     SK("PMOVZXBW")},	
	{ 0x00FFFFFF, 0x0030380F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														NNN,			     NNN,     SK("PMOVZXBW")},

	{ 0xC0FFFFFF, 0xC033380F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													NNN,			     NNN,     SK("PMOVZXWD")},	
	{ 0x00FFFFFF, 0x0033380F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														NNN,			     NNN,     SK("PMOVZXWD")},

	{ 0xC0FFFFFF, 0xC034380F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													NNN,			     NNN,     SK("PMOVZXWQ")},	
	{ 0x00FFFFFF, 0x0034380F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														NNN,			     NNN,     SK("PMOVZXWQ")},

	{ 0xC0FFFFFF, 0xC035380F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													NNN,			     NNN,     SK("PMOVZXDQ")},	
	{ 0x00FFFFFF, 0x0035380F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														NNN,			     NNN,     SK("PMOVZXDQ")},

	{ 0xC0FFFFFF, 0xC028380F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													NNN,			     NNN,     SK("PMULDQ")},	
	{ 0x00FFFFFF, 0x0028380F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														NNN,			     NNN,     SK("PMULDQ")},

	{ 0xC0FFFFFF, 0xC040380F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													NNN,			     NNN,     SK("PMULLD")},	
	{ 0x00FFFFFF, 0x0040380F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														NNN,			     NNN,     SK("PMULLD")},

	{ 0xC0FFFFFF, 0xC017380F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    NNN, NNN,						NNN,													NNN,			     NNN,     SK("PTEST")},	
	{ 0x00FFFFFF, 0xC017380F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,NNN, NNN,						NNN,														NNN,			     NNN,     SK("PTEST")},

	{ 0xC0FFFFFF, 0xC0093A0F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    IMM8, NNN,						NNN,													C_D2S_NN,			     NNN,     SK("ROUNDPD")},	
	{ 0x00FFFFFF, 0x00093A0F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,IMM8S, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("ROUNDPD")},

	{ 0xC0FFFFFF, 0xC0083A0F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    IMM8, NNN,						NNN,													C_D2S_NN,			     NNN,     SK("ROUNDPS")},	
	{ 0x00FFFFFF, 0x00083A0F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,IMM8S, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("ROUNDPS")},

	{ 0xC0FFFFFF, 0xC00B3A0F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    IMM8, NNN,						NNN,													C_D2S_NN,			     NNN,     SK("ROUNDSD")},	
	{ 0x00FFFFFF, 0x000B3A0F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,IMM8S, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("ROUNDSD")},

	{ 0xC0FFFFFF, 0xC00A3A0F, 3, ISSE|ISSE4,	  XMM_REG1D,   XMM_REG2S,    IMM8, NNN,						NNN,													C_D2S_NN,			     NNN,     SK("ROUNDSS")},	
	{ 0x00FFFFFF, 0xC00A3A0F, 3, ISSE|ISSE4,XMM_REG1D,   XMM_MEM128S,IMM8S, NNN,						NNN,														C_D2S_NN,			     NNN,     SK("ROUNDSS")},


	//sse4 end

	// sse end


	{ 0x38FFFF, 0x08010F, 2, 0,   MM2_EF,	MM1,		NNN, NNN,						NNN,														C_NNN,				     NNN,     SK("SIDT")},		// SIDT -> 0000 1111: 0000 0001: mod^a 001 r/m
	{ 0xF8FFFF, 0xC0000F, 2, 0,   MDR2_16,	NNN,		NNN, NNN,						NNN,														C_NNN,				     NNN,     SK("SLDT")},		// SLDT to r1 -> 0000 1111: 0000 0000: 11 000 r1
	{ 0x38FFFF, 0x00000F, 2, 0,   MM1_16,	NNN,		NNN, NNN,						NNN,														C_NNN,				     NNN,     SK("SLDT")},		// SLDT to MM -> 0000 1111: 0000 0000: mod 000 r/m



	// rest
	/* add flag: all regs from BSWAP are either source and dest */
	{ 0x0000FF, 0x00009B, 1, 0,   NNN,		NNN,		NNN, NNN,						NNN,														C_NNN,				     NNN,     SK("WAIT")},		// WAIT -> 1001 1011
	{ 0x00C8FF, 0x00C80F, 1, 0,  MDR2R,		NNN,		NNN, NNN,						NNN,														C_D2S,				     NNN,     SK("BSWAP")},		// r1 -> 0000 1111: 1100 1 reg
	{ 0x0000E7, 0x000007, 1, IRARE,   SREG2,	NNN,		NNN, R_ESP,						R_ESP,														C_NNN,				     NNN,     SK("POP")},			// POP DS/ES/SS -> 000 sreg2 111
	{ 0x0000FF, 0x0000D5, 1, 0,   IMM8CN,	NNN,		NNN, R_AX,						R_AX | SF | ZF | PF | OF | AF | CF,							NNN,			     OF|AF|CF,     SK("AAD")},			// AAD -> 1101 0101: IMM8
	{ 0x0000FF, 0x0000D4, 1, 0,   IMM8CN,	NNN,		NNN, R_AL,						R_AX | SF | ZF | PF | OF | AF | CF,							NNN,			     OF|AF|CF,     SK("AAM")},			// AAM -> 1101 0100: 0000 1010
	{ 0x0000FF, 0x0000F1, 1, 0,   NNN,		NNN,		NNN, NNN,						NNN,														C_NNN,				     NNN,     SK("INT1")},		// WAIT -> 1001 1011




	{ 0x000000, 0x000000, 0, 00,000, 000, 000,000, 000, 000, 000, ""},

};


int			_disasm(unsigned char *mutinstr, _dis_data *dis_data);
void			rotate_name2(const g_ddata *tc, char *name,_dis_data *ddmm);

bool disit_is_prefix(uchar s);


#endif
