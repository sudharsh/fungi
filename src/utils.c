/* 
 * utils.c
 * Written by Sudharshan "Sup3rkiddo" S <sudharsh@gmail.com>
 * All Rights Reserved
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */ 

#include "main.h"
#include <string.h>

/* Just a lazy helper function */
void print_current_coordinates(InstructionPointer *ip_ptr) {
    printf("%d %d\n", ip_ptr->row, ip_ptr->col);
}


/* Taken from Linux code */
static char *strstrip(char *s)
{
        size_t size;
        char *end;

        size = strlen(s);

        if (!size)
                return s;

        end = s + size - 1;
        while (end >= s && isspace(*end))
                end--;
        *(end + 1) = '\0';

        while (*s && isspace(*s))
                s++;

        return s;
}



int update_ip(InstructionPointer *ip_ptr, int dr, int dc)
{
    printf("Moving by %d, %d\n" , dr, dc);
    print_current_coordinates(ip_ptr);
    if (ip_ptr->row == ip_ptr->funge_height && dr != 0)
        ip_ptr->row = dr;
    else
        ip_ptr->row += dr;
            
    if (ip_ptr->col == ip_ptr->funge_width && dc != 0)
        ip_ptr->col = dc;
    else
        ip_ptr->col += dc;

    // If we have negative value, wrap it
    if (ip_ptr->row < 0) {
        printf("Peeking my head over the other vertical side\n");
        ip_ptr->row = ip_ptr->funge_height - abs(dr);
    }
    if (ip_ptr->col < 0) {
        printf("Peeking my head over the other side\n");
        ip_ptr->col = ip_ptr->funge_width - abs(dc);
    }
           
    print_current_coordinates(ip_ptr);
    return TRUE;
}


char** get_funge(FILE *fptr, InstructionPointer *ip_ptr)
{
    int height = 0;
    int width = 0;
    
    int curr_width = 0; /* Width of the current active line */    
    char curr_c;
    char **funge;
    char command;

    int i;
    
    while( (curr_c = getc(fptr)) != EOF) {
        if (curr_c == '\n') {
            printf("%d\n", curr_width);
            if (curr_width == 0) {
                printf("Empty new line\n");
                continue;
            }
            if (width < curr_width)
                width = curr_width - 1;
            curr_width = 0;
            height++;
        }
        curr_width++;
    }
    rewind(fptr);

    printf("height: %d, width %d\n", height, width);
    ip_ptr->funge_height = height;
    ip_ptr->funge_width = width;
    
    funge = (char **) malloc(height * sizeof(char *));
    for(i = 0; i <= height; i++) {
        funge[i] = (char *) malloc (width * sizeof(char *));
        fgets(strstrip(funge[i]), width + 2, fptr);
        printf("Line %d: %s\n", i, strstrip(funge[i]));
    }
    
    return funge;

}
