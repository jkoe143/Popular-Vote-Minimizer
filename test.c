#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "MinPopVote.h"


//function tests the totalEVs() with different sets of arrays
//no parameters
//returns true if all tests pass
bool test_totalEVs() {
    State aStates[10]; //array of state structs for testing
    int res; //variable that stores results from totalEVs
    
    //aStates is initialized with different votes
    aStates[0].electoralVotes = 5;
    aStates[1].electoralVotes = 8;
    aStates[2].electoralVotes = 12;
    aStates[3].electoralVotes = 6;
    aStates[4].electoralVotes = 7;
    aStates[5].electoralVotes = 10;

    printf(" Checking totalEVs() for 5 States:\n");
    res = totalEVs(aStates,5); //totalEVs called with 5 states 
    if (res != 38) {
        printf("  individual state EVs are 5, 8, 13, 6, 7\n");
        printf("  expected total EVs = 38, actual total EVs = %d\n",res);
        return false; //false if result is not 38
    }
    
    for(int i = 0; i < 12; i++){
        aStates[i].electoralVotes = 4;
    }
    printf(" Checking totalEVs() for 12 States:\n");
    res = totalEVs(aStates, 12); //totalEVs is called with 12 states 
    if(res != 48){
        printf("  there are 12 states with 4 electoral votes each\n");
        printf("  expected total EVs = 48, actual total EVs = %d\n", res);
        return false; //false if result is not 48
    }
    return true; //true if nothing was flagged 
}


//function tests the totalPVs() with different sets of arrays
//no parameters
//returns true if all tests pass
bool test_totalPVs() {
    State aStates[10]; //array of state structs for testing
    int res;  //variable that stores results from totalPVs
    
    //aStates is initialized with different votes
    aStates[0].popularVotes = 5;
    aStates[1].popularVotes = 8;
    aStates[2].popularVotes = 12;
    aStates[3].popularVotes = 6;
    aStates[4].popularVotes = 7;
    aStates[5].popularVotes = 10;

    printf(" Checking totalPVs() for 5 States:\n");
    res = totalPVs(aStates,5); //totalPVs called with 5 states 
    if (res != 38) {
        printf("  individual state PVs are 5, 8, 13, 6, 7\n");
        printf("  expected total PVs = 38, actual total PVs = %d\n",res);
        return false; //false if result is not 38
    }

    for(int i = 0; i < 12; i++){
        aStates[i].popularVotes = 4;
    }
    printf(" Checking totalPVs() for 12 States:\n");
    res = totalPVs(aStates, 12); //totalPVs is called with 12 states 
    if(res != 48){ 
        printf("  there are 12 states with 4 popular votes each\n");
        printf("  expected total PVs = 48, actual total PVs = %d\n", res);
        return false; //false if result is not 48
    }
    return true; //true if nothing was flagged 
}


//function tests the setSettings() with different settings
//no parameters
//returns true if all tests pass
bool test_setSettings() {
    //variables for flags are initialized 
    int year = 0; 
    bool fastMode = false;
    bool quietMode = false;
    bool success;

    // Test case 1: valid arguments with year 1872, quietMode ON, fastMode ON
    char* argvDefault[] = {"app.exe", "-y", "1872", "-q", "-f"};
    success = setSettings(5, argvDefault, &year, &fastMode, &quietMode);
    if(!success || year != 1872 || !quietMode || !fastMode){ //checks if there are any violations/inconsistensies
        printf("Test case 1\n");
        printf("  Expected: year 1872, quietMode ON, fastMode ON\n");
        printf("  Actual: year %d, quietMode ", year);
        if(quietMode){
            printf("ON");
        } else {
            printf("OFF");
        }
        printf(", fastMode ");
        if(fastMode){
            printf("ON\n");
        } else{
            printf("OFF\n");
        }
        return false;
    }

    //Test case 2: valid arguments using default year, quiteMode and fastMode on
    char* argvYear[] = {"app.exe", "-q", "-f"};
    year = 0;
    success = setSettings(3, argvYear, &year, &fastMode, &quietMode);
    if(!success || year != 0 || !quietMode || !fastMode){ //checks if there are any violations/inconsistensies
        printf("Test case 2\n");
        printf("  Expected - year 0, quietMode ON, fastMode ON\n");
        printf("  Actual: year %d, quietMode ", year);
        if(quietMode){
            printf("ON");
        } else {
            printf("OFF");
        }
        printf(", fastMode ");
        if(fastMode){
            printf("ON\n");
        } else{
            printf("OFF\n");
        }
        return false;
    }

    //Test case 3: valid arguments using year 1872, quiteMode off and fastMode on
    char* argvFast[] = {"app.exe", "-y", "1872", "-f"};
    year = 0;
    success = setSettings(4, argvFast, &year, &fastMode, &quietMode);
    if(!success || year != 1872  || !fastMode){ //checks if there are any violations/inconsistensies
        printf("Test case 3\n");
        printf("  Expected - year 1872, quietMode OFF, fastMode ON\n");
        printf("  Actual: year %d, quietMode ", year);
        if(quietMode){
            printf("ON");
        } else {
            printf("OFF");
        }
        printf(", fastMode ");
        if(fastMode){
            printf("ON\n");
        } else{
            printf("OFF\n");
        }
        return false;
    }

    //Test case 4: valid arguments using year 1872, quiteMode on and fastMode off
    char* argvQuiet[] = {"app.exe", "-y", "1872", "-q"};
    year = 0;
    success = setSettings(4, argvQuiet, &year, &fastMode, &quietMode);
    if(!success || year != 1872 || !quietMode){ //checks if there are any violations/inconsistensies
        printf("Test case 4\n");
        printf("  Expected - year 1872, quietMode ON, fastMode OFF\n");
        printf("  Actual: year %d, quietMode ", year);
        if(quietMode){
            printf("ON");
        } else {
            printf("OFF");
        }
        printf(", fastMode ");
        if(fastMode){
            printf("ON\n");
        } else{
            printf("OFF\n");
        }
        return false;
    }

    //Test case 5: invalid year argument of 55 with quietMode and fastMode on
    char* argvInvalidYear[] = {"app.exe",  "-y", "55", "-q", "-f"};
    year = 0;
    success = setSettings(5, argvInvalidYear, &year, &fastMode, &quietMode);
    if(!success || year != 0 || !quietMode || !fastMode){ //checks if there are any violations/inconsistensies
        printf("Test case 5\n");
        printf("  Expected - year 0, quietMode ON, fastMode ON\n");
        printf("  Actual: year %d, quietMode ", year);
        if(quietMode){
            printf("ON");
        } else {
            printf("OFF");
        }
        printf(", fastMode ");
        if(fastMode){
            printf("ON\n");
        } else{
            printf("OFF\n");
        }
        return false;
    }

    //Test case 6: no flags provided, expected default values 
    char* argvWithoutFlags[] = {"app.exe"};
    year = 0;
    success = setSettings(1, argvWithoutFlags, &year, &fastMode, &quietMode);
    if(!success || year != 0|| fastMode || quietMode){ //checks if there are any violations/inconsistensies
        printf("Test case 6\n");
        printf("  Expected - year 0, quietMode OFF, fastMode OFF\n");
        printf("  Actual: year %d, quietMode ", year);
        if(quietMode){
            printf("ON");
        } else {
            printf("OFF");
        }
        printf(", fastMode ");
        if(fastMode){
            printf("ON\n");
        } else{
            printf("OFF\n");
        }
        return false;
    }

    //Test case 7: Invalid command line and should return false
    char* argvInvalid[] = {"app.exe", "-y", "1828", "-f", "-p"};
    year = 0;
    success = setSettings(5, argvInvalid, &year, &fastMode, &quietMode);
    if (success) { //checks if the program wrongly returns success
        printf("Test case 7\n");
        printf("  Expected: Failure due to invalid command-line argument\n");
        printf("  Actual: Valid command-line accepted when it shouldn't be\n");
        return false;
    } 
    return true;
}


//function tests the inFilename() with different years
//no parameters
//returns true if all tests pass
bool test_inFilename() {
    char fileName[80]; //buffer to store generated filename
    int year; //variable that holds the year input

    //test case 1: year 2020
    year = 2020;
    inFilename(fileName, year);
    if(strcmp(fileName, "data/2020.csv") != 0){ //compares string between expected vs actual
        printf("Test case 1\n");
        printf("  Expected filename: data/2020.csv\n");
        printf("  Actual filename: %s\n", fileName);
        return false; //returns false if strings are different
    }

    //test case 2: year 1828
    year = 1828;
    inFilename(fileName, year); //compares string between expected vs actual
    if(strcmp(fileName, "data/1828.csv") != 0){
        printf("Test case 2\n");
        printf("  Expected filename: data/1828.csv\n");
        printf("  Actual filename: %s\n", fileName);
        return false; //returns false if strings are different
    }

    //test case 3: year 1900
    year = 1900;
    inFilename(fileName, year); //compares strings between expected vs actual file name
    if(strcmp(fileName, "data/1900.csv") != 0){
        printf("Test case 3\n");
        printf("  Expected filename: data/1900.csv\n");
        printf("  Actual filename: %s\n", fileName);
        return false; //returns false if strings are different
    }
    return true; //if everything passes, returns true
}


//function tests the outFilename() with different years
//no parameters
//returns true if all tests pass
bool test_outFilename() {
    char fileName[80]; //buffer to store generated filename
    int year; //variable that holds the year input

    //test case 1: year 2020
    year = 2020;
    outFilename(fileName, year);
    if(strcmp(fileName, "toWin/2020_win.csv") != 0){ //compares string between expected vs actual
        printf("Test case 1\n");
        printf("  Expected filename: toWin2020_win.csv\n");
        printf("  Actual filename: %s\n", fileName);
        return false; //returns false if strings are different
    }

    //test case 2: year 1828
    year = 1828;
    outFilename(fileName, year);
    if(strcmp(fileName, "toWin/1828_win.csv") != 0){ //compares string between expected vs actual
        printf("Test case 2\n");
        printf("  Expected filename: toWin1828_win.csv\n");
        printf("  Actual filename: %s\n", fileName);
        return false; //returns false if strings are different 
    }

    //test case 3: year 1900
    year = 1900;
    outFilename(fileName, year);
    if(strcmp(fileName, "toWin/1900_win.csv") != 0){ //compares string between expected vs actual
        printf("Test case 3\n");
        printf("  Expected filename: toWin1900_win.csv\n");
        printf("  Actual filename: %s\n", fileName);
        return false; //returns false if strings are different
    }
    return true; //returns true if everything passes

}


//function tests the parseLine() with different lines
//no parameters
//returns true if all tests pass
bool test_parseLine() {
    State sampleState; //sample state struct that stores the sample parsed data
    char line[] = "Illinois,IL,20,6748323";//sample line that will be parsed 
    bool valid = parseLine(line, &sampleState); //the line is parsed and stored into sampleState

    if(!valid){ //checks if parsing was successful to begin with
        printf("Test failed: Unable to read line\n");
        return false;
    }
    if(strcmp(sampleState.name, "Illinois") != 0){ //checks if name was parsed correctly
        printf("Test failed: Name parsed incorrectly\n");
        return false;
    }
    if(strcmp(sampleState.postalCode, "IL") != 0){ //checks if postalCode was parsed correctly
        printf("Test failed: Postal code parsed incorrectly\n");
        return false;
    }
    if(sampleState.electoralVotes != 20){ //checks if electoral votes were parsed correctly
        printf("Test failed: Electoral votes parsed incorrectly\n");
        return false;
    }
    if(sampleState.popularVotes != 6748323){ //checks if popular votes were parsed correctly
        printf("Test failed: Popular votes parsed incorrectly\n");
        return false;
    }
    return true;
}


//function tests the readElectionData() with different csv files
//no parameters
//returns true if all tests pass
bool test_readElectionData() {
    State sampleState[51]; //array created to stores sample state data
    int numStates; //variable that stores the number of states read 
    bool valid = readElectionData("data/1828.csv", sampleState, &numStates); //data is read from a csv file

    if(!valid){ //checks if the file reading was successful 
        printf("Test failed: Unable to read file\n");
        return false;
    }
    if(numStates != 24){ //checks if the number of states read matches expected number 
        printf("Test failed: Wrong state numbers were read\n");
        return false;
    }
    //checks the specific state values such as name, postal code, and votes
    if(strcmp(sampleState[0].name, "Alabama") != 0 || strcmp(sampleState[0].postalCode, "AL") != 0 || sampleState[0].electoralVotes != 5 || sampleState[0].popularVotes!= 18618){
        printf("Test failed: State %s(%s) had a mismatch of values\n", sampleState[0].name, sampleState[0].postalCode);
        return false;
    }
    //checks the specific state values such as name, postal code, and votes
    if(strcmp(sampleState[12].name, "Missouri") != 0 || strcmp(sampleState[12].postalCode, "MO") != 0 || sampleState[12].electoralVotes != 3 || sampleState[12].popularVotes!= 11654){
        printf("Test failed: State %s(%s) had a mismatch of values\n", sampleState[12].name, sampleState[12].postalCode);
        return false;
    }
    //checks the specific state values such as name, postal code, and votes
    if(strcmp(sampleState[8].name, "Maine") != 0 || strcmp(sampleState[8].postalCode, "ME") != 0 || sampleState[8].electoralVotes != 9 || sampleState[8].popularVotes!= 34789){
        printf("Test failed: State %s(%s) had a mismatch of values\n", sampleState[8].name, sampleState[8].postalCode);
        return false;
    }

    State testState[51];
    valid = readElectionData("data/2020.csv", testState, &numStates); //test is repeated with another csv file
    if(!valid){  //checks if the file reading was successful 
        printf("Test failed: Unable to read file\n");
        return false;
    }
    if(numStates != 51){ //checks if the number of states read matches expected number 
        printf("Test failed: Wrong state numbers were read\n");
        return false;
    }
    //checks the specific state values such as name, postal code, and votes
    if(strcmp(testState[0].name, "Alabama") != 0 || strcmp(testState[0].postalCode, "AL") != 0 || testState[0].electoralVotes != 9 || testState[0].popularVotes!= 2323282){
        printf("Test failed: State %s(%s) had a mismatch of values\n", testState[0].name, testState[0].postalCode);
        return false;
    }
    //checks the specific state values such as name, postal code, and votes
    if(strcmp(testState[12].name, "Idaho") != 0 || strcmp(testState[12].postalCode, "ID") != 0 || testState[12].electoralVotes != 4 || testState[12].popularVotes!= 868014){
        printf("Test failed: State %s(%s) had a mismatch of values\n", testState[12].name, testState[12].postalCode);
        return false;
    }
    //checks the specific state values such as name, postal code, and votes
    if(strcmp(testState[8].name, "District of Columbia") != 0 || strcmp(testState[8].postalCode, "DC") != 0 || testState[8].electoralVotes != 3 || testState[8].popularVotes!= 344356){
        printf("Test failed: State %s(%s) had a mismatch of values\n", testState[8].name, testState[8].postalCode);
        return false;
    }
    return true; //returns true if everything passed 
}


//function tests the minPopVoteToWin() with sample states
//no parameters
//returns true if all tests pass
bool test_minPVsSlow() {
    State sampleStates[24] = { //sample states are created 
        {"Alabama", "AL", 5, 18618},
        {"Connecticut", "CT", 8, 19378},
        {"Delaware", "DE", 3, 13944},
        {"Georgia", "GA", 9, 20004},
        {"Illinois", "IL", 3, 14222},
        {"Indiana", "IN", 5, 39210},
        {"Kentucky", "KY", 14, 70776},
        {"Louisiana", "LA", 5, 8687},
        {"Maine", "ME", 9, 34789},
        {"Maryland", "MD", 11, 45796},
        {"Massachusetts", "MA", 15, 39074},
        {"Mississippi", "MS", 3, 8344},
        {"Missouri", "MO", 3, 11654},
        {"New Hampshire", "NH", 8, 44035},
        {"New Jersey", "NJ", 8, 45570},
        {"New York", "NY", 36, 270975},
        {"North Carolina", "NC", 15, 51747},
        {"Ohio", "OH", 16, 131049},
        {"Pennsylvania", "PA", 28, 152220},
        {"Rhode Island", "RI", 4, 3580},
        {"South Carolina", "SC", 11, 51126},
        {"Tennessee", "TN", 11, 46533},
        {"Vermont", "VT", 7, 32833},
        {"Virginia", "VA", 24, 38924}
    };

    MinInfo result = minPopVoteToWin(sampleStates, 24);
    if(result.sufficientEVs != true){ //checks if sufficientEVs flag is true
        printf("Test failed: SufficientEVs should be true\n");
        return false;
    }
    if(result.subsetPVs != 196802){ //checks that the minimum popular votes match the expected value
        printf("Test failed: Expected PVs = %d, Given PVs = %d\n", 196802, result.subsetPVs);
        return false;
    }
    if(result.szSomeStates != 14){  //checks that the number of states in the subset match the expected value
        printf("Test failed: Expected number of states = 14, Given = %d\n", result.szSomeStates);
        return false;
    }
    return true;
}


//function tests the minPopVoteToWinFast() with sample states
//no parameters
//returns true if all tests pass
bool test_minPVsFast() {
    State sampleStates[51] = { //sample states are created 
        {"Alabama", "AL", 9, 2323282},
        {"Alaska", "AK", 3, 359530},
        {"Arizona", "AZ", 11, 3387326},
        {"Arkansas", "AR", 6, 1219069},
        {"California", "CA", 55, 17500881},
        {"Colorado", "CO", 9, 3256952},
        {"Connecticut", "CT", 7, 1824280},
        {"Delaware", "DE", 3, 504010},
        {"District of Columbia", "DC", 3, 344356},
        {"Florida", "FL", 29, 11067456},
        {"Georgia", "GA", 16, 4997716},
        {"Hawaii", "HI", 4, 574469},
        {"Idaho", "ID", 4, 868014},
        {"Illinois", "IL", 20, 6033744},
        {"Indiana", "IN", 11, 3033121},
        {"Iowa", "IA", 6, 1690871},
        {"Kansas", "KS", 6, 1372303},
        {"Kentucky", "KY", 8, 2136768},
        {"Louisiana", "LA", 8, 2148062},
        {"Maine", "ME", 4, 819461},
        {"Maryland", "MD", 10, 3037030},
        {"Massachusetts", "MA", 11, 3631403},
        {"Michigan", "MI", 16, 5539301},
        {"Minnesota", "MN", 10, 3277171},
        {"Mississippi", "MS", 6, 1313759},
        {"Missouri", "MO", 10, 3025962},
        {"Montana", "MT", 3, 603640},
        {"Nebraska", "NE", 5, 951712},
        {"Nevada", "NV", 6, 1405376},
        {"New Hampshire", "NH", 4, 806205},
        {"New Jersey", "NJ", 14, 4549353},
        {"New Mexico", "NM", 5, 923965},
        {"New York", "NY", 29, 8594826},
        {"North Carolina", "NC", 15, 5524804},
        {"North Dakota", "ND", 3, 361819},
        {"Ohio", "OH", 18, 5922202},
        {"Oklahoma", "OK", 7, 1560699},
        {"Oregon", "OR", 7, 2374321},
        {"Pennsylvania", "PA", 20, 6915283},
        {"Rhode Island", "RI", 4, 517757},
        {"South Carolina", "SC", 9, 2513329},
        {"South Dakota", "SD", 3, 422609},
        {"Tennessee", "TN", 11, 3053851},
        {"Texas", "TX", 38, 11315056},
        {"Utah", "UT", 6, 1488289},
        {"Vermont", "VT", 3, 367428},
        {"Virginia", "VA", 13, 4460524},
        {"Washington", "WA", 12, 4087631},
        {"West Virginia", "WV", 5, 794652},
        {"Wisconsin", "WI", 10, 3298041},
        {"Wyoming", "WY", 3, 276765}
    };
    
    MinInfo result = minPopVoteToWinFast(sampleStates, 51);
    if(result.sufficientEVs != true){ //checks if sufficientEVs flag is true
        printf("Test failed: SufficientEVs should be true\n");
        return false;
    }
    if(result.subsetPVs != 34142388){ //checks that the minimum popular votes match the expected value
        printf("Test failed: Expected PVs = %d, Given PVs = %d\n", 34142388, result.subsetPVs);
        return false;
    }
    if(result.szSomeStates != 35){  //checks that the number of states in the subset match the expected value
        printf("Test failed: Expected number of states = 35, Given = %d\n", result.szSomeStates);
        return false;
    }
    return true;
}


int main() {
    printf("Welcome to the Popular Vote Minimizer Testing Suite!\n\n");
    
    printf("Testing totalEVs()...\n"); 
    if (test_totalEVs()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing totalPVs()...\n"); 
    if (test_totalPVs()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing setSettings()...\n"); 
    if (test_setSettings()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }
    
    printf("Testing inFilename()...\n"); 
    if (test_inFilename()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing outFilename()...\n"); 
    if (test_outFilename()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing parseLine()...\n"); 
    if (test_parseLine()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing readElectionData()...\n"); 
    if (test_readElectionData()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }
    
    printf("Testing minPopVoteToWin()...\n"); 
    if (test_minPVsSlow()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing minPopVoteToWinFast()...\n"); 
    if (test_minPVsFast()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    return 0;
}
