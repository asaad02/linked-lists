/**
 * @file list.h
 * @author Abdullah Saad
 * @date October 10  2020
 * @brief File containing the function prototypes of linked list
 **/

/* A node in the linked list */
struct Node
{
    void *data;         /* Data is a pointer to the data stored at this node */
    struct Node *next;  /* Next is a pointer to the next node in the list */
};


/* structure to measure the performance of the code and Algorithms in linked list.*/
struct Performance
{
    unsigned int reads;     /*  how many reads operations    */
    unsigned int writes;    /*  how many writes operations   */
    unsigned int mallocs;   /*  haw many maloocs operation   */
    unsigned int frees;     /*  how many frees operations    */
};

/* this function allocate memory for the performance struct and return the address of the the structure */
struct Performance *newPerformance();

/* Add an item at the head of the list */
void push(struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width);

/* Copy data from the head of the list into dest */ 
void readHead( struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width );

/* Remove an item from the head of the lis*/
void pop( struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width );

/* Return pointer to the pointer to the second item in a list. */
struct Node **next( struct Performance *performance, struct Node **list_ptr);
/* check if the list is empty or not */
int isEmpty( struct Performance *performance, struct Node **list_ptr );
/* This function will pop item off the list isempty */
void freeList( struct Performance *performance, struct Node **list_ptr);
/* this function using next an dreadhead to find the Node and to retrieve data from the giving position */
void readItem( struct Performance *performance, struct Node **list_ptr, unsigned int index, void *dest, unsigned int width);
/* this function will add an element to the end of the list */
void appendItem( struct Performance *performance, struct Node**list_ptr, void *src, unsigned int width);
/* This function will insert a node at the giving index */
void insertItem(struct Performance *performance, struct Node **list_ptr, unsigned int index, void *src, unsigned int width);
/* This function will use insertItem to insert data at position 0 */
void prependItem(struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width);
/* This function will remove the Node at the giving index */
void deleteItem(struct Performance *performance, struct Node **list_ptr, unsigned int index );
/* This function will retrieve elemnts from list and apply compar to the target */
int findItem( struct Performance *performance, struct Node **list_ptr, int (*compar)(const void *, const void *), void *target, unsigned int width);

