#include "dtypes.h"


DtypeDecimal decimal__new(unsigned int integer, unsigned short fractional) {
	DtypeDecimal d;
	d.integer = integer;
	d.fractional = fractional;
	return d;
}

bool decimal__is_valid(DtypeDecimal d) {
	return (d.fractional < 100);

}

void decimal__parse(DtypeDecimal d, char* buff, size_t size) {
	if (decimal__is_valid(d)) {
		snprintf(buff, size, "%u.%u", d.integer, d.fractional);
	} else {
		snprintf(buff, size, "Invalid Decimal: %u.%2u", d.integer, d.fractional);
	}
}

int main() {
	DtypeDecimal d = decimal__new(10, 37);
	char buff[DTYPES_DECIMAL_STR_BUFFER_SIZE];
	decimal__parse(d, buff, 20);
	printf("%s\n", buff);
	return 0;
}
