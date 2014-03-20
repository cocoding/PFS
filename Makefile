CC=g++
OUT:=out.bin
LD=ld
CCFLAGS= -g -lpthread
LDFLAGS=
.PHONY : everything
everything :$(OUT)
OBJECT:=main.o reactor.o event.o 
$(OUT): $(OBJECT)
		$(LD) $(LDFLAGS) -o $(OUT) $(OBJECT)
reactor.o:reactor.cpp
		$(CC) $(CCFLAGS) -o $@ $<
event.o: event.cpp
		$(CC) $(CCFLAGS) -o $@ $<
main.o:main.cpp
		$(CC) $(CCFLAGS) -o $@ $<

