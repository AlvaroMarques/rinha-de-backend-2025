#include "request.h"


RequestPaymentsPost RequestPaymentsPost__from_string(char * string, size_t size) {
	RequestPaymentsPost p;
	return p;
}

int main() {
	char input[] = "{\"correlationId\":\"de6968d7-8746-4495-978f-5ea8da69e621\",\"amount\":19.9}";
	const char *pattern =
        "\"correlationId\"[[:space:]]*:[[:space:]]*\"([0-9a-fA-F-]{36})\""
        ".*"
        "\"amount\"[[:space:]]*:[[:space:]]*([0-9]+(?:\\.[0-9]+)?)";

	regex_t re;
	if (regcomp(&re, pattern, REG_EXTENDED) != 0) {
		perror("regcomp");
		return 1;
	}

	char uuid[37] = {0};
	char amt_str[32] = {0};

	return 0;
}
