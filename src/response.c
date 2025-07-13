#include "response.h"

const char* parse__content_type(ContentType t) {
	switch (t) {
		case CT_JSON:
			return "application/json";
		default:
			return "";
	}

}
const char* parse__connection_type(ConnectionType t) {
	switch (t) {
		case CT_CLOSE:
			return "close";
		default:
			return "";
	}
}
const char* parse_http_status(HTTPStatus s) {
	switch (s) {
		case HTTP_200_OK:
			return "200 OK";
		default:
			return "";
	}
}

int main() {
	printf("%s\n",  parse__content_type(CT_JSON));
	printf("%s\n",  parse__connection_type(CT_CLOSE));
	return 0;
}
