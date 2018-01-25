/*
 * Dylan Wright
 * C335
 * Hw0: implement a calculator using linked lists
 */

#include <stdio.h>

//node for linked list
typedef struct Node
{
  int data;
  struct Node * next;
} Node; //end Node

//two methods for the linked list
//return new pointer to current node
//newN is the node being created
//its made outside of the function because its a pointer
//and if I initialized it inside of this function, it would point to nothing
//I guess this doesn't look much like a push function anymore but this is how I decided to do it
//
//next is the node this will point to (tail node is initialized to NULL so no need to check if this is the first node)
//i is data that new node is to be initialized with
void push(Node * newN, Node * next, int i)
{
  newN->data = i;
  newN->next = next;
} //end push

//delete the "head" node and return its value
int pop(Node ** n)
{
  Node * curr = *n;
  if (curr == NULL)
  {
    return;
  } //end if

  else
  {
    int rtn = curr->data;
    Node * old = curr;
    *n = curr->next;
    free(old); 
  
    return rtn;
  } //end eles
} //end pop

//call when q or c is entered as a command
void clearStack(Node ** n)
{
  Node * curr = *n;
  while (curr != NULL) //pop till you drop
  {
    pop(n);
    curr = *n;
  } //end while
} //end clearStack

//apply operator to the first two elements in the list
//return the value for the node which will be pushed after the operation is complete
int applyOp(Node ** n, char op)
{
  Node * curr = *n;
  if (curr == NULL || curr->next == NULL)
  {
    printf("Not enough operands!\n");
  } //end if

  else
  {
    int rhs = pop(n);
    int lhs = pop(n);

    if (op == '+')
    {
      return (lhs + rhs);
    } //end if

    else if (op == '-')
    {
      return (lhs - rhs);
    } //end else if

    else if (op == '*')
    {
      return (lhs * rhs);
    } //end else if

    else if (rhs != 0)
    {
      return (lhs / rhs);
    } //end else if
  } //end else
} //end applyOp

void printList(Node * n)
{
  //kind of a redundant check
  //but I'm keeping it in for error handling
  if (n == NULL)
  {
    printf("Nothing to print!\n");
  } //end if

  while (n != NULL)
  {
    printf("%d\n", n->data);
    n = n->next;
  } //end while
} //end printList

int main()
{
  char c = ' ', input[100];
  int i;

  //initialize the tail element to be null
  //"tail" doesn't seem right in context of this being a stack, but it seems natural because it's a linked list
  Node * n = NULL;

  while (c != 'q' && c!= 'E')
  {
    scanf("%s", input); //scanf %s parses word by word and automatically inserts terminating character
 
    if (isdigit(input[0]) == 0) //if character
    {
      c = input[0];

      //return top of stack, don't alter anything
      if (c == 'p')
      {
        if (n != NULL)
        {
          printf("%d\n", n->data);
        } //end if

        else
        {
          printf("Nothing to print!\n");
        } //end else
      } //end else if

      //clear stack
      else if (c == 'c')
      {
        Node ** p = &n;
        clearStack(p);
      } //end else if

      //print everything "top to bottom"
      else if (c == 'f')
      {
        printList(n);
      } //end else if

      //otherwise it is an operator
      else
      {
        Node * newN = (Node*)malloc(sizeof(Node));
        if (newN)
        {
          Node ** p = &n;
          i = applyOp(p, c);
          push(newN, n, i);
          n = newN;
        } //end if

        else
        {
          printf("Error creating node");
        } //end else
      } //end else
    } //end if

    else
    {
      i = atoi(input);
  
      Node * newN = (Node*)malloc(sizeof(Node));
      if (newN)
      {      
        push(newN, n, i);
        n = newN;
      } //end if
  
      else
      {
        printf("Error creating node");
      } //end else
    } //end else
  } //end while

  //delete stack when program ends
  Node ** p = &n;
  clearStack(p);

  return 0;
}
