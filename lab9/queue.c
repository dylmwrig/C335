/* queue.c --- 
 * 
 * Filename: queue.c
 * Description: 
 * Author: Bryce Himebaugh
 * Maintainer: 
 * Created: Thu Feb  7 19:49:26 2013 (-0500)
 * Version: 
 * Last-Updated: 
 *           By: 
 *     Update #: 0
 * URL: 
 * Doc URL: 
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change Log:
 * 
 * 
 */

/* This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth
 * Floor, Boston, MA 02110-1301, USA.
 */

/* Code: */

#include "queue.h"

//initialization for queue
//tail represents the final index
//head represents the first
void init_queue(queue_t *buf) {
  buf->head = 0;
  buf->tail = 0;
  int i;
  for (i = 0; i < QUEUE_SIZE; i++){
    buf->buffer[i] = 0;
  } //end for
} //end init_queue

//add int to the buffer
//return 1 if successful
//return 0 if not, this means that there is not enough room in the buffer
int enqueue (queue_t *buf, int data) {
  if (buf->tail == 32) {
    return 0;
  } //end if

  else {
    buf->buffer[buf->tail] = data;
    buf->tail++;
    return 1;
  } //end else
} //end enqueue

//remove a character from the buffer
//return 1 if successful
//return 0 if not, this means that the buffer is empty
int dequeue (queue_t *buf) {
  if (buf->tail == 0){
    return 0;
  } //end if 

  //FIFO so remove the first element and shift everything to the left
  else{
    int data = buf->buffer[0];

    int i;
    for (i = 0; i < (QUEUE_SIZE - 1); i++){ 
      buf->buffer[i] = buf->buffer[i + 1];
    } //end for  

    buf->tail--;
    return data;
  } //end else
} //end dequeue

//return 1 if the buffer is empty
//return 0 if not
int queue_empty(queue_t *buf) {
  return (buf->tail == 0);
} //end queue_empty

/* queue.c ends here */
