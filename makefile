g++ = g++ -g -Wall -ansi -pedantic -std=c++17 -pthread
-lfl = /usr/lib/gcc/x86_64-linux-gnu/7/../../../x86_64-linux-gnu/libfl.a

lexicon = prs/lexicon
syntax = prs/syntax

program = compiler

execute:    build
			clear
			./tmp/$(program)

run:        build
			clear
			@ ./tmp/$(program) < app/main.fr

test:       main.o
			$(g++) tmp/main.o -o tmp/test
			./tmp/test

compile:    build
			clear
			@ ./tmp/$(program) < $(source)


build:      clean lexicon.o syntax.o main.o
			$(g++) tmp/lexicon.o tmp/syntax.o tmp/main.o $(-lfl) -o tmp/$(program)

lexicon.o:  lexicon.c t
			$(g++) -c $(lexicon).c -o tmp/lexicon.o

lexicon.c:  $(lexicon).lex
			flex -o $(lexicon).c $(lexicon).lex

syntax.o:   $(syntax).c t
			$(g++) -c $(syntax).c -o tmp/syntax.o

syntax.c:	$(syntax).y
			bison -d $(syntax).y -o $(syntax).c

main.o:     src/main.cpp t
			$(g++) -c src/main.cpp -o tmp/main.o



clean:
			rm -f tmp/* $(syntax).h $(syntax).c $(lexicon).c

t:
			@ if [ -f tmp/log ]; then rm tmp/log; fi
			@ touch tmp/log
			@ if [ ! -d tmp ]; then mkdir tmp; fi



# precedence
lexicon.o main.o: syntax.c
syntax.o: lexicon.c
