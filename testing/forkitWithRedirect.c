#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
#include "./pipes/pipes.h"
#include "./process/process.h"
#include "./tokenize/makeArgs.h"

# define MAX 100 


int main() {
   char s[MAX];

   printf("command?: ");
   fgets(s, MAX, stdin);
    
   // if(s is a redirect command)
   //    forkItwithRedirect(s)




    return 0;
}
