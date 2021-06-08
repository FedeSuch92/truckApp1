#include "data.h"

/* Get a textual representation of a truck */
void getTruckStr(tTruck truck, int maxSize, char *str);

/* Get a truck object from its textual representation */
void getTruckObject(const char *str, tTruck *truck);

/* Get a textual representation of a loaded truck */
void getLoadedTruckStr(tLoadedTruck loadedTruck, int maxSize, char *str);

/* Get a loaded truck object from its textual representation */
void getLoadedTruckObject(const char *str, tLoadedTruck *loadedTruck);

/* Copy the loaded truck data in src to dst*/
void loadedTruckCpy(tLoadedTruck *dst, tLoadedTruck src);

/* Initialize a loaded truck */
void loadedTruckInit(tLoadedTruck *t);

/* Copy the truck data in src to dst*/
void truckCpy(tTruck *dst, tTruck src);

/* Compares the truck data of p1 and p2*/
int truckCmp(tTruck p1, tTruck p2);

/* Compares the loaded truck data of p1 and p2*/
int loadedTruckCmp(tLoadedTruck d1, tLoadedTruck d2);

/* Initializes the given trucks table */
void trucksTableInit(tTruckTable *trucksTable);

/* Add a new truck to the table of trucks */
void trucksTableAdd(tTruckTable *tabTrucks, tTruck truck, tError *retVal);

/* Find a truck in the table */
int trucksTableFind(tTruckTable tabTrucks, tTruckId id);

/* Says if the trucks table is empty */
bool trucksTableEmpty(tTruckTable tabTrucks);

/* Gets a truck in the table by its id*/
tTruck trucksTableGet(tTruckTable tabTrucks, tTruckId id);

/* Load the table of trucks from a file */
void trucksTableLoad(tTruckTable *tabTrucks, const char* filename, tError *retVal);

/* Save a table of trucks to a file */
void trucksTableSave(tTruckTable tabTrucks, const char* filename, tError *retVal);

/* Obtain from a table of trucks those of a given truck type */
void trucksTableFilterByTruckType(tTruckTable tabTrucks, tTruckType truckType, tTruckTable *result);

/* Obtain from a table of trucks allowed to do international transport */
void trucksTableGetTrucksInternational(tTruckTable tabTrucks, tTruckTable *result);

/* Obtain from a table of trucks the average capacity by truck type */
float truckTableGetAverageCapacityByTruckType(tTruckTable tabTruck, tTruckType truckType);

/* Obtain from a table of trucks the maximum speed of a truck */
float truckTableGetMaxTruckSpeed(tTruckTable tabTruck);

