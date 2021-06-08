#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "material.h"

void getMaterialStr(tMaterial material, int maxSize, char *str) 
{
    /* Build the string */
	snprintf(str,maxSize-1,"%d %s %d %.2f %.2f %.2f %.2f %d %d %d", 
             material.id, material.name, (int)material.type, material.price, material.weight, material.height, 
			 material.volume, material.layers, (int)material.isFragile, (int)material.isDangerous);
}


void getMaterialObject(const char *str, tMaterial *material) {
	
    int id, type, isFragile, isDangerous;

    /* read material data */
	sscanf(str, "%d %s %d %f %f %f %f %d %d %d", &(id), material->name, &type, &(material->price), 
		 &(material->weight), &(material->height), &(material->volume), &(material->layers), &isFragile, &isDangerous);

	material->id = (tMaterialId)(id);
	material->type = (tMaterialType)(type);
    if (isFragile == 0)
        material->isFragile= false;
    else
        material->isFragile= true;
    if (isDangerous == 0)
        material->isDangerous= false;
    else
        material->isDangerous= true;
}

void materialTableInit(tMaterialTable *materialTable) {
	
	materialTable->nMaterials=0;
}
	
int materialCmp(tMaterial d1, tMaterial d2) {
	
	int result = 0;

    if ( strcmp(d1.name,d2.name)>0 )
		result = 1;
	else if ( strcmp(d1.name,d2.name)<0 )
		result = -1;
	else {
		if ( d1.type > d2.type )
			result = 1;
		else if ( d1.type < d2.type )
			result = -1;
		else {
			if (d1.id > d2.id) 
				result = 1;
			else if (d1.id < d2.id)
				result = -1;
			else{
				if (d1.layers > d2.layers)
					result = 1;
				else if (d1.layers < d2.layers)
					result = -1;
				else{
					if (d1.isFragile > d2.isFragile)
						result = 1;
					else if (d1.isFragile < d2.isFragile)
						result = -1;
					else{
						if (d1.isDangerous > d2.isDangerous)
							result = 1;
						else if (d1.isDangerous < d2.isDangerous)
							result = -1;
						else{
							if (d1.price > d2.price)
								result = 1;
							else if (d1.price < d2.price)
								result = -1;
							else{
								if (d1.weight > d2.weight)
									result = 1;
								else if (d1.weight < d2.weight)
									result = -1;
								else{
									if (d1.height > d2.height)
										result = 1;
									else if (d1.height < d2.height)
										result = -1;
									else{
										if (d1.volume > d2.volume)
											result = 1;
										else if (d1.volume < d2.volume)
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

    return result;
}

void materialCpy(tMaterial *dst, tMaterial src) {

	dst->id = src.id; 
    strcpy(dst->name,src.name);
    dst->type= src.type;
    dst->price= src.price;
    dst->weight = src.weight;
	dst->height = src.height;
	dst->volume = src.volume;
	dst->layers = src.layers;
	dst->isFragile = src.isFragile;
	dst->isDangerous = src.isDangerous;
}

void materialTableAdd(tMaterialTable *tabMaterial, tMaterial material, tError *retVal) {

	*retVal = OK;

	/* Check if there enough space for the new material */
	if(tabMaterial->nMaterials>=MAX_MATERIALS)
		*retVal = ERR_MEMORY;
    else {
		/* Add the new material to the end of the table */
		materialCpy(&tabMaterial->table[tabMaterial->nMaterials],material);
		tabMaterial->nMaterials++;        
    }
}

int materialTableFind(tMaterialTable tabMaterial, tMaterialId id) {

	int idx = NO_MATERIAL;
	
	int i=0;
	while(i< tabMaterial.nMaterials && idx==NO_MATERIAL) {
		/* Check if the id is the same */
		if(tabMaterial.table[i].id==id) {
			idx = i;
		}
		i++;
	}
	
	return idx;
}

tMaterial materialTableGet(tMaterialTable tabMaterial, tMaterialId id)
{
    tMaterial material;

	int i=0;
    material.id= NO_MATERIAL;

	while(i< tabMaterial.nMaterials && material.id==NO_MATERIAL) {
		/* Check if the id is the same */
		if(tabMaterial.table[i].id==id) {
			materialCpy(&material, tabMaterial.table[i]);
		}

		i++;
	}

	return material;
}

tMaterial materialTableMaterialAt(tMaterialTable tabMaterial, int index)
{
    tMaterial material;

	material.id= NO_MATERIAL;
	if (index >= 0 && index < tabMaterial.nMaterials) {
		materialCpy(&material, tabMaterial.table[index]);
	}

	return material;
}


void materialTableDel(tMaterialTable *tabMaterial, tMaterial material) {
	
	int i;
    int pos;

	pos = materialTableFind(*tabMaterial,material.id);
	if (pos!=NO_MATERIAL){
	/* If the material is found, all the rest of the elements are displaced one position */
		for(i=pos; i<tabMaterial->nMaterials-1; i++) {		
			materialCpy(&tabMaterial->table[i],tabMaterial->table[i+1]);
		}
		tabMaterial->nMaterials=tabMaterial->nMaterials-1;		
	}
}

void materialTableSave(tMaterialTable tabMaterial, const char* filename, tError *retVal) {

	*retVal = OK;
	
	FILE *fout=NULL;
	int i;
	char str[MAX_LINE];
	
	/* Open the output file */
	if((fout=fopen(filename, "w"))==NULL) {
		*retVal = ERR_CANNOT_WRITE;
	} else {
	
        /* Save all materials to the file */
        for(i=0;i<tabMaterial.nMaterials;i++) {
            getMaterialStr(tabMaterial.table[i], MAX_LINE, str);
            fprintf(fout, "%s\n", str);
        }
            
        /* Close the file */
        fclose(fout);
	}
}

void materialTableLoad(tMaterialTable *tabMaterial, const char* filename, tError *retVal) {
	*retVal = OK;
	FILE *fin=NULL;
	char line[MAX_LINE];
	tMaterial newMaterial;
	
	/* Initialize the output table */
	materialTableInit(tabMaterial);
	
	/* Open the input file */
	if((fin=fopen(filename, "r"))!=NULL) {

		/* Read all the lines */
		while(!feof(fin) && tabMaterial->nMaterials<MAX_MATERIALS) {
			/* Remove any content from the line */
			line[0] = '\0';
			/* Read one line (maximum 511 chars) and store it in "line" variable */
			fgets(line, MAX_LINE-1, fin);
			/* Ensure that the string is ended by 0*/
			line[MAX_LINE-1]='\0';
			if(strlen(line)>0) {
				/* Obtain the object */
				getMaterialObject(line, &newMaterial);
				/* Add the new material to the output table */
				materialTableAdd(tabMaterial, newMaterial, retVal);		
			}
		}
		/* Close the file */
		fclose(fin);
		
	}else {
		*retVal = ERR_CANNOT_READ;
	}
}

void materialTableFilterByType(tMaterialTable tabMaterial, tMaterialType materialType, tMaterialTable *result) {

	tError retVal;
	int i;
	materialTableInit(result);
	for(i=0;i<tabMaterial.nMaterials;i++) {
		if (materialType == tabMaterial.table[i].type){
			materialTableAdd(result, tabMaterial.table[i], &retVal);
			/* retVal will always be OK as the result table will be smaller than tabMaterial which cannot have more than MAX_MATERIALS*/
		}
	}
}

void materialTableFilterByWeightInterval(tMaterialTable tabMaterial, float minWeight, float maxWeight, tMaterialTable *result){

	tError retVal;
	int i;
	materialTableInit(result);

	for(i=0;i<tabMaterial.nMaterials;i++) {
		if (tabMaterial.table[i].weight >= minWeight && 
			tabMaterial.table[i].weight <= maxWeight) {
			materialTableAdd(result, tabMaterial.table[i], &retVal);
			/* retVal will always be OK as the result table will be smaller than tabMaterial which cannot have more than MAX_MATERIALS*/
		}
	}
}

int materialTableGetNumberOfFragileMaterials(tMaterialTable tabMaterial) {

	int numMaterials = 0;

	int i;
	for(i=0;i<tabMaterial.nMaterials;i++) {
		if (tabMaterial.table[i].isFragile){
			numMaterials++;
		}
	}

	return numMaterials;
}

float materialTableGetMaxMaterialHeight(tMaterialTable tabMaterial){

	float maxHeight = 0.0;

	int i;
	float height;

	for(i=0;i<tabMaterial.nMaterials;i++) {
		height= (1+tabMaterial.table[i].layers) * tabMaterial.table[i].height;
		if (height > maxHeight)
			maxHeight= height;
	}

	return maxHeight;
}

