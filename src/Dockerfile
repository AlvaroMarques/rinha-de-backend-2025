# Etapa de build
FROM gcc:13-bookworm AS builder
WORKDIR /app
COPY response.h .
COPY response.c .
COPY main.c .
RUN gcc -Wall -O2 -static -s -o main main.c
RUN gcc -Wall -O2 -static -s -o response response.c

# Imagem final enxuta
FROM debian:bookworm-slim
WORKDIR /app
COPY --from=builder /app/response .
COPY --from=builder /app/main .
EXPOSE 9999
# CMD ["./main"]
