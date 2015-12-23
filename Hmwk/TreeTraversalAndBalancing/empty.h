/*
 * File: empty.h
 * Interface for throwing an empty container structure exception
 * Created on: Nov 4, 2015
 * Author: Marlo Zeroth
 */

#ifndef EMPTY_H_
#define EMPTY_H_

#include <iostream>
#include <cstdlib>

class Empty{
public:
    Empty(std::string input){
        std::cout <<"Structure" << input <<" is empty." << std::endl;
        exit (EXIT_FAILURE);
    };

};

#endif /* EMPTY_H_ */
