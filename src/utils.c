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

/* Just a lazy helper function */
void print_current_coordinates(coordinates *ip_ptr) {
    printf("%d %d\n", ip_ptr->x, ip_ptr->y);
}


int update_ip(coordinates *ip_ptr, int dx, int dy)
{
    printf("Moving by %d, %d\n" , dx, dy);
    print_current_coordinates(ip_ptr);
    if (ip_ptr->x == MAX_ROW && dx != 0)
        ip_ptr->x = dx;
    else
        ip_ptr->x += dx;
            
    if (ip_ptr->y == MAX_COLUMN && dy != 0)
        ip_ptr->y = dy;
    else
        ip_ptr->y += dy;

    // If we have negative value, wrap it
    if (ip_ptr->x < 0)
        ip_ptr->x = MAX_ROW - abs(dx);
    if (ip_ptr->y < 0)
        ip_ptr->y = MAX_COLUMN - abs(dy);
           
    print_current_coordinates(ip_ptr);
    return TRUE;
}


char** get_funge(FILE *fptr)
{
    int height = 0;
    int width = 0;
    
    int curr_width = 0; /* Width of the current active line */    
    char curr_c;
    char **funge = NULL;
    char command;

    int i;
    
    while( (curr_c = getc(fptr)) != EOF) {
        if (curr_c == '\n') {
            if (curr_width == 0)
                continue;
            width = curr_width;
            curr_width = 0;
            height++;
        }
        curr_width++;
    }
    rewind(fptr);

    printf("height: %d, width %d\n", height, width);
    funge = (char **) malloc(height * sizeof(char *));
    for(i = 0; i <= height; i++) {
        funge[i] = (char *) malloc (width * sizeof(char *));
        fgets(funge[i], width + 1, fptr);
        printf("Line %d: %s", i, funge[i]);
    }
    
    return funge;

}
