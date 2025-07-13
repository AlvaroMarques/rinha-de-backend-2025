#ifndef DTYPES__H
#define DTYPES__H

#define DTYPES_DECIMAL_STR_BUFFER_SIZE 200
#define DTYPES_UUID_EXPECTED_SIZE 37

#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>

typedef enum Dtype {
	DTYPE_UUID = 0,
	DTYPE_DECIMAL
} Dtype;

typedef struct DtypeDecimal {
	unsigned int integer;
	unsigned short fractional;
} DtypeDecimal;

DtypeDecimal decimal__new(unsigned int integer, unsigned short fractional);
DtypeDecimal decimal__from_string(char* input, size_t size);

bool decimal__is_valid(DtypeDecimal d);
void decimal__parse(DtypeDecimal d, char* buff, size_t size);

typedef struct DtypeUUID {
	char uuid[DTYPES_UUID_EXPECTED_SIZE];
} DtypeUUID;

#endif
