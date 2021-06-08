#include "data.h"

/* Creates the stack */
void truckStackCreate(tTruckStack *s);

/* Push an element on the top of the stack */
void truckStackPush(tTruckStack *s, tLoadedTruck e);

/* Pops an element from the top of the stack */
void truckStackPop(tTruckStack *s);

/* Returns the element on top of the stack */
tLoadedTruck truckStackTop(tTruckStack s);

/* Says if the stack is empty */
bool truckStackEmpty(tTruckStack s);

/* Says if the stack is full */
bool truckStackFull(tTruckStack s);

/* Inverts a stack (puts bottom on top and top on bottom) */
void truckStackInvert(tTruckStack *s);

/* Cleans a stack (pops all elements) */
void truckStackClean(tTruckStack *s);

/* Returns the size (i.e. the number of elements) of the stack */
int truckStackSize(tTruckStack s);

/* Says if the given loaded truck is in the stack (on top or in any other position) */
bool truckStackContains(tTruckStack s, tLoadedTruck e);

/* Saves the stack on file */
void truckStackSave(tTruckStack  stack, const char* filename, tError *retVal);

/* Loads the stack from file */
void truckStackLoad(tTruckStack *stack, const char* filename, tError *retVal);

/* Gets the stack as a textual representation (string) */
void getStackStr( tTruckStack stack, int maxSize, char *str);

/* Gets the stack object out of its textual representation (string) */
void getStackObject(const char *str, tTruckStack *stack);
