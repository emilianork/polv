#ifndef POLV_TYPES_H_
#define POLV_TYPES_H_

typedef unsigned char u_char;

struct hexadecimal {
	const u_char* octs;
	int len;
};

typedef struct hexadecimal hexadecimal;

#endif POLV_TYPES_H_
