/* This code ensures that this file is included only once */
#ifndef __DATA_H
#define __DATA_H
/* If the constant DATA_H is not defined (ifndef), the code is added, otherwise,
 * this code is excluded. When the code is added, the constant is defined, 
 * therefore next time this file will be included it will be defined and no 
 * inclusion will be done. */

#include <stdbool.h>

#define MAX_NAME 20+1
#define MAX_MATERIALS 100
#define MAX_TRUCKS 20
#define MAX_PATHNAME 255
#define MAX_FILENAME 25
#define MAX_LINE 512
#define MAX_TRUCKS_IN_STACK 20
#define MAX_DELIVERIES 100
#define NO_TRUCK -1
#define NO_MATERIAL -1
#define NO_DELIVERY -1

/* Definition of the error type. */
typedef enum {OK=1, ERROR=0, ERR_CANNOT_READ=-1, ERR_CANNOT_WRITE=-2, 
              ERR_MEMORY=-3, ERR_DUPLICATED_ENTRY=-4, ERR_INVALID_DATA=-5, 
              ERR_ENTRY_NOT_FOUND=-6,
              ERR_NO_MATERIAL=-7,ERR_NO_TRUCK=-8,ERR_NO_FREE_GAP=-9} tError;

typedef int tMaterialId;
typedef int tTruckId;
typedef int tDeliveryId;

typedef enum {
   RIGID, COLLAPSIBLE, TRAILER, CONTAINER, CARRIAGE, TANK, REFRIGERATOR, TAULINER, PLATFORM, OTHER_TRUCKS
} tTruckType;

typedef struct {
    tTruckId id; 
	char brand[MAX_NAME]; 
	char model[MAX_NAME];
	int  year;
	tTruckType truckType;
	int  category;  
	float capacity; 
	bool international; 
	float weight;
	float gauge; 
	float maxSpeed;  
} tTruck;

typedef struct {
	tTruck table[MAX_TRUCKS];
	int nTrucks;
} tTruckTable;

typedef enum {
  CONCRETE, GLASS, WOOD, BRICK, TUBES, ALUMINUM, SAND, FOAM, PLADUR, TILES, INSULATION, GAS, WATER, OTHER_MATERIALS
} tMaterialType;

typedef int tMaterialId;

typedef struct {
    tMaterialId id;
	char name[MAX_NAME];	
	tMaterialType type;
	float price;
	float weight;
	float height;
	float volume;
	int layers;
	bool isFragile;
	bool isDangerous;
} tMaterial;

typedef struct {
	tMaterial table[MAX_MATERIALS];
	int nMaterials;
} tMaterialTable;

typedef struct {
    tMaterialId id;
    int qtt;
} tMaterialQtt;

typedef struct {
  tTruckId id;
  tMaterialQtt load;
} tLoadedTruck;

typedef struct {
	tLoadedTruck table[MAX_TRUCKS_IN_STACK];
	unsigned int nElem;
} tTruckStack;

typedef struct {
  tMaterialQtt stock[MAX_MATERIALS];
  int nMaterials;
  
} tWareHouse;

typedef struct {
  char id;
  tTruckStack accessRoad; 
  tTruckStack maneuveringTrack;
  tWareHouse wareHouse;
} tLocation;

typedef struct {
  tDeliveryId id;
  char originLocation;
  char destinationLocation;
  tMaterialQtt materialsToDeliver;
} tDelivery;

typedef struct {
  tDelivery table[MAX_DELIVERIES];
  int nDeliveries;
} tDeliveryTable;

/* Definition of the application data structure */
typedef struct {
	/* Path where data will be stored */
	char path[MAX_PATHNAME];
	
	/* Trucks table */
	tTruckTable trucks;
	
	/* Materials table */
	tMaterialTable materials;

    /* Location A */
    tLocation locationA;
    
    /* Location B */
    tLocation locationB;

    /* Pending deliveries */
    tDeliveryTable pendingDeliveries;

    /* Attended deliveries */
    tDeliveryTable attendedDeliveries;

    /* Unattended deliveries */
    tDeliveryTable unattendedDeliveries;

} tAppData;

#endif /*__DATA_H*/