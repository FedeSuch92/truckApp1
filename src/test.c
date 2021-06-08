#include <stdio.h>
#include <string.h>
#include <math.h>
#include "test.h"
#include "material.h"
#include "truck.h"
#include "stack.h"
#include "location.h"

#define MATERIAL1 "10 WALL 8 0.25 25.00 0.50 0.60 3 0 0"
#define MATERIAL2 "11 ASBESTOS 13 5.00 20.00 0.40 0.40 2 0 1"
#define MATERIAL3 "05 PVC 4 10.50 200.00 0.80 2.00 0 0 0"
#define MATERIAL4 "15 WINDOW 3 30.00 250.00 1.00 2.00 0 1 0"
#define MATERIAL5 "16 GAS 13 3.00 15.00 0.40 1.00 3 0 1"
#define MATERIAL6 "06 BEAM 2 2.50 30.00 0.20 0.50 0 0 0"

#define TRUCK1 "10 IVECO DAILY 2017 0 5 900.00 1 1.50 15.00 180.00"
#define TRUCK2 "11 IVECO TRAKKER 2015 1 8 1200.00 0 2.00 12.00 190.00"
#define TRUCK3 "5 ISUZU DMAX 2015 0 7 125.00 1 1.00 13.00 170.00"
#define TRUCK4 "15 VOLVO FH16 2018 2 6 225.00 0 1.50 15.00 175.00"
#define TRUCK5 "16 VOLVO FMX 2016 3 5 100.00 1 2.00 10.00 185.00"
#define TRUCK6 "6 ISUZU N60B 2018 3 5 100.00 1 2.00 10.00 190.00"

#define LOADED_TRUCK1 "10 06 100"
#define LOADED_TRUCK2 "11 16 150"
#define LOADED_TRUCK3 "5 15 200"
#define LOADED_TRUCK4 "15 05 250"
#define LOADED_TRUCK5 "16 11 300"
#define LOADED_TRUCK6 "6 10 350"

#define WAREHOUSE_1 "2 10 150 5 100"

#define ACCESS_ROAD_STACK1 "2 11 -1 0 10 -1 0"
#define ACCESS_ROAD_STACK2 "0"
#define ACCESS_ROAD_STACK3 "1 5 15 50"
#define ACCESS_ROAD_STACK4 "1 5 10 50"

void runTests() {	
	int passedTestPR2=0;
	int totalTestPR2=0;

	printf("=================================================\n");
	printf("====       PRACTICAL ACTIVITY 2 TESTS        ====\n");
	printf("=================================================\n");	
	runTestsPR2(&totalTestPR2, &passedTestPR2);   
        
	printf("===================================\n");
	printf("====       TEST SUMMARY        ====\n");
	printf("===================================\n");
    if (totalTestPR2 > 0)
        printf("\tPR2: Passed %d of %d [%0.2f%%]\n", passedTestPR2, totalTestPR2, (float)passedTestPR2/totalTestPR2*100.0);
    printf("===================================\n");		
}

void runTestsPR2(int* totalTest, int* passedTest)
{
	*totalTest=0;
	*passedTest=0;

	/* Exercise 1 */
	testInit(totalTest, passedTest);
	testPush(totalTest, passedTest);
	testTop(totalTest, passedTest);
	testPop(totalTest, passedTest);
	testEmpty(totalTest, passedTest);
	testFull(totalTest, passedTest);
    testInvert(totalTest, passedTest);
	testStackPersistence(totalTest, passedTest);

	/* Exercise 2 */
	testCheckStocks(totalTest, passedTest);
    testSearchTruck(totalTest, passedTest);
    testLoadTruck(totalTest, passedTest);
    testTruckTransport(totalTest, passedTest);    
    testUnloadTruck(totalTest, passedTest);  
}

void testInit(int *totalTest, int *passedTest) 
{	
	tTruckStack s;

	printf("=================================================\n");
	printf(" STACK INIT (Exercise 1A)\n");
	printf("=================================================\n");

	printf("\nTest 1A.1: Initialization");
	(*totalTest)++;
	truckStackCreate(&s);

    if (s.nElem==0) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
}

void testTop(int *totalTest, int *passedTest) 
{	
	tTruckStack s;
	tLoadedTruck t1, t2, t3;

	printf("=================================================\n");
	printf(" STACK TOP (Exercise 1C)\n");
	printf("=================================================\n");

	printf("\nTest 1C.1: Top of a one element stack");
	(*totalTest)++;

	s.nElem=0;
	getLoadedTruckObject(LOADED_TRUCK1,&t1);
	loadedTruckCpy(&(s.table[0]),t1);

	s.nElem=1;
	t2 = truckStackTop(s);

    if (loadedTruckCmp(t1,t2)==0 && loadedTruckCmp(s.table[0],t2)==0) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}

	printf("\nTest 1C.2: Top of a two element stack");
	(*totalTest)++;
	getLoadedTruckObject(LOADED_TRUCK2,&t2);
	loadedTruckCpy(&(s.table[1]),t2);
	s.nElem=2;
	t3 = truckStackTop(s);

    if (loadedTruckCmp(t2,t3)==0 && loadedTruckCmp(s.table[1],t3)==0) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
}

void testEmpty(int *totalTest, int *passedTest) 
{	
	tTruckStack s;

	printf("=================================================\n");
	printf(" STACK EMPTY (Exercise 1E)\n");
	printf("=================================================\n");
	printf("\nTest 1E.1: Check empty (simple)");
    
	(*totalTest)++;
	s.nElem=0;

    if (truckStackEmpty(s)) {
        printf("\n\t-> OK\n");
		(*passedTest)++;

	} else {
		printf("\n\t-> FAIL\n");
	}

	printf("\nTest 1E.2: Check empty (using init)");
	(*totalTest)++;
	truckStackCreate(&s);
    if (truckStackEmpty(s)) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
}

void testFull(int *totalTest, int *passedTest) 
{	
	tTruckStack s;
	tLoadedTruck t;

	int i;
	printf("=================================================\n");
	printf(" STACK FULL (Exercise 1F)\n");
	printf("=================================================\n");

	printf("\nTest 1F.1: Check full (simple)");
	(*totalTest)++;
    
	s.nElem = MAX_TRUCKS_IN_STACK;
    if (truckStackFull(s)) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}

	printf("\nTest 1F.2: Check full (pushing)");
	(*totalTest)++;
	s.nElem=0;
	getLoadedTruckObject(LOADED_TRUCK1,&t);

	for(i=0;i<MAX_TRUCKS_IN_STACK;i++)
		truckStackPush(&s,t);

    if (truckStackFull(s)) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
}

void testInvert(int *totalTest, int *passedTest) 
{	
	tTruckStack s;
	tLoadedTruck t1, t2, t3, t;
	tLoadedTruck tout1, tout2, tout3;

	printf("=================================================\n");
	printf(" STACK INVERT (Exercise 1G)\n");
	printf("=================================================\n");

	printf("\nTest 1G.1: Invert empty stack");
	(*totalTest)++;
    
	truckStackCreate(&s);
    truckStackInvert(&s);
    if (truckStackEmpty(s)) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}

	printf("\nTest 1G.2: Invert non empty stack (odd size)");
	(*totalTest)++;
	getLoadedTruckObject(LOADED_TRUCK1,&t1);
	getLoadedTruckObject(LOADED_TRUCK2,&t2);
	truckStackCreate(&s);
    truckStackPush(&s,t1);
    truckStackPush(&s,t2);
    truckStackInvert(&s);
    t= truckStackTop(s);
    if (loadedTruckCmp(t,t1)==0) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}

	printf("\nTest 1G.3: Invert non empty stack (even size)");
	(*totalTest)++;
	truckStackCreate(&s);
	getLoadedTruckObject(LOADED_TRUCK3,&t3);
    truckStackPush(&s,t1);
    truckStackPush(&s,t2);
    truckStackPush(&s,t3);
    truckStackInvert(&s);
    tout1= truckStackTop(s);
    truckStackPop(&s);
    tout2= truckStackTop(s);
    truckStackPop(&s);
    tout3= truckStackTop(s);
    truckStackPop(&s);
    if (truckStackEmpty(s) && 
        loadedTruckCmp(tout1,t1)==0 &&
        loadedTruckCmp(tout2,t2)==0 &&
        loadedTruckCmp(tout3,t3)==0) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
}

void testPush(int *totalTest, int *passedTest) 
{	
	tTruckStack s;
	tLoadedTruck t, t2;
	int i, prev_size, post_size;
    
	printf("=================================================\n");
	printf(" STACK PUSH (Exercise 1B)\n");
	printf("=================================================\n");

	printf("\nTest 1B.1: Push in empty stack");

	(*totalTest)++;
	truckStackCreate(&s);
	getLoadedTruckObject(LOADED_TRUCK1,&t);
	truckStackPush(&s,t);

    if ( s.nElem==1 && loadedTruckCmp(s.table[0],t)==0) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
    
	printf("\nTest 1B.2: Push in not empty stack");
	(*totalTest)++;
	getLoadedTruckObject(LOADED_TRUCK2,&t2);
	truckStackPush(&s,t2);

    if ( s.nElem==2 && loadedTruckCmp(s.table[1],t2)==0) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
    
	printf("\nTest 1B.3: Push in almost full stack");
	(*totalTest)++;
	truckStackCreate(&s);
	getLoadedTruckObject(LOADED_TRUCK1,&t);

	for(i=0;i<MAX_TRUCKS_IN_STACK;i++)
		truckStackPush(&s,t);

    if (s.nElem==MAX_TRUCKS_IN_STACK && 
        loadedTruckCmp(s.table[MAX_TRUCKS_IN_STACK-1],t)==0) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
    
	printf("\nTest 1B.4: Push in full stack");
	(*totalTest)++;
    prev_size= truckStackSize(s);
    truckStackPush(&s,t);
    post_size= truckStackSize(s);
    if (prev_size == MAX_TRUCKS_IN_STACK && 
        prev_size == post_size) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
}

void testPop(int *totalTest, int *passedTest) 
{	
	tTruckStack s;
	tLoadedTruck t1in, t1out, t2in, t2out;
	int i, prev_size, post_size;
    
	printf("=================================================\n");
	printf(" STACK POP (Exercise 1D)\n");
	printf("=================================================\n");

	printf("\nTest 1D.1: Pop in one element stack");
	(*totalTest)++;

	truckStackCreate(&s);
	getLoadedTruckObject(LOADED_TRUCK1,&t1in);
	truckStackPush(&s,t1in);
	t1out = truckStackTop(s);
	truckStackPop(&s);

    if (s.nElem==0 && loadedTruckCmp(t1in,t1out)==0) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
    
	printf("\nTest 1D.2: Pop in not empty stack");
	(*totalTest)++;
	truckStackCreate(&s);
	getLoadedTruckObject(LOADED_TRUCK1,&t1in);
	getLoadedTruckObject(LOADED_TRUCK2,&t2in);
	truckStackPush(&s,t1in);
	truckStackPush(&s,t2in);
	t1out = truckStackTop(s);
	truckStackPop(&s);

    if (s.nElem==1 && 
        loadedTruckCmp(s.table[0],t1in)==0 && 
        loadedTruckCmp(t2in,t1out)==0) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
    
	printf("\nTest 1D.3: Pop in full stack");
	(*totalTest)++;
	truckStackCreate(&s);
	getLoadedTruckObject(LOADED_TRUCK1,&t1in);
	truckStackPush(&s,t1in);
	getLoadedTruckObject(LOADED_TRUCK2,&t2in);

	for(i=1;i<MAX_TRUCKS_IN_STACK;i++)
		truckStackPush(&s,t2in);

	t1out = truckStackTop(s);
	truckStackPop(&s);

    if (s.nElem==MAX_TRUCKS_IN_STACK-1 && 
        loadedTruckCmp(s.table[MAX_TRUCKS_IN_STACK-2],t2in)==0 && 
        loadedTruckCmp(t2in,t1out)==0) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}

	printf("\nTest 1D.4: Clear a full stack by popping elements");
	(*totalTest)++;
	truckStackCreate(&s);
	getLoadedTruckObject(LOADED_TRUCK1,&t1in);
	truckStackPush(&s,t1in);
	getLoadedTruckObject(LOADED_TRUCK2,&t2in);
	for(i=1;i<MAX_TRUCKS_IN_STACK;i++)
		truckStackPush(&s,t2in);

	t1out = truckStackTop(s);
	truckStackPop(&s);

	for(i=1;i<MAX_TRUCKS_IN_STACK;i++) {
		t2out = truckStackTop(s);
		truckStackPop(&s);
	}
	if ( s.nElem==0 && loadedTruckCmp(t1in,t2out)==0 && loadedTruckCmp(t2in,t1out)==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
    
	printf("\nTest 1D.5: Pop on empty stack");
	(*totalTest)++;
    prev_size= truckStackSize(s);
	truckStackPop(&s);
    post_size= truckStackSize(s);
	if (prev_size==0 && 
        prev_size==post_size) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
}

void testStackPersistence(int *totalTest, int *passedTest) 
{
	tTruckStack stack;
	tLoadedTruck t1, t2;
	tError retVal;

	printf("=================================================\n");
	printf(" PERSISTENCE OF TRUCK STACK (Exercise 1H/I)\n");
	printf("=================================================\n");

	printf("\nTest 1HI.1: Save and load no data");

	(*totalTest)++;
	truckStackCreate(&stack);	
	truckStackSave(stack, "./testtrucks.csv",&retVal);

	truckStackCreate(&stack);	
	truckStackLoad(&stack, "./testtrucks.csv",&retVal);

	if(retVal==OK){

		if(truckStackEmpty(stack)) {
			printf("\n\t-> OK\n");
			(*passedTest)++;

		} else {
			printf("\n\t-> FAIL (unexpected number of registers in the stack. Expected %d and returned %d)\n", 0, stack.nElem);
		}

	} else {
		printf("\n\t-> FAIL (problem in file reading/writing)\n");
	}

	printf("\nTest 1HI.2: Save and load trucks");

	(*totalTest)++;

	getLoadedTruckObject(LOADED_TRUCK1, &t1);
	getLoadedTruckObject(LOADED_TRUCK2, &t2);
    truckStackPush(&stack,t1);
    truckStackPush(&stack,t2);
	truckStackSave(stack, "./testtrucks.csv",&retVal);

	truckStackCreate(&stack);	
	truckStackLoad(&stack, "./testtrucks.csv",&retVal);
	truckStackSave(stack, "./testtrucks2.csv",&retVal);

	if(retVal==OK){

		if(stack.nElem==2) {

			if(loadedTruckCmp(stack.table[1], t2) != 0 || 
			   loadedTruckCmp(stack.table[0], t1) != 0) {
				printf("\n\t-> FAIL (Values are not correct)\n");
			} else {
				printf("\n\t-> OK\n");
				(*passedTest)++;
			}

		} else {
			printf("\n\t-> FAIL (unexpected number of registers in the stack. Expected %d and returned %d)\n", 2, stack.nElem);
		}

	} else {
		printf("\n\t-> FAIL (problem in file reading/writing)\n");
	}
}

void testCheckStocks(int *totalTest, int *passedTest) {
	
	bool result;
	tWareHouse wh;
	tMaterial material;
	
	printf("========================================\n");
	printf(" CHECK WAREHOUSE STOCKS (Exercise 2A.1) \n");
	printf("========================================\n");

	getMaterialObject(MATERIAL1,&material);

	printf("\nTest 2A1.1: Check stock on an empty warehouse");
	(*totalTest)++;
	warehouseCleanAllStocks(&wh);
	result= checkStockAtOrigin(wh, material, 10);
	if (!result) {
			printf("\n\t-> OK\n");
			(*passedTest)++;
	}
	else {
			printf("\n\t-> FAIL (Good found on an empty warehouse)\n");
	}

	getWareHouseObject(WAREHOUSE_1, &wh);
	
	printf("\nTest 2A1.2: Check enough stock of existing material on non-empty warehouse");
	(*totalTest)++;
	result= checkStockAtOrigin(wh, material, 150);
	if (result) {
			printf("\n\t-> OK\n");
			(*passedTest)++;
	}
	else {
			printf("\n\t-> FAIL (Returned \"enough stock\", \"not enough\" expected)\n");
	}
	
	printf("\nTest 2A1.3: Check not enough stock of existing material on non-empty warehouse");
	(*totalTest)++;
	result= checkStockAtOrigin(wh, material, 151);
	if (!result) {
			printf("\n\t-> OK\n");
			(*passedTest)++;
	}
	else {
			printf("\n\t-> FAIL (Returned \"enough stock\", \"not enough\" expected)\n");
	}
	
	printf("\nTest 2A1.4: Check stock of non-existing material on non-empty warehouse");
	(*totalTest)++;
	material.id= 90;
	result= checkStockAtOrigin(wh, material, 5);
	if (!result) {
			printf("\n\t-> OK\n");
			(*passedTest)++;
	}
	else {
			printf("\n\t-> FAIL (Returned \"enough stock\" for a non-existing material)\n");
	}
	
	printf("\nTest 2A1.5: Check null-stock of non-existing material on non-empty warehouse");
	(*totalTest)++;
	material.id= 90;
	result= checkStockAtOrigin(wh, material, 0);
	if (result) {
			printf("\n\t-> OK\n");
			(*passedTest)++;
	}
	else {
			printf("\n\t-> FAIL (Returned \"not enough stock\" when asked for a quantity of 0)\n");
	}
}

void testSearchTruck(int *totalTest, int *passedTest)
{
    tTruckStack accessRoad, maneuveringTrack;
    tTruckTable table;
    tTruck truck1, truck2;
    tMaterial material1, material2, material3, material4;
 	char str[MAX_LINE];
    bool result;
    tError retVal;

    /* Initialize structures */
    trucksTableInit(&table);
    truckStackCreate(&accessRoad);
    truckStackCreate(&maneuveringTrack);

    /* Load materials */
    getMaterialObject(MATERIAL1,&material1); /* Volume = 0.6 m3 per unit */
    getMaterialObject(MATERIAL2,&material2); /* Volume = 0.4 m3 per unit */
    getMaterialObject(MATERIAL3,&material3); /* Volume = 2.0 m3 per unit */
    getMaterialObject(MATERIAL4,&material4); /* Volume = 2.0 m3 per unit */

    /* Load trucks */
    getTruckObject(TRUCK1, &truck1); /* Capacity = 5 wagons x 200.0 = 1000.0 m3 */
    getTruckObject(TRUCK2, &truck2); /* Capacity = 8 wagons x 150.0 = 1200.0 m3 */
    trucksTableAdd(&table,truck1,&retVal); 
    trucksTableAdd(&table,truck2,&retVal); 

	printf("=======================================\n");
	printf(" SUITABLE TRUCK SEARCH (Exercise 2A.2) \n");
	printf("=======================================\n");
    
	printf("\nTest 2A2.1: Search truck on empty access road and empty maneuver track");
	(*totalTest)++;
	result= searchTruckAtOrigin(table,&accessRoad,&maneuveringTrack,material1,1);
	if (!result) {
			printf("\n\t-> OK\n");
			(*passedTest)++;
	}
	else {
			printf("\n\t-> FAIL (truck found on an empty station)\n");
	}
        
    /* truck1 at top and truck2 at bottom of main platform; maneuveringTrack empty */
    getStackObject(ACCESS_ROAD_STACK1,&accessRoad);
    getStackObject(ACCESS_ROAD_STACK2,&maneuveringTrack);
    
	printf("\nTest 2A2.2: Search truck: Success at first attempt (stack remains the same)");
	(*totalTest)++;
	result= searchTruckAtOrigin(table,&accessRoad,&maneuveringTrack,material3,450);
	if (result) {
            getStackStr(accessRoad,MAX_LINE,str);
            if (strcmp(ACCESS_ROAD_STACK1,str)==0) {
                printf("\n\t-> OK\n");
                (*passedTest)++;                
            }
            else
                printf("\n\t-> FAIL (truck stack changed)\n");
	}
	else {
			printf("\n\t-> FAIL (truck not found)\n");
	}

    getStackObject(ACCESS_ROAD_STACK1,&accessRoad);
    getStackObject(ACCESS_ROAD_STACK2,&maneuveringTrack);

	printf("\nTest 2A2.3: Search truck: Success at second attempt");
	(*totalTest)++;
	result= searchTruckAtOrigin(table,&accessRoad,&maneuveringTrack,material3,550);
	if (result) {
            result= (truckStackSize(accessRoad) == 1 && 
                     truckStackSize(maneuveringTrack) == 1 &&
                     truckStackTop(accessRoad).id == 11 &&
                     truckStackTop(maneuveringTrack).id == 10);
            if (result) {
                printf("\n\t-> OK\n");
                (*passedTest)++;                
            }
            else
                printf("\n\t-> FAIL (truck stack configuration different than expected)\n");
	}
	else {
			printf("\n\t-> FAIL (truck not found)\n");
	}

    getStackObject(ACCESS_ROAD_STACK1,&accessRoad);
    getStackObject(ACCESS_ROAD_STACK2,&maneuveringTrack);

	printf("\nTest 2A2.4: Search truck: No success (stack remains the same)");
	(*totalTest)++;
	result= searchTruckAtOrigin(table,&accessRoad,&maneuveringTrack,material3,650);
	if (!result) {
            getStackStr(accessRoad,MAX_LINE,str);
            if (strcmp(ACCESS_ROAD_STACK1,str)==0) {
                printf("\n\t-> OK\n");
                (*passedTest)++;                
            }
            else
                printf("\n\t-> FAIL (truck stack changed)\n");
	}
	else {
			printf("\n\t-> FAIL (truck not found)\n");
	}
    
    getStackObject(ACCESS_ROAD_STACK1,&maneuveringTrack);
    getStackObject(ACCESS_ROAD_STACK2,&accessRoad);

	printf("\nTest 2A2.5: Search truck: No success (maneuveringTrack moves to main platform)");
	(*totalTest)++;
	result= searchTruckAtOrigin(table,&accessRoad,&maneuveringTrack,material3,700);
	if (!result) {
            result= (truckStackSize(accessRoad) == 2 && 
                     truckStackSize(maneuveringTrack) == 0 &&
                     truckStackTop(accessRoad).id == 11);
            if (result) {
                printf("\n\t-> OK\n");
                (*passedTest)++;                
            }
            else
                printf("\n\t-> FAIL (truck stack configuration different than expected)\n");
	}
	else {
			printf("\n\t-> FAIL (truck not found)\n");
	}
    
	printf("\nTest 2A2.6: Search truck: Success (empty main platform, suitable truck at top of maneuveringTrack)");
	(*totalTest)++;
    getStackObject(ACCESS_ROAD_STACK1,&maneuveringTrack);
    getStackObject(ACCESS_ROAD_STACK2,&accessRoad);
	result= searchTruckAtOrigin(table,&accessRoad,&maneuveringTrack,material3,450);
	if (result) {
            result= (truckStackSize(accessRoad) == 1 && 
                     truckStackSize(maneuveringTrack) == 1);
            if (result) {
                printf("\n\t-> OK\n");
                (*passedTest)++;                
            }
            else
                printf("\n\t-> FAIL (truck stack configuration different than expected)\n");
	}
	else {
			printf("\n\t-> FAIL (truck not found)\n");
	}
}

void testLoadTruck(int *totalTest, int *passedTest) 
{
    tTruckStack accessRoad;
    bool result;
    tWareHouse wh;
    tMaterial material;
    
    truckStackCreate(&accessRoad);
	warehouseCleanAllStocks(&wh);
	getMaterialObject(MATERIAL1,&material); /* id = 10 */

	printf("=======================================\n");
	printf(" LOADING TRUCK (Exercise 2A.3) \n");
	printf("=======================================\n");
    
	printf("\nTest 2A3.1: Try to load a non-existing truck of an empty platform");
	(*totalTest)++;
	loadTruck(&accessRoad,&wh,material,100);
    result= truckStackEmpty(accessRoad) &&
            warehouseGetStock(material.id,wh) == 0;
	if (result) {
			printf("\n\t-> OK\n");
			(*passedTest)++;
	}
	else {
			printf("\n\t-> FAIL (Loading performed on non-existing truck and empty warehouse)\n");
	}

    getWareHouseObject(WAREHOUSE_1,&wh); /* Initial stock for material 10 is 150 */
    getStackObject(ACCESS_ROAD_STACK1,&accessRoad); /* Two trucks on main platform */

	printf("\nTest 2A3.2: Try to load a truck with existing materials");
	(*totalTest)++;
	loadTruck(&accessRoad,&wh,material,100);
    result= (truckStackSize(accessRoad) == 2 &&
             truckStackTop(accessRoad).load.id == 10 &&
             truckStackTop(accessRoad).load.qtt == 100 &&
             warehouseGetStock(material.id,wh) == 50);
	if (result) {
        printf("\n\t-> OK\n");
        (*passedTest)++;                
	}
	else {
            printf("\n\t-> FAIL (truck not properly loaded)\n");
	}
}

void testTruckTransport(int *totalTest, int *passedTest)  
{
    tTruckStack origin, destination;

    truckStackCreate(&origin);
    truckStackCreate(&destination);

	printf("=====================================\n");
	printf(" TRUCKS TRANSPORTATION (Exercise 2B) \n");
	printf("=====================================\n");
    
	printf("\nTest 2B.1: Try to load a non-existing truck of an empty platform");
	(*totalTest)++;
    moveTruckFromOriginToDestination(&origin, &destination);
    if (truckStackEmpty(origin) && 
        truckStackEmpty(destination)) {
            printf("\n\t-> OK\n");
            (*passedTest)++;                
    }
    else
    {
            printf("\n\t-> FAIL (Not able to transport materials if no trucks at origin)\n");
    }
    
    getStackObject(ACCESS_ROAD_STACK1,&origin); /* Two trucks on main platform at origin (none at destination) */

	printf("\nTest 2B.2: Try to move materials from an origin platform to a destination platform");
	(*totalTest)++;
    moveTruckFromOriginToDestination(&origin, &destination);
    if (truckStackSize(origin) == 1 && 
        truckStackSize(destination) == 1) {
            printf("\n\t-> OK\n");
            (*passedTest)++;                
    }
    else
    {
            printf("\n\t-> FAIL (Wrong transportation)\n");
    }
    
	printf("\nTest 2B.3: Keep moving materials until origin becomes empty");
	(*totalTest)++;
    moveTruckFromOriginToDestination(&origin, &destination);
    if (truckStackSize(origin) == 0 && 
        truckStackSize(destination) == 2) {
            printf("\n\t-> OK\n");
            (*passedTest)++;                
    }
    else
    {
            printf("\n\t-> FAIL (Wrong transportation)\n");
    }
}

void testUnloadTruck(int *totalTest, int *passedTest) {
        
    tTruckStack accessRoad;
    bool result;
    tWareHouse wh;
    tMaterial material;
    
    truckStackCreate(&accessRoad);
	warehouseCleanAllStocks(&wh);
	getMaterialObject(MATERIAL1,&material); /* id = 10 */

	printf("=======================================\n");
	printf(" UNLOADING TRUCK (Exercise 2C) \n");
	printf("=======================================\n");

	printf("\nTest 2C.1: Try to unload a non-existing truck of an empty platform");
	(*totalTest)++;
	unloadTruckAtDestination(&accessRoad,&wh);
    result= truckStackEmpty(accessRoad) && 
            warehouseGetNumberOfMaterials(wh) == 0;
	if (result) {
			printf("\n\t-> OK\n");
			(*passedTest)++;
	}
	else {
			printf("\n\t-> FAIL (Wrong unload process)\n");
	}

    getStackObject(ACCESS_ROAD_STACK3,&accessRoad); 

	printf("\nTest 2C.2: Try to unload an existing truck (previously non-existing material)");
	(*totalTest)++;
	unloadTruckAtDestination(&accessRoad,&wh);
    result= truckStackSize(accessRoad) == 1 &&
            truckStackTop(accessRoad).id == 5 &&
            truckStackTop(accessRoad).load.id == NO_MATERIAL &&
            truckStackTop(accessRoad).load.qtt == 0 &&
            warehouseGetStock(15,wh) == 50; 
	if (result) {
			printf("\n\t-> OK\n");
			(*passedTest)++;
	}
	else {
			printf("\n\t-> FAIL (Stocks do not match)\n");
	}

    getStackObject(ACCESS_ROAD_STACK4,&accessRoad);
	getWareHouseObject(WAREHOUSE_1, &wh);

	printf("\nTest 2C.3: Try to unload an existing truck (previously existing material)");
	(*totalTest)++;
	unloadTruckAtDestination(&accessRoad,&wh);
    result= truckStackSize(accessRoad) == 1 &&
            truckStackTop(accessRoad).id == 5 &&
            truckStackTop(accessRoad).load.id == NO_MATERIAL &&
            truckStackTop(accessRoad).load.qtt == 0 &&
            warehouseGetStock(10,wh) == 200; 
	if (result) {
			printf("\n\t-> OK\n");
			(*passedTest)++;
	}
	else {
			printf("\n\t-> FAIL (Stocks do not match)\n");
	}
}

