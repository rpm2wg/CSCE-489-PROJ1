/*************************************************************************************
 * shellfuncts.c - code definitions for your functions
 *
 *************************************************************************************/

#include <stdio.h>
#include "shellfuncts.h"
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <stdlib.h>

//Parse the user input for the command if statements
int parse_input(const char *input){
	
	char *sptr;
	char ibuffer[100];
	strncpy(ibuffer, input, 100);
	sptr = ibuffer; 
	char *start = sptr;
	char param[100];
	
	
	while (*sptr != '\0')
	{
		if (*sptr == ' '){
			*sptr = '\0';
			strncpy(param, start, 100);
			
			//Start the command if statements
			if (strcmp(param, "update") == 0){
				//UPDATE COMMAND
				if (fork() == 0){
					printf("This child PID is: %d\n", getpid());
					char updParams[100];
					strncpy(updParams, start+7, 100);
					char *paraPtr;
					paraPtr = updParams;
					char *updstart = paraPtr;
					char newParam[4][100];
					int state = ' ';
				
				while (*paraPtr != '\0')
				{
					switch (state)
					{
					case '\n':
					case ' ':
						if (*paraPtr == '\"')
						break;
					
					default:
						break;
					}
				}
					
					return 0;
				} else {
					wait(NULL);
				} 
			}else if (strcmp(param, "list") == 0){
				//LIST COMMAND
				if (fork() == 0){
					printf("This child PID is: %d\n", getpid());
					char filename[100];
					strncpy(filename, start+5, 100);
				
					//Corrected the filename because of the carriage return
					if (filename[strlen(filename)-1] == '\n'){
					filename[strlen(filename)-1] = '\0';
					}

					//Opens file based off the filename given.
					FILE * filepoint;
					filepoint = fopen(filename,"r");
				
					//Catch error if file does not exitst
					if(filepoint == NULL){
				 		perror("Error! File does not exist or no file specified.\n");
				 		return -1;
					}
				
					//Creates the cat command then uses it to display the output of the specified file
					char command[200];
					snprintf(command, 200, "/bin/cat");
					printf("%s", command);
					execl(command, command, filename, NULL);
					fclose(filepoint);
					return 0;
				} else {
					wait(NULL);
				}
				

			} else if(strcmp(param, "create") == 0){
				//CREATE COMMAND
				if (fork() == 0){
					printf("This child PID is: %d\n", getpid());
					char filename[100];		
					strncpy(filename, start+7, 100);
					
					//Error catch for no file name
					if (strcmp(filename, "\n") == 0){
						printf("No file name specified!\n");
						return -1;
					}
					
					//Corrected the filename because of the carriage return
					if (filename[strlen(filename)-1] == '\n'){
						filename[strlen(filename)-1] = '\0';
					}

					FILE * filepoint;
					filepoint = fopen(filename, ("w"));
					printf("Created a file with the name %s! \n", filename);
					fclose(filepoint);
					return 0;
				}
			} else {printf("Error! Incorrect syntax or no arguments given.\n");}
		} else if (*sptr != ' ')
		{
			strncpy(param, start, 100);
			
			if (strcmp(param, "dir\n") == 0){
				//DIR COMMAND				
				if ( fork() == 0){
					printf("This child PID is: %d\n", getpid());
					execl("/bin/ls", "ls", NULL);
				} else {
					wait(NULL);
				}
				return 0;
			} 			
		}
		sptr++;
	}
	
	return 0;
}