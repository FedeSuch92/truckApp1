#include "data.h"

/* 
 * Methods for application data management 
 */

/* Initialize the application data */
void appDataInit(tAppData *object);

/* Load the application data from file */
void appDataLoad(tAppData *object, tError *error);

/* Save the application data to a file */
void appDataSave(tAppData object, tError *error);

/* Allow to assign a path to the application data */
void appDataSetPath(tAppData *object, const char *path);

/* 
 * API
 */

/* Return a table with the materials */
void getMaterials(tAppData object, tMaterialTable *result);

/* Get the material information */
void getMaterial(tAppData object, tMaterialId materialId, tMaterial *material, tError *retVal);

/* Add a new material */
void addMaterial(tAppData *object, tMaterial material, tError *retVal);

/* Remove a certain material */
void removeMaterial(tAppData *object, tMaterial material);

/* Return the table of trucks */
void getTrucks(tAppData object, tTruckTable *result);

/* Get the truck information */
void getTruck(tAppData object, tTruckId truckId, tTruck *truck, tError *retVal);

/* Add a new truck */
void addTruck(tAppData *object, tTruck truck, tError *retVal);

/* Adds stock for a material in a location */
void addStock( tAppData *object, char location, tMaterialId materialId, int qtt );

/* Removes stock for a material in a location */
void removeStock( tAppData *object, char location, tMaterialId materialId, int qtt );

/* Clean stocks for all materials in the specified location */
void cleanStocks( tAppData *object, char location );

/* Adds a truck to the specified platform of a location */
void addTruckToPlatform(tAppData *object, tTruckId truckId, char location, char platform, tError *retVal);

/* Removes a truck from the specified platform of a location */
void removeTruckFromPlatform(tAppData *object, tTruckId truckId, char location, char platform, tError *retVal);

/* Removes all trucks from all platforms of a location */
void removeAllTrucksOfLocation(tAppData *object, char location, tError *retVal);

/* Removes all deliveries from the panding, attended and unattended deliveries */
void cleanAllDeliveries(tAppData *object);

/* Adds a pending order to the system */
void addPendingDelivery(tAppData *object, tDelivery order, tError *retVal);

/* Checks if there's enough stock at the given warehouse */
bool checkStockAtOrigin( tWareHouse wh, tMaterial material, int qtt );

/* Loads a truck with the order and updates the warehouse' stock */
void loadTruck( tTruckStack *accessRoad, tWareHouse *wh, tMaterial material, int qtt );

/* Unloads a loaded truck and updates the warehouse' stock */
void unloadTruckAtDestination( tTruckStack *accessRoad, tWareHouse *wh );

/* Moves a truck form an origin platform to a destination platform */
void moveTruckFromOriginToDestination( tTruckStack *originPlatform, tTruckStack *destinationPlatform );

/* Says if a truck is suitable to be loaded with qtt units of the material */
bool checkSuitableTruck( tTruck truck, tMaterial material, int qtt );

/* Searches (and place on top of main platform) a suitable truck to be loaded with qtt units of material */
bool searchTruckAtOrigin( tTruckTable truckTable,
                              tTruckStack *accessRoad, 
                              tTruckStack *maneuveringTrack, 
                              tMaterial material, int qtt );

/* Prepares a loades truck to move de ordered material from origin to destination */
bool prepareLoadedTruckAtOrigin( tTruckTable truckTable,
                                     tTruckStack *accessRoad, tTruckStack *maneuveringTrack, 
                                     tWareHouse *wh, tMaterial material, int qtt );

/* Tries to attend the given order */
bool tryToAttendDelivery(  tTruckTable truckTable,
                            tLocation *originLocation, 
                            tLocation *destinationLocation, 
                            tMaterial material, int qtt );

/* Processes all deliveries and classifies then between unattented and attended */
void processDeliveries( tAppData *object, tError *retVal );
