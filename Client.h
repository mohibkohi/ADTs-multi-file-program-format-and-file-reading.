//
//  Client.h
//  Homework4
//
//  Created by Mohib Kohi on 5/20/16.
//  Copyright © 2016 Mohib Kohi. All rights reserved.
//

#ifndef Client_h
#define Client_h

#include <stdio.h>
//#include "Address.h"

/**
 * Address struct holds client name, street Address, city State, Phone number.
 */
struct address_st {
    char name[40];
    char street_address[40];
    char city_state[40];
    char phone_number[40];
};

/**
 * Preference struct holds client min bedrooms, min bathrooms, min footage, max price.
 */
struct preference_st {
    long min_bedrooms;
    long min_bathrooms;
    long min_footage;
    long max_price;
};

/**
 * Id struct holds client id, Address struct, Preference struct.
 */
struct id_st {
    char id[10];
    struct address_st address;
    struct preference_st preference;
};

//function takes 2d array updates struct fields.
struct id_st* createIdClient(struct id_st* client_id, char info[5][40]);

//function takes 2d array updates struct fields.
struct id_st* createClient(char info[5][40]) ;

//function takes 2d array updates struct fields. 
void assignPreference(struct id_st*  client_id, char info[4][40]);

#endif /* Client_h */
