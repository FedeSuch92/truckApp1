#include "data.h"

/* Get a textual representation of a delivery */
void getDeliveryStr(tDelivery delivery, int maxSize, char *str);

/* Get a delivery object from its textual representation */
void getDeliveryObject(const char *str, tDelivery *delivery);

/* Copy the delivery data in src to dst*/
void deliveryCpy(tDelivery *dst, tDelivery src);

/* Compares the delivery data of p1 and p2*/
int deliveryCmp(tDelivery p1, tDelivery p2);

/* Initializes the given deliveries table */
void deliveriesTableInit(tDeliveryTable *deliveriesTable);

/* Add a new delivery to the table of deliveries */
void deliveriesTableAdd(tDeliveryTable *tabDeliveries, tDelivery delivery, tError *retVal);

/* Find a delivery in the table */
int deliveriesTableFind(tDeliveryTable tabDeliveries, tDeliveryId delivery);

/* Cleans the given deliveries table */
void deliveriesTableClean(tDeliveryTable *deliveriesTable);

/* Load the table of deliveries from a file */
void deliveriesTableLoad(tDeliveryTable *tabDeliveries, const char* filename, tError *retVal);

/* Save a table of deliveries to a file */
void deliveriesTableSave(tDeliveryTable tabDeliveries, const char* filename, tError *retVal);
