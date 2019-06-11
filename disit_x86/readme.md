

This is some disassembler library for mine for X86 architecture. It brings some additional information about the instruction (including how are registers used, how the registers are used (source, dest, source-dest), how memory is used, what flags are used etc.)


Main function is:

```
int	_disasm(unsigned char *instr_data, _dis_data *dis_data)
```


The _dis_data struct is designed as follows:


```
typedef struct __dis_data {
	int8		prefix_len;
	int8		len;									// len of the instruction
	ulong32		dflags;									// main flags DF_XXX
	ulong32		mem_imm;								// immediate for mem
	uint16		reserved;								// reserved for TTTN fields
	

	uint8		tttn;									// for jumps

	ulong64		obj_src;								// all src objects
	ulong64		obj_dest;								// all dest objects

	ulong64		i_obj_src;								// src object style (register)
	ulong64		i_obj_dest;								// dst object style (register)


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
```


Additional logic function are listed in disit_func.h (dis_data->dflags such be passed as flags).







