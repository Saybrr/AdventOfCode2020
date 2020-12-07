#include <string>
#include <string.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <bits/stdc++.h> 
#include <regex>


/*
--- Day 5: Custom Customs ---
Part 1: Count answers that "anyone" in a group has marked 
In this example, the sum of these counts is 3 + 3 + 3 + 1 + 1 = 11.

For each group, count the number of questions to which anyone answered "yes". What is the sum of those counts?

Part2: count answers that EVERYONE in a group has marked 
i.e. letter exists on every row


Part 2 requires parsing input differently as newlines are now important information. 

Strategy: have a counter for number of people in a group
(newlines in a block of answers)
count number of times a char has been seen, count should equal number of people 

*/ 

int countGroup(std::string answers){
    /*
    count number of unique letters 
    */
    std::string seen = "";
    int count = 0;
    //split on spaces
    for(int i = 0 ; i < answers.length() ; i++){
        // std::cout << "got " << answers[i] << std::endl;
        if (seen.find(answers[i]) == std::string::npos) {
            count++;
            seen.append(answers.substr(i,1));
            // std::cout << answers[i] << " " << answers.substr(i,1) << std::endl;
        }
        // std::cout << "seen is " << seen << std::endl;
    }
    //std::cout << seen.length() << " "<< answers.length() << std::endl;
    return count;
}

int countTotalAnyone(std::ifstream input){


}


void test_countGroupAnyone()
{
    /*
   abc   3

    a
    b    3 
    c

    ab   3
    ac

    a
    a   1
    a
    a

    b   1
    */

    std::vector<std::string> answers {"abc","abc","abac","aaaa", "b"};
    std::vector<int> res {3,3,3,1,1};

    for (int i = 0; i < answers.size(); i++){
        std::cout << "Expected: " << res[i] << " Received: " <<  countGroup(answers[i]) <<std::endl;
    }
}

void test_countGroupEveryone()
{
    /*
   abc   3

    a
    b    0 
    c

    ab   1
    ac

    a
    a   1
    a
    a

    b   1
    */

    std::vector<std::string> answers {"abc","abc","abac","aaaa", "b"};
    std::vector<int> res {3,3,3,1,1};

    for (int i = 0; i < answers.size(); i++){
        std::cout << "Expected: " << res[i] << " Received: " <<  countGroup(answers[i]) <<std::endl;
    }
}




int main(int argc, char** argv){
    // Open the input file
    std::ifstream input;
    input.open("input");
    int answerCount = 0;
    std::string answers = "";

    test_countGroupAnyone();

    auto totalAnyone = countTotalAnyone(&input) 

    for(std::string line; std::getline(input, line);){
        if (line != ""){
            //add the line to our current answer string
            answers = answers.append(line);
        }
        else{
            //we have hit a linebreak and are done with current group
            //validate it, and reset the answer string
            std::cout << "Group is " << answers << std::endl;
            answerCount += (countGroup(answers));
            answers = "";
        }
    }

    std::cout << "TOTAL ANSWER COUNT " << answerCount << std::endl;

    // return 0;

}
