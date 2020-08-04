/*************************************************************************************
 * myshell - student code for Project 1 of CSCE 489 
 *
 *************************************************************************************/

#include <stdio.h>
#include "shellfuncts.h"
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

int main(int argv, const char *argc[]) {
	(void) argv; // Make compile warnings go away - be sure to delete this line if you use the param
	(void) argc; // Make compile warnings go away - be sure to delete this line if you use the param

	char buffer[100];
	bool exit_yet = false;
	char exit_now[] = "halt\n";
		
		
	printf("\nSimple Shell\n\n");
	__pid_t pid = getpid();
	printf("The parent PID is: %d\n", pid);
	while(!exit_yet)
	 {
	 	fgets(buffer, 100, stdin);
		parse_input(buffer);
		if (strcmp(buffer, exit_now) == 0)
			{
			printf("Goodbye!\n");
			exit_yet = true;
			}		
	 }
	return 0;
}