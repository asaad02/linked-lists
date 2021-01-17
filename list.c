/**
 * @file list.c
 * @author Abdullah Saad
 * @date october  10 2020
 * @brief File containing the function operate on linked list.
 **/

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <string.h>

/* This function allocate memory for performance structure and set function elements to zero */
struct Performance *newPerformance()
{
    // allocate memory for a performance struct 

    struct Performance *newPerformance = (struct Performance *) malloc( sizeof (struct Performance));

    //print an error message to the standard error stream and exit if the malloc function fails.
    if(newPerformance == NULL){
        fprintf(stderr,"%s","Memory allocation for structure performance has failed\n");
        exit(0);
    }
    
    // set zero to reads, writes, malloc , free 
    newPerformance -> reads = 0;
    newPerformance -> writes = 0;
    newPerformance -> mallocs = 0;
    newPerformance -> frees = 0;

    // return the address of the new function.
    return newPerformance;
}

/* This function will add an item at the head of the linked list */
void push(struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width)
{
    /* malloc a new struct Node structure */
    struct Node *newNode = (struct Node *) malloc( sizeof ( struct Node ));



    //print an error message to the standard error stream and exit if the malloc function fails.
    if(newNode == NULL){
        fprintf(stderr,"%s","Memory allocation for newNode structure has failed\n");
        exit(0);
    }


    /* allocate width bytes of data and stored in data address*/
    newNode -> data = malloc(width);


    //print an error message to the standard error stream and exit if the malloc function fails.
     if(newNode -> data == NULL){
        fprintf(stderr,"%s","Memory allocation for data in the newNode has failed\n");
        exit(0);
    }
    
    //copy width bytes of data from the parameter src to the address data in the new Node structure
    memcpy( newNode-> data, src  , width );

    

    // set the next pointer of the structure to be equal to the value pointed to by list_ptr.
    newNode -> next = *list_ptr;

    // store the address of structure in the head pointer
    *list_ptr= newNode;


    // increment mallocs at performance struct 
    performance -> mallocs++;


    // increment writes at performance struct 
    performance -> writes++;
    
}
/* This function copy the head of the list into dest */
void readHead( struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width )
{
    if(*list_ptr == NULL){
        fprintf(stderr,"%s","The lnked list is Empty \n");
        exit(0);
    }

    //copy width bytes of data from the parameter newNode data to dest
    memcpy(  dest, (*list_ptr)-> data  , width );

    //increment reads
    performance ->reads++;

}
/* This function will remove an node from the head of the list */
void pop( struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width )
{
    if(*list_ptr == NULL){
        fprintf(stderr,"%s","The linked kist is Empty in the pop function \n");
        exit(0);
    }

     //copy width bytes of data from the parameter newNode data  to dest
    memcpy(  dest, (*list_ptr)-> data , width );

    
    
     // create temperory variable to hold the node need to be deleted 
    struct Node * temp = *list_ptr;


    // update the pointer head to the next node 
    *list_ptr= (*list_ptr)->next;

   

    // free the temperory pointer that hold the node need to be removed 
    free(temp->data);
    free(temp);



    // reads and frees should be increment 
    performance ->reads++;
    performance ->frees++;


}

/* This function return pointer to the pointer to the second item in a list */
struct Node **next( struct Performance *performance, struct Node **list_ptr)
{
    // if list empty print a error message 
    if(list_ptr == NULL){
        fprintf(stderr,"%s","The linked list is Empty in **next Function  \n");
        exit(0);
    }

    performance ->reads++;


    return &((*list_ptr) -> next);
}

/* This function will return if the list is empty */
int isEmpty( struct Performance *performance, struct Node **list_ptr )
{
    // if statment if the head pointer is empty return 1
    if(*list_ptr == NULL){
        
        return (1);
    }

    // if not empty return 0 
    return (0);
    

}

/* This function will pop item off the list isempty */
void freeList( struct Performance *performance, struct Node **list_ptr)
{
    void * dest = malloc(sizeof((*list_ptr) -> data)) ;
    do // do loop 
    {
        pop(performance,list_ptr,dest,0); // calling pop function 
    } while (isEmpty(performance,list_ptr) != 1); // until list_ptr is empty 
    
}

/* this function using next an dreadhead to find the Node and to retrieve data from the giving position */
void readItem( struct Performance *performance, struct Node **list_ptr, unsigned int index, void *dest, unsigned int width)
{
    struct Node ** curruntNode = list_ptr; //create temporory pointer to hold the list_ptr
    // for loop for go though nodes 
    for (int i = 0; i < index; i++)
    {
        // store next pointer inside the current node
        curruntNode = next(performance,curruntNode); // store next pointer inside the current node 
    }

    // retreive data of the giving position by calling readHead function
    readHead(performance,curruntNode,dest,width); 
    
}

/* this function will add an element to the end of the list */
void appendItem( struct Performance *performance, struct Node**list_ptr, void *src, unsigned int width)
{
    struct Node ** curruntNode = list_ptr; //create temporory pointer to hold the list_ptr
    
    // while loop calling the next function until isempty return true 
    while (isEmpty(performance,curruntNode) != 1)
    {
        // store next pointer inside the current node
        curruntNode = next(performance,curruntNode); // store next pointer inside the current node 
    }

    // Add the item at the end of the list 
    push(performance,curruntNode,src ,width); 
}


/* This function will insert a node at the giving index */
void insertItem(struct Performance *performance, struct Node **list_ptr, unsigned int index, void *src, unsigned int width)
{
    struct Node ** curruntNode = list_ptr; //create temporory pointer to hold the list_ptr
    // for loop for go though nodes 
    for (int i = 0; i < index; i++)
    {
        // store next pointer inside the current node
        curruntNode = next(performance,curruntNode); // store next pointer inside the current node 
    }

    // insert item at the head of the list 
    push(performance,curruntNode,src,width); 
}

/* This function will use insertItem to insert data at position 0 */
void prependItem(struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width)
{
    // this function will insert data at position 0 
    insertItem(performance,list_ptr,0,src,width);
}

/* This function will remove the Node at the giving index */
void deleteItem(struct Performance *performance, struct Node **list_ptr, unsigned int index )
{
    struct Node ** curruntNode = list_ptr; //create temporory pointer to hold the list_ptr
    void * dest = malloc(sizeof((*list_ptr) -> data)) ;


    // for loop for go though nodes 
    for (int i = 0; i < index; i++)
    {
        // store next pointer inside the current node
        curruntNode = next(performance,curruntNode); // store next pointer inside the current node 
    }

    // delete a node at that index
    pop(performance,curruntNode,dest,0); 
}
/* This function will retrieve elemnts from list and apply compar to the target */
int findItem( struct Performance *performance, struct Node **list_ptr, int (*compar)(const void *, const void *), void *target, unsigned int width)
{
    //create temporory pointer to hold the list_ptr
    struct Node ** curruntNode = list_ptr; 
    // create dest to hold the value 
    void * dest = malloc(width) ;

     int i = 0;

    do 
    {
        
       
        // retrieve elements from list by calling the read head 
        readHead(performance,curruntNode,dest,width);
         
         // Apply compare function for each elemnts 
         if (compar(target,dest) == 0 ) { // if return 0 indicating a mach 
             return (i) ;
         }
        
        // starting at the first elemnt in the list abd incremented by calling the next function 
         curruntNode = next(performance,curruntNode); 
         i ++ ;
         

    } while (isEmpty(performance,curruntNode) != 1);
    
   
    free(dest);
    


    return -1 ; // if compare return non-zero indicating a mismatch 
}

