/*
 * File:   invalidargument.h
 * Author: Marlo Zeroth
 *
 * Created on November 9, 2015, 7:37 AM
 */

#ifndef INVALIDARGUMENT_H
#define	INVALIDARGUMENT_H

#include <iostream>
#include <cstdlib>

class InvalidArgument{
    public:
    InvalidArgument(){
        std::cout <<"Argument is not valid." << std::endl;
        exit (EXIT_FAILURE);
    };

};


#endif	/* INVALIDARGUMENT_H */

