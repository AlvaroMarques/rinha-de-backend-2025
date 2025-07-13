/* json_dummy_server.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "request.h"

#define PORT     9999
#define BACKLOG  10
#define RESPONSE "HTTP/1.1 200 OK\r\n"           \
                 "Content-Type: application/json\r\n" \
                 "Content-Length: 14\r\n"         \
                 "Connection: close\r\n"          \
                 "\r\n"                           \
                 "{\"foo\": \"bar\"}"

/*========= CONFIG & FIXED PAYLOADS =========*/
#define PORT        9999
#define BACKLOG     10

/* JSON bodies */
#define JSON_BODY_PAYMENTS "{\"message\":\"payment processed successfully\"}"
#define JSON_BODY_SUMMARY  "{\"default\":{\"totalRequests\":0,\"totalAmount\":0},\"fallback\":{\"totalRequests\":0,\"totalAmount\":0}}"

/* Pre-built HTTP responses (CRLF line endings) */
#define RESPONSE_PAYMENTS "HTTP/1.1 200 OK\r\n" \
                          "Content-Type: application/json\r\n" \
                          "Content-Length: 44\r\n" \
                          "Connection: close\r\n" \
                          "\r\n" \
                          JSON_BODY_PAYMENTS

#define RESPONSE_SUMMARY  "HTTP/1.1 200 OK\r\n" \
                          "Content-Type: application/json\r\n" \
                          "Content-Length: 94\r\n" \
                          "Connection: close\r\n" \
                          "\r\n" \
                          JSON_BODY_SUMMARY


int server_fd;

void cleanup(int signo)
{
    (void)signo;
    close(server_fd);
    puts("\nServer shut down.");
    exit(EXIT_SUCCESS);
}

int main(void)
{
    signal(SIGINT, cleanup);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) { perror("socket"); return 1; }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr = {0};
    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port        = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("bind"); return 1;
    }
    if (listen(server_fd, BACKLOG) == -1) { perror("listen"); return 1; }

    printf("Listening on port %d; always returns JSON dummy.\n", PORT);

    for (;;) {
        struct sockaddr_in client;
        socklen_t len = sizeof(client);
        int client_fd = accept(server_fd, (struct sockaddr *)&client, &len);
        if (client_fd == -1) { perror("accept"); continue; }

        printf("Connection from %s:%d\n",
               inet_ntoa(client.sin_addr), ntohs(client.sin_port));

        /* (Opcional) Ler e descartar a requisição */
        char buf[1024];
        recv(client_fd, buf, sizeof(buf), 0);
	printf("%s\n", buf);

	RequestPaymentsPost p;
	RequestPaymentsPost__from_string(&p, buf);
	RequestPaymentsPost__show(p);

        /* Enviar a resposta fixa */
        send(client_fd, RESPONSE_SUMMARY, sizeof(RESPONSE_SUMMARY) - 1, 0);
        close(client_fd);
    }
}
