lab4:	cscd340Lab4.c lab4.o ./utils/myUtils.o
	gcc -g cscd340Lab4.c lab4.o ./utils/myUtils.o -o lab4

lab4.o:	lab4.c lab4.h
	gcc -g -c lab4.c

myUtils.o:	./utils/myUtils.o ./utils/myUtils.h
		gcc -g -c ./utils/myUtils.c

clean:
	rm ./utils/myUtils.o
	rm lab4.o
	rm lab4

