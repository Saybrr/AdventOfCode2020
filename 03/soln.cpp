#include <string>
#include <string.h>
#include <vector>
#include <iostream>
#include <fstream>

/*
Problem 3 from: 
https://adventofcode.com/2020/day/3

Starting at the top-left corner of your map and following a slope of right 3 and down 1, 
how many trees would you encounter?
*/


int tree_check(int right, int down, std::vector<std::string> mapvec){

    int slopecount = right;
    int tree_count = 0;
    int i = 1;

    for (std::string line : mapvec){
        if (i % down == 0){ 
            // std::cout << line << std::endl;
            // std::cout << slopecount << std::endl;
            if (line[slopecount] == '#'){
                tree_count++;
                //std::cout << "TREE" << std::endl;
            }
            slopecount += right;
            slopecount %= line.length();
        } 
//    std::cout << tree_count << std::endl;
        i++;
    }
    return tree_count;
}


int main(int argc, char** argv){
    // Open the input file
    std::ifstream input;
    input.open("input");
    std::vector<std::string> mapvec; 
    std::string line; 

    //we are starting the count form the second row
    std::getline(input,line);
    //we move right 3 down 1 on the first row
     for (line ; std::getline(input,line);){
         mapvec.push_back(line);
     }
    std::cout << tree_check(3,1,mapvec) << std::endl;

    long long int a = tree_check(1,1,mapvec);
    long long int b = tree_check(3,1,mapvec);
    long long int c = tree_check(5,1,mapvec);
    long long int d = tree_check(7,1,mapvec);
    long long int e = tree_check(1,2,mapvec);
    std::cout << " 1,1 " << a << " 3,1 " << b <<" 5,1 " << c << " 7,1 "<< d << " 7,2 " << e << std::endl;
    std::cout << a * b * c * d * e << std::endl;
    return 0;
        
}

