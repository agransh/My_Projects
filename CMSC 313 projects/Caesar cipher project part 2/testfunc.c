#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>
#include <stdbool.h>


//TAKES IN THE ORIGINAL MESSAGE
//RETURNS THE NEW MESSAGE AFTER CHECKING IT
//IF THERE IS AN ERROR, IT RETURNS THE ORIGINAL MESSAGE ALONG WITH AN ERROR MESSAGE
void edit(char *arr[], int *index){
	int buffer = 256;
	int pos = 0;
	
	char *cmd = malloc(sizeof(char) * buffer);
	
	char cha;
	int cont = 1;
	
	while(cont == 1){ //LOOP UNTIL END OR WE GET AN ERROR
		
		cha = fgetc(stdin);
		
		if(pos == 0){ //CHECK THE FIRST LETTER
			
			if((int)cha < 65 || (int) cha > 90){ //CHECK FOR LOWERCASE
	
				printf("ERROR\n");
				return; //RETURNS	
			}

			cmd[pos]=cha;
		}
		
		else if(cha == EOF || cha == '\n'){ //END OF THE STRING
			
			if(cmd[pos - 1] == '?' || cmd[pos - 1] == '!' || cmd[pos - 1] == '.'){ //CHECKS IF IT ENDS ON PUNCTUATION
				
				cmd[pos] = '\0';
				cont = 0;
			}
			else{ //DOESN'T END ON PUNCTUATION
				
				printf("ERROR\n");
				return; //RETURNS
			}
		}
		
		else
			cmd[pos] = cha;
		pos++;
		
		if(pos >= buffer){ //SIZE EXCEEDS ALLOCATED SPACE
			
			buffer += 256;
			cmd = realloc(cmd, buffer);
		}
	}

	arr[*index] = cmd;

	*index = *index + 1;

	*index = *index % 10;

	return;
}



void display (char *arr[]) {

	for (int i = 0; i <10; ++i){
		printf ("Message[%d] %s \n",i,arr[i]);
    }
}

void decipher(char *arr[], int index){
	
	int buffer = 256;
	
	char *str = malloc(sizeof(char) * buffer);
	for(int i = 0; i < strlen(arr[index]); i++){ //Change everything to lowercase
		
		if((int)arr[index][i] >= 65 && (int)arr[index][i] <= 90) //UPPERCASE --> LOWERCASE
			str[i] = arr[index][i] + 32;
		
		else
			str[i] = arr[index][i];
	}
	
	int numList[26]; //LIST FOR LARGEST # FOR popularList
	char letterList[26]; //LIST FOR THE 5 MOST POPULAR CHARS
	int size = strlen(str); //SIZE OF THE ARRAY
	
	int numCount = 0;
	int letterCount = 0;
	
	for(int i = 0; i < 26; i++){ //Load in the arrays
		
		letterList[i] = ' ';
		numList[i] = 0;
	}
	
	for(int i = 0; i < size; i++){
		
		if((int)str[i] >= 97){ //Is a letter
			
			bool exists = false;
			
			for(int j = 0; j < 26; j++){
				
				if(letterList[j] == ' ') //Empty parts of the array
					break;
				
				else if(letterList[j] == str[i]){ //Already exists in array
					
					exists = true;
					break;
				}
			}
			
			if(exists == false){ //Word not in popularList yet
				
				int count = 0;
				
				for(int x = 0; x < size; x++){
					
					if(str[i] == str[x])
						count++;
				}
				
				letterList[letterCount] = str[i]; //Move in the character and count
				numList[numCount] = count;
				
				letterCount++; //Increment counters
				numCount++;
			}
		}
	}
	
	char popList[5];
	
	for(int i = 0; i < 5; i++){ //Loop through popList
		
		int biggest = 0; //Index of the biggest number
		
		for(int j = 0; j < 26; j++){ //Loops through the arrays
			
			if(numList[j] == 0) //Empty parts of array
				break;
			
			if(numList[j] != -1)
				if(numList[j] > numList[biggest])
					biggest = j;
		}
		
		popList[i] = letterList[biggest];
		numList[biggest] = -1; //Make it so it cant be reused
	}
	
	int asciiList[5]; //ARRAY FOR ASCII VALUES
	for(int i = 0; i < 5; i++)
		asciiList[i] = (int)popList[i];
	
	char *strTwo = malloc(sizeof(char) * buffer); //STRING TO PRINT
	
	//DECRYPT W/ 'e'
	int shifter = 101 - asciiList[0];
	shifter = abs(shifter);
	
	for(int i = 0; i < size; i++){
		
		char letter = str[i];

		if((int)letter >= 97 && (int)letter <= 122){ //Letter
			
			if(((int)letter + shifter) > 122){ //Wrap around
				
				int temp = ((int)letter + shifter) - 26;
				temp = (int)letter - temp;
				
				letter = letter - temp;
			}
			
			else //Shift letters
				letter = letter + shifter;
		}
		
		strTwo[i] = letter;
	}
	
	printf("%s \n", strTwo);
    printf("OR\n");
	
	//DECRYPT W/ 't'
	shifter = 116 - asciiList[1];
	shifter = abs(shifter);
	
	for(int i = 0; i < size; i++){
		
		char letter = str[i];
;
		if((int)letter >= 97 && (int)letter <= 122){ //Letter
			
			if(((int)letter + shifter) > 122){ //Wrap around
				
				int temp = ((int)letter + shifter) - 26;
				temp = (int)letter - temp;
				
				letter = letter - temp;
			}
			
			else //Shift letters
				letter = letter + shifter;
		}
		
		strTwo[i] = letter;
	}
	
	printf("%s \n", strTwo);
    printf("OR\n");
	
	//DECRYPT W/ 'a'
	shifter = 97 - asciiList[2];
	shifter = abs(shifter);
	
	for(int i = 0; i < size; i++){
		
		char letter = str[i];

		if((int)letter >= 97 && (int)letter <= 122){ //Letter
			
			if(((int)letter + shifter) > 122){ //Wrap around
				
				int temp = ((int)letter + shifter) - 26;
				temp = (int)letter - temp;
				
				letter = letter - temp;
			}
			
			else //Shift letters
				letter = letter + shifter;
		}
		
		strTwo[i] = letter;
	}
	
	printf("%s \n", strTwo);
    printf("OR\n");
	
	//DECRYPT W/ 'o'
	shifter = 111 - asciiList[3];
	shifter = abs(shifter);
	
	for(int i = 0; i < size; i++){
		
		char letter = str[i];

		if((int)letter >= 97 && (int)letter <= 122){ //Letter
			
			if(((int)letter + shifter) > 122){ //Wrap around
				
				int temp = ((int)letter + shifter) - 26;
				temp = (int)letter - temp;
				
				letter = letter - temp;
			}
			
			else //Shift letters
				letter = letter + shifter;
		}
		
		strTwo[i] = letter;
	}
	
	printf("%s \n", strTwo);
    printf("OR\n");
	
	//DECRYPT W/ 'i'
	shifter = 105 - asciiList[4];
	shifter = abs(shifter); 
	
	
	for(int i = 0; i < size; i++){
		
		char letter = str[i];
		
		if((int)letter >= 97 && (int)letter <= 122){ //Letter
			
			if(((int)letter + shifter) > 122){ //Wrap around
				
				int temp = ((int)letter + shifter) - 26;
				temp = (int)letter - temp;
				
				letter = letter - temp;
			}
			
			else //Shift letters
				letter = letter + shifter;
		}
		
		strTwo[i] = letter;
	}
	
	printf("%s \n", strTwo);
    printf("\n");

	return;

}

