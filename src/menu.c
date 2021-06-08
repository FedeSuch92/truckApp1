#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "truck.h"
#include "material.h"

int getOption(int numOptions) {
	int option=0;
		
	while(option<1 || option>numOptions) {
		/* Read the input */
		printf(">> ");
			scanf("%u", &option);
		getchar();
		
		/* Check the user input */
		if(option<1 || option>numOptions) {
			printf("Incorrect option.\n");
		}
	}
	 return option;
}

void readMaterial(tMaterial *material, tError *retVal) {	

	*retVal = OK;
	int number;
	char buffer[MAX_LINE];
	int length;

	/* Request information from user */ 
    printf("Material id (integer less than %d):\n>> ", MAX_MATERIALS);
    scanf("%d",&number);
	if(number>MAX_MATERIALS) 
		*retVal = ERROR;
	else
		material->id = (tMaterialId)number;

    printf("Material name (20 char max, no spaces):\n>> ");
    scanf("%s",buffer);
	length = strlen(buffer);
	if (length<MAX_NAME) 
		strncpy(material->name,buffer,MAX_NAME);
	else 
		*retVal = ERROR;
	
    printf("Material Type (integer value being 0=CONCRETE, 1=GLASS, 2=WOOD, 3=BRICK, 4=TUBES, 5=ALUMINUM, 6=SAND, 7=FOAM, 8=PLADUR, 9=TILES, 10=INSULATION, 11=GAS, 12=WATER, 13=OTHERS):\n");
	scanf("%d",&number);
	if(number>=0 && number <=13)
		material->type = (tMaterialType)(number);
	else 
		*retVal = ERROR;

	printf("Price:\n>> ");
	scanf("%f",&material->price); 
	
	printf("Weight:\n>> ");
	scanf("%f",&material->weight); 
   
	printf("Height:\n>> ");
	scanf("%f",&material->height); 
	
	printf("Volume:\n>> ");
	scanf("%f",&material->volume); 
	
	printf("Maximum number of layers allowed on top:\n>> ");
	scanf("%d",&material->layers);
	
	printf("Is fragile? (YES/NO):\n>> ");
	scanf("%s", buffer);
	if (strcmp(buffer,"YES") == 0 || strcmp(buffer,"yes") == 0 || strcmp(buffer,"Yes") == 0) 
		material->isFragile = true;
	else if  (strcmp(buffer,"NO") == 0 || strcmp(buffer,"no") == 0 || strcmp(buffer,"No") == 0)
		material->isFragile = false;
	else 
		*retVal = ERROR;
	
	printf("Is dangerous? (YES/NO):\n>> ");
	scanf("%s", buffer);
	if (strcmp(buffer,"YES") == 0 || strcmp(buffer,"yes") == 0 || strcmp(buffer,"Yes") == 0) 
		material->isDangerous = true;
	else if  (strcmp(buffer,"NO") == 0 || strcmp(buffer,"no") == 0 || strcmp(buffer,"No") == 0)
		material->isDangerous = false;
	else 
		*retVal = ERROR;
}

void readTruck(tTruck *truck, tError *retVal) {	

	*retVal = OK;

	char buffer[MAX_LINE];
	int number, length;

	printf("Truck id (integer less than %d):\n>> ",MAX_TRUCKS);
	scanf("%d",&number);
	if(number>MAX_TRUCKS) {
		*retVal = ERROR;
	} else {
		truck->id= (tTruckId)(number);
	}
	
    printf("Truck brand (max 20 char, no spaces):\n>> ");
    scanf("%s",buffer);
	length = strlen(buffer);
	if (length<MAX_NAME) {
		strncpy(truck->brand,buffer,MAX_NAME);
	} else {
		*retVal = ERROR;
	}

	printf("Truck model (max 20 char, no spaces):\n>> ");
    scanf("%s",buffer);
	length = strlen(buffer);
	if (length<MAX_NAME) {
		strncpy(truck->model,buffer,MAX_NAME);
	} else {
		*retVal = ERROR;
	}

	printf("Fabrication year:\n>> ");
	scanf("%d",&(truck->year));

	printf("Truck type of truck (1 digit being 0=RIGID 1=COLLAPSIBLE 2=TRAILER 3=CONTAINER 4=CARRIAGE 5=TANK 6=REFRIGERATOR 7=TAULINER 8=PLATFORM 9=OTHERS):\n>> ");
	scanf("%d",&number);
	if(number>=0 && number <=9) {
		truck->truckType= (tTruckType)(number);
	} else {
		*retVal = ERROR;
	}

	printf("Truck category (allowed values are: 1 when truck weight is up to 3500kg, 2 when between 3500 kg and 12000 kg or 3 when exceeds 12000 kg):\n>> ");
	scanf("%d",&number);
	if(number>=1 && number <=3) {
		truck->category= number;
	} else {
		*retVal = ERROR;
	}
	
	printf("Truck capacity (in cubic meters):\n>> ");
	scanf("%f",&(truck->capacity));

	printf("Is allowed to do international transport? (YES/NO):\n>> ");
	scanf("%s", buffer);
	if (strcmp(buffer,"YES") == 0 || strcmp(buffer,"yes") == 0 || strcmp(buffer,"Yes") == 0) {
		truck->international = true;
	} else if  (strcmp(buffer,"NO") == 0 || strcmp(buffer,"no") == 0 || strcmp(buffer,"No") == 0) {
		truck->international = false;
	} else {
		*retVal = ERROR;
	}

	printf("Truck weight (in tones):\n>> ");
	scanf("%f",&(truck->weight));
	
	printf("Truck gauge (in meters):\n>> ");
	scanf("%f",&(truck->gauge));

	printf("Truck max speed (in km/h):\n>> ");
	scanf("%f",&(truck->maxSpeed));
}

void printTruckTable(tTruckTable table) {
    
  	int i;	
	char truckStr[MAX_LINE];
	
	if(table.nTrucks==0) {
		printf("No trucks.\n");
	} else {
		for(i=0;i<table.nTrucks;i++) {
			getTruckStr(table.table[i], MAX_LINE, truckStr);
			printf("[%u] - %s\n", i+1, truckStr);
		}		
	}
}

void printMaterialTable(tMaterialTable table) {
	int i;	
	char materialStr[MAX_LINE];
	
	if(table.nMaterials==0) {
		printf("No materials.\n");
	} else {
		for(i=0;i<table.nMaterials;i++) {
			getMaterialStr(table.table[i], MAX_LINE, materialStr);
			printf("[%u] - %s\n", i+1, materialStr);
		}		
	}
}


/*****************
 **   MAIN MENU **
*****************/
void printMainMenuOptions() {
	/* Show menu options */
	printf("=======================\n");
	printf(" Main Menu \n");
	printf("=======================\n");
	printf("1) Load data from file\n");
	printf("2) Save data to file\n");
	printf("3) Manage materials\n");
	printf("4) Manage trucks\n");
	printf("5) View statistics\n");
	printf("6) Exit\n");	
}

tMainMenuOptions getMainMenuOption() {
	/* Convert to the correct type */
	return (tMainMenuOptions)(getOption(6)-1);
}

void mainMenu(tAppData *appData) 
{
	tMainMenuOptions option;
	tError retVal;
		
	/* Assign the data path */
	appDataSetPath(appData,"../");
		
	/* Start the menu */
	do {
		/* Show list of options and ask the user for an option */
		printMainMenuOptions();
		option=getMainMenuOption();
		
		/* Do the action for the given option */
		if (option == MAIN_MENU_LOAD) {
			appDataLoad(appData,&retVal);
			if(retVal==OK) {
				printf("Data loaded\n");
			} else {	
				printf("No previous data loaded\n");
			}
		} else if (option == MAIN_MENU_SAVE) {
			appDataSave(*appData,&retVal);
			if(retVal==OK) {
				printf("Data saved\n");
			} else {	
				printf("Cannot save the data\n");
			}
		} else if (option == MAIN_MENU_MATERIAL) {
			materialMenu(appData);
		} else if (option == MAIN_MENU_TRUCK) {
			truckMenu(appData);
		} else if (option == MAIN_MENU_STAT) {
			statMenu(*appData);
		} 
	} while (option!=MAIN_MENU_EXIT);
}

/*********************************
 **   MATERIAL MANAGEMENT MENU **
*********************************/
void printMaterialMenuOptions() {
	/* Show menu options */
	printf("=======================\n");
	printf(" Manage Materials\n");
	printf("=======================\n");
	printf("1) List materials\n");	
	printf("2) Add material\n");
	printf("3) Delete material\n");	
	printf("4) Clear all materials\n");
	printf("5) Get list of materials by type\n");	
	printf("6) Get list of materials by weight interval\n");	
	printf("7) Exit\n");	
}

tMaterialMenuOptions getMaterialMenuOption() {
	/* Convert to the correct type */
	return (tMaterialMenuOptions)(getOption(7)-1);
}

void materialMenu(tAppData *appData) {
	tMaterialMenuOptions option;
	tMaterial newMaterial;
	tMaterialTable materialTable,resultTable;
	char materialStr[MAX_LINE];
	int i, materialType, pos=0;
	float minWeight, maxWeight;
	tError retVal;
			
	/* Start the menu */
	do {
		/* Show list of options and ask the user for an option */
		printMaterialMenuOptions();
		option=getMaterialMenuOption();
		
		/* Do the action for the given option */
		if (option == MATERIAL_MENU_LIST ) {
			getMaterials(*appData, &materialTable);
			printMaterialTable(materialTable);
		} else if (option == MATERIAL_MENU_ADD) {
			printf("Enter the information for the new material:\n");
			readMaterial(&newMaterial,&retVal);
			getMaterialStr(newMaterial, MAX_LINE, materialStr);
			if(retVal==OK) {
				addMaterial(appData, newMaterial, &retVal);
				if(retVal==OK){
					printf("Material added: %s\n", materialStr);
				} else if(retVal==ERR_DUPLICATED_ENTRY) {
					printf("Duplicated material not added: %s\n", materialStr);
				} else {
					printf("No more space. Material not added: %s\n", materialStr);
				}
			} else {
				printf("Error in input. Material not added: %s\n", materialStr);
			}
		} else if (option == MATERIAL_MENU_DEL) {
			getMaterials(*appData, &materialTable);			
			/* Print the materials */			
			printMaterialTable(materialTable);		

			if (materialTable.nMaterials > 0) {
				/* Ask the number of the register to be removed */
				printf("Enter the number of the material to delete:\n");
				pos=getOption(materialTable.nMaterials);
				/* Remove the selected material */				
				removeMaterial(appData, materialTable.table[pos-1]);
			}
		} else if (option == MATERIAL_MENU_CLEAR_ALL) {
			getMaterials(*appData, &materialTable);	
			for (i= materialTable.nMaterials-1; i >= 0; i--) {
				/* Remove the material */				
				removeMaterial(appData, materialTable.table[i]);
			}
		} else if (option == MATERIAL_MENU_MATERIALS_BY_TYPE) {
            


			printf("Material Type (integer value being 0=CONCRETE, 1=GLASS, 2=WOOD, 3=BRICK, 4=TUBES, 5=ALUMINUM, 6=SAND, 7=FOAM, 8=PLADUR, 9=TILES, 10=INSULATION, 11=GAS, 12=WATER, 13=OTHERS):\n");
			scanf("%d",&materialType);			
			getMaterials(*appData, &materialTable);
			materialTableFilterByType(materialTable,(tMaterialType)materialType,&resultTable); 
			printMaterialTable(resultTable);	
			
		} else if (option == MATERIAL_MENU_MATERIALS_BY_WEIGHT_INTERVAL) {
			printf("Enter minimum value for weight interval (kg):\n");
			scanf("%f",&minWeight);
			printf("Enter maximum value for weight interval (kg):\n");
			scanf("%f",&maxWeight);			
			getMaterials(*appData, &materialTable);
			materialTableFilterByWeightInterval(materialTable, minWeight, maxWeight, &resultTable); 
			printMaterialTable(resultTable);	
		}

	} while(option!=MATERIAL_MENU_EXIT);
}

/********************************
 **   TRUCK MANAGEMENT MENU **
********************************/
void printTruckMenuOptions() {
	/* Show menu options */
	printf("=======================\n");
	printf(" Manage trucks\n");
	printf("=======================\n");
	printf("1) List trucks\n");	
	printf("2) Add truck\n");
	printf("3) List by truck type\n");
	printf("4) List trucks allowed to do international transport\n");
	printf("5) Exit\n");	
}

tTruckMenuOptions getTruckMenuOption() {
	/* Convert to the correct type */
	return (tTruckMenuOptions)(getOption(5)-1);
}

void truckMenu(tAppData *appData) {
	tError retVal = OK;
	tTruckMenuOptions option;
	tTruckTable truckTable, propTable, internationalTable;
	tTruck newTruck;
	char truckStr[MAX_LINE];
	int truckType;
			
	/* Start the menu */
	do {
		/* Show list of options and ask the user for an option */
		printTruckMenuOptions();
		option=getTruckMenuOption();
		
		/* Do the action for the given option */
		if (option == TRUCK_MENU_LIST) {
			getTrucks(*appData, &truckTable);
			printTruckTable(truckTable);
		} else if (option == TRUCK_MENU_ADD) {
			readTruck(&newTruck,&retVal);
			getTruckStr(newTruck, MAX_LINE, truckStr);
			if(retVal==OK) {
				addTruck(appData, newTruck, &retVal);
				if(retVal==ERR_DUPLICATED_ENTRY) {
					printf("ERROR: A truck with the same ID already exists\n");
				} else {
					printf("Truck added: %s\n", truckStr);
				}
			} else {
				printf("Error in input. Truck not added: %s\n", truckStr);
			}
		} else if (option == TRUCK_MENU_TRUCKTYPE) {
			getTrucks(*appData, &truckTable);
			printf("Truck type of truck (1 digit being 0=RIGID, 1=COLLAPSIBLE, 2=TRAILER, 3=CONTAINER, 4=CARRIAGE, 5=TANK, 6=REFRIGERATOR, 7=TAULINER, 8=PLATFORM, 9=OTHERS):\n");
			scanf("%d",&truckType);
			trucksTableFilterByTruckType(truckTable, (tTruckType)truckType, &propTable);
			printTruckTable(propTable);
		} else if (option == TRUCK_MENU_INTERNATIONAL) {
			getTrucks(*appData, &truckTable);
			trucksTableGetTrucksInternational(truckTable, &internationalTable);
			printTruckTable(internationalTable);
		}
	} while(option!=TRUCK_MENU_EXIT);	
}


/******************
 **   STAT MENU **
******************/
void printStatMenuOptions() {
	/* Show menu options */
	printf("=======================\n");
	printf(" Stats \n");
	printf("=======================\n");
	printf("1) Get number of fragile materials\n");	
	printf("2) Get max material height\n");	
	printf("3) Get average truck capacity for a type of truck\n");	
	printf("4) Get maximum truck speed\n");	
	printf("5) Exit\n");	
}


tStatMenuOptions getStatMenuOption() {
	/* Convert to the correct type */
	return (tStatMenuOptions)(getOption(5)-1);
}

void statMenu(tAppData appData) {
	tStatMenuOptions option;
	tMaterialTable materialTable;
	tTruckTable truckTable;
	float maxHeight;
    int truckType, numFragileMaterials;
	
	/* Start the menu */
	do {
		/* Show list of options and ask the user for an option */
		printStatMenuOptions();
		option=getStatMenuOption();
		
		/* Do the action for the given option */
		if (option == STAT_MENU_NUM_FRAGILE_MATERIALS) {			
			getMaterials(appData, &materialTable);
			numFragileMaterials= materialTableGetNumberOfFragileMaterials(materialTable); 
			printf("Number of fragile materials: %d\n", numFragileMaterials);

		} else if (option == STAT_MENU_MAX_HEIGHT) {
			getMaterials(appData, &materialTable);
			maxHeight= materialTableGetMaxMaterialHeight(materialTable); 
			printf("Maximum height for a material is: %.2f m\n", maxHeight);
		
		} else if (option == STAT_MENU_AVG_CAPACITY) {
			getTrucks(appData, &truckTable);
			printf("Truck type of truck (1 digit being 0=RIGID, 1=COLLAPSIBLE, 2=TRAILER, 3=CONTAINER, 4=CARRIAGE, 5=TANK, 6=REFRIGERATOR, 7=TAULINER, 8=PLATFORM, 9=OTHERS):\n");
			scanf("%d",&truckType);
			printf("Average capacity by truck type: %.2f m3\n", truckTableGetAverageCapacityByTruckType(truckTable,(tTruckType)truckType));
		} else if (option == STAT_MENU_MAX_TRUCK_SPEED) {
			getTrucks(appData, &truckTable);
			printf("Maximum speed: %.2f km/h\n", truckTableGetMaxTruckSpeed(truckTable));
		} 
		
	} while(option!=STAT_MENU_EXIT);	
}
