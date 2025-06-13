/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Matthew McCaughan
 * Date        : October 8th, 2022
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;


// HELPER FUNCTION
// ripped STRAIGHT out of primesSieve, this function calculated the number of digits in an integer (for width and formatting).
int num_digits(int num) {
    int counter = 0;
    while (num != 0)
    {
        num = num/10;
        counter++;
    }
    return counter;
}




// belly button vectors
vector<int> innie;
vector< vector<int>> outie;



// get_ways

vector< vector<int> > get_ways(int num_stairs) {
    // Returns a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.


                                                    // base case
                                                    // if n <= 0
                                                    // returns the sequence of instructions as there is no more stairs to climb
if (num_stairs <= 0){
    outie.push_back(innie);
}
                                                    // recursive case
                                                    // for i in range(1,4) (can only climb stairs 1, 2, or 3 at a time.)
for (int i = 1; i <= 3; i++){
                                                    
    if (num_stairs >= i){                           // if n >= i:
                                                    
        innie.push_back(i);                         // appends i to innie, and calls get_ways(numstairs-i) for recursive call
        get_ways(num_stairs-i);                     // recursive call
        innie.pop_back();                           // stops duplications in innie.
    }
}

return outie;
}

// Leftover code

/*
    // result = get_ways(n-i)
    vector<vector<int>> result = get_ways(num_stairs- i);

    // prepending i to all solutions of result
    for (size_t j = 0; j < result.size(); j++){

        //result[j] = [i] + result[j];
        result.at(j).push_back(i);
    }
    // WAYS += RESULT
    // insert at the end of outie, from the beginning of result to the end
    // insert method for vectors
    
}
}
}
*/

// display_ways
void display_ways(const vector< vector<int> > &ways) {
    // Displays the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
    
    for (size_t i = 0; i < ways.size(); i++){
        if (ways.size() > 10){                                  // labels are right-aligned to the width of the highest label
        cout << setw(num_digits(ways.size()));                  // sets width using num_digits with parameter ways.size()
        }
        cout << i+1 << ". ";                                    // labels and bracket per line
        cout << "[";                                        
        for (size_t j = 0; j < ways[i].size(); j++){
        if (j == ways[i].size()-1) {
            cout << ways[i][j];                                 // nightmarish double index notation for the last element in ways[i]
        }
        else {
        cout << ways[i][j] << ", ";                             // double indexing for elements of ways[i] (except last one)
        }
        }
        cout << "]" << endl;                                    // closing bracket per line

    }

}

int main(int argc, char * const argv[]) {

                                                                                // check for correct number of arguments
    if (argc != 2){
        cerr << "Usage: ./stairclimber <number of stairs>" << endl;
        return -1;
    }
                                                                                // string stream reads argv[1] as an integer
     istringstream iss;                                                         
    int a;
    iss.str(argv[1]);

                                                                                // checks for correct data type and value for int a.
     if(!(iss >> a)){
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return -1;
    }                                                                           // cant climb zero stairs, so a <= 0.
         if(a <= 0){
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return -1;
    }

    int way = get_ways(a).size();                                                   // more formatting because 1 stair and >1 stair are different words in english
    if (way == 1){
        cout << "1 way to climb 1 stair." << endl;
        
    }
    if (way != 1){
        cout << way << " ways to climb " << a << " stairs." << endl;
    }

                                                                                // since i declared innie and outie as global variables, 
                                                                                // I need to clear them because they still store data when I intiialized int way.
                                                                                // (took way too long to realize why my list was duping)
    outie.clear();      
    innie.clear();


    display_ways(get_ways(a));                                                  // finally, the function call. calls get_ways with parameter a, and 
                                                                                // returns a vector of vectors. This is passed as a parameter to display ways
                                                                                // which iterates through the vector of vectors and prints


return 0;

}