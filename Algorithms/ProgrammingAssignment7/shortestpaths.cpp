/*******************************************************************************
 * Name        : floyd.cpp
 * Author      : Matthew McCaughan
 * Version     : Final
 * Date        : December 7th, 2022
 * Description : Implements Floyd's algorithm
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <fstream>

using namespace std;


int main(int argc, char *argv[]) {

 if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    ifstream input_file(argv[1]);

if (!input_file) {
    cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
    return 1;
    }

    input_file.exceptions(ifstream::badbit);
    string line;
    try {
        unsigned int line_number = 1;
        // Use getline to read in a line.
        // See http://www.cplusplus.com/reference/string/string/getline/

        // line 1
        getline(input_file, line);
         char value = (int)(line[0]);
         string valuestr = line;

        if (value <= '0' || value >= '9'){
            cerr << "Error: Invalid number of vertices '" << valuestr << "' on line " << line_number << "." << endl;
            return -1;
        }
        //cout << value << endl;
        char lower = 'A';
        char upper = (value-48) + '@';
        //cout << "DEBUG RANGE: " << lower << "-" << upper << endl;

        
        string a,b,cc;

        int i = 0;

        while (getline(input_file, line)) {
            line_number++;
            while ((int)(line[i]) != 32){       // get first vertex
                a.push_back(line[i]);
                i++;
            }
            i++;
            
            while ((int)(line[i]) != 32){       // get second vertex
                    if ((int)(line[i]) == 0){
                    break;
                    }
                b.push_back(line[i]);
                i++;

                
            }
            i++;
           while ((int)(line[i]) != 0){         // get weight
                cc.push_back(line[i]);
                i++;
                }


                if (cc <= " ") {
                cerr << "Error: Invalid edge data '" << a << " " <<  b << "'" << " on line " << line_number << endl;
                return -1;
                }
    
           i = 0;
           

            if (a[0] > upper){
                cerr << "Error: Starting vertex '" << a << "' on line " << line_number << " is not among valid values " << lower << "-" << upper << "." << endl;
                return -1;
            }
            if (b[0] > upper || b[0] < 'A'){
                cerr << "Error: Ending vertex '" << b << "' on line " << line_number << " is not among valid values " << lower << "-" << upper << "." << endl;
                return -1;
            }
           a.clear();
           b.clear();
          
           if ( cc[0] <= '0' || cc[0] >= '9'){
            cerr << "Error: Invalid edge weight '" << cc << "' on line " << line_number << "." << endl;
           }
 cc.clear();
        }

        
        // Don't forget to close the file.
        input_file.close();
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
        return 1;
    }




    // Spent 4 hours trying to parce the input. I'm not even going to get into the main algorithm.
}
