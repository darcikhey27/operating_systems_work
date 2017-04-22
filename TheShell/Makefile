CC=gcc


lab7: ush.c alias/alias.o history/history.o linkedlist/linkedList.o pipes/pipes.o process/process.o tokenize/makeArgs.o utils/myUtils.o
	gcc ush.c alias/alias.o history/history.o linkedlist/linkedList.o pipes/pipes.o process/process.o tokenize/makeArgs.o utils/myUtils.o -o lab7

alias.o: alias/alias.c alias/alias.h alias/aliasUtil.c alias/aliasUtil.c
	gcc -g -c alias/alias.c alias/aliasUtil.c 

history.o: history/history.c history/history.h
	gcc -g -c history/history.c 

linkedList.o: linkedlist/linkedList.c linkedlist/linkedList.h linkedlist/listUtils.c linkedlist/listUtils.h linkedlist/requiredIncludes.h
	gcc -g -c linkedlist/linkedList.c linkedlist/listUtils.c 

pipes.o:	pipes/pipes.c pipes/pipes.h
	gcc -g -c pipes/pipes.c 

process.o:	process/process.c process/process.h
	gcc -g -c process/process.c

makeArgs.o:	tokenize/makeArgs.c tokenize/makeArgs.h
	gcc -g -c tokenize/makeArgs.c 

myUtils.o:	utils/myUtils.c utils/myUtils.h
	gcc -g -c utils/myUtils.c 

clean:
	find . -name "*.o" -type f -delete
