#include "request.h"

RequestPaymentsPost RequestPaymentsPost__new() {
	RequestPaymentsPost n = {0};
	return n;
}

void RequestPaymentsPost__from_string(RequestPaymentsPost *p, char * string) {
	const char *correlationIdPattern =
        "\"correlationId\"[[:space:]]*:[[:space:]]*\"([0-9a-fA-F-]{36})\"";
	const char *amountPattern = "\"amount\"[[:space:]]*:[[:space:]]*([0-9.]+)";

	regex_t reCorrelationId;
	if (regcomp(&reCorrelationId, correlationIdPattern, REG_EXTENDED) != 0) {
		perror("Error compiling pattern on correlation id regex");
		return;
	}

	regex_t reAmount;
	if (regcomp(&reAmount, amountPattern, REG_EXTENDED) != 0) {
		perror("Error compiling pattern on regex of amount");
		return;
	}

	char amt_str[REQUEST_PAYMENT_AMMOUNT_SIZE] = {0};

	regmatch_t m[2];
	if (regexec(&reCorrelationId, string, 2, m, 0) == 0) {
		memcpy(p->correlationId.uuid,
		       string + m[1].rm_so,
		       m[1].rm_eo - m[1].rm_so);
	} else {
		perror("Error reading correlation id!");
	}

	if (regexec(&reAmount, string, 2, m, 0) == 0) {
		memcpy(amt_str,
		       string + m[1].rm_so,
		       m[1].rm_eo - m[1].rm_so);
		p->amount = decimal__from_string(amt_str, sizeof(amt_str));
	} else {
		perror("Error reading amount!");
	}
}
void RequestPaymentsPost__show(RequestPaymentsPost p) {
	printf("request payments post uuid %s\n", p.correlationId.uuid);
	char buff[DTYPES_DECIMAL_STR_BUFFER_SIZE] = {0};
	decimal__parse(p.amount, buff, sizeof(buff));
	printf("request payments post amount %s\n", buff);
}

int main() {
	char input[] = "{\"correlationId\":\"de6968d7-8746-4495-978f-5ea8da69e621\",\"amount\":19.9}";
	RequestPaymentsPost p;
	RequestPaymentsPost__from_string(&p, input);
	RequestPaymentsPost__show(p);
	return 0;
}
