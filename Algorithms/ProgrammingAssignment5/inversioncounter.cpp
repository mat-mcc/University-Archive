/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Matthew McCaughan
 * Version     : Final
 * Date        : November 5th, 2022
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in Theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    // TODO
    long counter = 0;                                 // keep track of inversions
    for (int i = 0; i <= length - 2; i ++){           // two loops to iterate over every number and all the numbers after it.
        for (int j = i+1; j <= length-1; j++){
            if (array[i] > array[j]){                 // if number ahead is less than current number, it is an inversion
                counter++;                            // increment counter
            }
        }
    }
    return counter;
}

/**
 * Counts the number of inversions in an array in Theta(n lg n) time.
 */

long count_inversions_fast(int array[], int length) {

    int *scratch =  new int[length];                        // dynamically allocated array (DELETE IT!!!)                         
    long inversions = mergesort(array,scratch,0,length-1);  // mergesort returns long
    delete[] scratch;                                       // abra cadabra!
    return inversions;                                      // return inversions to main
}

/*
 * Helper function: performs merging of two subarrays
 */
long merge(int array[], int scratch[], int low, int mid, int high){

    long inversions = 0;
    int g = low;
    int h = mid;    // variables for keeping track of bounds
    int i = low;
    
    while ((g <= mid-1) && (h <= high)){
        if (array[g] <= array[h]){  // item from left subarray is greater, add it to scratch
            scratch[i++] = array[g++];
        }
        else {                      // else right subarray item is greater, add it to scratch
            scratch[i++] = array[h++];
            inversions += (mid-g);

        }
    }                               // now we add the leftover elements because we've done all necessary comparisons between subarrays
    while (g <= mid-1){
        scratch[i++] = array[g++];  // add rest of lower subarray elements
    }
    while (h <= high){
        scratch[i++] = array[h++];  // add rest of upper subarray elements
    }
    for (int j = low; j <= high; j++){  // copy array from scratch array to actual array (they're merged!)
        array[j] = scratch[j];

    }
    
    return inversions;      // ANOTHER return! (to mergesort)
}

static long mergesort(int array[], int scratch[], int low, int high) {
    int mid;
    long count = 0;
    if (low < high)
    {
        mid = (low + high)/2;
        count += mergesort(array,scratch,low,mid);          // recursive call on left subarray
        count += mergesort(array,scratch,mid+1,high);       // recursive call on right subarray
        count += merge(array,scratch,low,mid+1,high);       // merge two subarrays 
    }
    return count;       // return to count_inversions_fast
}



int main(int argc, char *argv[]) {
    // TODO: parse command-line argument

    // too many command line arguments
    if (argc > 2) {
        cerr << "Usage: " << argv[0] << " [slow]" << endl;
        return 1;
    }
    // if you're putting a command line argument, it better be "slow"!
    if (argc == 2){
        if ((strcmp(argv[1], "slow")) != 0) {
            cerr << "Error: Unrecognized option '" << argv[1] <<  "'." << endl;
            return -1;
        }
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }
    
    int num_values = values.size();
    if (num_values == 0) {
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }


    // produces output

    // slow inversion counter
    if (argc == 2){
        if ((strcmp(argv[1], "slow")) == 0) {
            long result = count_inversions_slow(&values[0],values.size());
            cout << "Number of inversions: " << result << endl;
        }
    } 
    // fast inversion counter
    else {
        long result = count_inversions_fast(&values[0],values.size());
        if (values.size() == 1){
            result = 0;
        }
        cout << "Number of inversions: " << result << endl;
    }


    return 0;
}
