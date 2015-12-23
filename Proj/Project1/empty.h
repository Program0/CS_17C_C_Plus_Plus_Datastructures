/*
 * Emtpy.h
 *
 *  Created on: Nov 4, 2015
 *      Author: super0
 */

#ifndef EMPTY_H_
#define EMPTY_H_

#include <iostream>
#include <cstdlib>

class Empty{
public:
    Empty(){
        std::cout <<"Structure is empty." << std::endl;
        exit (EXIT_FAILURE);
    };

};

#endif /* EMPTY_H_ */
