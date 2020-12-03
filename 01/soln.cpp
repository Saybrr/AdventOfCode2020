#include <string>
#include <vector>
#include <iostream>
#include <fstream>

/*
Problem 01: From a list of ints, return a * b if a + b == 2020
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

    //Find two ints that add to 2020
    //return their product
    for(int i; i < intvec.size(); i++){
        //addition is communitive, starting inner loop at i
        //prevents double-counting
        for (int j = i; j < intvec.size(); j++){
             if(intvec[i] + intvec[j] == 2020){
                int prod = intvec[i] * intvec[j];
                std::cout << "Found a value" << std::endl;  
                std::cout << prod;
                return prod;
            }
        }
    }

    std::cout << "Nothing Found";
    return -1;

}
