CC      ?= $(CROSS_COMPILE)gcc                                                                                                                 
LD      ?= $(CROSS_COMPILE)ld
AR      ?= $(CROSS_COMPILE)ar
NM      ?= $(CROSS_COMPILE)nm
OBJCOPY ?= $(CROSS_COMPILE)objcopy
OBJDUMP ?= $(CROSS_COMPILE)objdump
READELF ?= $(CROSS_COMPILE)readelf

OBJS = main.o incbin.o

CFLAGS += -Wall -I../ta/include/host -I$(TEEC_EXPORT)/include -I./include

#Add/link other required libraries here
LDADD += -lteec -L$(TEEC_EXPORT)/lib
LDADD += -lutil -L$(TEEC_EXPORT)/lib

BINARY = sodtest

.PHONY: all
all: $(BINARY)

$(BINARY): $(OBJS)
	$(CC) -o $@ $< $(LDADD)

.PHONY: clean
clean:
	rm -f $(OBJS) $(BINARY)

%.o: %.c
	$(CC) $(CFLAGS) -c main.c -o main.o
	$(CC) -c incbin.c -o incbin.o

