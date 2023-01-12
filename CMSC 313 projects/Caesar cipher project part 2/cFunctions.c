#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>
#include <stdbool.h>

//function for r menu option


int sqaure(int num){
	return (int)sqrt ((double)num);
}

void show(char *str[]){
	for(int i = 0; i < 10, i++){
		printf("%s \n", arr[i]);
	}
	return;

}


char * readIn(char * messages){
	int buffer = 256;
	int position = 0;

	char* cmd = malloc(sizeof(char) * buffer);
	
	int cha;
	int count = 1;
	
	if((int)cmd[0] < 64 && (int)cmd[0] > 91){
		printf ("error");
	}

	while (count == 1){
		cha = fgetc(stdin);
		if (cha == EOF || cha == '\n'){
			if(cmd[position-1] != '!' || cmd[position-1] != '.' || cmd[position-1] != '?' ){
				printf ("error");
			}	
			cmd[position] = '\0';
			count = 0;
		}
		else{
			cmd[position] = cha;

		}
		position++;

		if (position >= buffer){
			cmd realloc(cmd, buffer);
		}
	}

	return cmd;	
}



void freeUp (char* messages){
	free(messages);
}

