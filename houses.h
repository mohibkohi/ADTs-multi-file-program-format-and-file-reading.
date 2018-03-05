//
//  houses.h
//  pract
//
//  Created by Mohib Kohi on 5/25/16.
//  Copyright © 2016 Mohib Kohi. All rights reserved.
//

//House class header.

#ifndef houses_h
#define houses_h

#include <stdio.h>

/**
 * House Struct.
 * Holds house mls, stree Address, city, zip, min Bedrooms, min bathrooms
 * min footage, max price.
 */
struct houses_st {
    // struct id_st obj;
    char mls[40];
    char street_address[40];
    char city[40];
    char zip[10];
    
    long min_bedrooms;
    long min_bathrooms;
    long min_footage;
    long max_price;
};
//house pointer to struct house.
typedef struct houses_st *houses;

//function takes 2d array updates struct fields. 
houses createHouse(char info[8][100]);

#endif /* houses_h */
