#include "request.h"


RequestPaymentsPost RequestPaymentsPost__from_string(char * string, size_t size) {
	RequestPaymentsPost p;
	const char *correlationIdPattern =
        "\"correlationId\"[[:space:]]*:[[:space:]]*\"([0-9a-fA-F-]{36})\"";
	const char *ammountPattern =
         "\"amount\"[[:space:]]*:[[:space:]]*([0-9]+(?:\\.[0-9]+)?)";

	regex_t reCorrelationId;
	if (regcomp(&reCorrelationId, correlationIdPattern, REG_EXTENDED) != 0) {
		perror("Error compiling pattern on correlation id regex");
		return p;
	}

	regex_t reAmmount;
	if (regcomp(&reAmmount, ammountPattern, REG_EXTENDED) != 0) {
		perror("Error compiling pattern on regex of ammount");
		return p;
	}

	char uuid[DTYPES_UUID_EXPECTED_SIZE] = {0};
	char amt_str[REQUEST_PAYMENT_AMMOUNT_SIZE] = {0};



	return p;
}

int main() {
	char input[] = "{\"correlationId\":\"de6968d7-8746-4495-978f-5ea8da69e621\",\"amount\":19.9}";
	const char *pattern =
        "\"correlationId\"[[:space:]]*:[[:space:]]*\"([0-9a-fA-F-]{36})\"";

	regex_t re;
	if (regcomp(&re, pattern, REG_EXTENDED) != 0) {
		perror("regcomp");
		return 1;
	}

	char uuid[37] = {0};
	char amt_str[32] = {0};

	regmatch_t m[2];
	if (regexec(&re, input, 2, m, 0) == 0) {
	memcpy(uuid,
	       input + m[1].rm_so,
	       m[1].rm_eo - m[1].rm_so);
	}
	printf("%s\n", uuid);


	return 0;
}
