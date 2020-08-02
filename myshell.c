/*************************************************************************************
 * myshell - student code for Project 1 of CSCE 489 
 *
 *************************************************************************************/

#include <stdio.h>
#include "shellfuncts.h"
#include <string.h>
#include <stdbool.h>

int main(int argv, const char *argc[]) {
	(void) argv; // Make compile warnings go away - be sure to delete this line if you use the param
	(void) argc; // Make compile warnings go away - be sure to delete this line if you use the param

	char buffer[100];
	bool exit_yet = false;
	char exit_now[] = "exit\n";
	
		
	printf("\nSimple Shell\n\n");
	while(!exit_yet)
	 {

	 	fgets(buffer, 100, stdin);
		

	 	if (strcmp(exit_now, buffer) == 0) 
		{
			exit_yet = true;
		}
		
		
	 }
	return 0;
}