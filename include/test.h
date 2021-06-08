/* Run all the test set */
#include "data.h"
#include "api.h"

/* Runs the applications tests */
void runTests();

/* Runs the applications tests corresponding to PR2 */
void runTestsPR2(int* totalTest, int* passedTest);

/* Test stack initialization */
void testInit(int *totalTest, int *passedTest);

/* Test stack push of elements */
void testPush(int *totalTest, int *passedTest);

/* Test stack pop of elements */
void testPop(int *totalTest, int *passedTest);

/* Test stack top */
void testTop(int *totalTest, int *passedTest);

/* Test stack empty checking */
void testEmpty(int *totalTest, int *passedTest);

/* Test stack full checking */
void testFull(int *totalTest, int *passedTest);

/* Test stack inversion */
void testInvert(int *totalTest, int *passedTest);

/* Test the stack data persistence */
void testStackPersistence(int *totalTest, int *passedTest);

/* Test the warehouse stock checking */
void testCheckStocks(int *totalTest, int *passedTest);

/* Test the search truck on access road and maneuver track */
void testSearchTruck(int *totalTest, int *passedTest);

/* Test the truck loading of materials */
void testLoadTruck(int *totalTest, int *passedTest);

/* Test the truck transportation */
void testTruckTransport(int *totalTest, int *passedTest);

/* Test the truck unloading of materials */
void testUnloadTruck(int *totalTest, int *passedTest);
