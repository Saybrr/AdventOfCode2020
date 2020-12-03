#include <string>
#include <string.h>
#include <vector>
#include <iostream>
#include <fstream>

/*
Problem 02: 
min-max char password
1-3     a:   abcde
1-3     b:   cdefg
2-9     c:   ccccccccc

In the above example, 2 passwords are valid. The middle password, cdefg, is not; 
it contains no instances of b, but needs at least 1. The first and third passwords are valid: 
they contain one a or nine c, both within the limits of their respective policies.

How many passwords are valid according to their policies?
*/

bool check_part1(int min, int max, char letter, std::string password){
    //return true if valid false otherwise
    int lettercount = 0;
    // std::cout << letter << endl;
    for(int i = 0; i < password.length(); i++){       
        if(password[i] == letter){
            lettercount++;
        }
    }
    //std::cout << lettercount << "FOR " << min <<" " << max <<" "<< letter<<" " << password << std::endl;
    return lettercount >= min && lettercount <= max;
}

/*
Each policy actually describes two positions in the password, 
where 1 means the first character, 2 means the second character, and so on. 
(Be careful; Toboggan Corporate Policies have no concept of "index zero"!) 
Exactly one of these positions must contain the given letter. 
Other occurrences of the letter are irrelevant for the purposes of policy enforcement.

Given the same example list from above:

1-3 a: abcde is valid: position 1 contains a and position 3 does not.
1-3 b: cdefg is invalid: neither position 1 nor position 3 contains b.
2-9 c: ccccccccc is invalid: both position 2 and position 9 contain c.
How many passwords are valid according to the new interpretation of the policies?

*/

bool check_part2(int loc1, int loc2, char letter, std::string password){
    // std::cout << letter << endl;
    //logical xor
    return (password[loc1 - 1] == letter) != (password[loc2 - 1] == letter);

}


int main(int argc, char** argv){
    // Open the input file
    std::ifstream input;
    input.open("input");

    std::string minmax, letter,password;
    int validcount_p1 = 0, validcount_p2 = 0;
    while((input >> minmax >> letter >> password))
    {
        //tokenize minmax 
        //probably inneficient using c++ string parsing in combination with c strtok
        const char* minmax_c = minmax.c_str();
        auto min = strtok((char*)minmax_c,"-");
        auto  max = strtok(NULL,"-");
        //std::cout<< minmax <<" " << letter << " " << password << std::endl;
        if (check_part1(atoi(min),atoi(max), letter[0], password))
        {
            validcount_p1++;
        }
        if (check_part2(atoi(min),atoi(max), letter[0], password))
        {
            validcount_p2++;
        }

    }
    std::cout << "Part 1: " << validcount_p1  << "Part 2: " << validcount_p2 << std::endl;
    return 0;

}
