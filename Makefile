.SUFFIXES: .c .o .h
CCFLAGS = -Wall #-pg -pedantic -std=c99 
OBJS = wordPairsMain.o getWord.o crc64.o hashTable.o output.o
EXEC = wordpairs 
OPTIONS = -g

${EXEC}: ${OBJS}
	gcc ${CCFLAGS} ${OPTIONS} -o ${EXEC} ${OBJS} -lm
	

wordPairsMain.o: wordPairsMain.c getWord.h crc64.h
	gcc ${CCFLAGS} ${OPTIONS} -c wordPairsMain.c -lm
	
getWord.o: getWord.c getWord.h
	gcc ${CCFLAGS} ${OPTIONS} -c getWord.c -lm
	
crc64.o: crc64.c crc64.h
	gcc ${CCFLAGS} ${OPTIONS} -c crc64.c -lm

hashTable.o: hashTable.c hashTable.h
	gcc ${CCFLAGS} ${OPTIONS} -c hashTable.c -lm

output.o: output.c hashTable.h
	gcc ${CCFLAGS} ${OPTIONS} -c output.c -lm


run: ${EXEC}
	./${EXEC} 
	
clean:
	rm -f ${EXEC} ${OBJS}

valgrind: ${EXEC}
	#valgrind ./${EXEC}
	#valgrind --tool=memcheck --leak-check=full ./${EXEC}
	valgrind --track-origins=yes --leak-check=full ./${EXEC}

prof:
	gprof ${EXEC} gmon.out > prof_output
	
