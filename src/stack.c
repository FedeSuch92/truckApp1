#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "truck.h"

void truckStackCreate(tTruckStack *s) 
{
/*************** PR2 EX1A *****************/
    s->nElem=0;
/******************************************/
}

void truckStackPush(tTruckStack *s, tLoadedTruck t)
{
/*************** PR2 EX1B *****************/
    if (s->nElem < MAX_TRUCKS_IN_STACK) {
        loadedTruckCpy(&s->table[s->nElem], t);
        s->nElem++;
    }
/******************************************/
}

tLoadedTruck truckStackTop(tTruckStack s)
{
    tLoadedTruck t;
    
	loadedTruckInit(&t);
/*************** PR2 EX1C *****************/
    if (s.nElem > 0) {
        loadedTruckCpy(&t, s.table[s.nElem - 1]);
    }
/******************************************/
    return t;
}

void truckStackPop(tTruckStack *s)
{
/*************** PR2 EX1D *****************/
    if (s->nElem > 0) {
        s->nElem--;
    }
/******************************************/  
}

bool truckStackEmpty(tTruckStack s)
{
    bool result= true;
/*************** PR2 EX1E *****************/
    if (s.nElem > 0) {
        result = false;
    }
/******************************************/
    return result;
}

bool truckStackFull(tTruckStack s)
{
    bool result= true;
/*************** PR2 EX1F *****************/
    if (s.nElem <  MAX_TRUCKS_IN_STACK) {
        result = false;
    }
 
/******************************************/
    return result;
}

void truckStackInvert(tTruckStack *stack)
{
/*************** PR2 EX1G *****************/
    tTruckStack temp;
    tLoadedTruck t;
    int i;
    truckStackCreate(&temp);
    while (!truckStackEmpty(*stack)) {
        t = truckStackTop(*stack);
        truckStackPop(stack);
        truckStackPush(&temp, t);
    }
    for (i=0; i < temp.nElem; i++) {
        truckStackPush(stack, temp.table[i]);
    }
/******************************************/
}

void truckStackClean(tTruckStack *s)
{
    s->nElem= 0;
}

int truckStackSize(tTruckStack s)
{
    return s.nElem;
}

bool truckStackContains(tTruckStack s, tLoadedTruck e)
{
    bool found;
    int i;

    i= 0;
    found= false;
    while (i < s.nElem && !found) {
        found= (loadedTruckCmp(s.table[i],e) == 0);
        i++;
    }
    
    return found;
}

void truckStackSave(tTruckStack stack, const char* filename, tError *retVal)
{
/*************** PR2 EX1H *****************/
    *retVal = OK;

	FILE *fout=NULL;
	char str[MAX_LINE];
    tLoadedTruck loadedTruck;
    
	/* invert to allow writting from bottom to top*/
    truckStackInvert(&stack);
    
	/* Open the output file */
	if((fout=fopen(filename, "w"))==NULL) {
		*retVal = ERR_CANNOT_WRITE;
	} else {
	
        /* Save all materials to the file */
        while (!truckStackEmpty(stack)) {
            loadedTruck = truckStackTop(stack);
            
            /*Write it as a string*/
            snprintf(str, MAX_LINE, "%d %d %d", (int)loadedTruck.id, (int)loadedTruck.load.id, 
                        loadedTruck.load.qtt);
            fprintf(fout, "%s\n", str);
            
            truckStackPop(&stack);
        }
        /* Close the file */
        fclose(fout);
	}
/******************************************/
}

void truckStackLoad(tTruckStack *stack, const char* filename, tError *retVal)
{
/*************** PR2 EX1I *****************/
    *retVal = OK;

	FILE *fin=NULL;
	char line[MAX_LINE];
	int aux_truck_id, aux_material_id;
    tLoadedTruck loadedTruck;
	
	/* Open the input file */
	if((fin=fopen(filename, "r"))!=NULL) {

		/* Read all the loaded trucks */
		while(!feof(fin) && !truckStackFull(*stack)) {
			/* Remove any content from the line */
			line[0] = '\0';
			/* Read one line (maximum 511 chars) and store it in "line" variable */
			fgets(line, MAX_LINE-1, fin);
			/* Ensure that the string is ended by 0*/
			line[MAX_LINE-1]='\0';
			if(strlen(line)>0) {
				/* Obtain the object */
				sscanf(line, "%d %d %d", &aux_truck_id, &aux_material_id, &(loadedTruck.load.qtt));
                loadedTruck.id = (tTruckId)(aux_truck_id);
                loadedTruck.load.id = (tMaterialId)(aux_material_id);
                
				/* push it on the top of the stack*/
				truckStackPush(stack, loadedTruck);
			}
		}
		/* Close the file */
		fclose(fin);
		
	}else {
		*retVal = ERR_CANNOT_READ;
	}
/******************************************/
}

/* The content of the fields of the stack structure is written into the string str */
void getStackStr( tTruckStack stack, int maxSize, char *str) {

    int length;
	tLoadedTruck loadedTruck;
    char tempStr[MAX_LINE];    
    
    /* invert to allow writting from bottom to top */
    truckStackInvert(&stack);

    /* write the size of the stack */
    length= snprintf(str, maxSize-1, "%d", truckStackSize(stack));
    
    while(!truckStackEmpty(stack))
    {
        /* copy str into an auxiliar copy of it */
        strcpy(tempStr,str);

        /* get the top of the stack */
        loadedTruck = truckStackTop(stack);
        
        /* write it as a string */
        length= snprintf(str, maxSize-1, "%s %d %d %d", tempStr, 
                loadedTruck.id, loadedTruck.load.id, loadedTruck.load.qtt);
        if (length>0) 
            str[length]='\0';
            
        /* pop the top element to allow writting of next element */
        truckStackPop(&stack);
    }
}

/* The content of the string str is parsed into the fields of the stack structure */
void getStackObject(const char *str, tTruckStack *stack) {

	int i, size, aux_truck_id, aux_material_id;
    char tempStr[MAX_LINE];   
    char nextStr[MAX_LINE];   
	tLoadedTruck newTruck;

    /* read stack size */
    sscanf(str, "%d %[^\n]s", &size, tempStr); 
    
    /* Initialize the stack */
    truckStackCreate(stack);
        
    for (i= 0; i< size; i++)
    {
        /* read the loaded truck as a string*/
        sscanf(tempStr, "%d %d %d %[^\n]s", &aux_truck_id, &aux_material_id, &(newTruck.load.qtt), nextStr); 
        newTruck.id= (tTruckId)(aux_truck_id);
        newTruck.load.id= (tMaterialId)(aux_material_id);
        
        /* push it on the top of the stack */
        truckStackPush( stack, newTruck );
     
        /* prepare next iteration */
        strcpy(tempStr,nextStr);   
    }
}
