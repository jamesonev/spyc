OOPTS = -Wall -Wextra -g -std=c99 -c
LOPTS = -Wall -Wextra -g -std=c99

.PHONY: run

all: environment

lexeme.o: lexeme.c lexeme.h
	gcc $(OOPTS) lexeme.c

env.o: env.c env.h
	gcc $(OOPTS) env.c

control.o: control.c lexeme.h
	gcc $(OOPTS) control.c

custString.o: custString.c custString.h
	gcc $(OOPTS) custString.c

environment: control.o lexeme.o  env.o custString.o
	gcc $(LOPTS) control.o lexeme.o env.o custString.o -o environment

run:
	./environment

clean:
	rm -f *.o environment