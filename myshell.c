/*************************************************************************************
 * myshell - A very simple Linux shell project 
 * 
 * Ryan Montgomery
 * CSCE 489 - Project 1
 * Lt Col George E. Noel, Ph.D.
 * August 5, 2020
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
		
		
	printf("\nThe not-so-Simple Shell!\n\n");
	printf("Available commands:\n");
	printf("dir\n");
	printf("create <filename>\n");
	printf("update <filename> <number> <\"Your text\"> <&>\n");
	printf("list <filename>\n");
	printf("halt\n\n");
	__pid_t pid = getpid();
	printf("The parent PID is: %d\n******************************\n", pid);
	while(!exit_yet)
	 {
	 	fgets(buffer, 100, stdin);
		if (strcmp(buffer, exit_now) == 0)
			{
			printf("Goodbye!\n");
			exit_yet = true;
			}	
			parse_input(buffer);	
	 }
	return 0;
}