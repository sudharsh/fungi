/* 
 * cartographer.c
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

#include "fungi.h"


int update_ip_by_offset(InstructionPointer *ip_ptr, int dr, int dc)
{
    __debug("Moving by %d, %d\n" , dr, dc);
    __debug("Before: "); print_current_coordinates(ip_ptr);
    
    if ((ip_ptr->row == ip_ptr->funge_height) && dr != 0) {
        __debug("Fixing torus\n");
        ip_ptr->row = 0;
    }
    else
        ip_ptr->row += dr;
            
    if ((ip_ptr->col == ip_ptr->funge_width) && dc != 0) {
        __debug("Fixing torus\n");
        ip_ptr->col = 0;
    }
    else
        ip_ptr->col += dc;

    // If we have negative value, wrap it
    if (ip_ptr->row < 0) {
        __debug("Peeking my head over the other side\n");
        ip_ptr->row = ip_ptr->funge_height - abs(dr);
    }
    if (ip_ptr->col < 0) {
        __debug("Peeking my head over the other side\n");
        ip_ptr->col = ip_ptr->funge_width - abs(dc);
    }
           
    __debug("After: "); print_current_coordinates(ip_ptr);
    return TRUE;
}



void move_ip(InstructionPointer *ip_ptr, int direction)
{
    switch(direction) {
    case MOVE_WEST:
        update_ip_by_offset(ip_ptr, 0, -1);
        break;
    case MOVE_EAST:
        update_ip_by_offset(ip_ptr, 0, 1);
        break;
    case MOVE_NORTH:
        update_ip_by_offset(ip_ptr, -1, 0);
        break;
    case MOVE_SOUTH:
        update_ip_by_offset(ip_ptr, 1, 0);
        break;
    }
    ip_ptr->direction = direction;

}
