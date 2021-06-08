#include "data.h"

/* Get a textual representation of a material */
void getMaterialStr(tMaterial material, int maxSize, char *str);
	
/* Get a material object from its textual representation */
void getMaterialObject(const char *str, tMaterial *material);

/* Compare two materials */
int materialCmp(tMaterial material1, tMaterial material2);

/* Copy the material data in src to dst*/
void materialCpy(tMaterial *dst, tMaterial src);

/* Initialize the table of materials */
void materialTableInit(tMaterialTable *table);

/* Add a new material to the table of materials */
void materialTableAdd(tMaterialTable *table, tMaterial material, tError *retVal);

/* Find a material in the table and returns its position */
int materialTableFind(tMaterialTable table, tMaterialId id);

/* Gets a material in the table by its id */
tMaterial materialTableGet(tMaterialTable tabMaterial, tMaterialId id);

/* Gets a material in the table by its index */
tMaterial materialTableMaterialAt(tMaterialTable tabMaterial, int index);

/* Remove the first occurence of a material in the table */
void materialTableDel(tMaterialTable *table, tMaterial material);

/* Load the table of materials from a file */
void materialTableLoad(tMaterialTable *table, const char* filename, tError *retVal);

/* Save a table of materials to a file */
void materialTableSave(tMaterialTable table, const char* filename, tError *retVal);

/* Filter all materials with the given type */
void materialTableFilterByType(tMaterialTable table, tMaterialType materialType, tMaterialTable *result);

/* Filter all materials with a weight wihtin the specified interval */
void materialTableFilterByWeightInterval(tMaterialTable tabMaterial, float minWeight, float maxWeight, tMaterialTable *result);

/* Gets the number of fragile materials */
int materialTableGetNumberOfFragileMaterials(tMaterialTable tabMaterial);

/* Gets the maximum height of all materials */
float materialTableGetMaxMaterialHeight(tMaterialTable tabMaterial);
