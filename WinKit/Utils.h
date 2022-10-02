#pragma once

#define uint8_t  unsigned int
#define uint16_t unsigned short
#define uint32_t unsigned int
#define uint64_t unsigned long long

#define MAX_IDT_ENTRIES 0xFF
#define MAKE_INT_ADDR(off1,off2,off3) ((uint64_t) \
((uint64_t)(off3) << 32) | ((uint64_t)(off2) << 16) | ((uint64_t)(off1))\
)
#define MAKE_IDT_BASE(LowBase,HighBase) ((uint64_t)\
(LowBase) | ((HighBase) << 32))

typedef enum
{
	INT_GATE = 0xE, // interrupt gate
	TRP_GATE = 0xF  // Trap Gate
} GATE_TYPE;

#pragma pack(push,1)
typedef struct
{
	unsigned short offset_1; // offset bit 0..15
	unsigned short selector; // a code segment selector in GDT or LDT
	unsigned char ist : 3, reserved : 5; // bits 0..2 holds interrupt stack table offset
	unsigned char gate_type : 4, reserved1 : 1, DPL : 2, P : 1; // gate type, dpl and p fields
	unsigned short offset_2; // offset bits 16..31
	unsigned int offset_3; // offset bits 32..63
	unsigned int zero;
} IDT_ENTRY_64;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct {
	uint16_t IDT_Limit;
	uint32_t LowIDTBase;
	uint32_t HighIDTBase;
} IDT_INFO_64;
#pragma pack(pop)

typedef struct
{
	unsigned short offset_1; // offset bits 0..15
	unsigned short selector; // a code segment selector in GDT or LDT
	unsigned zero;  // unused set to 0
	unsigned char type_attributes; // gate type, dpl and p fields
	unsigned short offset_2; // offset bits 16..31
}IDT_ENTRY_32;

/* Make sure buffer is exactlyt 10 bytes */
extern "C" void __sidt__(uint8_t * idt_buffer);
