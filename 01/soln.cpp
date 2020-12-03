#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

/*
Problem 01: From a list of ints, return a * b if a + b == 2020
*/

int part1(std::vector<int> intvec){
        

    //Find two ints that add to 2020
    //return their product
    for(int i; i < intvec.size(); i++){
        //addition is communitive, starting inner loop at i
        //prevents double-counting
        for (int j = i; j < intvec.size(); j++){
             if(intvec[i] + intvec[j] == 2020){
                int prod = intvec[i] * intvec[j];
                std::cout << "Found a value" << std::endl;  
                return prod;
            }
        }
    }

    std::cout << "Nothing Found";
    return -1;

}

int part2_naive(std::vector<int> intvec){
    //Find three ints that add to 2020
    //return their product
    //like part 1 but with an added loop -- not working
    for(int i; i < intvec.size(); i++){
        //addition is communitive, starting inner loop at i
        //prevents double-counting
        for (int j = i + 1; j < intvec.size(); j++){
            //only check for a 3rd number if we aren't already larger than 2020
                for(int k = j + 1; k < intvec.size(); k++){
                    //std::cout <<intvec[i] << "+" << intvec[j] << "+" << intvec[k] << "==" << intvec[i] + intvec[j] + intvec[k] << " Maybe?" << std::endl;
                    if((intvec[i] + intvec[j] + intvec[k]) == 2020){
                        int prod = intvec[i] * intvec[j] * intvec[k];
                        return prod;
                    }
                }
            
        }
    }
    std::cout << "Nothing Found";
    return -1;
}


int main(int argc, char** argv){
    // Open the input file
    std::ifstream input;
    input.open("input");
    std::vector<int> intvec; 
    //Populate a vector from the input file
    for (std::string lineA; std::getline(input,lineA); ){
        intvec.push_back(stoi(lineA));
    }

    for(auto i : intvec){
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "VECTOR SIZE: " << intvec.size() << std::endl;    
    std::cout <<"Part One Solution: " << part1(intvec) << std::endl;
    std::cout <<"Part Two Naive Solution: " << part2_naive(intvec) << std::endl;

    //make sure we added to the vector correctly

}
