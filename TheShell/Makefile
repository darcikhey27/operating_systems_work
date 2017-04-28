CC=gcc


ush: cscd340Lab7.c alias/alias.o aliasUtil.o history/history.o historyUtil.o linkedlist/linkedList.o listUtils.o pipes/pipes.o process/process.o tokenize/makeArgs.o utils/myUtils.o
	gcc cscd340Lab7.c alias/alias.o aliasUtil.o history/history.o historyUtil.o linkedlist/linkedList.o listUtils.o pipes/pipes.o process/process.o tokenize/makeArgs.o utils/myUtils.o -o ush

alias.o: alias/alias.c alias/alias.h
	gcc -g -c alias/alias.c

aliasUtil.o: alias/aliasUtil.c alias/aliasUtil.h
	gcc -g -c alias/aliasUtil.c

history.o: history/history.c history/history.h
	gcc -g -c history/history.c 

historyUtil.o: history/historyUtil.c history/historyUtil.h
	gcc -g -c history/historyUtil.c 

linkedList.o: linkedlist/linkedList.c linkedlist/linkedList.h
	gcc -g -c linkedlist/linkedList.c

listUtils.o: linkedlist/listUtils.c linkedlist/listUtils.h
	gcc -g -c linkedlist/listUtils.c

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
