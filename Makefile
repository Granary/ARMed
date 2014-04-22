
CC	:= gcc

LIBSRC	:= decode_table.c decode_fast.c decode.c instruction.c #encode.c instrlist.c
LIBOBJ	:= $(LIBSRC:.c=.o)

LIBARM	:= 	libarm.a

CFLAGS	:=	-w -Wall -g -O0
LOADLIBES	:=	-L./

TARGET	:= $(LIBARM)

all: $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(LIBOBJ)
	ar rcs $(LIBARM) $(LIBOBJ)
	ranlib $(LIBARM)
	
	
clean:
	rm -f *.o $(LIBARM)
