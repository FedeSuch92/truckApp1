#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "location.h"
#include "stack.h"

void getWareHouseStr(tWareHouse wh, int maxSize, char *str)
{
    int i;
    char tempStr[MAX_LINE];    

    /* Build the string */	
	snprintf(str,maxSize-1,"%d", wh.nMaterials );
        
    for (i= 0; i<wh.nMaterials; i++)
    {
        /* copy str into an auxiliar copy of it */
        strcpy(tempStr,str);
        
        /* write it as a string */
        snprintf(str, maxSize-1, "%s %d %d", tempStr, 
                wh.stock[i].id, wh.stock[i].qtt);
    }
}

void getWareHouseObject(const char *str, tWareHouse *wh)
{
	int i, aux_material_id, aux_qtt;
    char tempStr[MAX_LINE];   
    char nextStr[MAX_LINE];   

    /* read stack size */
    sscanf(str, "%d %[^\n]s", &wh->nMaterials, tempStr); 
        
    for (i= 0; i< wh->nMaterials; i++)
    {
        /* read the loaded truck as a string*/
        sscanf(tempStr, "%d %d %[^\n]s", &aux_material_id, &aux_qtt, nextStr); 
        wh->stock[i].id= (tMaterialId)aux_material_id;
        wh->stock[i].qtt= aux_qtt;
     
        /* prepare next iteration */
        strcpy(tempStr,nextStr);   
    }
}

void locationLoad(tLocation *tabLocations, const char* filename, tError *retVal)
{
	*retVal = OK;

	FILE *fin=NULL;
	char line[MAX_LINE];
		
	/* Open the input file */
	if((fin=fopen(filename, "r"))!=NULL) {

        /* read location id */
        line[0] = '\0';
        fgets(line, MAX_LINE-1, fin);
        line[MAX_LINE-1]='\0';
        if(strlen(line)>0)
           tabLocations->id= line[0];

        /* read access road of the location */
        line[0] = '\0';
        fgets(line, MAX_LINE-1, fin);
        line[MAX_LINE-1]='\0';
        if(strlen(line)>0) 
            getStackObject(line,&tabLocations->accessRoad);

        /* read maneuvering track of the location */
        line[0] = '\0';
        fgets(line, MAX_LINE-1, fin);
        line[MAX_LINE-1]='\0';
        if(strlen(line)>0) 
            getStackObject(line,&tabLocations->maneuveringTrack);

        /* read warehouse of the location */
        line[0] = '\0';
        fgets(line, MAX_LINE-1, fin);
        line[MAX_LINE-1]='\0';
        if(strlen(line)>0) 
            getWareHouseObject(line,&tabLocations->wareHouse);
   
        /* Close the file */
        fclose(fin);
		
	}else {
		*retVal = ERR_CANNOT_READ;
	}
}

void locationSave(tLocation tabLocations, const char* filename, tError *retVal)
{
    *retVal = OK;

	FILE *fout=NULL;
	char str[MAX_LINE];
	
	/* Open the output file */
	if((fout=fopen(filename, "w"))==NULL) {
		*retVal = ERR_CANNOT_WRITE;
	} else {
	
        /* write the id of the location */
        fprintf(fout, "%c\n", tabLocations.id);

        /* write the access road of the location */
        getStackStr( tabLocations.accessRoad, MAX_LINE, str);
        fprintf(fout, "%s\n", str);

        /* write the maneuvering track of the location */
        getStackStr( tabLocations.maneuveringTrack, MAX_LINE, str);
        fprintf(fout, "%s\n", str);

        /* write the warehouse of the location */
        getWareHouseStr( tabLocations.wareHouse, MAX_LINE, str);
        fprintf(fout, "%s\n", str);
            
        /* Close the file */
        fclose(fout);
	}
}

void locationInit(tLocation *location, char id)
{
    location->id= id;
    truckStackCreate(&location->accessRoad);
    truckStackCreate(&location->maneuveringTrack);
    warehouseCleanAllStocks(&location->wareHouse);
}

int warehouseFind( tMaterialId id, tWareHouse wh )
{
    bool found;
    int i, idx;
    
    i= 0;
    found= false;
    while (i< wh.nMaterials && !found) {
        found= (wh.stock[i].id == id);
        i++;
    }
    
    if (found)
        idx= i-1;
    else 
        idx= NO_MATERIAL;
    
    return idx;
}

void warehouseAddStock( tMaterialId id, tWareHouse *wh, int qtt )
{
    wh->stock[ wh->nMaterials ].id= id;
    wh->stock[ wh->nMaterials ].qtt= qtt;
    wh->nMaterials++;
}

void warehouseUpdateStock( tMaterialId id, tWareHouse *wh, int qtt )
{
    int i;
    bool found;
    
    i= 0;
    found= false;
    while (i< wh->nMaterials && !found) {
        found= (wh->stock[i].id == id);
        i++;
    }
    
    if (found) {
        wh->stock[i-1].qtt += qtt;
        if (wh->stock[i-1].qtt < 0)
            wh->stock[i-1].qtt = 0;        
    }        
}

void warehouseSetStock( tMaterialId id, tWareHouse *wh, int qtt )
{
    int i;
    bool found;
    
    i= 0;
    found= false;
    while (i< wh->nMaterials && !found) {
        found= (wh->stock[i].id == id);
        i++;
    }
    
    if (found) {
        wh->stock[i-1].qtt= qtt;        
        if (wh->stock[i-1].qtt < 0)
            wh->stock[i-1].qtt = 0;
    }
}

int warehouseGetStock( tMaterialId id, tWareHouse wh )
{
    int index, qtt;
    
    index= warehouseFind( id, wh );
    if (index != NO_MATERIAL)
        qtt= wh.stock[index].qtt;
    else 
        qtt= 0;
   
    return qtt;
}

int warehouseGetNumberOfMaterials( tWareHouse wh )
{
    return wh.nMaterials;
}

void warehouseCleanAllStocks( tWareHouse *wh )
{
    wh->nMaterials= 0;
}