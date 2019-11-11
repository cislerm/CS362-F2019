CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard
	./testDrawCard &> unittestresults.out
	gcov dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)
	
unit1: unittest1.c dominion.o rngs.o
	gcc -o unit1 unittest1.c dominion.o rngs.o $(CFLAGS)
	
unit2: unittest2.c dominion.o rngs.o
	gcc -o unit2 unittest2.c dominion.o rngs.o $(CFLAGS)
	
unit3: unittest3.c dominion.o rngs.o
	gcc -o unit3 unittest3.c dominion.o rngs.o $(CFLAGS)
	
unit4: unittest4.c dominion.o rngs.o
	gcc -o unit4 unittest4.c dominion.o rngs.o $(CFLAGS)
	
unit5: unittest5.c dominion.o rngs.o
	gcc -o unit5 unittest5.c dominion.o rngs.o $(CFLAGS)
	
unittestresults: unit1 unit2 unit3 unit4 unit5 
	./unittest1 &> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./unittest5 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

all: playdom player testDrawCard unit1 unit2 unit3 unit4 unit5 

clean:
	rm -f *.o playdom.exe playdom test.exe test unittest1 unittest1.exe unittest2 unittest2.exe unittest3 unittest3.exe unittest4.exe unittest4 unittest5.exe unittest5 player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe \
	randomtest1 randomtest2 randomtest3
