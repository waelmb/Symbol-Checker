/*
* File name: wmobei2proj2.c
* Project 2
* CS211, Spring 2019
* Author: Wael Abdulelah F Mobeirek (wmobei2)
* Description: Symbol checker program using a C struct that includes a dynamic array
***************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //for the boolean data type

bool debugMode = false; //debugMode gobal variable
   
// Defines a struct named Stack
typedef struct StackStruct
{
 char*    darr;  /* pointer to dynamic array  */
 int     allocated;  /* amount of space allocated */
 int     inUse; /* top of stack indicator 
		   - counts how many values are on the stack   */
} Stack;

// Initializes the stack
void init (Stack* s)
{
 s->allocated= 2;
 s->darr = (char*) malloc ( sizeof (char) * s->allocated);
 s->inUse  = 0;
}

// Adds a val into the stack
void push (Stack* s, char c)
{
  /* check if enough space currently on stack and grow if needed */
  if(s->inUse == s->allocated) {
    char *temp = s->darr;
    s->allocated = s->allocated + 2;	
    s->darr = (char*) malloc ( sizeof (char) * s->allocated); 
    int i;
    for (i = 0 ; i < s->inUse; i++) {
    	s->darr[i] = temp[i];
	} 	
    free (temp);
    if(debugMode) {
      printf("The stack has grown from %d elements to %d elements.\n", s->allocated-2, s->allocated);
      printf("%d elements have been copied from the old array to the new array.\n", i);                                          
    }
 }
 
  /* add val onto stack */
  s->darr[s->inUse] = c;
  if(debugMode) {              
   printf("%c has been pushed to the stack.\n", c);                          
  }
  s->inUse = s->inUse + 1;
  
}

// A function to check if a stack is empty or not
bool isEmpty (Stack* s)
{
  if ( s->inUse == 0)
    return true;
  else
    return false;
}

// A function that returns what's at the top of the stack
char top (Stack* s)
{
  return (  s->darr[s->inUse-1] );
}

// A function that deletes the item that's at the top of a stack
/* QUESTION 9 */
void pop (Stack* s)
{
  if(debugMode) {              
   printf("%c has been poped off the stack.\n", s->darr[s->inUse-1]);                          
  }
  s->inUse = s->inUse - 1;
}

// A function that deletes all items in a stack
void clear (Stack* s)
{
  free(s->darr);
  s->allocated= 2;
  s->inUse = 0;
}


// A function that checks if a char is a proper opening symbol or not. 
bool isOpeningSymbol(char c) {
     if(c == '{' ||
        c == '(' || 
        c == '[' || 
        c == '<' ) {
          return true;      
     }
     else {
          return false;
     }       
}

// A function that checks if a char is a proper closing symbol or not. 
bool isClosingSymbol(char c) {
     if(c == '}' || 
        c == ')' ||
        c == ']' ||
        c == '>') {
          return true;      
     }
     else {
          return false;
     }       
}

// A function that checks if two symbols are matching or not. 
bool areMatchingSymbols(char a, char b) {
     if(a == '{' && b == '}') {
          return true;      
     }
     else if(a == '(' && b == ')') {
          return true;      
     }
     else if(a == '[' && b == ']') {
          return true;      
     }
     else if(a == '<' && b == '>') {
          return true;      
     } 
     else {
          return false;
     }       
}

// A function that prints what's in the stack
void printStack(Stack* s) {
 int i;
 for(i = 0; i < s->inUse; i++) {
    printf("index: %d symbol: %c\n", i, s->darr[i]);        
 }    
}

// A function that returns the opposing matching symbol
char opposingSymbol(char c){
     if(c == '(') {
          return ')';
     }
     else if(c == '{') {
          return '}';
     }
     else if(c == '[') {
          return ']';
     }
     else if(c == '<') {
          return '>';
     }
     else if(c == ')') {
          return '(';
     }
     else if(c == '}') {
          return '{';
     }
     else if(c == ']') {
          return '[';
     }
     else if(c == '>') {
          return '<';
     }
     else {
          return '\0';
     }
}
// A function that reports error 1 "expecting"
void reportErrorExpecting(char input[],int index, char c) {
     printf("%s\n", input);
     int i;
     for(i = 0; i < index; i++) {
           printf(" ");
     }
     printf("^ expecting %c\n", opposingSymbol(c));
}

// A function that reports error 2 and 3 "missing"
void reportErrorMissing(char input[],int index, char c) {
     printf("%s\n", input);
     int i;
     for(i = 0; i < index; i++) {
           printf(" ");
     }
     printf("^ missing %c\n", opposingSymbol(c));
}


int main (int argc, char** argv)
{
 char input[301];

 /* set up an infinite loop */
 while (1)
 {
   /* get line of input from standard input */
   printf ("\nEnter input to check or q to quit\n");
   fgets(input, 300, stdin);

   /* remove the newline character from the input */
   int inputCounter = 0;
   while (input[inputCounter] != '\n' && input[inputCounter] != '\0')
   {
      inputCounter++;
   }
   input[inputCounter] = '\0';

   /* check if user enter q or Q to quit program */
   if ( (strcmp (input, "q") == 0) || (strcmp (input, "Q") == 0) )
     break;


   /* run the algorithm to determine is input is balanced */
   //Setup debugMode
   int i;
   for(i = 0; i < argc; i++) {
         if(strcmp(argv[i], "-d") == 0) {
                            debugMode = true;
                            printf ("Debug Mode is ON\n");
         }
    }

   //Initialize the isBalanced variable 
   bool isBalanced = true;
   
   //Initialize the stack
   Stack s;
   init (&s); 
   // scan the input
   int j;
   for(j = 0; j < inputCounter+1; j++) {
          //if an openning symbol is found
          if(isOpeningSymbol(input[j])) {
            //push it in the stack
            push(&s, input[j]); 
          }
          
          //if a closing symbol is found
          if(isClosingSymbol(input[j])) {
              //check if the stack isn't empty
              if(!isEmpty(&s)) {
                 //check if the last item in the stack is matching to the closing symbol
                 if(areMatchingSymbols(top(&s), input[j])) {
                    //report a balanced statement
				    //pop the stack
                    pop(&s);                                                  
                 }
                 //if it doesn't match
                 else {
                    //report error 1  
                    reportErrorExpecting(input, j, top(&s));
                    isBalanced = false;
                    //break out of the loop
                    break; 
                 }
                      
              }
              //if there isn't an openning symbol (stack is empty)
              else {
                   //report error 2
                   reportErrorMissing(input, j, input[j]);
                   isBalanced = false;
                   //break out of the loop
                    break;
              }                             
          }
    }
    //The end of the input has been reached
    
        //check if the stack is not empty    
        if(!isEmpty(&s) && isBalanced) {
                //report error 3
                reportErrorMissing(input, j, top(&s));
                isBalanced = false;
        }        
        else {
             //stack is empty
             //report a balanced statement if so
             if(isBalanced) {
                      printf("%s\n", input);      
                      printf ("Expression is balanced\n");
             }  
        }
    //make the stack empty
    clear(&s);
 }

 printf ("\nGoodbye\n");
 return 0;
}
