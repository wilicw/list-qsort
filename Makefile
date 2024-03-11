CC = gcc
CFLAGS = -g -std=c99 -Wall -I.

# Emit a warning should any variable-length array be found within the code.
CFLAGS += -Wvla

all: main

tid := 0

OBJS := main.o queue.o

deps := $(OBJS:%.o=.%.o.d)

# Control the build verbosity
ifeq ("$(VERBOSE)","1")
    Q :=
    VECHO = @true
else
    Q := @
    VECHO = @printf
endif

main: $(OBJS)
	$(Q)$(CC) $(LDFLAGS) -o $@ $^ -lm

%.o: %.c
	@mkdir -p .$(DUT_DIR)
	$(VECHO) "  CC\t$@\n"
	$(Q)$(CC) -o $@ $(CFLAGS) -c -MMD -MF .$@.d $<

clean:
	rm -f $(OBJS) $(deps) *~
	rm -rf *.dSYM

distclean: clean
	rm -f .cmd_history

-include $(deps)
