#ifndef REQUEST__H
#define REQUEST__H

#include "dtypes.h"
#include <regex.h>

typedef struct RequestPaymentsPost {
	DtypeUUID correlationId;
	DtypeDecimal amount;
} RequestPaymentsPost;

RequestPaymentsPost RequestPaymentsPost__from_string(char * string, size_t size);

#endif
