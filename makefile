OOPTS = -Wall -Wextra -g -std=c99 -c
LOPTS = -Wall -Wextra -g -std=c99

.PHONY: run test1 t1p test2 test3 test4 test5

all: dpl

control.o: control.c lexer.h
	gcc $(OOPTS) control.c

custString.o: custString.c custString.h
	gcc $(OOPTS) custString.c

digit.o: digit.c digit.h
	gcc $(OOPTS) digit.c

env.o: env/env.c env/env.h
	gcc $(OOPTS) env/env.c

eval.o: eval.c eval.h
	gcc $(OOPTS) eval.c

lexeme.o: lexeme.c lexeme.h
	gcc $(OOPTS) lexeme.c

lexer.o: lexer.c lexer.h
	gcc $(OOPTS) lexer.c

printer.o: printer.c printer.h
	gcc $(OOPTS) printer.c

recognizer.o: recognizer.c recognizer.h
	gcc $(OOPTS) recognizer.c

dpl: control.o lexeme.o lexer.o printer.o digit.o recognizer.o env.o eval.o custString.o
	gcc $(LOPTS) control.o lexeme.o lexer.o printer.o digit.o recognizer.o env.o eval.o custString.o -o dpl

run:
	./dpl tests/test1.spc 
	./dpl tests/test2.spc
	./dpl tests/test3.spc

test1:
	./dpl tests/test1.spc

t1p:
	./dpl tests/test1.spc -pp

test2:
	./dpl tests/test2.spc

test3:
	./dpl tests/test3.spc

error1:
	@cat tests/e1.spc

error1x:
	./dpl tests/e1.spc

error2:
	@cat tests/e2.spc

error2x:
	./dpl tests/e2.spc

error3:
	@cat tests/e3.spc

error3x:
	./dpl tests/e3.spc

error4:
	@cat tests/e4.spc

error4x:
	./dpl tests/e4.spc

error5:
	@cat tests/e5.spc

error5x:
	./dpl tests/e5.spc

conditionals:
	@cat tests/cond.spc

conditionalsx:
	./dpl tests/cond.spc

clean:
	rm -f *.o dpl 
