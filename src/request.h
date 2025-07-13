#ifndef REQUEST__H
#define REQUEST__H

#include "dtypes.h"
#include <regex.h>
#include <string.h>

#define REQUEST_PAYMENT_AMMOUNT_SIZE 32

typedef struct RequestPaymentsPost {
	DtypeUUID correlationId;
	DtypeDecimal amount;
} RequestPaymentsPost;

void RequestPaymentsPost__from_string(RequestPaymentsPost *p, char * string);
RequestPaymentsPost RequestPaymentsPost__new();
void RequestPaymentsPost__show(RequestPaymentsPost p);

#endif
