#include <stdio.h>
#include <math.h>
#include <string.h>
#include <api.h>
#include "material.h"
#include "truck.h"
#include "location.h"
#include "delivery.h"
#include "stack.h"

void appDataInit(tAppData *object) {
	/* Set parent folder as the default path */
	strcpy(object->path, "../");
	
	/* Initialize the material table */
	materialTableInit(&(object->materials));
	
	/* Initialize the trucks table */
	trucksTableInit(&(object->trucks));
	
	/* Initialize the locations */
    locationInit( &object->locationA, 'A');
    locationInit( &object->locationB, 'B');

	/* Initialize the pending, attended and unattended deliveries */
    deliveriesTableInit(&object->pendingDeliveries);
    deliveriesTableInit(&object->attendedDeliveries);
    deliveriesTableInit(&object->unattendedDeliveries);
}

void appDataLoad(tAppData *object, tError *retVal) {
	char path[MAX_LINE];
	*retVal = OK;
	
	/* Load the table of trucks */
	snprintf(path,MAX_PATHNAME+MAX_FILENAME,"%strucks.txt", object->path);
	trucksTableLoad(&(object->trucks), path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error reading the file of trucks\n");
	}

	/* Load the table of materials */
	snprintf(path,MAX_PATHNAME+MAX_FILENAME,"%smaterials.txt", object->path);
	materialTableLoad(&(object->materials), path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error reading the file of materials\n");
	}
    
	/* Load the location A */
	snprintf(path,MAX_PATHNAME+MAX_FILENAME,"%slocationA.txt", object->path);
	locationLoad(&(object->locationA), path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error reading the file of location A\n");
	}

	/* Load the location B */
	snprintf(path,MAX_PATHNAME+MAX_FILENAME,"%slocationB.txt", object->path);
	locationLoad(&(object->locationB), path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error reading the file of location B\n");
	}

	/* Load the pending deliveries */
	snprintf(path,MAX_PATHNAME+MAX_FILENAME,"%sdeliveriesPending.txt", object->path);
	deliveriesTableLoad(&(object->pendingDeliveries), path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error reading the file of pending deliveries\n");
	}

	/* Load the attended deliveries */
	snprintf(path,MAX_PATHNAME+MAX_FILENAME,"%sdeliveriesAttended.txt", object->path);
	deliveriesTableLoad(&(object->attendedDeliveries), path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error reading the file of attended deliveries\n");
	}

	/* Load the unattended deliveries */
	snprintf(path,MAX_PATHNAME+MAX_FILENAME,"%sdeliveriesUnattended.txt", object->path);
	deliveriesTableLoad(&(object->unattendedDeliveries), path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error reading the file of unattended deliveries\n");
	}
}

void appDataSave(tAppData object, tError *retVal)  {
	char path[MAX_LINE];
	*retVal = OK;
	
	/* Save the table of trucks */
	snprintf(path,MAX_PATHNAME+MAX_FILENAME,"%strucks.txt", object.path);
	trucksTableSave(object.trucks, path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error saving the file of trucks\n");
	}
	
	/* Save the table of materials */
	snprintf(path,MAX_PATHNAME+MAX_FILENAME,"%smaterials.txt", object.path);
	materialTableSave(object.materials, path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error saving the file of materials\n");
	}
    
	/* Save the location A */
	snprintf(path,MAX_PATHNAME+MAX_FILENAME,"%slocationA.txt", object.path);
    locationSave(object.locationA, path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error saving the location A\n");
	}

	/* Save the location B */
	snprintf(path,MAX_PATHNAME+MAX_FILENAME,"%slocationB.txt", object.path);
    locationSave(object.locationB, path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error saving the location B\n");
	}

	/* Save the pending deliveries */
	snprintf(path,MAX_PATHNAME+MAX_FILENAME,"%sdeliveriesPending.txt", object.path);
    deliveriesTableSave(object.pendingDeliveries, path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error saving the pending deliveries\n");
	}

	/* Save the attended deliveries */
	snprintf(path,MAX_PATHNAME+MAX_FILENAME,"%sdeliveriesAttended.txt", object.path);
    deliveriesTableSave(object.attendedDeliveries, path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error saving the attended deliveries\n");
	}

	/* Save the unattended deliveries */
	snprintf(path,MAX_PATHNAME+MAX_FILENAME,"%sdeliveriesUnattended.txt", object.path);
    deliveriesTableSave(object.unattendedDeliveries, path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error saving the unattended deliveries\n");
	}
}

void appDataSetPath(tAppData *object, const char *path)  {		
	strncpy(object->path, path, MAX_PATHNAME);	
}


/*********************** 
 *        API
 **********************/

void getTrucks(tAppData object, tTruckTable *result) {
	*result = object.trucks;	
}

void getTruck(tAppData object, tTruckId truckId, tTruck *truck, tError *retVal) {
	
	int i;
	*retVal = OK;

	/* Check if there is a truck with this id */
	i = trucksTableFind(object.trucks, truckId);
	if (i!=NO_TRUCK) {
		truckCpy(truck,object.trucks.table[i]);
	} else {
		*retVal = ERR_ENTRY_NOT_FOUND;
	}
}

void addTruck(tAppData *object, tTruck truck, tError *retVal) {
	*retVal = OK;
	tTruck tmp;

	/* Check if there is another truck with the same id */
	getTruck(*object, truck.id, &tmp, retVal);
	if(*retVal==OK) {
		*retVal = ERR_DUPLICATED_ENTRY;
	} else {
		/* Add the new truck using the truck table method */
		trucksTableAdd(&(object->trucks), truck, retVal);
	}
}

void getMaterials(tAppData object, tMaterialTable *result) {
	*result = object.materials;	
}

void getMaterial(tAppData object, tMaterialId id, tMaterial *material, tError *retVal) {
	
	int i;
	*retVal = OK;
	
	/* Check if there is a material with this id */
	i = materialTableFind(object.materials, id);
	if (i!=NO_MATERIAL) {
		materialCpy(material,object.materials.table[i]);
	} else {
		*retVal = ERR_ENTRY_NOT_FOUND;
	}

}

void addMaterial(tAppData *object, tMaterial material, tError *retVal) {
	*retVal = OK;
	tMaterial tmpMaterial;
    
	/* Check if there is another material with the same id */
	getMaterial(*object, material.id, &tmpMaterial, retVal);
	if(*retVal==OK) {
		*retVal = ERR_DUPLICATED_ENTRY;
	} else {
		/* Add the new material using the material table method */
		materialTableAdd(&(object->materials), material, retVal);
	}

}

void removeMaterial(tAppData *object, tMaterial material) {
	
	/* Call the method from the materials table*/
	materialTableDel(&(object->materials), material);
}

void addStock( tAppData *object, char location, tMaterialId materialId, int qtt ) 
{
    if (location == 'A') {
        if (warehouseFind(materialId, object->locationA.wareHouse) == NO_MATERIAL)
            warehouseAddStock(materialId, &(object->locationA.wareHouse), qtt); 
        else
            warehouseUpdateStock(materialId, &(object->locationA.wareHouse), qtt); 
    }
    else if (location == 'B') {
        if (warehouseFind(materialId, object->locationB.wareHouse) == NO_MATERIAL)
            warehouseAddStock(materialId, &(object->locationB.wareHouse), qtt);
        else
            warehouseUpdateStock(materialId, &(object->locationB.wareHouse), qtt); 
    }
}

void removeStock( tAppData *object, char location, tMaterialId materialId, int qtt ) 
{
    if (location == 'A')
        warehouseUpdateStock(materialId, &(object->locationA.wareHouse), -qtt); 
    else if (location == 'B')
        warehouseUpdateStock(materialId, &(object->locationB.wareHouse), -qtt);     
}

void cleanStocks( tAppData *object, char location ) 
{
    if (location == 'A')
        warehouseCleanAllStocks( &(object->locationA.wareHouse) ); 
    else if (location == 'B')
        warehouseCleanAllStocks( &(object->locationB.wareHouse) ); 
}

void addTruckToPlatform(tAppData *object, tTruckId truckId, char location, char platform, tError *retVal) 
{
	*retVal = OK;
    tLoadedTruck loadedTruck;
    
    loadedTruck.id= truckId;
    loadedTruck.load.id= NO_MATERIAL;
    loadedTruck.load.qtt= 0;

    if (location=='A')
    {
        if (platform=='M')
            truckStackPush( &object->locationA.accessRoad, loadedTruck );
        else if (platform=='S')
            truckStackPush( &object->locationA.maneuveringTrack, loadedTruck );
    }   

    else if (location=='B')
    {
        if (platform=='M')
            truckStackPush( &object->locationB.accessRoad, loadedTruck );
        else if (platform=='S')
            truckStackPush( &object->locationB.maneuveringTrack, loadedTruck );        
    }
}

void removeTruckFromStack( tTruckStack *s, tTruckId truckId ) 
{
    tTruckStack auxStack;
    tLoadedTruck e;
    int i,count;
    
    if (!truckStackEmpty(*s))
    {
        truckStackCreate(&auxStack);  
        count= 0;
        e= truckStackTop(*s);

        while ( !truckStackEmpty(*s) && (e.id != truckId) )
        {  
            truckStackPop(s);
            truckStackPush(&auxStack, e);
            e= truckStackTop(*s);
            count++;
        }
        truckStackPop(s);
        
        for (i= 0; i<count;i++)
        {
            e= truckStackTop(auxStack);
            truckStackPop(&auxStack);
            truckStackPush(s, e);
        }
    }
}

void removeTruckFromPlatform(tAppData *object, tTruckId truckId, char location, char platform, tError *retVal) 
{
	*retVal = OK;

    if (location=='A')
    {
        if (platform=='M')
            removeTruckFromStack( &object->locationA.accessRoad, truckId );
        else if (platform=='S')
            removeTruckFromStack( &object->locationA.maneuveringTrack, truckId );
    }   
    else if (location=='B')
    {
        if (platform=='M')
            removeTruckFromStack( &object->locationB.accessRoad, truckId );
        else if (platform=='S')
            removeTruckFromStack( &object->locationB.maneuveringTrack, truckId );        
    }
}

void removeAllTrucksOfLocation(tAppData *object, char location, tError *retVal) 
{
	*retVal = OK;

    if (location=='A')
    {
        truckStackClean( &object->locationA.accessRoad );
        truckStackClean( &object->locationA.maneuveringTrack );
    }   
    else if (location=='B')
    {
        truckStackClean( &object->locationB.accessRoad );
        truckStackClean( &object->locationB.maneuveringTrack );
    }
}

void cleanAllDeliveries(tAppData *object)
{
    deliveriesTableInit( &object->pendingDeliveries );
    deliveriesTableInit( &object->attendedDeliveries );
    deliveriesTableInit( &object->unattendedDeliveries );    
}

void addPendingDelivery(tAppData *object, tDelivery order, tError *retVal)
{
    deliveriesTableAdd(&object->pendingDeliveries, order, retVal);
}

/********************/
/* Delivery processing */
/********************/

bool checkStockAtOrigin( tWareHouse wh, tMaterial material, int qtt )
{
    bool result= false;
/*************** PR2 EX2A.1 *****************/
    /* Get stock of material*/
    int in_stock;
    in_stock = warehouseGetStock( material.id, wh );
    /* Check if qtt is equal to the material in stock*/
    if (qtt <= in_stock) {
        result = true;
    }
    /******************************************/
    return result;
}

bool searchTruckAtOrigin( tTruckTable truckTable,
                              tTruckStack *accessRoad, 
                              tTruckStack *maneuveringTrack, 
                              tMaterial material, int qtt )
{
    bool success= false;

/*************** PR2 EX2A.2 *****************/
    tTruck tempTruck;
    tLoadedTruck loadedTruck;
    
    while (!truckStackEmpty(*accessRoad) && !success) {
        /* Returns the element on top of the accessRoad */
        loadedTruck = truckStackTop(*accessRoad);
         /* Gets a truck in the table by its id*/
        tempTruck = trucksTableGet(truckTable, loadedTruck.id);
        success = checkSuitableTruck( tempTruck, material, qtt );
        if (!success) {
            truckStackPop(accessRoad);
            truckStackPush(maneuveringTrack, loadedTruck);
        }
    }
    
    while (!truckStackEmpty(*maneuveringTrack) && !success) {
        /* Returns the element on top of the stack */
        loadedTruck = truckStackTop(*maneuveringTrack);
         /* Gets a truck in the table by its id*/
        tempTruck = trucksTableGet(truckTable, loadedTruck.id);
        success = checkSuitableTruck( tempTruck, material, qtt );
        truckStackPop(maneuveringTrack);
        truckStackPush(accessRoad, loadedTruck);
    }
/******************************************/
    return success;
}

void loadTruck( tTruckStack *accessRoad, tWareHouse *wh, tMaterial material, int qtt )
{
/*************** PR2 EX2A.3 *****************/
    tLoadedTruck loadedTruck;
    
    if (checkStockAtOrigin( *wh, material, qtt)) {
        /* Returns the element on top of the accessRoad */
        loadedTruck = truckStackTop(*accessRoad);
        /* Pops an element from the top of the accessRoad */
        truckStackPop(accessRoad);
        /*Load truck*/
        loadedTruck.load.id = material.id;
        loadedTruck.load.qtt = qtt;
        
        /* Push an element on the top of the stack */
        truckStackPush(accessRoad, loadedTruck);
        
        /* Updates a material in the warehouse with the given increment or decrement of stock (+/- qtt) */
        warehouseUpdateStock( material.id, wh, -qtt );
    }
/******************************************/
}

void moveTruckFromOriginToDestination(  tTruckStack *originPlatform, 
                                        tTruckStack *destinationPlatform )
{
/*************** PR2 EX2B *****************/
    tLoadedTruck loadedTruck;
    
    if (!truckStackEmpty(*originPlatform)) {
        /* Returns the element on top of the origin */
        loadedTruck = truckStackTop(*originPlatform);
    
        /* Pops an element from the top of the origin */
        truckStackPop(originPlatform);

        /* Push an element on the top of the destination*/
        truckStackPush(destinationPlatform, loadedTruck);
    }
/******************************************/
}

void unloadTruckAtDestination( tTruckStack *accessRoad, tWareHouse *wh )
{
/*************** PR2 EX2C *****************/
     tLoadedTruck loadedTruck;
     int qtt;
     tMaterialId id;
        
    if (!truckStackEmpty(*accessRoad)) {
        
        /* Returns the element on top of the accessRoad */
        loadedTruck = truckStackTop(*accessRoad);
        /* Pops an element from the top of the accessRoad */
        truckStackPop(accessRoad);
        
        id = loadedTruck.load.id;
        qtt = loadedTruck.load.qtt;
        
        if (warehouseFind(id, *wh ) == NO_MATERIAL) {
            /* Adds a material in the warehouse with the specified stock */
            warehouseAddStock(id, wh, qtt );
        } else {
            /* Updates a material in the warehouse with the given increment or decrement of stock (+/- qtt) */
            warehouseUpdateStock( id, wh, qtt );
        }
     
        /*Unload truck*/
        loadedTruck.load.id = NO_MATERIAL;
        loadedTruck.load.qtt = 0;
        
        /* Push an element on the top of the stack */
        truckStackPush(accessRoad, loadedTruck);
    }
/******************************************/
}

bool checkSuitableTruck( tTruck truck, tMaterial material, int qtt )
{
    return (truck.capacity) >= (material.volume * (float)qtt);
}

bool prepareLoadedTruckAtOrigin( tTruckTable truckTable,
                                     tTruckStack *accessRoad, tTruckStack *maneuveringTrack, 
                                     tWareHouse *wh, tMaterial material, int qtt )
{
    bool success;

    /* Check there is enough stock to satisfy the order */
    success= checkStockAtOrigin( *wh, material, qtt );

    /* Search truck (let the suitable truck on top of the main platform) */
    if (success)
        success= searchTruckAtOrigin( truckTable, accessRoad, maneuveringTrack, material, qtt );

    /* Load the truck on top of the main platform (truck about to leave origin location) */
    if (success) 
        loadTruck( accessRoad, wh, material, qtt );

    return success;
}

bool tryToAttendDelivery(  tTruckTable truckTable,
                            tLocation *originLocation, 
                            tLocation *destinationLocation, 
                            tMaterial material, int qtt )
{
    bool success;

    /* Prepare the truck and place it in the top of origin main platform */
    success= prepareLoadedTruckAtOrigin( truckTable,
                                         &originLocation->accessRoad, 
                                         &originLocation->maneuveringTrack, 
                                         &originLocation->wareHouse, 
                                         material, qtt );

    /* Move the materials from origin location to destination location */
    if (success)
        moveTruckFromOriginToDestination( &originLocation->accessRoad, 
                                          &destinationLocation->accessRoad );

    /* Unload the truck at destination location and update stocks on the warehouse */
    if (success)
        unloadTruckAtDestination( &destinationLocation->accessRoad, 
                                  &destinationLocation->wareHouse );

    return success;
}

void processDeliveries( tAppData *object, tError *retVal )
{
    bool attended;
    tDelivery order;
    tMaterial  material;
    int i, qtt;

    for (i= 0; i < object->pendingDeliveries.nDeliveries; i++) 
    {
        /* get the current order */
        order= object->pendingDeliveries.table[i];

        /* find out the material and its ordered qtt*/
        material= materialTableGet( object->materials, order.materialsToDeliver.id );
        qtt= order.materialsToDeliver.qtt;

        /* try to attend the order */
        if (order.originLocation=='A')
            attended= tryToAttendDelivery( object->trucks,
                                        &object->locationA, 
                                        &object->locationB, 
                                        material, qtt );
        else 
            attended= tryToAttendDelivery( object->trucks,
                                        &object->locationB, 
                                        &object->locationA, 
                                        material, qtt );

        /* classify order according to result */
        if (attended)
            deliveriesTableAdd( &object->attendedDeliveries, order, retVal );
        else
            deliveriesTableAdd( &object->unattendedDeliveries, order, retVal );            
    }

    /* cleans pending list because all deliveries have been processed */
    deliveriesTableClean( &object->pendingDeliveries );  
}
