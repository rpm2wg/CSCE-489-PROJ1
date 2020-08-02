/*************************************************************************************
 * myshell - student code for Project 1 of CSCE 489 
 *
 *************************************************************************************/

#include <stdio.h>
#include "shellfuncts.h"
#include <string.h>
#include <stdbool.h>

int main() {
	
	char buffer[100];
	bool exit_yet = false;
	char exit[] = "exit";

	printf("\nSimple Shell\n\n");
	
	while(!exit_yet){

	fgets(buffer, 100, stdin);
	
	if (strcmp(exit, buffer) == 0) {
		exit_yet = true;
		}
	}
	return 0;
}


