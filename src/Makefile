# ---------- Makefile ----------
# Toolchain
CC      := gcc
CFLAGS  := -Wall -Wextra -O2 -static -s -MMD -MP   # -MMD auto-generates .d deps

# Sources / objects
SRCS    := main.c request.c dtypes.c
OBJS    := $(SRCS:.c=.o)
DEPS    := $(OBJS:.o=.d)      # list of generated dep files

# -------- default target -------
all: main

# --- link step (build executable) ---
main: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# --- compile step (generic rule) ----
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# -------- convenience targets -------
run: main
	./main

clean:
	rm -f $(OBJS) $(DEPS) main

# pull in header dependencies (.d files) if they exist
-include $(DEPS)

.PHONY: all run clean
# ------------------------------------
