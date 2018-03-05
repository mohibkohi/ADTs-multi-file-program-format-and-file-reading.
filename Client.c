//
//  Client.c
//  Homework4
//
//  Created by Mohib Kohi on 5/20/16.
//  Copyright © 2016 Mohib Kohi. All rights reserved.
//

#include "Client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

/**
 * Function takes 2d array updates struct fields.
 * returns pointer to the id struct.
 */
struct id_st* createClient(char info[5][40]) {
    
    struct id_st* client_ptr = (struct id_st*) malloc(sizeof (struct id_st));
    strncpy(client_ptr->id, info[0], strlen(info[0]) - 2);
    return client_ptr;
}

/**
 * Function takes 2d array updates struct fields.
 */
void assignPreference(struct id_st* client_id, char info[4][40]) {
    char *ptr;
    
    client_id->preference.min_bedrooms = strtol(info[0], &ptr, 10);
    client_id->preference.min_bathrooms = strtol(info[1], &ptr, 10);
    client_id->preference.min_footage = strtol(info[2], &ptr, 10);
    client_id->preference.max_price = strtol(info[3], &ptr, 10);
}

/**
 * Function takes 2d array updates struct fields.
 * returns pointer to the id struct.
 */
struct id_st* createIdClient(struct id_st* client_id, char info[5][40]) {
    
    strncpy(client_id->address.name, info[1], strlen(info[1]) - 2);
    strncpy(client_id->address.street_address, info[2], strlen(info[2]) - 2);
    strncpy(client_id->address.city_state, info[3], strlen(info[3]) - 2);
    strncpy(client_id->address.phone_number, info[4], 12);
    
    return client_id;
}