#include <string>
#include <string.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <bits/stdc++.h> 
#include <regex>
/*
https://adventofcode.com/2020/day/4

The automatic passport scanners are slow because they're having trouble detecting 
which passports have all required fields. The expected fields are as follows:

byr (Birth Year)
iyr (Issue Year)
eyr (Expiration Year)
hgt (Height)
hcl (Hair Color)
ecl (Eye Color)
pid (Passport ID)
cid (Country ID)

Passport data is validated in batch files (your puzzle input). 
Each passport is represented as a sequence of key:value pairs separated by spaces or newlines. 
Passports are separated by blank lines.

Test cases
1: valid
2: Invalid -- missing hgt
3: Valid -- missing 'cid' can be ignored and treated as valid if all othe are present
4: Invalid -- missing byr 

part 1: -hasAllFields
Count the number of valid passports - those that have all required fields. 
Treat cid as optional. In your batch file, how many passports are valid?

part 2:  -isValidFields
Your job is to count the passports where all required fields are both present and valid according to the above rules. Here are some example values:
*/

// byr (Birth Year) - four digits; at least 1920 and at most 2002.
static const int BYR[] = {1920,2002}; 
// iyr (Issue Year) - four digits; at least 2010 and at most 2020.
static const int IYR[] = {2010,2020}; 
// eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
static const int EYR[] = {2020,2030}; 
// hgt (Height) - a number followed by either cm or in:
// If cm, the number must be at least 150 and at most 193.
// If in, the number must be at least 59 and at most 76.
static const int HGT_CM[] = {150,193};
static const int HGT_INCH[] = {59,76};
// hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
// ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
// pid (Passport ID) - a nine-digit number, including leading zeroes.
// cid (Country ID) - ignored, missing or not.




enum Fields {byr, iyr, eyr, hgt, hcl, ecl, pid, cid};

bool hasAllFields(std::string passport){
    //passport is a map of key, value pairs
    //check size: if 8, return true 
    //else if 7 and not cid return true 
    //else return false 
    int numKeys = std::count(passport.begin(), passport.end(), ':');
    std::string cid = "cid";
    auto hasCID = passport.find(cid);


    //std::cout << passport << " NumKeys " << numKeys << " hasCID " << hasCID << std::endl;
    return (numKeys == 8) != ((hasCID == std::string::npos) && numKeys == 7);


} 

bool isValidFields(std::string passport){
    //strtok by space to get a pair
    //strtok on : to get the key, value
    //split passport into vector of k,v pairs

    //make sure passport has all required fields before validating (part 1)
    if (!hasAllFields(passport)) {return false;} 
    std::vector<std::string> passvec; 
    char* rest; 
    std::stringstream stream(passport);
    //split on spaces
    for(std::string keyval; std::getline(stream, keyval, ' ');){
        //need lhs and rhs of ':'
        char* value;
        char* key = strtok_r((char*)keyval.c_str(),":", &value);
        std::string valstr = static_cast<std::string>(value);

        //std::cout << "KEY " << key << " VALUE " << value << std::endl;
        // byr (Birth Year) - four digits; at least 1920 and at most 2002.
        if (!strcmp(key, "byr")) {
            if (( std::stoi(valstr) > BYR[1]) || std::stoi(valstr) < BYR[0]){ 
                std::cout << "INVALID BYR" << std::endl;
                return false;
                }

        } else if (!strcmp(key, "iyr")) {
             // iyr (Issue Year) - four digits; at least 2010 and at most 2020.    
            if (( std::stoi(valstr) > IYR[1]) || std::stoi(valstr) < IYR[0]){ 
                std::cout << "INVALID IYR" << std::endl;
                return false;}
        } else if (!strcmp(key, "eyr")) {
            // eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
            if (( std::stoi(valstr) > EYR[1]) || std::stoi(valstr) < EYR[0]){ 
                std::cout << "INVALID EYR" << std::endl;
                return false;}
        } else if (!strcmp(key, "hgt")) {
            // hgt (Height) - a number followed by either cm or in:
            int height = std::stoi(valstr.substr(0,valstr.length() - 2));
            std::cout << height << " " << valstr << std::endl; 
            //check for cm or inch, then check respective min or max 
            if (valstr.find("cm") != std::string::npos) {

                if ((height > HGT_CM[1]) || (height < HGT_CM[0])){ 
                    std::cout << "INVALID HGT CM" << std::endl;
                    return false;}

            } else if (valstr.find("in") != std::string::npos) {
                if ((height > HGT_INCH[1]) || (height < HGT_INCH[0])){ 
                    std::cout << "INVALID HGT INCH" << std::endl;
                    return false;}
            } else { 
                std::cout << "INVALID HGT FORMAT" << std::endl;
                return false; }
            

        } else if (!strcmp(key, "hcl")) {
            // hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
            //check for correct number of characters after a #
            if (valstr.find('#') == std::string::npos) {
                std::cout << "INVALID HCL NO #" << std::endl;
                return false;
                } 
            valstr = valstr.substr(1);
            if (valstr.length() == 6){
                if (valstr.find_first_not_of("0123456789abcdef") != std::string::npos){
                    std::cout << "INVALID HCL CHARS" << std::endl;
                    return false;}

            } else { 
                std::cout << "INVALID HCL LENGTH" << std::endl;
                return false;}


        } else if (!strcmp(key, "ecl")) {
            // ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
            if (!((valstr.length() == 3) && (valstr == "amb" || valstr == "blu" || valstr =="brn" || valstr == "gry" ||
                                           valstr == "grn" || valstr == "hzl" || valstr == "oth"))) {
                std::cout << "INVALID ECL" << std::endl;
                return false;}


        } else if (!strcmp(key, "pid")) {
            // pid (Passport ID) - a nine-digit number, including leading zeroes.
            if (!(valstr.find_first_not_of("01123456789") == std::string::npos && (valstr.length() == 9))) {
                std::cout << "INVALID PID" << std::endl;
                return false;
            }
            

        } else {
            //optional cid -- do nothing 
            continue;
        }   
    }
    //if we get here, we hae made it through all checks, return valid
    return true;
}

int countValidPassports(std::ifstream & passports){
    //loop through passport vector and count valid passports
    int numValid = 0;
    std::string passport = "";
    for(std::string line; std::getline(passports, line);){
        if (line != ""){
            //add the line to our current passport
            passport = passport.append(line).append(" ");

        }
        else{
            //we have hit a linebreak and are done with current passport
            //validate it, and reset the passport string
            numValid += (isValidFields(passport));
            passport = "";
        }
    }
    return numValid;
}

void test_hasAllFields(){
    //test suite using the provided test cases to prove correctness

    std::string test01 = "ecl:gry pid:860033327 eyr:2020 hcl:#fffffd byr:1937 iyr:2017 cid:147 hgt:183cm";
    std::string test02 = "iyr:2013 ecl:amb cid:350 eyr:2023 pid:028048884 hcl:#cfa07d byr:1929";
    std::string test03 = "hcl:#ae17e1 iyr:2013 eyr:2024 ecl:brn pid:760753108 byr:1931 hgt:179cm";
    std::string test04 = "hcl:#cfa07d eyr:2025 pid:166559648 iyr:2011 ecl:brn hgt:59in";


    std::cout << "Expecting Valid, Received: " << hasAllFields(test01) << std::endl;
    std::cout << "Expecting Invalid, Received: " << hasAllFields(test02) << std::endl;
    std::cout << "Expecting Valid, Received: " << hasAllFields(test03) << std::endl;
    std::cout << "Expecting Invalid, Received: " << hasAllFields(test04) << std::endl;
}

void test_isValidFields(){
    //INVALID
    std::vector<std::string> invalids {"eyr:1972 cid:100 hcl:#18171d ecl:amb hgt:170 pid:186cm iyr:2018 byr:1926",
        "iyr:2019 hcl:#602927 eyr:1967 hgt:170cm ecl:grn pid:012533040 byr:1946",
        "hcl:dab227 iyr:2012 ecl:brn hgt:182cm pid:021572410 eyr:2020 byr:1992 cid:277",
        "hgt:59cm ecl:zzz eyr:2038 hcl:74454a iyr:2023 pid:3556412378 byr:2007"};

    for(std::string passport : invalids){
        std::cout << "Expecting Invalid: " <<  isValidFields(passport) << std::endl;
    }

    //VALID 
    std::vector<std::string> valids {"pid:087499704 hgt:74in ecl:grn iyr:2012 eyr:2030 byr:1980 hcl:#623a2f",
        "eyr:2029 ecl:blu cid:129 byr:1989 iyr:2014 pid:896056539 hcl:#a97842 hgt:165cm",
        "hcl:#888785 hgt:164cm byr:2001 iyr:2015 cid:88 pid:545766238 ecl:hzl eyr:2022",
        "iyr:2010 hgt:158cm hcl:#b6652a ecl:blu byr:1944 eyr:2021 pid:093154719"};

        for(std::string passport : valids){
        std::cout << "Expecting Valid: " <<  isValidFields(passport) << std::endl;
    }
}

int main(int argc, char** argv){
    // Open the input file
    std::ifstream input;
    input.open("input");
    std::ifstream testcase;
    testcase.open("testcase");

    // test_hasAllFields();
    test_isValidFields();

    auto validInput = countValidPassports(input);

    std::cout << validInput << " Valid Passports In Input" << std::endl;



}

