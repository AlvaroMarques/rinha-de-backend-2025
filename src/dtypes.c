#include "dtypes.h"


DtypeDecimal decimal__new(unsigned int integer, unsigned short fractional) {
	DtypeDecimal d;
	d.integer = integer;
	d.fractional = fractional;
	return d;
}

DtypeDecimal decimal__from_string(char *input, size_t size) {
	/* Ultra Not Safe function, known bugs that I won't bother trying to make it work:
	 * 	If the input is:
	 * 		- "10. junk 20" -> Will return 10.20
	 * 		- "10.2" -> Will return 10.02
	 * 	If the number is too big (> unsigned int limit) it will overflow.
	 * 	If the input doesn't have an ., the fraction will be 0 (which thinking about it it can make sense)
	 * I'm assuming the decimal input will always be perfect
	 */
	size_t i;
	// Adding this for safety when reading the int
	input[size-1] = '\0';

	DtypeDecimal d;
	d.fractional = 0;
	d.integer = (unsigned int) strtol(input, NULL, 10);
	for (i = 0; i < size; i++){
		if (input[i] == '.') {
			d.fractional = (unsigned int) strtol(&(input[i+1]), NULL, 10);
		}
	}
	return d;
}

bool decimal__is_valid(DtypeDecimal d) {
	return (d.fractional < 100);
}

void decimal__parse(DtypeDecimal d, char* buff, size_t size) {
	if (decimal__is_valid(d)) {
		snprintf(buff, size, "%u.%02u", d.integer, d.fractional);
	} else {
		snprintf(buff, size, "Invalid Decimal: %u.%02u", d.integer, d.fractional);
	}
}

/*
int main() {
	DtypeDecimal d = decimal__new(10, 37);
	char buff[DTYPES_DECIMAL_STR_BUFFER_SIZE];
	decimal__parse(d, buff, 20);
	printf("%s\n", buff);
	d = decimal__new(10, 107);
	decimal__parse(d, buff, 30);
	printf("%s\n", buff);
	printf("%ld\n", strtol("10.10", NULL, 10));
	char input[] = "10.20";
	d = decimal__from_string(input, sizeof(input));
	printf("%u %u\n", d.integer, d.fractional);
	decimal__parse(d, buff, 20);
	printf("%s - Result\n", buff);
	return 0;
}*/
