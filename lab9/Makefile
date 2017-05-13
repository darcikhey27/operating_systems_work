lab9: cscd340Lab9.c utils/myUtils.o
	gcc cscd340Lab9.c utils/myUtils.o -lm -o lab9

myUtils.o:./utils/myUtils.o ./utils/myUtils.h
		gcc	 -g -c ./utils/myUtils.c
clean:
	rm *.o
