#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#define DECL(f)				void f() 
#define IS_REG(x)			((x) > (uint16)0x7FFF)
#define IS_VALID_VALUE(x)	((x) < (uint16)0x8000)
#define IS_VALID_OPCODE(x)	((x) < (uint16)0x16)
#define STACK_MAX			0x1000
#define OPCODE_COUNT		22

#endif
