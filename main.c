//
//  main.c
//  Homework4
//
//  Created by Mohib Kohi on 5/20/16.
//  Copyright © 2016 Mohib Kohi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "Client.h"
#include "arraylist.h"
#include "houses.h"


int compare(int*, int*);
void printItem(void*);
ListType readClients();
void addPreferrences(ListType* clientList);
ListType readHousesAndTitle(char title[][100]);
void writeClients(ListType clientList, ListType houseList, char title[][100]);
void writeHouses(ListType clientList, ListType houseList, char title[][100]);

/**
 * Main runs the program.
 * Calls five functions to carry out
 * file reading and writing.
 */
int main() {
    ListType clientList, houseList;
    
    char title[8][100];
    
    clientList = readClients();
    
    addPreferrences(&clientList);
    
    houseList = readHousesAndTitle(title);
    
    writeClients(clientList, houseList, title);
    writeHouses(clientList, houseList, title);
    
    destroy(houseList);
    destroy(clientList);
    return 0;
}

/**
 * ReadClients reads client txt file
 * and creats clients.
 */
ListType readClients() {
    FILE *fptr;
    ListType list;
    //temp 2d array.
    char temp[5][40];
    int count;
    
    //Client pointer to id struct
    struct id_st* clientptr;
    
    //pointer to clients txt file to read and store.
    fptr = fopen("clients.txt", "r");
    
    //create pointer to struct id.
    list = create(sizeof(struct id_st), NULL);
    //while file pointer is not null and there is text to be red.
    count = 0;
    if (fptr != NULL) {
        while (!feof(fptr)) {
            //store text inside t
            fgets(temp[count++], 10, fptr);
            fgets(temp[count++], 40, fptr);
            fgets(temp[count++], 40, fptr);
            fgets(temp[count++], 40, fptr);
            fgets(temp[count++], 40, fptr);
            
            //create client fromt temp info.
            clientptr = createClient(temp);
            createIdClient(clientptr, temp);
            
            count = 0;
            //push the cllient iside the arraylist.
            push(list,clientptr);
            //free client pointer.
            free(clientptr);
        }
    }
    
    clientptr  = NULL;
    fclose(fptr);
    return list;
}

/**
 * ReadClients reads preferences txt file
 * and updates clients.
 * Takes in parameters arraylist pointer.
 */
void addPreferrences(ListType* clientList) {
    int i = 0;
    struct id_st*  client;
    FILE *fptr;
    char newid[10];
    char preferences[5][40];
    //pointer to clients txt file to read and store.
    fptr = fopen("preferences.txt", "r");
    
    //while file pointer is not null and there is text to be red.
    if (fptr != NULL) {
        while (!feof(fptr)) {
            //read text file and match with arraylist elements.
            fgets(newid, 10, fptr);
            do{
                client = get(*clientList, i++);
            } while(strncmp(client->id, newid, 4) != 0);
            
            i = 0;
            //scan the file
            fscanf(fptr, "%s %s %s %s", preferences[0], preferences[1], preferences[2], preferences[3]);
            //assign client preferences
            assignPreference(client, preferences);
            //skip to next line.
            fgets(newid, 10, fptr);
        }
    }
    fclose(fptr);
    fptr = NULL;
}


/**
 * eeadHousesAndTitle reads houses txt file.
 * Takes in parameters 2d arraylist.
 */
ListType readHousesAndTitle(char title[][100]) {
    
    //Arraylist opbject.
    ListType houseList;
    char house[8][100];
    char newid[10];
    FILE *fptr;
    //house struct object.
    houses houseptr;
    
    //create an arraylist.
    houseList = create(sizeof(struct houses_st), NULL);
    
    fptr = fopen("houses.csv", "r");
    
    //while file pointer is not null and there is text to be red.
    if (fptr != NULL) {
        while (!feof(fptr)) {
            if(strlen(title[0]) == 0) {
                //read in the title.
                fscanf(fptr, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,\r]",
                       title[0], title[1], title[2], title[3], title[4], title[5], title[6], title[7]);
            } else {
                //read in elements seprated by comma.
                fscanf(fptr, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,\r]",
                       house[0], house[1], house[2], house[3], house[4], house[5], house[6], house[7]);
                //create the house.
                houseptr = createHouse(house);
                //push the house into the houseList.
                push(houseList, houseptr);
                //free the house pointer.
                free(houseptr);
            }
            //skip to next line.
            fgets(newid, 10, fptr);
        }
    }
    houseptr = NULL;
    fclose(fptr);
    fptr = NULL;
    return houseList;
}

/**
 * writeClients takes in parameters two lists and the title to compare and write the
 * matched houses for each client.
 */
void writeClients(ListType clientList, ListType houseList, char title[][100]) {
    int k;
    int i;
    //boolean to add the title.
    int boolean = 0;
    //boolean if no match was found.
    int oneMatch = 0;
    
    //create a pointer to the file to write.
    FILE* wptr = fopen("clientsView.csv", "w");
    
    //write to the file.
    fprintf(wptr, "%s,%s,%s,,,", "Client ID", "Name", "Phone Number");
    fprintf(wptr, "%s,%s,%s,%s,%s,%s,%s,%s\n", title[0], title[1], title[2], title[3], title[4],
            title[5], title[6], title[7]);
    
    //keep searching for all the clients.
    for (i = 0; i < size_is(clientList); i++) {
        //get the client to compare with house.
        struct id_st*  cl = get(clientList, i);
        
        boolean = 1;
        for (k = 0; k < size_is(houseList); k++) {
            //get the house to compare with client.
            houses house = get(houseList, k);
            
            //if the client preference matches with house preference.
            if (house->max_price <= cl->preference.max_price &&
                house->min_bedrooms >= cl->preference.min_bedrooms &&
                house->min_bathrooms >= cl->preference.min_bathrooms &&
                house->min_footage >= cl->preference.min_footage) {
                if (boolean == 0) {
                    fprintf(wptr, ",,,,,");
                } else {
                    fprintf(wptr, "%.4s,%s,%s,,,", cl->id, cl->address.name, cl->address.phone_number);
                }
                fprintf(wptr, "%s,%s,%s,%s,%lu,%lu,%lu,%lu\n", house->mls, house->street_address,
                        house->city, house->zip, house->min_bedrooms, house->min_bathrooms,
                        house->min_footage,house->max_price);
                boolean = 0;
                oneMatch = 1;
            }
        }
    }
    
    if (oneMatch == 0) {
        fprintf(wptr, "%s", "No match");
    }
    fclose(wptr);
}

/**
 * writeHouses takes in parameters two lists and the title to compare and write the
 * matched clients for each house.
 */
void writeHouses(ListType clientList, ListType houseList, char title[][100]) {
    
    int k;
    int i;
    //boolean to add the title.
    int boolean = 0;
    //create a pointer to the file to write.
    int oneMatch = 0;
    
    //create a pointer to the file to write.
    FILE* wptr = fopen("houseView.csv", "w");
    
    //write to the file.
    fprintf(wptr, "%s,%s,%s,%s,%s,%s,%s,%s,,", title[0], title[1], title[2], title[3], title[4],
            title[5], title[6], title[7]);
    fprintf(wptr, "%s,%s,%s\n", "Client ID", "Name", "Phone Number");
    
    //keep searching for all the houses.
    for (k = 0; k < size_is(houseList); k++) {
        //get the house to compare with client.
        houses house = get(houseList, k);
        boolean = 1;
        
        for (i = 0; i < size_is(clientList); i++) {
            
            //get the house to compare with client.
            struct id_st*  cl = get(clientList, i);
            if (house->max_price <= cl->preference.max_price &&
                house->min_bedrooms >= cl->preference.min_bedrooms &&
                house->min_bathrooms >= cl->preference.min_bathrooms &&
                house->min_footage >= cl->preference.min_footage) {
                if (boolean == 0) {
                    fprintf(wptr, ",,,,,,,,,");
                } else {
                    fprintf(wptr, "%s,%s,%s,%s,%lu,%lu,%lu,%lu,,", house->mls, house->street_address,
                            house->city, house->zip, house->min_bedrooms, house->min_bathrooms,
                            house->min_footage,house->max_price);
                }
                
                fprintf(wptr, "%.4s,%s,%s\n", cl->id, cl->address.name, cl->address.phone_number);
                
                boolean = 0;
                oneMatch = 1;
            }
        }
    }
    
    if (oneMatch == 0) {
        fprintf(wptr, "%s", "No match");
    }
    fclose(wptr);

}


/**
 * compare method.
 */
int compare(int *a, int *b) {
    short int toReturn = 0;
    if (*a < *b)
        toReturn = -1;
    else if (*a > *b)
        toReturn = 1;
    
    return toReturn;
}
