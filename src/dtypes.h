#ifndef DTYPES__H
#define DTYPES__H

#define DTYPES_DECIMAL_STR_BUFFER_SIZE 200

#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>

typedef struct DtypeDecimal {
	unsigned int integer;
	unsigned short fractional;
} DtypeDecimal;

DtypeDecimal decimal__new(unsigned int integer, unsigned short fractional);

bool decimal__is_valid(DtypeDecimal d);
void decimal__parse(DtypeDecimal d, char* buff, size_t size);

#endif
