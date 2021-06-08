#include "data.h"

/* Get a textual representation of a warehouse */
void getWareHouseStr(tWareHouse wh, int maxSize, char *str);

/* Get a warehouse object from its textual representation */
void getWareHouseObject(const char *str, tWareHouse *wh);

/* Load the location from a file */
void locationLoad(tLocation *locations, const char* filename, tError *retVal);

/* Save the location to a file */
void locationSave(tLocation locations, const char* filename, tError *retVal);

/* Inits a location */
void locationInit(tLocation *locations, char id);

/* Finds a material in the warehouse. Returns NO_MATERIAL if not found. Returns the index if found */
int warehouseFind( tMaterialId id, tWareHouse wh );

/* Adds a material in the warehouse with the specified stock */
void warehouseAddStock( tMaterialId id, tWareHouse *wh, int qtt );

/* Updates a material in the warehouse with the given increment or decrement of stock (+/- qtt) */
void warehouseUpdateStock( tMaterialId id, tWareHouse *wh, int qtt );

/* Sets a material in the warehouse with the given stock (absolute value for qtt) */
void warehouseSetStock( tMaterialId id, tWareHouse *wh, int qtt );

/* Gets the stock qtt of a material in the warehouse */
int warehouseGetStock( tMaterialId id, tWareHouse wh );

/* Gets the number of materials in the warehouse */
int warehouseGetNumberOfMaterials( tWareHouse wh );

/* Cleans all stocks of the warehouse */
void warehouseCleanAllStocks( tWareHouse *wh );

