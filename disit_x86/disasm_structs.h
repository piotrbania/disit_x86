/**

    DISIT X86
	by Piotr Bania <bania.piotr@gmail.com>
	http://www.piotrbania.com

**/

#ifndef __DISASM_S_H
#define __DISASM_S_H


#include "disit_types.h"

ulong64 t_regs_n[3][8] = {
	R_AL,  R_CL,  R_DL,  R_BL,  R_AH,  R_CH,  R_DH,  R_BH,
	R_AX,  R_CX,  R_DX,  R_BX,  R_SP,  R_BP,  R_SI,  R_DI,
	R_EAX, R_ECX, R_EDX, R_EBX, R_ESP, R_EBP, R_ESI, R_EDI
};


#define R_DR_UNDEFINED R_DR0
ulong64 t_drx_regs_n[] = {
	R_DR0, R_DR1, R_DR2, R_DR3, R_DR_UNDEFINED, R_DR_UNDEFINED, R_DR6, R_DR7 
};

#define R_CR_UNDEFINED R_CR0
ulong64 t_crx_regs_n[] = {
	R_CR0, R_CR_UNDEFINED, R_CR2, R_CR3, R_CR4, R_CR_UNDEFINED, R_CR_UNDEFINED, R_CR_UNDEFINED
};


ulong64 t_fpu_regs_n[] = {
	R_ST0, R_ST1, R_ST2, R_ST3, R_ST4, R_ST5, R_ST6, R_ST7
};

ulong64 t_mmx_regs_n[] = {
	R_MMX0, R_MMX1, R_MMX2, R_MMX3, R_MMX4, R_MMX5, R_MMX6, R_MMX7
};

ulong64 t_xmm_regs_n[] = {
	R_XMM0, R_XMM1, R_XMM2, R_XMM3, R_XMM4, R_XMM5, R_XMM6, R_XMM7
};


// tttn fields
ulong64 t_cpu_flags_n[]	= {
	OF, OF, CF, CF, ZF, ZF, ZF | CF, ZF | CF, SF, SF, PF, PF, SF | OF, SF | OF, ZF | OF | SF, ZF | OF | SF
};


#define T_REGS16_M_N_MAX 7
ulong64 t_regs16m_n[] = {
	R_BX | R_SI, R_BX | R_DI, R_BP | R_SI, R_BP | R_DI, R_SI, R_DI, R_BP, R_BX
};




#endif