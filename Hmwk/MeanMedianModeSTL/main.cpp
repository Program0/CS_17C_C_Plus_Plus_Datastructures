/* 
 * File:   main.cpp
 * Author: super0
 *
 * Created on October 28, 2015, 10:13 PM
 */

#include <cstdlib>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <algorithm>

using namespace std;

/*
 * 
 */

vector <int> mode(int *array, int size);
// Returns a vector with the mode(s) of the passed array. The number of modes
// is the size of the vector returned.

float mean(int *array, int size);
// Returns the mean of the passed array

int median(int *array, int size);
// Returns the median of the passed array

int* copyArray(int *array, int size);
// Returns a copy of the passed array

int main(int argc, char** argv) {

    
    cout<< "Hello world!"<<endl;
    return 0;
}

vector <int> mode(int *input, int size){
    
    // Copy then sort the copy array
    int *array=copyArray(input,size);
    std::sort(array,array+size);
    
    int frequency = 0; // For holding the max frequency

    // Go through the vector adding unique elements to the map
    // and updating each element's frequency.
    std::map<int, int> freq;    
    
    for (int i = 0; i < size; i++) {       
        // If an element is not there add with freq. 1
        if (!freq.count(array[i])) {
            freq[array[i]] = 1;
        } else {
            int count = freq.at(array[i]) + 1;
            if (frequency < count)
                frequency = count;
            freq.at(array[i]) = count;
        }
    }
    // Now go through each element in the map and compare its frequency 
    // with the highest frequency found. This will give us the number of modes.
    int mode = 0;
    vector<int> modes;
    
    //std::stringstream s;
    
    typedef std::map<int, int>::iterator map_it;
    for (map_it iterator = freq.begin(); iterator != freq.end(); iterator++) {
        // Insert the frequency values into the set                
        if (frequency == iterator->second) {
            //numberModes++;
            mode = iterator->first;
            modes.push_back(mode);
        }
    }
    return modes;
    
}

int* copyArray(int *array, int size){
    if(array&&size>0){
        int *copy= new int[size];
        for(int i =0;i<size; i++){
            copy[i]=array[i];
        }
        return copy;
    }
    return NULL;
}