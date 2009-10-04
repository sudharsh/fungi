/* 
 *  main.c
 *  Author: Sudharshan "Sup3rkiddo" sudharsh@gmail.com>
 *  All Rights Reserved
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 */


#include "fungi.h"


int interpret_funge(InstructionPointer *ip_ptr, char **funge)
{
    char command = funge[ip_ptr->row][ip_ptr->col];
    
    if (command == ' ' || !isascii(command) || !command) {
        printf("Whitespace/Non character command. Processing last seen valid command %c\n", ip_ptr->last_command);
        command = ip_ptr->last_command;
    }

    printf("Processing %c\n", command);

 interpret_command:
    
	switch(command) {
    case '>': /* Move east */
        update_ip(ip_ptr, 0, 1);
        break;
    case '<': /* Move west */
        update_ip(ip_ptr, 0, -1);
        break;
    case '^': /* Move north */
        update_ip(ip_ptr, -1, 0);
        break;
    case 'v': /* Move south */
        update_ip(ip_ptr, 1, 0);
        break;
    case 'r': /* Reflect */
        ip_ptr->row = (ip_ptr->row) * -1;
        ip_ptr->col = (ip_ptr->col) * -1;
        break;
    case '@': /* End program */
        exit(1);
        break;
    default:
        if(isdigit(command)) {
            stack_push(&(ip_ptr)->stack, command);
            printf("Digit found. Pushing it to the number stack\n");
            command = ip_ptr->last_command;
            goto interpret_command; /* Refactor this. This won't work at all, when new commandsets come in */
        }
        break;
            
    }
    if (command != ' ' || !isdigit(command))
        ip_ptr->last_command = command;
    printf("-----------------\n");
}



int load_source(const char *source)
{
    InstructionPointer ip; /* Instruction Pointer */
    char **funge;
        
    ip.row = 0;
    ip.col = 0;
    ip.stack = __get_node();
    
    FILE *file_ptr = fopen(source, "r");

	if (!file_ptr) {
		fprintf(stderr, "Error: No such file %s\n", source);
		return FALSE;
	}

    /* Get the funge size in first pass and initialise the data structures accordingly */
    funge = get_funge(file_ptr, &ip);

    while (TRUE)
        interpret_funge(&ip, funge);
    
            
    /* Clean up stuff */        
	fclose(file_ptr);
    free(funge);
    return TRUE;
}

		 
int main(int argc, char **argv) 
{
    /* Use getopts? */
	if (argc > 1)
		load_source(argv[1]);
	return 0;
}
