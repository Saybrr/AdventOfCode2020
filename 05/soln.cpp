#include <string>
#include <string.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <bits/stdc++.h> 
#include <regex>


/*
--- Day 5: Binary Boarding ---
 A seat might be specified like FBFBBFFRLR, where F means "front", B means "back", L means "left", and R means "right".
 he first 7 characters will either be F or B

For example, consider just the first seven characters of FBFBBFFRLR:

Start by considering the whole range, rows 0 through 127.
F means to take the lower half, keeping rows 0 through 63.
B means to take the upper half, keeping rows 32 through 63.
F means to take the lower half, keeping rows 32 through 47.
B means to take the upper half, keeping rows 40 through 47.
B keeps rows 44 through 47.
F keeps rows 44 through 45.
The final F keeps the lower of the two, row 44.

The same process as above proceeds again, this time with only three steps. 
L means to keep the lower half, while R means to keep the upper half.

For example, consider just the last 3 characters of FBFBBFFRLR:

Start by considering the whole range, columns 0 through 7.
R means to take the upper half, keeping columns 4 through 7.
L means to take the lower half, keeping columns 4 through 5.
The final R keeps the upper of the two, column 5.

So, decoding FBFBBFFRLR reveals that it is the seat at row 44, column 5.

Every seat also has a unique seat ID: multiply the row by 8, then add the column.
 In this example, the seat has ID 44 * 8 + 5 = 357.

*/ 

int binsearch(int low, int high, std::string seat){
    // std::cout<< seat; 
    for(auto s : seat){
        auto mid = low + (high - low) / 2;
        if (s == 'F' || s == 'L'){
            //F means take the lower half by dividing the upper bound by 2
            high = mid;
        }
        else if (s == 'B' || s == 'R'){
            //take the upper half by incrementing the lower bound by low/2
            low = mid;
        }
        //std::cout << s << " " << low << " " << high << std::endl;
    }
    // std::cout << high << " " << low << '\n';
    int row = seat[0] == 'F' || seat[0] == 'B' ? high : low ;
    //int row = seat[6] == 'F' ? low : high;

    //std::cout << row << std::endl;
    return row;

}

int findRow(std::string seat){
    seat = seat.substr(0,7);
    int low = 0;
    int high = 127;
   
   return binsearch(low, high, seat);

}

int findCol(std::string seat){
    seat = seat.substr(7,3);
    int low = 0;
    int high = 8;
    return binsearch(low,high,seat);
}

int getSeatID(int row, int col){

    return row * 8 + col;
}


void test_SeatID()
{
    /*
    BFFFBBFRRR: row 70, column 7, seat ID 567.
    FFFBBBFRRR: row 14, column 7, seat ID 119.
    BBFFBBFRLL: row 102, column 4, seat ID 820.
    */

    std::vector<std::string> seats {"BFFFBBFRRR","FFFBBBFRRR","BBFFBBFRLL"};
    std::cout << "Expected row 70, column 7, seat ID 567." << std::endl << "Received: Row " << findRow(seats[0]) << " Col " <<  findCol(seats[0]) << " ID " << getSeatID(findRow(seats[0]),findCol(seats[0])) << std::endl;
    std::cout << "Expected row 14, column 7, seat ID 119." << std::endl << "Received: Row " << findRow(seats[1]) << " Col " <<  findCol(seats[1]) << " ID " << getSeatID(findRow(seats[1]),findCol(seats[1])) << std::endl;
    std::cout << "Expected row 102, column 4, seat ID 820." << std::endl << "Received: Row " << findRow(seats[2]) << " Col " <<  findCol(seats[2]) << " ID " << getSeatID(findRow(seats[2]),findCol(seats[2])) << std::endl;
   
}

int maxSeatID(std::ifstream & seats){
    int max = 0;
    for(std::string seat; std::getline(seats,seat);){

        auto id = getSeatID(findRow(seat),findCol(seat));
        std::cout << seat << " " << id << std::endl;
        max = id > max ? id : max;


    }

    return max;

}

std::vector<int> getAllIDs(std::ifstream & seats) {
    int max = 0;
    std::vector<int> ids; 
    for(std::string seat; std::getline(seats,seat);){
        auto id = getSeatID(findRow(seat),findCol(seat));
        ids.push_back(id);

    }

    return ids;
}



int main(int argc, char** argv){
    // Open the input file
    std::ifstream input;
    input.open("input");



    //declare range vectors to serve as binary search

    // findRow("FBFBBFFRLR");
    test_SeatID();

    //part 1
    auto max = maxSeatID(input);
    std::cout << max << " LARGEST ID" <<  std::endl;
    //part 2 
    //find the missing seat
    input.close();
    input.open("input");
    std::vector<int> allIDs = getAllIDs(input);

    std::sort(allIDs.begin(), allIDs.end());
    std::cout << "Sorted IDS" << std::endl;
    //iterate through vector, if difference between current and next is > 1, return current + 1
    for (int i = 0 ; i < allIDs.size(); i++){
        // std::cout << allIDs[i] << std::endl;
        auto gap = (allIDs[i+1] - allIDs[i]);
        if ( gap == 2){
            std::cout << "YOUR SEAT IS: " << allIDs[i] + 1 << std::endl;
            return allIDs[i] + 1;
        }
    }



    // test_SeatID();


    // test_hasAllFields();


}
