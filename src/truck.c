#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "truck.h"

/* The content of the fields of the truck structure is written into the string str */
void getTruckStr(tTruck truck, int maxSize, char *str) 
{	
    /* Build the string */	
	snprintf(str,maxSize-1,"%d %s %s %d %d %d %.2f %d %.2f %.2f %.2f", 
             (int)truck.id, truck.brand, truck.model, truck.year, 
			 (int)truck.truckType, truck.category, 
			 truck.capacity, (int)truck.international,
			 truck.weight, truck.gauge, truck.maxSpeed);
}

/* The content of the string str is parsed into the fields of the truck structure */
void getTruckObject(const char *str, tTruck *truck) {

	int aux_id, aux_truck_type, aux_international;
 	
    /* read truck data */
    sscanf(str, "%d %s %s %d %d %d %f %d %f %f %f", 
             &aux_id, truck->brand, truck->model, &truck->year, &aux_truck_type, 
			 &truck->category, &truck->capacity, &aux_international,
			 &truck->weight, &truck->gauge, &truck->maxSpeed);

    truck->id = (tTruckId)aux_id;
    truck->truckType = (tTruckType)aux_truck_type;
    if (aux_international == 0)
        truck->international = false;
    else
        truck->international = true;
}

/* The content of the fields of the loaded truck structure is written into the string str */
void getLoadedTruckStr(tLoadedTruck loadedTruck, int maxSize, char *str)
{
    /* Build the string */	
	snprintf(str,maxSize-1,"%d %d %d", 
             (int)loadedTruck.id, (int)loadedTruck.load.id, loadedTruck.load.qtt);
}

/* The content of the string str is parsed into the fields of the loaded truck structure */
void getLoadedTruckObject(const char *str, tLoadedTruck *loadedTruck) 
{
	int aux_truck_id, aux_material_id;

    /* read truck data */
    sscanf(str, "%d %d %d", 
             &aux_truck_id, &aux_material_id, &(loadedTruck->load.qtt));

    loadedTruck->id = (tTruckId)aux_truck_id;
    loadedTruck->load.id = (tMaterialId)aux_material_id;
}

void loadedTruckCpy(tLoadedTruck *dst, tLoadedTruck src)
{
    dst->id= src.id;
    dst->load.id= src.load.id;
    dst->load.qtt= src.load.qtt;
}

void loadedTruckInit(tLoadedTruck *t)
{
	t->id= NO_TRUCK;
	t->load.id= NO_MATERIAL;
	t->load.qtt= 0;
}

int loadedTruckCmp(tLoadedTruck d1, tLoadedTruck d2)
{
    int result= 0;

    if (d1.id > d2.id)
        result= 1;
    else if (d1.id < d2.id)
        result= -1;
    else {
        if (d1.load.id > d2.load.id)
            result= 1;
        else if (d1.load.id < d2.load.id)
            result= -1;
        else {
            if (d1.load.qtt > d2.load.qtt)
                result= 1;
            else if (d1.load.qtt < d2.load.qtt)
                result= -1;
        }
    }
    
    return result;
}

void truckCpy(tTruck *dst, tTruck src) {

    dst->id = src.id;
    strcpy(dst->brand,src.brand);
	strcpy(dst->model,src.model);
	dst->year = src.year;
	dst->truckType = src.truckType;
	dst->category = src.category;
	dst->capacity = src.capacity;
	dst->international = src.international;
	dst->weight = src.weight;
	dst->gauge = src.gauge;
	dst->maxSpeed = src.maxSpeed;
}

int truckCmp(tTruck d1, tTruck d2)
{
    int result = 0;
    
    if ( strcmp(d1.brand,d2.brand)>0 )
		result = 1;
	else if ( strcmp(d1.brand,d2.brand)<0 )
		result = -1;
	else {
		if ( strcmp(d1.model,d2.model)>0 )
			result = 1;
		else if ( strcmp(d1.model,d2.model)<0 )
			result = -1;
		else {
			if (d1.year > d2.year) 
				result = 1;
			else if (d1.year < d2.year)
				result = -1;
			else{
				if (d1.id > d2.id)
					result = 1;
				else if (d1.id < d2.id)
					result = -1;
				else{
					if (d1.truckType > d2.truckType)
						result = 1;
					else if (d1.truckType < d2.truckType)
						result = -1;
					else{
						if (d1.category > d2.category)
							result = 1;
						else if (d1.category < d2.category)
							result = -1;
						else{
							if (d1.capacity > d2.capacity)
								result = 1;
							else if (d1.capacity < d2.capacity)
								result = -1;
							else{
								if (d1.international > d2.international)
									result = 1;
								else if (d1.international < d2.international)
									result = -1;
								else{
									if (d1.weight > d2.weight)
										result = 1;
									else if (d1.weight < d2.weight)
										result = -1;
									else{
										if (d1.gauge > d2.gauge)
											result = 1;
										else if (d1.gauge < d2.gauge)
											result = -1;
										else{
											if (d1.maxSpeed > d2.maxSpeed)
												result = 1;
											else if (d1.maxSpeed < d2.maxSpeed)
												result = -1;
										}
									}
								}
							}
						}
					}
				}
			}
		}
    }
    
    return result;
}

void trucksTableInit(tTruckTable *trucksTable) {
	
	trucksTable->nTrucks= 0;
}

void trucksTableAdd(tTruckTable *tabTrucks, tTruck truck, tError *retVal) {

	*retVal = OK;

	/* Check if there enough space for the new truck */
	if(tabTrucks->nTrucks>=MAX_TRUCKS)
		*retVal = ERR_MEMORY;
		

	if (*retVal == OK) {
		/* Add the new truck to the end of the table */
		truckCpy(&tabTrucks->table[tabTrucks->nTrucks],truck);
		tabTrucks->nTrucks++;
	}
	
}

int trucksTableFind(tTruckTable tabTrucks, tTruckId id) {

	int idx = NO_TRUCK;
	
	int i=0;
	while(i< tabTrucks.nTrucks && idx==NO_TRUCK) {
		/* Check if the id is the same */
		if(id==tabTrucks.table[i].id)  {
			idx = i;
		}
		i++;
	}
	
	return idx;
}

bool trucksTableEmpty(tTruckTable tabTrucks)
{
    return tabTrucks.nTrucks==0;
}

tTruck trucksTableGet(tTruckTable tabTrucks, tTruckId id)
{
    tTruck truck;
    truck.id= NO_TRUCK;
	int i=0;

	while(i< tabTrucks.nTrucks && truck.id==NO_TRUCK) {
		/* Check if the id is the same */
		if(id==tabTrucks.table[i].id)  {
			truckCpy(&truck,tabTrucks.table[i]);
		}
		i++;
	}

	return truck;    
}

void trucksTableSave(tTruckTable tabTrucks, const char* filename, tError *retVal) {

    *retVal = OK;

	FILE *fout=NULL;
	int i;
	char str[MAX_LINE];
	
	/* Open the output file */
	if((fout=fopen(filename, "w"))==NULL) {
		*retVal = ERR_CANNOT_WRITE;
	} else {
	
        /* Save all materials to the file */
        for(i=0;i<tabTrucks.nTrucks;i++) {
            getTruckStr(tabTrucks.table[i], MAX_LINE, str);
            fprintf(fout, "%s\n", str);
        }
            
        /* Close the file */
        fclose(fout);
	}
}

void trucksTableLoad(tTruckTable *tabTrucks, const char* filename, tError *retVal) {
	
	*retVal = OK;

	FILE *fin=NULL;
	char line[MAX_LINE];
	tTruck newTruck;
	
	/* Initialize the output table */
	trucksTableInit(tabTrucks);
	
	/* Open the input file */
	if((fin=fopen(filename, "r"))!=NULL) {

		/* Read all the trucks */
		while(!feof(fin) && tabTrucks->nTrucks<MAX_TRUCKS) {
			/* Remove any content from the line */
			line[0] = '\0';
			/* Read one line (maximum 511 chars) and store it in "line" variable */
			fgets(line, MAX_LINE-1, fin);
			/* Ensure that the string is ended by 0*/
			line[MAX_LINE-1]='\0';
			if(strlen(line)>0) {
				/* Obtain the object */
				getTruckObject(line, &newTruck);
				/* Add the new truck to the output table */
				trucksTableAdd(tabTrucks, newTruck, retVal);
			}
		}
		/* Close the file */
		fclose(fin);
		
	}else {
		*retVal = ERR_CANNOT_READ;
	}
}

void trucksTableFilterByTruckType(tTruckTable tabTrucks, tTruckType truckType, tTruckTable *result) {

	tError retVal;
	int i;
	trucksTableInit(result);
	for(i=0;i<tabTrucks.nTrucks;i++) {
		if (truckType == tabTrucks.table[i].truckType){
			trucksTableAdd(result, tabTrucks.table[i],&retVal);
		/* retVal will always be OK as the result table will be smaller than tabTrucks which cannot have more than MAX_TRUCKS*/
		}
	}

}

void trucksTableGetTrucksInternational(tTruckTable tabTrucks, tTruckTable *result) {

	tError retVal;
	int i;
	trucksTableInit(result);
	for(i=0;i<tabTrucks.nTrucks;i++) {
		if (tabTrucks.table[i].international){
			trucksTableAdd(result, tabTrucks.table[i],&retVal);
		/* retVal will always be OK as the result table will be smaller than tabTrucks which cannot have more than MAX_TRUCKS*/
		}
	}

}

float truckTableGetAverageCapacityByTruckType(tTruckTable tabTruck, tTruckType truckType) {

	float avgCapacity = 0.0;

	int numTruckProp=0, i;
	float sumCapacity = 0.0;
	
	for(i=0;i<tabTruck.nTrucks;i++) {
		if (tabTruck.table[i].truckType==truckType){
			sumCapacity+= (tabTruck.table[i].capacity * tabTruck.table[i].category);			
			numTruckProp++;
		}
	}
	if (numTruckProp>0)
		avgCapacity = sumCapacity / (float)numTruckProp;

	
	return avgCapacity;
}

float truckTableGetMaxTruckSpeed(tTruckTable tabTruck){

	float maxSpeed = 0.0;
	
	int i;
	
	for(i=0;i<tabTruck.nTrucks;i++) {
		if (tabTruck.table[i].maxSpeed > maxSpeed){
			maxSpeed = tabTruck.table[i].maxSpeed;
		}
	}

	return maxSpeed;
}
