//
//  houses.c
//  pract
//
//  Created by Mohib Kohi on 5/25/16.
//  Copyright © 2016 Mohib Kohi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "houses.h"

/**
 * Function takes 2d array updates struct fields.
 * returns pointer to the house struct.
 */
houses createHouse(char info[8][100]) {
    char *ptr;
    
    houses house_ptr = malloc(sizeof (struct houses_st));
    
    
    //strcpy(temp, info[0]);
    
    strcpy(house_ptr->mls, info[0]);
    strcpy(house_ptr->street_address, info[1]);
    strcpy(house_ptr->city, info[2]);
    strcpy(house_ptr->zip, info[3]);
    
    house_ptr->min_bedrooms = strtol(info[4], &ptr, 10);
    house_ptr->min_bathrooms = strtol(info[5], &ptr, 10);
    house_ptr->min_footage = strtol(info[6], &ptr, 10);
    house_ptr->max_price= strtol(info[7], &ptr, 10);

    return house_ptr;
}