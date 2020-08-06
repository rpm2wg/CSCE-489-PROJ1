/*************************************************************************************
 * This function is designed to parse input from the main function and execute		 *
 * the commands of the user. 														 *
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
				//UPDATE COMMAND will update a file and add text to it.
			
				char *updPtr;
				char updiBuffer[200];
				strcpy(updiBuffer, start+7);
				updPtr = updiBuffer;
				char *updStart = updPtr;
				char updparam[200];
				char updFilename[200];  //This is the filename of the file to be updated.
				int n;
				int c;
				char copyNum[100];  //This is the number of times to copy the text into the file.
				char copyText[200];  //This is the variable that holds the text to be updated in the file.
				char bgOpt[100];
				
				//This loop captures the filename until it encounters a space.
				while (*updPtr != '\0')
				{
					if (*updPtr == ' ')
					{ 
						*updPtr = '\0';
						strcpy(updparam, updStart);
					}
					updPtr++;
				}
				
				//This copies the filename to the updFilename variable and prepares for the next part of the command.
				strcpy(updFilename, updparam);
				n = strlen(updFilename)+8;
				strncpy(updiBuffer, start+n, 200);
				updPtr=updiBuffer;
				//Captures the number of times to copy the text string into the file.
				while (*updPtr != '\0')
				{
					if (*updPtr == ' ')
					{ 
						*updPtr = '\0';
						strcpy(updparam, updStart);
						
					}
					updPtr++;
				}
				
				//Copies the number into the copyNum variable and prepares the rest of the command.
				strncpy(copyNum, updparam, 100);
				int numcopy = atoi(copyNum);				
				c = strlen(copyNum)+1+n;
				strncpy(updiBuffer, start+c, 200);
				updPtr = updiBuffer;
				//Gathers the text input for the file
				while (*updPtr != '\0')
				{
					updPtr++;
					if (*updPtr == '"')
					{ 
						updPtr++;
						*updPtr = '\0';
						strcpy(updparam, updStart);
						
					}
					
				}
				
				//Copies the text into the copyText variable and prepares the rest of the command
				strncpy(copyText, updparam, 200);							
				int d = strlen(copyText)+1+c;
				strncpy(updiBuffer, start+d, 200);
				updPtr=updiBuffer;
				
				//Looks for the optional & at the end
				while (*updPtr != '\0')
				{
					strcpy(updparam, updStart);	
					updPtr++;
				}
				
				//Copy and cleanup output for the optional &
				strncpy(bgOpt, updStart, 100);
				if (bgOpt[strlen(bgOpt)-1] == '\n')
				{
					bgOpt[strlen(bgOpt)-1] = '\0';
				}				
				//updFilename is the file to put the text in
				//numcopy is the number of times to copy as an int
				//copyText is the text to copy
				//bgOpt is the option for background
				
				if (strcmp(bgOpt, "&") == 0)
				{
				 	if (fork() == 0){
						FILE * filepoint;
						filepoint = fopen(updFilename,"a");
						for (int i = 0; i < numcopy; i++)
						{
							fprintf(filepoint, "%s", copyText);
						}
						fflush(filepoint);
						sleep(strlen(copyText)/5);
						fclose(filepoint);
						printf("This child PID is: %d\n", getpid());
						printf("The file update has completed!\n");
						return 0;
					 }
				}else if (fork() == 0){
					FILE * filepoint;
					filepoint = fopen(updFilename,"a");
					for (int i = 0; i < numcopy; i++)
					{
						fprintf(filepoint, "%s", copyText);
					}
					fflush(filepoint);
					sleep(strlen(copyText)/5);
					fclose(filepoint);
					printf("This child PID is: %d\n", getpid());
					printf("The update has completed!\n");
					return 0;
					}else
					{
						wait(NULL);
					}
				
				return 0;
				
			
			
				
			}else if (strcmp(param, "list") == 0){
				//LIST COMMAND is used to show the contents of a file
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
				 		printf("Error! File does not exist or no file specified.\n");
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
				return 0;
				

			} else if(strcmp(param, "create") == 0){
				//CREATE COMMAND creates a new file
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

					//Checks if file exists before the user overwrites it!
					if (access(filename, F_OK) != -1)
					{
						printf("Error! File already exists!\n");
						return -1;
					}
					
					//creates the new file and notifies the user that it was successful
					FILE * filepoint;
					filepoint = fopen(filename, ("w"));
					printf("Created a file with the name %s! \n", filename);
					fclose(filepoint);
					return 0;
				}
			} else {printf("Error! Incorrect syntax or no arguments given.\n");} //Trying to catch errors from input
			return 0;
		} else if (*sptr != ' ')
		{
			strncpy(param, start, 100);
			
			if (strcmp(param, "dir\n") == 0){
				//DIR COMMAND lists everything in the directory of the program			
				if ( fork() == 0){
					printf("This child PID is: %d\n", getpid());
					execl("/bin/ls", "ls", NULL);
					return 0;
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