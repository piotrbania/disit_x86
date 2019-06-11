/**

    DISIT X86
	by Piotr Bania <bania.piotr@gmail.com>
	http://www.piotrbania.com

**/


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>		// strncpy and others....


#include "disasm.h"
#include "disit_func.h"
#include "disasm_structs.h"
#include "disit_i_table.h"



#define	MUTDEBUG_IT	0
#define	debug OutputDebugString(debug_buff);

#if MUTDEBUG_IT == 1
char	debug_buff[1024];
#endif




void set_segment(_dis_data *ddm, unsigned char seg_prefix)
{
	switch(seg_prefix)
	{
		case 0x2E:				// CS
			disit_setDF_RESERVED_TYPEVALUE(&ddm->reserved,DF_RESERVED_SEG_CS,0);
#if ASLAN_EMU
			ddm->seg = SEG_CS;
#endif
			return;
		case 0x36:				// SS
			disit_setDF_RESERVED_TYPEVALUE(&ddm->reserved,DF_RESERVED_SEG_SS,0);
#if ASLAN_EMU
			ddm->seg = SEG_SS;
#endif
			return;
		case 0x3E:				// DS
			disit_setDF_RESERVED_TYPEVALUE(&ddm->reserved,DF_RESERVED_SEG_DS,0);
#if ASLAN_EMU
			ddm->seg = SEG_DS;
#endif
			return;
		case 0x26:				// ES
			disit_setDF_RESERVED_TYPEVALUE(&ddm->reserved,DF_RESERVED_SEG_ES,0);
#if ASLAN_EMU
			ddm->seg = SEG_ES;
#endif
			return;
		case 0x64:				// FS
			disit_setDF_RESERVED_TYPEVALUE(&ddm->reserved,DF_RESERVED_SEG_FS,0);
#if ASLAN_EMU
			ddm->seg = SEG_FS;
#endif
			return;
		case 0x65:				// GS
			disit_setDF_RESERVED_TYPEVALUE(&ddm->reserved,DF_RESERVED_SEG_GS,0);
#if ASLAN_EMU
			ddm->seg = SEG_GS;
#endif
			return;
	}
	//return SEG_DS;	// default
}

/* 32bit are enough for this one */
ulong32 decodeREG(int reg, int d_size)
{
	return (ulong32)t_regs_n[(d_size >> 1)][reg];
}

/* here we need 64 bits */
inline ulong64 decodeDRX_REG(int reg)
{
	return (ulong64)t_drx_regs_n[reg];
}

inline ulong64 decodeCRX_REG(int reg)
{
	return (ulong64)t_crx_regs_n[reg];
}

inline ulong64 decodeFPU_REG(int reg)
{
	return (ulong64)t_fpu_regs_n[reg];
}

inline ulong64 decodeMMX_REG(int reg)
{
	return (ulong64)t_mmx_regs_n[reg];
}

inline ulong64 decodeXMM_REG(int reg)
{
	return (ulong64)t_xmm_regs_n[reg];
}

inline ulong64 decodeTTTN(int tttn)
{
	return (ulong64)t_cpu_flags_n[tttn];
}

unsigned long decodeIMM(char *i, int d_size)
{
	unsigned long a;
	//memcpy((void*)&a, (void*)i, d_size);
	
	switch(d_size)
	{
		default:
			memcpy((void*)&a, (void*)i, d_size);
			
		case 4:
			a = *(unsigned long*)i;
			break;

		case 2:
			a = (int)(short)(*(unsigned short*)i);

		case 1:
			a = (int)(char)i[0];
			break;

	}
	
	return a;
}


unsigned long decodeSIB(_dis_data *ddm, char *i, int d_size, int mod)
{
	uchar sib = i[0];
	uchar sib_ss = D_GET_SIB_SCALE(sib);
	uchar sib_index = D_GET_SIB_INDEX(sib);
	uchar base = D_GET_SIB_BASE(sib);

	ddm->sib = sib;
	disit_setDF_USE_SIB(&ddm->dflags);

	if (sib_ss == 0x01)
		disit_setDF_SIBMUL2(&ddm->dflags);
	else if (sib_ss == 0x02)
		disit_setDF_SIBMUL4(&ddm->dflags);
	else if (sib_ss == 0x03)
		disit_setDF_SIBMUL8(&ddm->dflags);

	
	ddm->sib_mul_reg = decodeREG(sib_index,d_size);

	if (sib_index == 0x4) /* none */
		ddm->sib_mul_reg = 0;


	// is there is a ESP request, segment is changed to SS
	if (base == 4)
		disit_setDF_RESERVED_TYPEVALUE(&ddm->reserved,DF_RESERVED_SEG_SS,0);


	// some global exception if index = 4, there is no scaled index
	// only base
	if ((sib_index == 0x4) && (base != 5))
		return decodeREG(base,d_size);

	if (base != 5)
		return (decodeREG(base,d_size) | decodeREG(sib_index,d_size));

	
	if (base == 5) 
	{
		// base = 5 / mod = 0 -> [sc.in] + disp32
		// like: 00401003   . 110C2D 1122110>ADC DWORD PTR DS:[EBP+4112211],ECX
	
		if (mod == 0)
		{
			//ddm->mem_imm_size = 4;						// 32 bit data
			disit_setDF_MEM_IMM(&ddm->dflags);
			ddm->mem_imm = decodeIMM(i+1,4);			// decode 32 bit disp
			return 0;									// no reg for mem
			//return decodeREG(sib_index,d_size);
		}

		// [sc.in] + disp8/32 + EBP
		else
		{
			return (decodeREG(sib_index,d_size) | decodeREG(RR_EBP,4));

		}

	}

	

	return 0;
}

unsigned long decodeMEM(_dis_data *ddm, char *i)
{
	int n = 0;

	n = (i[0] & 0xC7);

	// firstly take care of 16bit addressing forms
	if (disit_isDF_AMODE16(ddm->dflags))
	{				
							    // like: adc     ds:6766h, al
		if (n == 0x06)			// Effective Address: disp16
		{
			//ddm->mem_imm_size = 2;						// 16 bit data
			disit_setDF_MEM_IMM(&ddm->dflags);
			ddm->mem_imm = decodeIMM(i+1,2);			// decode 16 bit disp
			return 0;
		}

		// from [BX+SI] to [BX]
		// like: 00401000 > $ 67:1300        ADC EAX,DWORD PTR DS:[BX+SI]
		else if ((n >= 0) && (n <= 7))
		{
			if ((n == 2) || (n == 3))					// BP requests requires SS
				disit_setDF_RESERVED_TYPEVALUE(&ddm->reserved,DF_RESERVED_SEG_SS,0);
			return t_regs16m_n[(n & 0x7)];
		}

		// from [BX+SI]+disp8 to [BX]+disp8
		else if ((n >= 0x40) && (n <= 0x47))
		{
			//ddm->mem_imm_size = 1;						// 8 bit data
			disit_setDF_MEM_IMM8(&ddm->dflags);
			ddm->mem_imm = decodeIMM(i+1,1);

			if ((n == 0x42) || (n == 0x43) || (n == 0x46))
				disit_setDF_RESERVED_TYPEVALUE(&ddm->reserved,DF_RESERVED_SEG_SS,0);
				//ddm->seg = SEG_SS;

			return t_regs16m_n[(n & 0x7)];
		}

		// from [BX+SI]+disp16 to [BX]+disp16	
		else if ((n >= 0x80) && (n <= 0x87))
		{
			//ddm->mem_imm_size = 2;							// 16 bit data
			disit_setDF_MEM_IMM(&ddm->dflags);
			ddm->mem_imm = decodeIMM(i+1,2);

			if ((n == 0x82) || (n == 0x83) || (n == 0x86))
				disit_setDF_RESERVED_TYPEVALUE(&ddm->reserved,DF_RESERVED_SEG_SS,0);

			return t_regs16m_n[(n & 0x7)];
		}
	}

	// now take care of 32 bit addressing forms
	else {
		// disp32
		if (n == 0x5)
		{
			//ddm->mem_imm_size = 4;						// 32 bit data
			disit_setDF_MEM_IMM(&ddm->dflags);
			ddm->mem_imm = decodeIMM(i+1,4);			// decode 32 bit disp
			return 0;
		}

		// from [EAX] to [EDI] (except of SIB block and disp32)
		// example: 00401000 > $ 1302           ADC EAX,DWORD PTR DS:[EDX]

		else if ((n >= 0) && (n != 0x04) && (n <= 7))
		{
			return decodeREG((n & 0x7),4);		//hardcore 32 bits!!!
		}

		// from [EAX]+disp8 to [EDI]+disp8, except of SIB block
		else if ((n >= 0x40) && (n <= 0x47) && (n != 0x44))
		{
			//ddm->mem_imm_size = 1;					// 8 bit
			disit_setDF_MEM_IMM8(&ddm->dflags);
			ddm->mem_imm = decodeIMM(i+1,1);
			return decodeREG((n & 0x7),4);
		}

		// from [EAX]+disp32 to [EDI]+disp32, except SIB block
		else if ((n >= 0x80) && (n <= 0x87) && (n != 0x84))
		{
			//ddm->mem_imm_size = 4;						// 32 bit data
			disit_setDF_MEM_IMM(&ddm->dflags);
			ddm->mem_imm = decodeIMM(i+1,4);			// decode 32 bit disp
			return decodeREG((n & 0x7),4);
		}

		// now SIB meine freunds
		else if (n == 4)
		{	
			return decodeSIB(ddm,(i+1),4,((n >> 6) & 0x3));
		}

		// SIB + disp8
		else if (n == 0x44)
		{	
			//ddm->mem_imm_size = 1;					// 8 bit
			disit_setDF_MEM_IMM8(&ddm->dflags);
			ddm->mem_imm = decodeIMM(i+2,1);
			return decodeSIB(ddm,(i+1),4,((n >> 6) & 0x3));
		}

		// SIB + dis32
		else if (n == 0x84)
		{
			//ddm->mem_imm_size = 4;					// 32 bit
			disit_setDF_MEM_IMM(&ddm->dflags);
			ddm->mem_imm = decodeIMM(i+2,4);
			return decodeSIB(ddm,(i+1),4,((n >> 6) & 0x3));
		}
	}

	return 0;

}



void rotate_name(const g_ddata *tc, char *name)
{
	/*
			// MOVS*
		if (tc->name[4] == '*')
		{
			if (ddm->default_data == 4)							// give MOVSD
				name[4] = 'D';
			else if (ddm->default_data == 2)
				name[4] = 'W';									// give MOVSW
			else if (ddm->default_data == 1)			
				name[4] = 'B';									// give MOVSB
		}

		// CWDE/CBW
		else if (tc->name[3] == '*')
		{
			if (ddm->default_data == 2)
				name[3] = 0;									// give CBW
			else
			{
				name[1] = 'W'; name[2] = 'D'; name[3] = 'E';	// give CWDE
			}
		}

		// CWD/CDQ
		else if (tc->name[2] == '*')
		{
			if (ddm->default_data == 4)							// give CDQ
				name[2] = 'Q';
			else
			{
				name[1] = 'W'; name[2] = 'D';					// give CWD
			}
		}


		// jump names are based on tttn fields
		if (strcmp(name,"JCC") == 0)
			strcpy(name,t_tttns[ddm->reserved]);
*/

}


void rotate_name2(const g_ddata *tc, char *name,_dis_data *ddmm)
{
	/*
			// MOVS*
		if (tc->name[4] == '*')
		{
			if (ddmm->default_data == 4)							// give MOVSD
				name[4] = 'D';
			else if (ddmm->default_data == 2)
				name[4] = 'W';									// give MOVSW
			else if (ddmm->default_data == 1)			
				name[4] = 'B';									// give MOVSB
		}

		// CWDE/CBW
		else if (tc->name[3] == '*')
		{
			if (ddmm->default_data == 2)
				name[3] = 0;									// give CBW
			else
			{
				name[1] = 'W'; name[2] = 'D'; name[3] = 'E';	// give CWDE
			}
		}

		// CWD/CDQ
		else if (tc->name[2] == '*')
		{
			if (ddmm->default_data == 4)							// give CDQ
				name[2] = 'Q';
			else
			{
				name[1] = 'W'; name[2] = 'D';					// give CWD
			}
		}


		// jump names are based on tttn fields
		if (strcmp(name,"JCC") == 0)
			strcpy(name,t_tttns[ddmm->reserved]);

*/
}







void normalize_regs(_dis_data *ddm, ulong64 *static_obj_src, ulong64 *static_obj_dest, uint8 bits, int emul_int)
{
	if (disit_isDF_AMODE16(ddm->dflags))
	{
		if (disit_isOBJ(*static_obj_src,R_ESI))
			*static_obj_src = (*static_obj_src & ~R_ESI) | R_SI;
		if (disit_isOBJ(*static_obj_src,R_EDI))
			*static_obj_src = (*static_obj_src & ~R_EDI) | R_DI;
		if (disit_isOBJ(*static_obj_dest,R_ESI))
			*static_obj_dest = (*static_obj_dest & ~R_ESI) | R_SI;
		if (disit_isOBJ(*static_obj_dest,R_EDI))
			*static_obj_dest = (*static_obj_dest & ~R_EDI) | R_DI;
	}

	// for popad/pushad
	if (disit_isDF_OMODE16(ddm->dflags))
	{
		if (disit_isOBJ(*static_obj_src,R_ALL32))
			*static_obj_src = (*static_obj_src & ~R_ALL32) | R_ALL16;
		if (disit_isOBJ(*static_obj_dest,R_ALL32))
			*static_obj_dest = (*static_obj_dest & ~R_ALL32) | R_ALL16;

		if (disit_isOBJ(*static_obj_src,R_ESP))
			*static_obj_src = (*static_obj_src & ~R_ESP) | R_SP;
		if (disit_isOBJ(*static_obj_dest,R_ESP))
			*static_obj_dest = (*static_obj_dest & ~R_ESP) | R_SP;
	}


	//special case for I/MUL
	if ((bits & EX_MUL) == EX_MUL)
	{
		switch(disit_getDF_size_data(ddm->dflags))
		{
			case D_SIZE8:
				*static_obj_src	= R_AL;
				*static_obj_dest	= R_AX;
				break;

			case D_SIZE16:
				*static_obj_src	= R_AX;
				*static_obj_dest	= R_AX | R_DX;
				break;

			default:
			case D_SIZE32:
				*static_obj_src	= R_EAX;
				*static_obj_dest	= R_EAX | R_EDX;
				break;
		}
	}


	//special case for I/DIV
	if ((bits & EX_DIV) == EX_DIV)
	{
		switch(disit_getDF_size_data(ddm->dflags))
		{
			case D_SIZE8:
				*static_obj_src	= R_AX;
				*static_obj_dest	= R_AX;
				break;

			case D_SIZE16:
				*static_obj_src	= *static_obj_dest = R_AX | R_DX;
				break;

			default:
			case D_SIZE32:
				*static_obj_src = *static_obj_dest = R_EAX | R_EDX;
				break;
		}
	}


	// lodsb/lodsw/lodsd -> need to ad MEMORY ACT SOURCE and change the EAX (AL/AX/EAX)

	if (emul_int == LODS_0)
	{
		disit_setDF_MEM_ACTSRC(&ddm->dflags);
		ddm->mem_regs	|= R_ESI;

		switch(disit_getDF_size_data(ddm->dflags))
		{
			case D_SIZE8:
				*static_obj_dest = (*static_obj_dest & ~R_EAX) | R_AL;
				disit_setDF_MEM_REQ8(&ddm->dflags);
				break;

			case D_SIZE16:
				*static_obj_dest = (*static_obj_dest & ~R_EAX) | R_AX;
				disit_setDF_MEM_REQ16(&ddm->dflags);
				break;

			case D_SIZE32:
			default:
				//static_obj_dest = (static_obj_dest & ~R_EAX) | R_AL;
				disit_setDF_MEM_REQ32(&ddm->dflags);
				break;
		}
	} // lods


	// stosb/stos/stos -> need to ad MEMORY ACT SOURCE and change the EAX (AL/AX/EAX)
	if (emul_int == STOS_0)
	{
		disit_setDF_MEM_ACTDEST(&ddm->dflags);
		ddm->mem_regs	|= R_EDI;

		switch(disit_getDF_size_data(ddm->dflags))
		{
			case D_SIZE8:
				*static_obj_src = (*static_obj_dest & ~R_EAX) | R_AL;
				disit_setDF_MEM_REQ8(&ddm->dflags);
				break;

			case D_SIZE16:
				*static_obj_src = (*static_obj_dest & ~R_EAX) | R_AX;
				disit_setDF_MEM_REQ16(&ddm->dflags);
				break;

			case D_SIZE32:
			default:
				//static_obj_dest = (static_obj_dest & ~R_EAX) | R_AL;
				disit_setDF_MEM_REQ32(&ddm->dflags);
				break;
		}
	} // stos


	//movs
	
	if ((emul_int == MOVS_0) || (emul_int == CMPS_0))
	{
		// EXCEPTION 
		if (emul_int != CMPS_0)
			disit_setDF_MEM_ACTDEST(&ddm->dflags);
		disit_setDF_MEM_ACTSRC(&ddm->dflags);
		ddm->mem_regs	|= R_EDI | R_ESI;

		switch(disit_getDF_size_data(ddm->dflags))
		{
			case D_SIZE8:
				disit_setDF_MEM_REQ8(&ddm->dflags);
				break;

			case D_SIZE16:
				disit_setDF_MEM_REQ16(&ddm->dflags);
				break;

			case D_SIZE32:
			default:
				//static_obj_dest = (static_obj_dest & ~R_EAX) | R_AL;
				disit_setDF_MEM_REQ32(&ddm->dflags);
				break;
		}

	}



}


bool disit_is_prefix(uchar s)
{
	if ((s == 0xF0) || ((s == 0xF2) || (s == 0xF3)) || 
		(s == 0x26) || (s == 0x2E) || (s == 0x36) || \
		(s == 0x3E) || (s == 0x64) || (s == 0x65) || \
		(s == 0x2E) || (s == 0x3E) ||
		(s == 0x66) || (s == 0x67))
		return true;
	return false;
}



int	_disasm(unsigned char *instr_data, _dis_data *dis_data)
{


	int sse_prefix = 0;
	int ii;
	ulong64 static_obj_src;		
	ulong64 static_obj_dest;		

	int							l, p, adj;
	unsigned char				*i = instr_data;
	unsigned char				s;
	ulong32						data;
	char						*bytes;
	const g_ddata				*tc;
	char						l_args[3];
	int							s_md = 0;
	ulong32						temp;
	bool						prefix_found;

	
	_dis_data *ddm;

	ddm = dis_data;

	if (ddm == NULL)
		return -1;

	memset((void*)ddm, 0, sizeof(_dis_data));
	
	
	for (l = p = 0; l < MAX_PREFIXES; l++)
	{
		prefix_found = false;
		s = *i++;
		
		if (s == 0xF0)	/* lock prefix */
		{
			disit_setDF_PrefixLOCK(&ddm->dflags);
			prefix_found = true;
			p++;
			continue;
		}

		if ((s == 0xF2) || (s == 0xF3)) /* repne-repnz and rep*/
		{

//			if (*i == 0x0F) sse_prefix = 1; //continue;	// sse

			/* rep + ECX */
			//ddm->obj_dest |= R_ECX;
			//ddm->obj_src |= R_ECX;

			disit_setDF_PrefixREP(&ddm->dflags);
			prefix_found = true;
			p++;
			continue;
		}


		if ((s == 0x26) || (s == 0x2E) || (s == 0x36) || \
			(s == 0x3E) || (s == 0x64) || (s == 0x65) || \
			(s == 0x2E) || (s == 0x3E))
		{

#if MUTDEBUG_IT == 1
	OutputDebugString("Prefixes found\r\r\n");
#endif
			//ddm->seg = set_segment(s);		// set the active segment
			set_segment(ddm,s);
			disit_setDF_PrefixSEG(&ddm->dflags);
			prefix_found = true;
			p++;
			continue;

		}

		if (s == 0x66)	/* operand-size ovveride prefix */
		{

		//	if (*i == 0x0F) sse_prefix; //continue;	// sse

#if MUTDEBUG_IT == 1
	OutputDebugString("Operand-size Prefix found\r\r\n");
#endif
			//ddm->default_data = ((ddm->default_data) / 2);
			disit_setDF_OMODE16(&ddm->dflags);
			prefix_found = true;
			p++;
			continue;
		}

		if (s == 0x67) /* address-size override prefix */
		{
			

#if MUTDEBUG_IT == 1
	OutputDebugString("Address-size Prefix found\r\r\n");
#endif
			disit_setDF_AMODE16(&ddm->dflags);
			prefix_found = true;
			p++;
			continue;
		}

		if ((p == 0) || (!prefix_found))
			break;

	}

	
	
	ddm->prefix_len		= (int8)p;
	s					= *(instr_data + p);
	data				= *(ulong32*)(instr_data + p);	
	ddm->opcode			= *(BYTE*)(instr_data + p);

	ddm->emul_int = 0;

	
    temp = *(ulong32*)instr_data;

	for (tc = i_data; tc->len != 0; tc++)
	{				
		if (((ulong32)(data & tc->mask) == (ulong32)tc->code))
		{
//			if (sse_prefix && (tc->len == 1))
//				continue;
			break;
		}

		if ((tc->len == 3) && ((ulong32)(temp & tc->mask) == (ulong32)tc->code))
		{
				// we need to delete prefixes right now
//				disit_setDF_PrefixNONE(&ddm->dflags);
//				ddm->obj_dest = ddm->obj_src = ddm->reserved = 0;
			     p = 0;
				break;
		}
//		}

		ddm->emul_int++;
	}


	
	if (tc->len == 0)						// command not found
	{
		//free(ddm);
		return 0;
	}


	// SSE instr_datauction delete the prefixes
	if (tc->bits & ISSE)
	{
				disit_setDF_PrefixNONE(&ddm->dflags);
				ddm->obj_dest = ddm->obj_src = ddm->reserved = 0;
	}


#if MUTDEBUG_IT == 1
	OutputDebugString("Found name: ");
	OutputDebugString(tc->name);
	OutputDebugString("\r\r\n");
#endif


	
    adj		= tc->len-1;
	data	= *(ulong32*)(instr_data + p + adj);
	if (adj)	ddm->opcode2 = *(uint8*)(instr_data + p + adj);

	bytes = (char*)(instr_data + p + adj);


	// only for SPIDERPIG
#ifdef _NO_PARENT_
	ddm->modrm_offset = ((ulong32)bytes - (ulong32)instr_data) + 1;
#endif


	// now take care of w/w3/s bits
	if (((tc->bits & WW ) == WW || (tc->bits & WS) == WS))
	{
		disit_setDF_USE_WRITEBIT(&ddm->dflags);	
		if (data & WW)
			disit_setDF_WRITEBIT(&ddm->dflags);
	}
	else if (tc->bits == W3)
	{
		disit_setDF_USE_WRITEBIT(&ddm->dflags);
		if (data & W3)
			disit_setDF_WRITEBIT(&ddm->dflags);


		//ddm->w_bit = (data & W3) >> 3;
		//if (ddm->w_bit == 0)
		//	ddm->default_data = 1;			// switch to 32 bit to 8 bit mode (w = 0)
	}

	if (((tc->bits & SS ) == SS || (tc->bits & WS) == WS))
	{
		disit_setDF_USE_SIGNEXTBIT(&ddm->dflags);
		if ((data & SS) >> 1)
			disit_setDF_SIGNEXTBIT(&ddm->dflags);
	}

	if ((tc->bits & MMX_GG) == MMX_GG)
	{
		disit_setDF_RESERVED_TYPEVALUE(&ddm->reserved,DF_RESERVED_MMX_GG,D_GET_FILE_MMX_GG(bytes[0]));

	}


#if MUTDEBUG_IT == 1
	_snprintf(debug_buff,sizeof(debug_buff),"Current size mode is: %x\r\r\n",ddm->default_data);
	debug;
	_snprintf(debug_buff,sizeof(debug_buff),"W_bit = %x | S_bit = %x\r\r\n",ddm->w_bit,ddm->s_bit);
	debug;
#endif

//	_asm { int 3 };

	ddm->additional_flags  = tc->bits;


	l_args[0] = tc->arg1;
	l_args[1] = tc->arg2;
	l_args[2] = tc->arg3;

	ddm->len = tc->len + p;			// size init


	// too late to differ, i'm very insane


	// add some additional objects for specific instr_datauction
	// firstly lets change the EDI/DI ESI/SI if needed (address mode is 16)
	static_obj_src		= tc->static_obj_src;
	static_obj_dest		= tc->static_obj_dest;





	for (ii = 0; ii != 3; ii++)
	{

		if (l_args[ii] == NNN)
			continue;
		
		
		switch(l_args[ii])
		{

			// SEGMENT FIELDS (possible SEGMENT as dest/source)
		case SREG3:
			//ddm->spec_regs_on = USE_SREG;
			//ddm->spec_regs = ((bytes[1] >> 3) & 0x07); // SREG3 field
			disit_setDF_RESERVED_TYPEVALUE(&ddm->reserved,DF_RESERVED_SREG3,((bytes[1] >> 3) & 0x07));
			s_md = 1;
			break;

		case SREG2:
			//ddm->spec_regs_on = USE_SREG;
			//ddm->spec_regs = ((bytes[0] >> 3) & 0x03); // SREG2 field
			disit_setDF_RESERVED_TYPEVALUE(&ddm->reserved,DF_RESERVED_SREG2,((bytes[0] >> 3) & 0x03));
			break;

			// CR register as dest
		case CRX:
			ddm->modrm = bytes[1];
			
			//ddm->spec_regs_on = USE_CRS;
			//ddm->spec_regs = ((bytes[1] >> 3) & 0x07);	// no need to decode EEE field
			disit_setDF_RESERVED_TYPEVALUE(&ddm->reserved,DF_RESERVED_REG_CRX,D_GET_FIELD_EEE(bytes[1]));
			ddm->obj_dest = decodeCRX_REG(D_GET_FIELD_EEE(bytes[1]));
			break;

			// CR register as source
		case CRXR:
			ddm->modrm = bytes[1];
			disit_setDF_RESERVED_TYPEVALUE(&ddm->reserved,DF_RESERVED_REG_CRX,D_GET_FIELD_EEE(bytes[1]));
			ddm->obj_src = decodeCRX_REG(D_GET_FIELD_EEE(bytes[1]));
			break;

			// DR register as dest
		case DRX:
			ddm->modrm = bytes[1];
			//ddm->spec_regs_on = USE_DRS;
			//ddm->spec_regs = ((bytes[1] >> 3) & 0x07);	// no need to decode EEE field
			disit_setDF_RESERVED_TYPEVALUE(&ddm->reserved,DF_RESERVED_REG_DRX,D_GET_FIELD_EEE(bytes[1]));
			ddm->obj_dest = decodeDRX_REG(D_GET_FIELD_EEE(bytes[1]));
			break;

			// DR register as source
		case DRXR:
			ddm->modrm = bytes[1];
			disit_setDF_RESERVED_TYPEVALUE(&ddm->reserved,DF_RESERVED_REG_DRX,D_GET_FIELD_EEE(bytes[1]));
			ddm->obj_src = decodeDRX_REG(D_GET_FIELD_EEE(bytes[1]));
			break;


			// REG2 field
			// situation: this is source (alternate encoding - XCHG)
		case MDR2_AA:
			ddm->obj_src |= decodeREG((bytes[0] & 0x07),disit_getDF_size_data(ddm->dflags));
			break;



			// REG2 field
			// situation: this is destination (alternate encoding - dec/inc/...)
		case MDR2_A:
			temp = disit_getDF_size_data(ddm->dflags);
			ddm->obj_dest |= decodeREG((bytes[0] & 0x07),disit_getDF_size_data(ddm->dflags));
			break;

			// REG1 field
			// situation: this is destination (screw the direction bits :))
		case MDR1:
			ddm->obj_dest |= decodeREG(((bytes[1] >> 3) & 0x07),disit_getDF_size_data(ddm->dflags));
			s_md = 1; // for size
			break;

			// REG2 field
			// situation: this is source
		case MDR2:
			ddm->obj_src |= decodeREG((bytes[1] & 0x07),disit_getDF_size_data(ddm->dflags));
			s_md = 1;
			break;

			// REG1 field
			// situation now REG1 is source (d=0)
		case MDR1R:
			ddm->obj_src |= decodeREG(((bytes[1] >> 3) & 0x07),disit_getDF_size_data(ddm->dflags));
			s_md = 1;
			break;

			// REG2 field
			// situation: now REG2 is dest (d=0)
		case MDR2R:
			ddm->obj_dest |= decodeREG((bytes[1] & 0x07),disit_getDF_size_data(ddm->dflags));
			s_md = 1;
			break;

			// REG1 field
			// situation 16 bit register as source
		case MDR1R_16:
			ddm->obj_src |= decodeREG(((bytes[1] >> 3) & 0x07),D_SIZE16);   // hardcored 16 bit
			s_md = 1;
			break;

			// REG1 field
			// situation 16 bit reg as dest
		case MDR1_16:
			ddm->obj_dest |= decodeREG(((bytes[1] >> 3) & 0x07),D_SIZE16);   // hardcored 16 bit
			s_md = 1;
			break;


			// REG2 field
			//situation 16 bit reg as source
		case MDR2_16:
			ddm->obj_src |= decodeREG((bytes[1] & 0x07),D_SIZE16);		  // hardcored 16 bit
			s_md = 1;
			break;


			// REG2 field
			// situation 16 bit register as dest
		case MDR2R_16:
			ddm->obj_dest |= decodeREG((bytes[1] & 0x07),D_SIZE16);		  // hardcored 16 bit
			s_md = 1;
			break;


		case MDR2_8:
			ddm->obj_src |= decodeREG((bytes[1] & 0x07),D_SIZE8);		  // hardcored 8 bit
			s_md = 1;
			break;



		case MDR2R_8:
			ddm->obj_dest |= decodeREG((bytes[1] & 0x07),D_SIZE8);		  // hardcored 8 bit
			s_md = 1;
			break;


			// SELECTOR DECODING (2 BYTES)
		case IMM_SEL:
			//ddm->selector = decodeIMM(bytes + 1 + 4,D_SIZE16); // selector after offset
			D_STORE_SELECTOR(decodeIMM(bytes + 1 + 4,D_SIZE16));			// store selector to mem_imm
			disit_setDF_RESERVED_TYPEVALUE(&ddm->reserved,DF_RESERVED_SELECTOR,0);
			ddm->len += 2;	// update the len !!!			
			break;

			// ENTER "SELECTOR" decoding (2 BYTES)
		case IMM_SEL_E:
			//ddm->spec_flag = F_ENTER;					 // set flag to ENTER command
			//ddm->selector = decodeIMM(bytes + 1,D_SIZE8);  // directly after op
			D_STORE_SELECTOR(decodeIMM(bytes + 1,D_SIZE8));			// store selector to mem_imm
			disit_setDF_RESERVED_TYPEVALUE(&ddm->reserved,DF_RESERVED_SELECTOR8,0);
			ddm->len += 2;
			break;


			// 8 Bit immediate directly after op
		case IMM8C:
//			ddm->spec_flag = F_CALL;

		case IMM8CN:
			//ddm->imm_size = 1;
			disit_setDF_IMM8(&ddm->dflags);
			ddm->imm_data = (char)decodeIMM(bytes + 1,D_SIZE8);
			break;


			// Immediate: value = 1 (no size)
		case IMM1:
			//obadaj
			// ddm->imm_size = 1;
			//disit_setDF_IMM8(&ddm->dflags);
			ddm->imm_data = 1;
			//ddm->len--;				// fixed - needed decreasion
			break;

			// CL
		case REG_CL_I:
			//ddm->spec_flag = F_SHL3;
			//ddm->spec_regs = decodeREG(RR_ECX, 1);
			disit_setDF_RESERVED_TYPEVALUE(&ddm->reserved,DF_RESERVED_REG_CL,0);		// value not needed in this case
			break;



			// CL
		case REG_CL:
			ddm->obj_src |= decodeREG(RR_ECX, D_SIZE8);
			break;

			// DX
		case REG_DX:
			ddm->obj_src |= decodeREG(RR_EDX, D_SIZE16);
			break;


			// Jumps decoding
			//TTTN field in opcode
		case JTTTN:
			//ddm->reserved = (decodeIMM(bytes,1)) & 0x0F;	// reserved = tttn field now
			temp = ((decodeIMM(bytes,1)) & 0x0F);
			//disit_setDF_RESERVED_TYPEVALUE(&ddm->reserved,DF_RESERVED_JTTTN,temp);
			ddm->tttn = temp;
			static_obj_src |= decodeTTTN(temp);
			break;

		case JTTTNS:
			//ddm->spec_flag = F_SETXX;
			//ddm->reserved = (decodeIMM(bytes,1)) & 0x0F;	// reserved = tttn field now
			temp = ((decodeIMM(bytes,1)) & 0x0F);
			//disit_setDF_RESERVED_TYPEVALUE(&ddm->reserved,DF_RESERVED_JTTTN,temp);
			ddm->tttn = temp;
			static_obj_src |= decodeTTTN(temp);
			break;

	

			// 8 bit Immediate after selector (ENTER)
		case IMM8E:
			//ddm->imm_size = 1;
			disit_setDF_IMM8(&ddm->dflags);
			//ddm->imm_data = decodeIMM(bytes + 1 + 2,ddm->imm_size);
			ddm->imm_data = decodeIMM(bytes + 1 + 2,D_SIZE8);
			break;

			// Immediate data directly after op.
		case IMMC:
			//ddm->imm_size = (ddm->s_bit == 0? getDF_size_data(ddm->dflags) : D_SIZE8);
			//ddm->imm_data = decodeIMM(bytes + 1,ddm->imm_size);
			ddm->imm_data	= decodeIMM(bytes + 1,disit_setDF_IMM_SIZE_oSIGN(&ddm->dflags));
			break;


			// Immediate data decoding (special member)
			// Possible after SIB lock (adjust needed)
		case IMMI:
			//ddm->reserved_size = (isDF_SIGNEXTBIT(ddm->dflags) == 0? getDF_size_data(ddm->dflags) : D_SIZE8);
			//ddm->reserved = decodeIMM(bytes + 1 + 1 + getDF_size_MEM_IMM(ddm->dflags) + ddm->use_sib,ddm->reserved_size);
			ddm->imm_data = decodeIMM(bytes + 1 + 1 + (int8)disit_getDF_size_MEM_IMM(ddm->dflags) + (int8)disit_is_DF_USE_SIB(ddm->dflags),disit_setDF_IMM_SIZE_oSIGN(&ddm->dflags));
			break;

		case IMMI8:
			//_asm { int 3 };
			//ddm->reserved_size = 1;
			disit_setDF_IMM8(&ddm->dflags);
			ddm->imm_data	= decodeIMM(bytes + 1 + 1 + disit_getDF_size_MEM_IMM(ddm->dflags) + (int8)disit_is_DF_USE_SIB(ddm->dflags),D_SIZE8);
			//ddm->reserved = decodeIMM(bytes + 1 + 1 + getDF_size_MEM_IMM(ddm->dflags) + ddm->use_sib,D_SIZE8);
			break;



			// Immediate data decoding
			// Possible after SIB lock (adjust needed)
		case IMMS:
			//ddm->imm_size = (ddm->s_bit == 0? getDF_size_data(ddm->dflags) : D_SIZE8);
			//ddm->imm_data = decodeIMM(bytes + 1 + 1 + getDF_size_MEM_IMM(ddm->dflags) + ddm->use_sib,ddm->imm_size);
			ddm->imm_data = decodeIMM(bytes + 1 + 1 + disit_getDF_size_MEM_IMM(ddm->dflags) + (int8)disit_is_DF_USE_SIB(ddm->dflags),disit_setDF_IMM_SIZE_oSIGN(&ddm->dflags));
			break;


			// Immediate 8 bit
			// Possible after SIB block (adjust needed)
		case IMM8S:
			disit_setDF_IMM8(&ddm->dflags);
			ddm->imm_data = decodeIMM(bytes + 1 + 1 + disit_getDF_size_MEM_IMM(ddm->dflags) + (int8)disit_is_DF_USE_SIB(ddm->dflags),D_SIZE8);
			break;


			// Immediate 32 bit for call
		case IMM32C:
//			ddm->spec_flag = F_CALL;		// call flag on

		case IMM32:
			//ddm->imm_size = 4;		// upcoming 32 bit imm
			disit_setDF_IMM(&ddm->dflags);
			ddm->imm_data = decodeIMM(bytes + 1,D_SIZE32);
			break;


			// Immediate 8 bit
		case IMM8:
			//ddm->imm_size = 1;
			disit_setDF_IMM8(&ddm->dflags);
			ddm->imm_data = decodeIMM(bytes + 2,D_SIZE8);
			break;

			// Immediate 16 bit
		case IMM16:
			//ddm->imm_size = 2;
			disit_setDF_IMM16(&ddm->dflags);
			ddm->imm_data = decodeIMM(bytes + 2,D_SIZE16);
			break;

			// Immediate 16 bit (direct after op)
		case IMM16C:
			//ddm->imm_size = 2;
			disit_setDF_IMM16(&ddm->dflags);
			ddm->imm_data = decodeIMM(bytes + 1,D_SIZE16);
			break;
			


			// Memory as dest (FULL DISP) 
		case MM1_FD:
			disit_setDF_MEM_ACTDEST(&ddm->dflags);

			//ddm->mem_act = MEM_ACT_DEST;
			//ddm->mem_imm_size = 4;
			//ddm->mem_imm_size = ddm->default_addr;

			disit_setDF_MEM_IMM(&ddm->dflags);
			ddm->mem_imm = decodeIMM(bytes + 1,disit_getDF_size_MEM_IMM(ddm->dflags));
			break;

			// Memory as src (FULL DISP) 
		case MM2_FD:
			disit_setDF_MEM_ACTSRC(&ddm->dflags);
			//ddm->mem_act = MEM_ACT_SOURCE;
			//ddm->mem_imm_size = 4;
			//ddm->mem_imm_size = ddm->default_addr;

			disit_setDF_MEM_IMM(&ddm->dflags);
			ddm->mem_imm = decodeIMM(bytes + 1,disit_getDF_size_MEM_IMM(ddm->dflags));
			break;



			// Immediate data decoding
			// IMM directly after mod reg fields
		case IMM:
			//ddm->imm_size = (ddm->s_bit == 0? getDF_size_data(ddm->dflags) : D_SIZE8);
			//ddm->imm_data = decodeIMM(bytes + 2,ddm->imm_size);
			ddm->imm_data = decodeIMM(bytes + 2,disit_setDF_IMM_SIZE_oSIGN(&ddm->dflags));
			break;


			//Accumulator reg (EAX/AX/AL)
			//Always as src reg
		case ACCR:
			ddm->obj_src |= decodeREG(RR_EAX, disit_getDF_size_data(ddm->dflags));
			break;


			// Accumulator register (EAX/AX/AL)
			// a destination register (RR_EAX)
		case ACC:
			ddm->obj_dest |= decodeREG(RR_EAX, disit_getDF_size_data(ddm->dflags));
			break;


			// Memory
			// situation: this is dest
		case MM1:
			
			disit_setDF_MEM_ACTDEST(&ddm->dflags);
//			ddm->mem_act = MEM_ACT_DEST;			// act like dest
			ddm->mem_regs |= decodeMEM(ddm,bytes + 1);
			s_md = 1;
			break;

			// Memory
			// situation: this is source
		case MM2:
			
			disit_setDF_MEM_ACTSRC(&ddm->dflags);
//			ddm->mem_act = MEM_ACT_SOURCE;			// act like source
			ddm->mem_regs |= decodeMEM(ddm,bytes + 1);
			s_md = 1;
			break;

		case MM_8:
//			ddm->mem_act = MEM_ACT_SOURCE;
//			ddm->mem_super_size = 1;		// hardcore 8 bits

			disit_setDF_MEM_ACTSRC(&ddm->dflags);
			disit_setDF_MEM_REQ8(&ddm->dflags);
			ddm->mem_regs |= decodeMEM(ddm,bytes + 1);
			s_md = 1;
			break;

		case MM_16:
			//ddm->mem_act = MEM_ACT_SOURCE;
			//			ddm->mem_super_size = 2;		// hardcore 8 bits	

			disit_setDF_MEM_ACTSRC(&ddm->dflags);
			disit_setDF_MEM_REQ16(&ddm->dflags);
			ddm->mem_regs |= decodeMEM(ddm,bytes + 1);
			s_md = 1;
			break;


		case MM2R_8:
			//ddm->mem_act = MEM_ACT_DEST;
			//ddm->mem_super_size = 1;		// hardcore 8 bits
			
			disit_setDF_MEM_ACTDEST(&ddm->dflags);
			disit_setDF_MEM_REQ8(&ddm->dflags);
			ddm->mem_regs |= decodeMEM(ddm,bytes + 1);
			s_md = 1;
			break;


			// Memory 
			// situation: 16 bit dest
		case MM1_16:
			//ddm->mem_act = MEM_ACT_DEST;
			//ddm->mem_super_size = 2;		// hardcore 16 bits
			disit_setDF_MEM_ACTDEST(&ddm->dflags);
			disit_setDF_MEM_REQ16(&ddm->dflags);
			ddm->mem_regs |= decodeMEM(ddm,bytes + 1);		
			s_md = 1;
			break;

			// Memory source exteneded (calls)
			// Situation: src exteneded
		case MM2CE:
			disit_setDF_MEM_ACTSRC(&ddm->dflags);
			disit_setDF_MEM_REQ48(&ddm->dflags);
			
			//ddm->mem_act = MEM_ACT_SOURCE;
			//ddm->spec_flag = F_CALL;		// call flag on
			ddm->mem_regs |= decodeMEM(ddm,bytes + 1);
			//ddm->mem_super_size = 5;	// switch to fword
			s_md = 1;
			break;


			// Memory
			// Situation: src extended
		case MM2_EF:
			disit_setDF_MEM_ACTSRC(&ddm->dflags);
			//ddm->mem_act = MEM_ACT_SOURCE;
			ddm->mem_regs |= decodeMEM(ddm,bytes + 1);
			if (disit_getDF_size_data(ddm->dflags) == 4)
				disit_setDF_MEM_REQ48(&ddm->dflags);
				//ddm->mem_super_size = 5;
			else if (disit_getDF_size_data(ddm->dflags) == 2)
				disit_setDF_MEM_REQ32(&ddm->dflags);
				//ddm->mem_super_size = 4;
			break;

			// Memory
			// Situation: src extended (depends on first param)
		case MM2_E:
			disit_setDF_MEM_ACTSRC(&ddm->dflags);
			//ddm->mem_act = MEM_ACT_SOURCE;
			ddm->mem_regs |= decodeMEM(ddm,bytes + 1);
			if (disit_getDF_size_data(ddm->dflags) == 2)
				disit_setDF_MEM_REQ32(&ddm->dflags);
				//ddm->mem_super_size = 4;
			else if (disit_getDF_size_data(ddm->dflags) == 4)
				disit_setDF_MEM_REQ48(&ddm->dflags);
				//ddm->mem_super_size = 6;
			s_md = 1;
			break;


			// FPU memory as source
		case FPU_MEM:
			// bit 5-6 of first bytes speak about memory: 
			// 00 - 32bit real
			// 01 - 32bit int
			// 10 - 64bit real
			// 11 - 16bit int

			disit_setDF_MEM_ACTSRC(&ddm->dflags);
			switch (D_GET_FIELD_FPU_MF(bytes[0]))
			{
				case D_FPU_SIZE32R:
					disit_setDF_MEM_REQ32(&ddm->dflags);
					disit_setDF_FPU_MEM_REAL(&ddm->dflags);
					break;

				case D_FPU_SIZE32I:
					disit_setDF_MEM_REQ32(&ddm->dflags);
					break;

				case D_FPU_SIZE64R:
					disit_setDF_MEM_REQ64(&ddm->dflags);
					disit_setDF_FPU_MEM_REAL(&ddm->dflags);
					break;

				case D_FPU_SIZE16I:
					disit_setDF_MEM_REQ16(&ddm->dflags);
					break;
			} // switch

			// now decode memory
			ddm->mem_regs |= decodeMEM(ddm,bytes + 1);
			s_md = 1;
			break;


			// 80bit memory request fpu as source
		case FPU_MEM80S:
			disit_setDF_MEM_ACTSRC(&ddm->dflags);
			disit_setDF_MEM_REQ80(&ddm->dflags);
			ddm->mem_regs |= decodeMEM(ddm,bytes + 1);
			s_md = 1;
			break;

			// 64bit memory request fpu as source
		case FPU_MEM64S:
			disit_setDF_MEM_ACTSRC(&ddm->dflags);
			disit_setDF_MEM_REQ64(&ddm->dflags);
			ddm->mem_regs |= decodeMEM(ddm,bytes + 1);
			s_md = 1;
			break;

			// 32bit memory request fpu as source
		case FPU_MEM32S:
			disit_setDF_MEM_ACTSRC(&ddm->dflags);
			disit_setDF_MEM_REQ32(&ddm->dflags);
			ddm->mem_regs |= decodeMEM(ddm,bytes + 1);
			s_md = 1;
			break;

			// 16bit memory request fpu as source
		case FPU_MEM16S:
			disit_setDF_MEM_ACTSRC(&ddm->dflags);
			disit_setDF_MEM_REQ16(&ddm->dflags);
			ddm->mem_regs |= decodeMEM(ddm,bytes + 1);
			s_md = 1;
			break;


			// 80bit memory request fpu as dest
		case FPU_MEM80D:
			disit_setDF_MEM_ACTDEST(&ddm->dflags);
			disit_setDF_MEM_REQ80(&ddm->dflags);
			ddm->mem_regs |= decodeMEM(ddm,bytes + 1);
			s_md = 1;
			break;


			// 16bit memory request fpu as dest
		case FPU_MEM16D:
			disit_setDF_MEM_ACTDEST(&ddm->dflags);
			disit_setDF_MEM_REQ16(&ddm->dflags);
			ddm->mem_regs |= decodeMEM(ddm,bytes + 1);
			s_md = 1;
			break;

			// 32bit memory request fpu as dest
		case FPU_MEM32D:
			disit_setDF_MEM_ACTDEST(&ddm->dflags);
			disit_setDF_MEM_REQ32(&ddm->dflags);
			ddm->mem_regs |= decodeMEM(ddm,bytes + 1);
			s_md = 1;
			break;

			// 64bit memory request fpu as dest
		case FPU_MEM64D:
			disit_setDF_MEM_ACTDEST(&ddm->dflags);
			disit_setDF_MEM_REQ64(&ddm->dflags);
			ddm->mem_regs |= decodeMEM(ddm,bytes + 1);
			s_md = 1;
			break;






		case FPU_REG:
			//_asm { int 3 };
			// if there is a D bit and it is set, ST(0) is no longer dest register
			if (((tc->bits & FPU_DBIT) == FPU_DBIT) && (D_GET_FIELD_FPU_DBIT(bytes[0])))
			{
				ddm->obj_dest		|= decodeFPU_REG((bytes[1] & 0x07));	
				ddm->i_obj_src		=  decodeFPU_REG((bytes[1] & 0x07));
			}
			else
			{
				ddm->obj_src		|= decodeFPU_REG((bytes[1] & 0x07));	
				static_obj_dest		|= R_ST0;
			}
			s_md = 1;
			break;



			// MMX REG 1 as source
		case MMX_REG1S:
			ddm->obj_src			|= decodeMMX_REG(((bytes[1] >> 3) & 0x07));
			s_md = 1;
			break;

			// MMX REG 1 as dest
		case MMX_REG1D:
			ddm->obj_dest			|= decodeMMX_REG(((bytes[1] >> 3) & 0x07));
			s_md = 1;
			break;

			// MMX REG 2 as src
		case MMX_REG2S:
			ddm->obj_src			|= decodeMMX_REG(bytes[1] & 0x07);
			s_md = 1;
			break;

			// MMX REG 2 as src
		case MMX_REG2D:
			ddm->obj_dest			|= decodeMMX_REG(bytes[1] & 0x07);
			s_md = 1;
			break;


			// MMX memory as source, size based on GG if there is any
		case MMX_MEMS:
			disit_setDF_MEM_ACTSRC(&ddm->dflags);
			if ((tc->bits  & MMX_GG) == MMX_GG)
			{
				switch(D_GET_FILE_MMX_GG(bytes[0]))
				{
					case D_MMX_SIZE8P:
						disit_setDF_MEM_REQ8(&ddm->dflags);
						break;

					case D_MMX_SIZE16P:
						disit_setDF_MEM_REQ16(&ddm->dflags);
						break;

					case D_MMX_SIZE32P:
						disit_setDF_MEM_REQ32(&ddm->dflags);
						break;

					case D_MMX_SIZE64P:
						disit_setDF_MEM_REQ64(&ddm->dflags);
						break;
				}
			} // GGbit
			ddm->mem_regs |= decodeMEM(ddm,bytes + 1);
			s_md = 1;
			break;
			
			// MMX memory as source, size based on GG if there is any
		case MMX_MEMD:
			disit_setDF_MEM_ACTDEST(&ddm->dflags);

			if ((tc->bits  & MMX_GG) == MMX_GG)
			{
				switch(D_GET_FILE_MMX_GG(bytes[0]))
				{
					case D_MMX_SIZE8P:
						disit_setDF_MEM_REQ8(&ddm->dflags);
						break;

					case D_MMX_SIZE16P:
						disit_setDF_MEM_REQ16(&ddm->dflags);
						break;

					case D_MMX_SIZE32P:
						disit_setDF_MEM_REQ32(&ddm->dflags);
						break;

					case D_MMX_SIZE64P:
						disit_setDF_MEM_REQ64(&ddm->dflags);
						break;
				}
			} // GGbit
			ddm->mem_regs |= decodeMEM(ddm,bytes + 1);
			s_md = 1;
			break;
			

			// XMM reg1 as src
		case XMM_REG1S:
			ddm->obj_src			|= decodeXMM_REG(((bytes[1] >> 3) & 0x07));
			s_md = 1;
			break;

			// XMM reg1 as dest
		case XMM_REG1D:
			ddm->obj_dest			|= decodeXMM_REG(((bytes[1] >> 3) & 0x07));
			s_md = 1;
			break;


			// XMM reg2 as src
		case XMM_REG2S:
			ddm->obj_src			|= decodeXMM_REG(bytes[1] & 0x07);
			s_md = 1;
			break;

		case XMM_REG2D:
			ddm->obj_dest			|= decodeXMM_REG(bytes[1] & 0x07);
			s_md = 1;
			break;



		case XMM_MEM128S:
			disit_setDF_MEM_ACTSRC(&ddm->dflags);
			disit_setDF_MEM_REQ128(&ddm->dflags);
			ddm->mem_regs |= decodeMEM(ddm,bytes + 1);
			s_md = 1;
			break;


		case XMM_MEM128D:
			disit_setDF_MEM_ACTDEST(&ddm->dflags);
			disit_setDF_MEM_REQ128(&ddm->dflags);
			ddm->mem_regs |= decodeMEM(ddm,bytes + 1);
			s_md = 1;
			break;



		}
	}

	//set the memory request size, if it wasnt set already
//	_asm { int 3 };
//	int wri_wri = isDF_USE_WRITEBIT(ddm->dflags); // & !isDF_WRITEBIT(ddm->dflags);
	disit_setDF_size_MEM_REQ(&ddm->dflags);




	// setup modrm, well where there sreg3 (etc.) fields available i made modrms from
	// them also, well it makes no diff for me
	if (s_md >= 1)
		ddm->modrm = bytes[1];


	// if the name depends on size, give the proper one
//	strncpy((char*)&name, tc->name, 255);
//	if ((tc->bits & NA) == NA)
//		rotate_name(tc, name);


#if MUTDEBUG_IT == 1
	_snprintf(debug_buff,sizeof(debug_buff),"Name is: %s - Code: %x\r\r\n",name,tc->code);
	debug;
#endif

	// calclate the size
	//ddm->len += (s_md + getDF_size_IMM(ddm->dflags) + ddm->use_sib + getDF_size_MEM_IMM(ddm->dflags) + ddm->reserved_size);



	
	ddm->len += (s_md + disit_getDF_size_IMM(ddm->dflags) + (int8)disit_is_DF_USE_SIB(ddm->dflags) + disit_getDF_size_MEM_IMM(ddm->dflags));





	// ------------------------------------------
	// sign extend datas urm!
	// ------------------------------------------
	// Tylko wtedy jest dest jest 16/32 bitowe(w=1) i jest sign extend.

	if (disit_is_DF_IMM_SIGNEXT(ddm->dflags))
		ddm->imm_data	=	(int)(int8)ddm->imm_data;



	/*
	if ((tc->arg3 == 0) && ((tc->arg2 == IMM) || (tc->arg2 == IMMC) || (tc->arg2 == IMMS)) && \
		((tc->arg1 == MDR2R) || (tc->arg1 == ACC) || (tc->arg1 == MM1)) || \
		((tc->arg1 == IMM8C) && (tc->arg2 == 0)) || \
		((tc->arg1 == JTTTN) && (tc->arg2 == IMM8C))) 
	{
		if ((getDF_size_data(ddm->dflags) != ddm->imm_size) && (ddm->imm_size == 1))
		{
			if ((ddm->imm_data & s_masks[1]) != 0)		// sign found
				ddm->imm_data = (~n_masks[1] | ddm->imm_data) & n_masks[getDF_size_data(ddm->dflags)];
			//ddm->imm_size = ddm->default_data;		// rotate the size - wyjebalem to nie wiem jak bez tego emulator bedzie trajkotal
			ddm->imm_signextend = 1;
		}

	}
	*/



		


//	show_the_function(name,base_plus_addr);
	

	// make a view
	
//	_asm { int 3 };

	ddm->i_obj_dest = ddm->obj_dest;
	ddm->i_obj_src = ddm->obj_src;


	if (disit_isDF_PrefixREP(ddm->dflags))
	{
		ddm->obj_src |= R_ECX;
		ddm->obj_dest |= R_ECX;
	}

	
	// now do some final actions, in future versions this should be replaced by some bits
	// operations (this will require (prolly) to add 2 fields for the g_ddata table for
	// each entry) - currently it is case ...

	//ddm->flags = tc->s_flag;

	switch(tc->s_flag)
	{

		// Here i don't care about reg modes (16/32/8)
		// in cmpxchg instr_datauction there are possiblities when
		// there will be no destination register so there
		// are few exceptions, and following calculations
		// may not be 100% correct.

		/*
		// Dest: EAX | EDX , Source |= EAX
		case C_DS_EAXEDX_EAX:
			ddm->obj_dest = R_EAX | R_EDX;
			ddm->obj_src |= R_EAX;
			break;
		*/

		// Dest regs are source regs
		case C_D2S:
			ddm->obj_src = ddm->obj_dest;
			break;


		// Dest 2 Source, Dest = EAX
		case C_D2S_DEAX:
			ddm->obj_src |= ddm->obj_dest;
			ddm->obj_dest |= R_EAX;
			break;

		// Src regs are dest regs
		case C_S2D:
			ddm->obj_dest = ddm->obj_src;
			break;


		case C_D2SN:
			//_asm { int 3 };
			ddm->obj_src |= ddm->obj_dest;
			ddm->obj_dest = 0;
			break;

	
		case C_S_CL_N:
			ddm->obj_src |= R_CL | ddm->obj_dest;
			break;


			

			// Src |= Dest
			// Dest - unchanged
		case C_D2S_NN:
			ddm->obj_src |= ddm->obj_dest;
			break;

			// MEM IS THE SOURCE TOO
		case C_S_MEM:
			disit_setDF_MEM_ACTSRC(&ddm->dflags);
			break;


		case C_DS_ESP_N:
			ddm->obj_src |= ddm->obj_dest |= R_ESP;
			ddm->obj_dest = R_ESP;
			break;
				
			
			// mem is only source / no mem in dest
		case C_SND_MEM:
			//_asm { int 3 };
			disit_clearDF_MEM_ACT(&ddm->dflags);
			disit_setDF_MEM_ACTSRC(&ddm->dflags);
			break;

			// for FPU's cmp - no dest ST regs
		case C_FPU_CMP:
			ddm->obj_dest	= 0;
			static_obj_dest &= ~R_ALL_ST;
			break;

			// for MMX cmp - no dest
		case C_MMX_CMP:
			ddm->obj_src |= ddm->obj_dest;
			ddm->obj_dest	= 0;
			static_obj_dest &= ~R_ALL_XMM;
			break;


			// dest|=src; src|=dest; for XCHG
		case C_DOS:	
			ddm->obj_dest	|= ddm->obj_src;
			ddm->obj_src	= ddm->obj_dest;
			break;


			// dest|=src; memory is both dest and source
		case C_DOSM:
			ddm->obj_src	|= ddm->i_obj_dest;
			ddm->obj_dest	= ddm->obj_src;
			disit_setDF_MEM_ACTSRC(&ddm->dflags);
			disit_setDF_MEM_ACTDEST(&ddm->dflags);
			break;





	default:
			break;
	}




	// Extra "case"
	// Here if the memory request will be found we will adjust
	// the registers for the source
	if (ddm->mem_regs != 0)
		ddm->obj_src |= ddm->mem_regs;
	if (ddm->sib_mul_reg != 0)
		ddm->obj_src |= ddm->sib_mul_reg;



	normalize_regs(ddm,&static_obj_src,&static_obj_dest,tc->bits,ddm->emul_int);

	ddm->obj_src	|= static_obj_src;
	ddm->obj_dest	|= static_obj_dest;


	// if the BA bit is located we set the MEMORY operand (which is now only dest) as SOURCE also
	// this is important for instr_datauctions like add [mem]/xor [mem]/or [mem] etc.
	if ((tc->bits & BM) == BM)
		disit_setDF_MEM_ACTSRC(&ddm->dflags);



	return dis_data->len;
}

