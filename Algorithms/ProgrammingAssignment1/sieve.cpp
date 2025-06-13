/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Matthew McCaughan
 * Date        : September 21st, 2022
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstring>

using namespace std;

class PrimesSieve {
    // public methods
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};
// constructor, creates is_prime_ array of boolean values and calls sieve immediately
PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {
    // Display the primes in the format specified in the
    // requirements document.

    // Setup
    cout << endl;
    cout << "Number of primes found: " << count_num_primes() << endl;
    cout << "Primes up to " << limit_ << ":" << endl;
    // int max to keep track of last prime
    int max = 0;
    for (int i = 2; i < limit_; i++){
        if (is_prime_[i]){
            max = i;
        }

    }
// calculates the width of the largest prime & amount of primes per row using the max variable
 const int max_prime_width = num_digits(max), 
  primes_per_row = 80 / (max_prime_width + 1); 


// if primes will only take up one row
if (primes_per_row > count_num_primes()){
    


// another "max" type variable, numlast, is the last prime in the list
        bool last = false;
int numlast = limit_;
while (last != true){
    if (is_prime_[numlast] == true){
        last = true;
    }
    numlast--;
}

     for (int i = 2; i <= limit_; i++){
          if (limit_ == 2){
        cout << 2;
        break;
    }

        if (i == numlast){
            cout << i+1;
            break;
           
}
        if (is_prime_[i] && i != limit_){
            cout << i;
             cout << " ";

        }
     }
}

// primes will take up more than one row, and must be formatted accordingly
else{

    bool last = false;
int numlast = limit_;
while (last != true){
    if (is_prime_[numlast] == true){
        last = true;
    }
    numlast--;
}

int COUNT = 0;
  for (int i = 2; i < limit_; i++){
  

        if (i == numlast){
            cout << i+1;
            break;
        }

        if (is_prime_[i] && i != numlast){
            cout << setw(num_digits(max) - num_digits(is_prime_[i]) + 1);
            cout << i;
            COUNT++;
            // conditions for avoiding spaces at the end of every line (will break the test script)
            if (COUNT < primes_per_row){
                cout << " ";
            }
            if (COUNT >=primes_per_row){
                cout << endl;
                COUNT = 0;
            }
        }
    }
}

cout << endl;
  } 

// counts the number of primes using a counter variable
int PrimesSieve::count_num_primes() const {
    int counter = 0;
    for (int i = 2; i <= limit_; i++){
        if (is_prime_[i] == true){
            counter++;
        }
    }
return counter;

}
// sieve function, called from constructor
void PrimesSieve::sieve() {

    for (int i = 0; i <= limit_; i++){
        is_prime_[i] = true;
    }


    for (int i = 2 ; i*i <= limit_; i++){
        if (is_prime_[i] == true){
            for (int j = i*i; j <= limit_; j += i){
                is_prime_[j] = false;
                
            }
        }
    }
    display_primes();
// calls display primes (all in one function!)
}

// divides a number by 10 to calculate how many digits it holds
int PrimesSieve::num_digits(int num) {
    int counter = 0;
    while (num != 0)
    {
        num = num/10;
        counter++;
    }
    return counter;
}
// MAIN FUNCTION!!!!!!!!
int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

//OUTPUTTING


    // DYANMICALLY CREATED OBJECT (DELETE IT!!!!!!)
 PrimesSieve *p = new PrimesSieve(limit);

    // professional memory manager 
    delete p;
    return 0;
}
