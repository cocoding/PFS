CC=g++
OUT:=out.bin
LD=ld
CCFLAGS= -g
LDFLAGS=
.PHONY : everything
everything :$(OUT)
OBJECT:=reactor.o event.o 
$(OUT): $(OBJECT)
		$(LD) $(LDFLAGS) -o $(OUT) $(OBJECT)
reactor.o:reactor.cpp
		$(CC) $(CCFLAGS) -o $@ $<
event.o: event.cpp
		$(CC) $(CCFLAGS) -o $@ $<
