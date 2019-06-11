/**

    DISIT X86
	by Piotr Bania <bania.piotr@gmail.com>
	http://www.piotrbania.com


    -- this thing below is for debugging mostly

**/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "disit_types.h"
#include "disasm.h"
#include "disit_func.h"
//#include "disasm_structs.h"




#define		q(x)					lstrcat(out,x);
#define		check_flag(flag,text)	{ if ((obj & flag) == flag) q(text);   }
#define		check_obj(obj,flag)		{ if ((obj & flag) == flag) return flag; }


// movsB/movsW/movsD - depends on the size (D_SIZE8/D_SIZE16/D_SIZE32)
char *t_iname_adds[]		= { "x","B","W","x","D" };

// MMX name based on the GG bit
char *t_iname_gg_adds[]		= { "B","W","D","Q" };

char *t_regs[3][8] = {
	"AL", "CL", "DL", "BL", "AH", "CH", "DH", "BH",
	"AX", "CX", "DX", "BX", "SP", "BP", "SI", "DI",
	"EAX", "ECX", "EDX", "EBX", "ESP", "EBP", "ESI", "EDI"
};


char *t_regs_dr[] = {
	"DR0", "DR1", "DR2", "DR3", "DR??", "DR??","DR6","DR7"
};

char *t_regs_cr[] = {
	"CR0","CR??","CR2","CR3","CR4","CR??","CR??","CR??"
};


char *t_segs[] = {
	"ES", "CS", "SS", "DS", "FS", "GS","??","??"
};

char *t_sizes[] = {
	"??", "BYTE  PTR", "WORD  PTR", "3-BYTE PTR", "DWORD PTR", "5-BYTE PTR", "FWORD PTR", "7-BYTE PTR", "QWORD PTR", "9-BYTE PTR", "TBYTE PTR", "??", "??", "??", "??", "??", "DQWORD PTR" };

/*
char *t_tttns[] = {
	"JO", "JNO", "JB", "JNB", "JE", "JNE", "JBE", "JNBE", "JS","JNS", "JP", "JNP", "JL", "JNL", "JLE", "JNLE"
};
*/

char *t_tttns[] = {
	"O", "NO", "B", "NB", "E", "NE", "BE", "NBE", "S","NS", "P", "NP", "L", "NL", "LE", "NLE"
};


char *t_tttns_s[] = {
	"SETO", "SETNO", "SETB", "SETNB", "SETE", "SETNE", "SETBE", "SETNBE", "SETS","SETNS", "SETP", "SETNP", "SETL", "SETNL", "SETLE", "SETNLE"
};


// dont change the order
#define disit_singles_size	(sizeof(disit_singles)/sizeof(ulong64))
ulong64 disit_singles[]	=	{
	R_EAX, R_AX, R_AH, R_AL,									\
	R_ECX, R_CX, R_CH, R_CL,									\
	R_EBX, R_BX, R_BH, R_BL,									\
	R_EDX, R_DX, R_DH, R_DL,									\
	R_EDI, R_DI,												\
	R_ESI, R_SI,												\
	R_EBP, R_BP,												\
	R_ESP,														\
	R_MMX0,R_MMX1,R_MMX2,R_MMX3,R_MMX4,R_MMX5,R_MMX6,R_MMX7,	\
	R_XMM0,R_XMM1,R_XMM2,R_XMM3,R_XMM4,R_XMM5,R_XMM6,R_XMM7,	\
	F_CARRY,F_PARITY,F_AUXILIARY,F_ZERO,F_SIGN,F_OVERFLOW,F_DIRECTION, \
	F_TRAP,F_INTERRUPT,F_IOPL,F_NT,F_RESUME,F_VM,				\
	R_CR0, R_CR2,R_CR3,R_CR4,									\
	R_DR0, R_DR1,R_DR2,R_DR3,R_DR6,R_DR7						\
};




// splits OBJ per single, use this in a loop
ulong64 disit_getsingleobj(ulong64 obj) // sprawdz to
{
	int		i;
	for (i = 0;	i != disit_singles_size; i++)
		check_obj(obj,disit_singles[i]);
	return 0;
}






void disit_show_general_regs(ulong32 obj, char *out)
{
	if ((obj & R_EAX) == R_EAX) 
	{
		q("EAX+"); 
	}
    else if ((obj & R_AX) == R_AX)
	{
		q("AX+");
	}
	else {
		if ((obj & R_AL) == R_AL)
			q("AL+");
		if ((obj & R_AH) == R_AH)
			q("AH+");
	}

	// ECX/CX/CH/CL support
	if ((obj & R_ECX) == R_ECX)
	{
		q("ECX+");
	}
	else if ((obj & R_CX) == R_CX)
	{
		q("CX+");
	}
	else {
		if ((obj & R_CL) == R_CL)
			q("CL+");
		if ((obj & R_CH) == R_CH)
			q("CH+");
	}

	// EBX/BX/BH/BL support
	if ((obj & R_EBX) == R_EBX)
	{
		q("EBX+");
	}
	else if ((obj & R_BX) == R_BX)
	{
		q("BX+");
	}
	else {
		if ((obj & R_BL) == R_BL)
			q("BL+");
		if ((obj & R_BH) == R_BH)
			q("BH+");
	}
	// EDX/DX/DH/DL support
	if ((obj & R_EDX) == R_EDX)
	{
		q("EDX+");
	}
	else if ((obj & R_DX) == R_DX)
	{
		q("DX+");
	}
	else {
		if ((obj & R_DL) == R_DL)
			q("DL+");
		if ((obj & R_DH) == R_DH)
			q("DH+");
	}

	// EDI/DI
	if ((obj & R_EDI) == R_EDI)
	{
		q("EDI+");
	}
	else if ((obj & R_DI) == R_DI)
	{
		q("DI+");
	}
	// ESP/SP
	if ((obj & R_ESP) == R_ESP)
	{
		q("ESP+");
	}
	else if ((obj & R_SP) == R_SP)
	{
		q("SP+");
	}
	// EBP/BP
	if ((obj & R_EBP) == R_EBP)
	{
		q("EBP+");
	}
	else if ((obj & R_BP) == R_BP)
	{
		q("BP+");
	}

	// ESI/SI
	if ((obj & R_ESI) == R_ESI)
	{
		q("ESI+");
	}
	else if ((obj & R_SI) == R_SI)
	{
		q("SI+");
	}
}

void disit_show_general_all_regs(ulong64 obj, char *out)
{
	disit_show_general_regs((ulong32)obj,out);

	check_flag(R_XMM0,"XMM0+");
	check_flag(R_XMM1,"XMM1+");
	check_flag(R_XMM2,"XMM2+");
	check_flag(R_XMM3,"XMM3+");
	check_flag(R_XMM4,"XMM4+");
	check_flag(R_XMM5,"XMM5+");
	check_flag(R_XMM6,"XMM6+");
	check_flag(R_XMM7,"XMM7+");


	//R_MMX0
	check_flag(R_MMX0,"MMX0+");
	check_flag(R_MMX1,"MMX1+");
	check_flag(R_MMX2,"MMX2+");
	check_flag(R_MMX3,"MMX3+");
	check_flag(R_MMX4,"MMX4+");
	check_flag(R_MMX5,"MMX5+");
	check_flag(R_MMX6,"MMX6+");
	check_flag(R_MMX7,"MMX7+");

	//R_DR0
	check_flag(R_DR0,"DR0+");
	check_flag(R_DR1,"DR1+");
	check_flag(R_DR2,"DR2+");
	check_flag(R_DR3,"DR3+");
	check_flag(R_DR6,"DR6+");
	check_flag(R_DR7,"DR7+");

	//CR0
	check_flag(R_CR0,"CR0+");
	check_flag(R_CR2,"CR2+");
	check_flag(R_CR3,"CR3+");
	check_flag(R_CR4,"CR4+");
}

int disit_show_object(ulong64 obj, char *out)
{
	memset((void*)out,0,512);

	// EAX/AX/AH/AL support
	if ((obj & R_EAX) == R_EAX) 
	{
		q("EAX+"); 
	}
    else if ((obj & R_AX) == R_AX)
	{
		q("AX+");
	}
	else {
		if ((obj & R_AL) == R_AL)
			q("AL+");
		if ((obj & R_AH) == R_AH)
			q("AH+");
	}

	// ECX/CX/CH/CL support
	if ((obj & R_ECX) == R_ECX)
	{
		q("ECX+");
	}
	else if ((obj & R_CX) == R_CX)
	{
		q("CX+");
	}
	else {
		if ((obj & R_CL) == R_CL)
			q("CL+");
		if ((obj & R_CH) == R_CH)
			q("CH+");
	}

	// EBX/BX/BH/BL support
	if ((obj & R_EBX) == R_EBX)
	{
		q("EBX+");
	}
	else if ((obj & R_BX) == R_BX)
	{
		q("BX+");
	}
	else {
		if ((obj & R_BL) == R_BL)
			q("BL+");
		if ((obj & R_BH) == R_BH)
			q("BH+");
	}
	// EDX/DX/DH/DL support
	if ((obj & R_EDX) == R_EDX)
	{
		q("EDX+");
	}
	else if ((obj & R_DX) == R_DX)
	{
		q("DX+");
	}
	else {
		if ((obj & R_DL) == R_DL)
			q("DL+");
		if ((obj & R_DH) == R_DH)
			q("DH+");
	}

	// EDI/DI
	if ((obj & R_EDI) == R_EDI)
	{
		q("EDI+");
	}
	else if ((obj & R_DI) == R_DI)
	{
		q("DI+");
	}
	// ESP/SP
	if ((obj & R_ESP) == R_ESP)
	{
		q("ESP+");
	}
	else if ((obj & R_SP) == R_SP)
	{
		q("SP+");
	}
	// EBP/BP
	if ((obj & R_EBP) == R_EBP)
	{
		q("EBP+");
	}
	else if ((obj & R_BP) == R_BP)
	{
		q("BP+");
	}

	// ESI/SI
	if ((obj & R_ESI) == R_ESI)
	{
		q("ESI+");
	}
	else if ((obj & R_SI) == R_SI)
	{
		q("SI+");
	}


	check_flag(R_XMM0,"XMM0+");
	check_flag(R_XMM1,"XMM1+");
	check_flag(R_XMM2,"XMM2+");
	check_flag(R_XMM3,"XMM3+");
	check_flag(R_XMM4,"XMM4+");
	check_flag(R_XMM5,"XMM5+");
	check_flag(R_XMM6,"XMM6+");
	check_flag(R_XMM7,"XMM7+");


	//R_MMX0
	check_flag(R_MMX0,"MMX0+");
	check_flag(R_MMX1,"MMX1+");
	check_flag(R_MMX2,"MMX2+");
	check_flag(R_MMX3,"MMX3+");
	check_flag(R_MMX4,"MMX4+");
	check_flag(R_MMX5,"MMX5+");
	check_flag(R_MMX6,"MMX6+");
	check_flag(R_MMX7,"MMX7+");

	//R_DR0
	check_flag(R_DR0,"DR0+");
	check_flag(R_DR1,"DR1+");
	check_flag(R_DR2,"DR2+");
	check_flag(R_DR3,"DR3+");
	check_flag(R_DR6,"DR6+");
	check_flag(R_DR7,"DR7+");

	//CR0
	check_flag(R_CR0,"CR0+");
	check_flag(R_CR2,"CR2+");
	check_flag(R_CR3,"CR3+");
	check_flag(R_CR4,"CR4+");


	// flags
	check_flag(F_CARRY,"FCARRY+");
	check_flag(F_PARITY,"FPARITY+");
	check_flag(F_AUXILIARY,"FAUXILIARY+");
	check_flag(F_ZERO,"FZERO+");
	check_flag(F_SIGN,"FSIGN+");
	check_flag(F_OVERFLOW,"FOVERFLOW+");
	//check_flag(F_PARITY,"FPARITY+");
	check_flag(F_DIRECTION,"FDIRECTION+");
	check_flag(F_TRAP,"FTRAP+");

	check_flag(F_INTERRUPT,"FINTERRUPT+");
	check_flag(F_IOPL,"FIOPL+");
	check_flag(F_NT,"FNT+");
	check_flag(F_RESUME,"FRESUME+");
	check_flag(F_VM,"FVM+");

	return 0;

}

// out should be a 255 char array

/*
#define DISIT_TEXT_SIZE	255
#define scat(dst,text) { strcpy(dst,text); dst += strlen(text); }

/// makes <size> ptr [XXXXX]
void disit_make_mtext(char *out, _dis_data *dd)
{
#define REG_STR_SIZE 32
	char mem_reg[REG_STR_SIZE];
	char mem_mul_reg[REG_STR_SIZE];
	char mem_mul_reg_text[REG_STR_SIZE];

	ulong32 dflags = dd->dflags;
	ulong32 mem_reg_value = (dd->mem_regs & ~dd->sib_mul_reg);

	memset((void*)mem_reg,0,REG_STR_SIZE);
	memset((void*)mem_mul_reg,0,REG_STR_SIZE);
	memset((void*)mem_mul_reg_text,0,REG_STR_SIZE);

	if (mem_reg_value)
		disit_show_general_regs(mem_reg_value,(char*)&mem_reg);
	if (dd->sib_mul_reg)
	{
		disit_show_general_regs(dd->sib_mul_reg,(char*)&mem_mul_reg);
		mem_mul_reg[strlen(mem_mul_reg)-1] = 0;
			if (mem_reg_value)
				sprintf(mem_mul_reg_text,"+%s*%d",mem_mul_reg,disit_getDF_size_SIBMUL(dflags));
			else 
				sprintf(mem_mul_reg_text,"%s*%d",mem_mul_reg,disit_getDF_size_SIBMUL(dflags));
	}

	if (mem_reg_value)
		mem_reg[strlen(mem_reg)-1] = 0;


	if (disit_isDF_MEM_IMM(dflags))
		sprintf(out,"%s [%s%s+%.08xh]",t_sizes[disit_getDF_size_MEM_REQ(dflags)],mem_reg,mem_mul_reg_text,dd->mem_imm);
	else
		sprintf(out,"%s [%s%s]",t_sizes[disit_getDF_size_MEM_REQ(dflags)],mem_reg,mem_mul_reg_text);
}


int disit_show_itext(char *out, _dis_data *dd)
{
	int			i;
	uint8		argz[DISIT_MAX_ARGS];
	char		*p;
	const		g_ddata *tc;
	ulong32		dflags = dd->dflags;

	p = out;
	memset((void*)out,0,DISIT_TEXT_SIZE);

	if (disit_isDF_PrefixREP(dflags))
		scat(p,"REP ");
	if (disit_isDF_PrefixLOCK(dflags))
		scat(p,"LOCK ");
		
	tc = i_data + dd->emul_int;

	argz[0]		=	tc->arg1;
	argz[1]		=	tc->arg2;
	argz[2]		=	tc->arg3;



	// write the mutinstruction name and check if it relies on size
	scat(p,tc->name);
	if ((tc->bits & NA) == NA)
	{
		if ((tc->bits & MMX_GG) == MMX_GG)
		{
			// get the GG streight from the reserved field!!!
			scat(p,t_iname_gg_adds[D_GET_FILE_MMX_GG(dd->reserved)]);
		}
		else
		{
			p--; scat(p,t_iname_adds[disit_getDF_size_data(dflags)]);
		}
	}


	*p = ' '; p++;


	if (dd->reserved)
	{

		//_asm { int 3 };
		switch(disit_getDF_RESERVED_TYPE(dd->reserved))
		{
		default:
			break;

			// jmps *
		case DF_RESERVED_TTTN:
			p = (char*)(out+1);
			sprintf(p,"%s $+%xh",t_tttns[disit_getDF_RESERVED_VALUE(dd->reserved)],dd->imm_data);
			goto end_text;

			// cmovcc
		case DF_RESERVED_JTTTN:
			p = (char*)(out + 4);
			sprintf(p,"%s ",t_tttns[disit_getDF_RESERVED_VALUE(dd->reserved)]);
			break;

		} // switch
	} // if-exceptions





	if (disit_is_DF_MEM_ACTDEST(dflags))
		disit_make_mtext(p,dd); 
	else if (dd->i_obj_dest)
		disit_show_general_all_regs(dd->i_obj_dest,p);
	else if (argz[1] == NNN)					// for callz and jumps
		sprintf(p,"$+%xh",dd->imm_data);
	


	p = (char*)(p+strlen(p)-1);


	

	// travell the rest 
	for (i = 1; ((i < 3) && (argz[i] != NNN)); i++,	p = (char*)(p+strlen(p)-1))
	{
		*p = ','; p++;
		if (!disit_is_DF_MEM_ACTDEST(dflags) && disit_is_DF_MEM_ACTSRC(dflags) && (i == 1))
			disit_make_mtext(p,dd); 
		else if (dd->i_obj_src && (i == 1))
			disit_show_general_all_regs(dd->i_obj_src,p);
		else if (disit_isDF_IMM(dflags))
			// maybe its an IMM param !? !? !?
			sprintf(p,"%xh",dd->imm_data);
		else if (dd->reserved)
		{
			// reserved types?
			uint16 resv = dd->reserved;
			switch(resv)
			{
				case DF_RESERVED_REG_CL:
					scat(p,"CL");
					break;
				default:
					break;

			}
		}
	}
	
	if (*p == ',' || *p == '+')
		*p = 0;

end_text:;
	return 0;
}

*/