#ifndef RESPONSE_H
#define RESPONSE_H
#include <stdio.h>
#include <stdlib.h>

typedef enum ContentType {
	CT_JSON = 1,
} ContentType;

typedef enum ConnectionType {
	CT_CLOSE = 1,
} ConnectionType;

typedef struct {
	unsigned short status;
	unsigned short length;
	ConnectionType connection_type;
	unsigned char* message;
} response;

const char* parse__content_type(ContentType t);
const char* parse__connection_type(ConnectionType t);


#endif
