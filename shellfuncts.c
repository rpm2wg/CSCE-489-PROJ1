/*************************************************************************************
 * shellfuncts.c - code definitions for your functions
 *
 *************************************************************************************/

#include <stdio.h>
#include "shellfuncts.h"
#include <string.h>

/*************************************************************************************
 * hello - sends hello world to the user! I'm doing proper function commenting so future
 *         coders might not find my code as painful.
 *
 *		Params:	param1 - I explain my parameters, like this is 1 for American, 2 for
 *                      Australian
 *
 *		Returns: always returns 1, no matter what. Fairly useless.
 *
 *************************************************************************************/

int hello(int param1) {
	// I'm commenting to explain that this checks param and changes the message
	if (param1 == 1)
		send_msg("Hello world!\n");
	else
		send_msg("G'day world!\n");

	// Return 1 because, why not.
	return 1;
}

/*************************************************************************************
 * hello - sends hello world to the user! I'm doing proper function commenting so future
 *         coders might not find my code as painful.
 *
 *    Params:  param2 - not a very good parameter name - something better might be
 *                      say, msgstr or sendtext
 *
 *************************************************************************************/

void send_msg(const char *param2) {
	printf("%s", param2);
}

/*************************************************************************************
 *		Parse user input 
 *         
 *
 *************************************************************************************/

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

/*************************************************************************************
 *		Execute commands 
 *         
 *
 *************************************************************************************/

			if (strcmp(param, "list") == 0){
				//LIST COMMAND
				printf("List command entered!\n");
				//return 1;
				char filename[100];
				start = sptr+1;

				//Error if no filename
				if (*start == '\0'){
					printf("No filename specified!\n");
					return -1;
				}
				strncpy(filename, start, 100);

				//Opens file based off the filename given.
				FILE * filepoint;
				int readout;
				filepoint = fopen(filename,"r");

				//This IF statement may be redundant given the if statement above
				if(filepoint == NULL){
					perror("Error opening file!\n");
					return -1;
				}

				//Reads the file and displays contents
				while(1){
					readout = fgetc(filepoint);
					if(feof(filepoint)){
						break;
					}
					printf("%c", readout);
				}
				fclose(filepoint);
				return 1;

			} else if(strcmp(param, "create") == 0){
				//CREATE COMMAND
				printf("Create command entered!\n");
				//return 1;
				char filename[100];
				start = sptr+1;

				if (*start == '\0'){
					printf("No file name specified!\n");
					return -1;
				}
				strncpy(filename, start, 100);
				FILE * filepoint;
				filepoint = fopen(filename, ("w"));
				printf("A file with the name %s was created.", filename);
				fclose(filepoint);
				return 1;
			}
		}
	}
	return 0;
}