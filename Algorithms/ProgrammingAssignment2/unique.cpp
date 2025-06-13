/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Matthew McCaughan
 * Date        : 
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <iostream>
#include <cctype>
#include <sstream>
#include <string>

using namespace std;


bool is_all_lowercase(const string &s) {

    // returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.



bool alllower = true;                                   // declares a bool variable to store true/false
    for (size_t i = 0; i < s.size(); i++){              // iterates through string by character
    char test = s[i];
    if (!('a' <= test && test <= 'z')){                 // if ASCII value is outside of lowercases, then it isnt a lowercase
        alllower = false;                               // bool value false
        }
    }

return (alllower);                                      // return bool
}


bool all_unique_letters(const string &s) {
    // returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.


unsigned int vector = 0;                               // unsigned int vector to "store" if character has been seen
unsigned int setter;                                   // unsigned int setter to be set to compare to vector for every character

bool answer = true;                                    // declare a bool variable to store true/false

for (size_t i = 0; i < s.size(); i++){                 // iterates through string by character
    char charrep = s[i];

    setter = 1 << (charrep - 'a');                     // setter is bit shifted so a "1" occurs at the bit cooresponding to the ith character
    if ((setter & vector) != 0){                       // vector already stores this value as 1, so this character has been seen before, return false
        answer = false;
        break;
    }
    if ((setter & vector) == 0){                       // else the vector doesn't hold this value yet, so & operation returns 0
        vector = (setter | vector);                    // vector now also stores 1 at bit cooresponding to the character, will loop 
                                                       //again to see if other characters will occur at this bit
    }
    
}
return answer;                                        // return bool

}

int main(int argc, char * const argv[]) {                                       // MAIN 
   
    if(argc != 2){                                                             // TOO LITTLE OR TOO MANY ARGUMENTS
        cerr << "Usage: ./unique <string>" << endl;
        return -1;
    }
    istringstream iss;                                                         // PASSES ARGUMENT INTO ISS AS A STRING
    string a;
    iss.str(argv[1]);
    iss >> a;
    if (is_all_lowercase(a) == false){                                         // CHECKS is_all_lowercase is false
       cerr << "Error: String must contain only lowercase letters." << endl;   // PRINTS ERROR ACCORDINGLY
        return -1;
    }                                                                          // OTHERWISE is_all_lowercase (hopefully) is true
    if (all_unique_letters(a) == true){                                        
        cout << "All letters are unique." << endl;                             // Runs all_unique_letters on string and if true, prints accordingly
    }
    else {
        cout << "Duplicate letters found." << endl;                            // if duplicates are found, prints accordingly
    }

    return 0;                                                                  // last but not least, return 0 for main
}
