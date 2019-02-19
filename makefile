OOPTS = -Wall -Wextra -g -std=c99 -c
LOPTS = -Wall -Wextra -g -std=c99

.PHONY: run test1 test2 test3 test4 test5

all: pp

lexeme.o: lexeme.c lexeme.h
	gcc $(OOPTS) lexeme.c

lexer.o: lexer.c lexer.h
	gcc $(OOPTS) lexer.c

printer.o: printer.c printer.h
	gcc $(OOPTS) printer.c

custString.o: custString.c custString.h
	gcc $(OOPTS) custString.c

digit.o: digit.c digit.h
	gcc $(OOPTS) digit.c

recognizer.o: recognizer.c recognizer.h
	gcc $(OOPTS) recognizer.c

eval.o: eval.c eval.h
	gcc $(OOPTS) eval.c

control.o: control.c lexer.h
	gcc $(OOPTS) control.c

pp: control.o lexeme.o lexer.o printer.o digit.o recognizer.o eval.o custString.o
	gcc $(LOPTS) control.o lexeme.o lexer.o printer.o digit.o recognizer.o eval.o custString.o -o pp

run:
	./pp test1.spc 
	./pp test2.spc
	./pp test3.spc

test1:
	./pp test1.spc

test2:
	./pp test2.spc

test3:
	./pp test3.spc


clean:
	rm -f *.o pp 
