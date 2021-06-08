#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "delivery.h"

/* The content of the fields of the delivery structure is written into the string str */
void getDeliveryStr(tDelivery delivery, int maxSize, char *str) 
{	  
    /* Build the string */	
	snprintf(str,maxSize-1,"%d %c %c %d %d", 
             (int)delivery.id, delivery.originLocation, delivery.destinationLocation, 
             (int)delivery.materialsToDeliver.id, delivery.materialsToDeliver.qtt );
}

/* The content of the string str is parsed into the fields of the delivery structure */
void getDeliveryObject(const char *str, tDelivery *delivery) {

	int aux_id, aux2_id;
 	
    /* read truck data */
    sscanf(str, "%d %c %c %d %d", 
             &aux_id, &delivery->originLocation, &delivery->destinationLocation, 
             &aux2_id, &delivery->materialsToDeliver.qtt );

    delivery->id = (tDeliveryId)aux_id;
    delivery->materialsToDeliver.id= (tMaterialId)aux2_id;
}

void deliveryCpy(tDelivery *dst, tDelivery src) {

    dst->id = src.id;
    dst->originLocation= src.originLocation;
    dst->destinationLocation= src.destinationLocation;
    dst->materialsToDeliver.id= src.materialsToDeliver.id;
    dst->materialsToDeliver.qtt= src.materialsToDeliver.qtt;
}

int deliveryCmp(tDelivery d1, tDelivery d2)
{
    int result = 0;

    if (d1.id > d2.id)
        result = 1;
    else if (d1.id < d2.id)
        result = -1;
    else 
    {
        if (d1.originLocation > d2.originLocation)
            result = 1;
        else if (d1.originLocation < d2.originLocation)
            result = -1;
        else 
        {
            if (d1.destinationLocation > d2.destinationLocation)
                result = 1;
            else if (d1.destinationLocation < d2.destinationLocation)
                result = -1;
            else 
            {
                if (d1.materialsToDeliver.id > d2.materialsToDeliver.id)
                    result = 1;
                else if (d1.materialsToDeliver.id < d2.materialsToDeliver.id)
                    result = -1;
                else 
                {
                    if (d1.materialsToDeliver.qtt > d2.materialsToDeliver.qtt)
                        result = 1;
                    else if (d1.materialsToDeliver.qtt > d2.materialsToDeliver.qtt)
                        result = -1;
                }                            
            }            
        }
    }
        
    return result;
}

void deliveriesTableInit(tDeliveryTable *deliveriesTable) {
	
	deliveriesTable->nDeliveries= 0;
}

void deliveriesTableAdd(tDeliveryTable *tabDeliveries, tDelivery delivery, tError *retVal) {

	*retVal = OK;

	/* Check if there enough space for the new delivery */
	if(tabDeliveries->nDeliveries>=MAX_DELIVERIES)
		*retVal = ERR_MEMORY;
    
	if (*retVal == OK) {
		/* Add the new delivery to the end of the table */
		deliveryCpy(&tabDeliveries->table[tabDeliveries->nDeliveries],delivery);
		tabDeliveries->nDeliveries++;
	}
}

int deliveriesTableFind(tDeliveryTable tabDeliveries, tDeliveryId id) {

	int idx = NO_DELIVERY;
	
	int i=0;
	while(i< tabDeliveries.nDeliveries && idx==NO_DELIVERY) {
		/* Check if the id is the same */
		if(id==tabDeliveries.table[i].id)  {
			idx = i;
		}
		i++;
	}
	
	return idx;
}

void deliveriesTableClean(tDeliveryTable *deliveriesTable)
{
    deliveriesTable->nDeliveries= 0;
}

void deliveriesTableSave(tDeliveryTable tabDeliveries, const char* filename, tError *retVal) {

    *retVal = OK;

	FILE *fout=NULL;
	int i;
	char str[MAX_LINE];
	
	/* Open the output file */
	if((fout=fopen(filename, "w"))==NULL) {
		*retVal = ERR_CANNOT_WRITE;
	} else {
	
        /* Save all materials to the file */
        for(i=0;i<tabDeliveries.nDeliveries;i++) {
            getDeliveryStr(tabDeliveries.table[i], MAX_LINE, str);
            fprintf(fout, "%s\n", str);
        }
            
        /* Close the file */
        fclose(fout);
	}
}

void deliveriesTableLoad(tDeliveryTable *tabDeliveries, const char* filename, tError *retVal) {
	
	*retVal = OK;

	FILE *fin=NULL;
	char line[MAX_LINE];
	tDelivery newDelivery;
	
	/* Initialize the output table */
	deliveriesTableInit(tabDeliveries);
	
	/* Open the input file */
	if((fin=fopen(filename, "r"))!=NULL) {

		/* Read all the trucks */
		while(!feof(fin) && tabDeliveries->nDeliveries<MAX_DELIVERIES) {
			/* Remove any content from the line */
			line[0] = '\0';
			/* Read one line (maximum 511 chars) and store it in "line" variable */
			fgets(line, MAX_LINE-1, fin);
			/* Ensure that the string is ended by 0*/
			line[MAX_LINE-1]='\0';
			if(strlen(line)>0) {
				/* Obtain the object */
				getDeliveryObject(line, &newDelivery);
				/* Add the new delivery to the output table */
				deliveriesTableAdd(tabDeliveries, newDelivery, retVal);		
			}
		}
		/* Close the file */
		fclose(fin);
		
	}else {
		*retVal = ERR_CANNOT_READ;
	}
}

