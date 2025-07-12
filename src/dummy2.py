#!/usr/bin/env python3
from http.server import HTTPServer, BaseHTTPRequestHandler

# Fixed JSON payload
BODY = b'''{
    "default" : {
        "totalRequests": 43236,
        "totalAmount": 415542345.98
    },
    "fallback" : {
        "totalRequests": 423545,
        "totalAmount": 329347.34
    }
}
'''

class StatsHandler(BaseHTTPRequestHandler):
    def _serve(self):
        # Log client IP and port
        ip, port = self.client_address
        print(f"Request from {ip}:{port}")

        # Send 200 OK with JSON
        self.send_response(200, "Ok")
        self.send_header("Content-Type", "application/json; charset=utf-8")
        self.send_header("Content-Length", str(len(BODY)))
        self.end_headers()

        # HEAD should omit body
        if self.command != "HEAD":
            self.wfile.write(BODY)

    # Route all common verbs to the same handler
    do_GET     = _serve
    do_POST    = _serve
    do_PUT     = _serve
    do_DELETE  = _serve
    do_PATCH   = _serve
    do_HEAD    = _serve
    do_OPTIONS = _serve

if __name__ == "__main__":
    PORT = 9999
    with HTTPServer(("", PORT), StatsHandler) as httpd:
        print(f"Listening on port {PORT}; always returns 200 with fixed stats JSON.")
        httpd.serve_forever()

