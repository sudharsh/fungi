/* 
 * utils.h
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

#include <stdio.h>
#include <stdlib.h>
#include <error.h>

#include <config.h>

/* The (x,y) coordinates on a 2D plane */
typedef struct _coordinates {
    int x;
    int y;
} coordinates;


/* A helper function */
void print_current_coordinates(coordinates *ip);

/* Update the given instruction pointer given a delta */
int update_ip(coordinates *ip_ptr, int dx, int dy);

/* Read the source file and initialise funge space */
char** get_funge(FILE *fptr);
