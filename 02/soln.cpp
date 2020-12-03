#include <string>
#include <vector>
#include <iostream>
#include <fstream>

/*
Problem 02: Extension of problem 1 --
From a list of ints, return a * b * c if a + b + c == 2020
*/

int main(int argc, char** argv){
    // Open the input file
    std::ifstream input;
    input.open("input");
    std::vector<int> intvec; 
    //Populate a vector from the input file
    for (std::string lineA; std::getline(input,lineA); ){
        intvec.push_back(stoi(lineA));
    }
    //make sure we added to the vector correctly
    std::cout << "VECTOR SIZE: " << intvec.size() << std::endl;    



}
