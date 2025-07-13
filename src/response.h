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

typedef enum HTTPStatus {
	HTTP_200_OK = 200,
} HTTPStatus;

typedef struct {
	HTTPStatus status;
	ContentType content_type;
	ConnectionType connection_type;
	unsigned short length;
	char* message;
} response;

const char* parse__content_type(ContentType t);
const char* parse__connection_type(ConnectionType t);
const char* parse_http_status(HTTPStatus s);


#endif
