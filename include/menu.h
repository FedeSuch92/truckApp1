#include "data.h"
#include "api.h"

/* Request an option to the user and check its validity */
int getOption(int numOptions);

/* Define the main menu options type */
typedef enum {MAIN_MENU_LOAD, MAIN_MENU_SAVE, MAIN_MENU_MATERIAL, 
              MAIN_MENU_TRUCK, MAIN_MENU_STAT,
              MAIN_MENU_EXIT} tMainMenuOptions;

/* Define the materials management menu options type */
typedef enum {MATERIAL_MENU_LIST, MATERIAL_MENU_ADD, MATERIAL_MENU_DEL, 
              MATERIAL_MENU_CLEAR_ALL, MATERIAL_MENU_MATERIALS_BY_TYPE,
			  MATERIAL_MENU_MATERIALS_BY_WEIGHT_INTERVAL,
              MATERIAL_MENU_EXIT} tMaterialMenuOptions;

/* Define the trucks management menu options type */
typedef enum {TRUCK_MENU_LIST, TRUCK_MENU_ADD, TRUCK_MENU_TRUCKTYPE, TRUCK_MENU_INTERNATIONAL,
              TRUCK_MENU_EXIT} tTruckMenuOptions;

/* Define the status menu options type */
typedef enum {STAT_MENU_NUM_FRAGILE_MATERIALS,  STAT_MENU_MAX_HEIGHT,
			  STAT_MENU_AVG_CAPACITY, STAT_MENU_MAX_TRUCK_SPEED,
              STAT_MENU_EXIT} tStatMenuOptions;

/* Print the main menu options */
void printMainMenuOptions();

/* Get the option for the main menu */
tMainMenuOptions getMenuOption();

/* Perform the actions for the main menu */
void mainMenu(tAppData *appData);

/* Print the material management menu options */
void printMaterialMenuOptions();

/* Get the option for the material management menu */
tMaterialMenuOptions getMaterialMenuOption();

/* Perform the actions for the material management menu */
void materialMenu(tAppData *appData);

/* Print the trucks management menu options */
void printTruckMenuOptions();

/* Get the option for the trucks management menu */
tTruckMenuOptions getTruckMenuOption();

/* Perform the actions for the trucks management menu */
void truckMenu(tAppData *appData);

/* Print the stats menu options */
void printStatMenuOptions();

/* Get the option for the status menu */
tStatMenuOptions getStatMenuOption();

/* Perform the actions for the status menu */
void statMenu(tAppData appData);
