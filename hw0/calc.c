/*
 * Dylan Wright
 * C335
 * Hw0: implement a calculator using linked lists
 */

#include <stdio.h>

struct Node
{
  int data;
  struct Node * next;
}; //end Node

//call when q or c is entered as a command
void clearStack(struct Node * head)
{
  if (head == NULL)
  {
    return;
  } //end if
} //end clearStack

void applyOp(char op)
{

} //end applyOp

void printList(struct Node * head)
{
  while (head != NULL)
  {
    printf("%d\n", head->
  } //end while
} //end printList

int main()
{
  char c = ' ', input[100];
  int i;

  //initialize the tail element, shouldn't point to anything
  //"tail" doesn't seem right in context of this being a stack, but it seems natural because it's a linked list
  struct Node * tail = (node*)malloc(sizeof(Node));
  tail->next = NULL;

  while (c != 'q')
  {
    scanf("%s", input); //scanf %s parses word by word and automatically inserts terminating character
 
    if (isdigit(input[0]) == 0) //if character
    {
      c = input[0];

      //EOF and q both indicate end of program
      if (c == 'E' || c == 'q')      
      {

      } //end if

      //return top of stack, don't alter anything
      else if (c == 'p')
      {

      } //end else if

      //clear stack
      else if (c == 'c')
      {
        
      } //end else if

      //print everything "top to bottom"
      else if (c == 'f')
      {

      } //end else if

      //otherwise it is an operand
      else
      {
        applyOp(c);
      } //end else
    } //end if

    else
    {
      i = atoi(input);
    } //end else
  } //end while

  return 0;
}
