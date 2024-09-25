#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "MinPopVote.h"

//sets the program setting based on the command line
//returns true if the settings are able to be set succesfully
//argc - number of command lines, argv- array of command line strings, year- pointer to an integer to store year
//fastMode - pointer to boolean to store fast setting, quietMode - pointer to bool to store quiet setting
bool setSettings(int argc, char** argv, int* year, bool* fastMode, bool* quietMode) {
    //values are initialized to appropriate starting default settings
    *year = 0; 
    *quietMode = false; 
    *fastMode = false; 
    bool fFound = false, qFound = false, yFound = false;
    //iterates through command line array
    for(int i = 1; i < argc; i++){ 
        if(strcmp(argv[i], "-f") == 0){//checks for -f fast option
            *fastMode = true; //enables fast mode and flags down that fast was set
            fFound = true;
        } else if(strcmp(argv[i], "-q") == 0){ //checks for -q quiet option
            *quietMode = true; //enables quiet mode and flags down that fast was set
            qFound = true;
        } else if(strcmp(argv[i], "-y") == 0){ //checks for -y year option
            yFound = true; //flags down that year was found
            if(i+1 < argc){
                int yr;
                sscanf(argv[i+1], "%d", &yr); //integer is read from argument 
                if(yr % 4 == 0 && yr >= 1828 && yr <= 2020){ //makes sure that year is in range
                    *year = yr;
                } else{
                    *year = 0; //invalid year is set to 0(default)
                }
                i++; //moves to next argument
            } else{
                *year = 0; //no year provided, set to 0
            }
        } else{
            return false; //invalid option, returns false
        }
    }
    if(argc == 1){ //only program name provided, returns true
        return true;
    }
    if(fFound || yFound || qFound){ //any of the three settings found, returns true
        return true;
    }
    return false;//invalid settings or none found
}


//generates input file name with given year
//void: returns nothing
//takes in pointer to character array to store filename
//takes in integer year to use for file name
void inFilename(char* filename, int year) {
    //file name is formatted and stored filename array
    sprintf(filename, "data/%d.csv", year);
}


//generates output file name with given year
//void: returns nothing
//takes in pointer to character array to store filename 
//takes in integer year to use for file name
void outFilename(char* filename, int year) {
    //file name is formatted and stored filename array
    sprintf(filename, "toWin/%d_win.csv", year);
}


//parses a csv line to create the State struct
//returns true if parsing is successful
//takes in the line to be parsed and pointer to the state struct
bool parseLine(char* line, State* myState) {
    char* part = line; //pointer is set to current line being parsed 
    char* comma;//pointer to the position of comma
    int index = 0; //index to track the part of the state info being parsed 

    //loops through the line and extracts info until all 4 parts are parsed 
    while(part != NULL && index < 4){
        comma = strchr(part, ','); //next comma is found in the line
        if(comma != NULL){
            *comma = '\0'; //comma is replaced with null terminator to isolate the part
        }
        if(index == 0){ //extracted part is assigned appropriately 
            strncpy(myState -> name, part, sizeof(myState -> name) -1); //state name is copied and checked for null termination
            myState -> name[sizeof(myState -> name) - 1] = '\0';
        } else if(index == 1){ //state postal code is copied and checked for null termination
            strncpy(myState -> postalCode, part, sizeof(myState -> postalCode) -1);
            myState -> postalCode[sizeof(myState -> postalCode) - 1] = '\0';
        } else if(index == 2){ //string converted to integer 
            myState -> electoralVotes = atoi(part);
        } else if(index == 3){ //string converted to integer 
            myState -> popularVotes = atoi(part);
        } 
        //moves on to the next part of the line 
        if(comma != NULL){
            part = comma +1; //moves after the comma 
        } else{
            part = NULL; //end of parsing, nothing left 
        }
        index ++; //moves on to the next index
    }
    if(index == 4){
        return true;//returns true if all 4 parts were parsed succesfully
    } else{
        return false; //returns false if not
    }
}


//election data is read and populated into array of state struct
//filename - name of file with election data, allStates - array of states
//nStates - Pointer to an  integer that stores the num of states read 
//returns true if all processes were successful
bool readElectionData(char* filename, State* allStates, int* nStates) {
    *nStates = 0; //number of states initialized to 0
    FILE *fileptr = fopen(filename, "r"); //file opened in reading mode
    if(fileptr == NULL){
        return false; //returns file if file was not able to be opened
    }
    char str[300]; //buffer that holds each line from file
    while(fgets(str, sizeof(str), fileptr) != NULL){ //reads each line until the end 
        int length = strlen(str);
        if(length > 0 && str[length -1] == '\n'){ //remove newline character if encountered 
            str[length - 1] = '\0';
        }
        //line is parsed and populated into state struct 
        parseLine(str, &allStates[*nStates]);
        (*nStates) ++; //number of states increased by one 
    }
    fclose(fileptr); //file closed 
    return true;
}


//total number of electoral votes are calculated from a array of State structs
//states - array of State structs, szStates - number of states in array
//returns total number of electoral votes
int totalEVs(State* states, int szStates) {
    int totalElectoral = 0;
    for(int i = 0; i < szStates; i++){ //iterates through each state in array
        totalElectoral += states[i].electoralVotes; //electoral votes are added to total
    }
    return totalElectoral;
}


//total number of popular votes are calculated from a array of State structs
//states - array of State structs, szStates - number of states in array
//returns total number of popular votes
int totalPVs(State* states, int szStates) {
    int totalPopular = 0;
    for(int i = 0; i < szStates; i++){ //iterates through each state in array
        totalPopular += states[i].popularVotes; //popular votes are added to total
    }
    return totalPopular;
}


//determines the minimum popular vote needed to win the election with enough electoral votes 
//states - array of State structs, szStates - number of states in array
//start -starting index for current subset
//EVs - number of electoral votes needed
//szStates- The number of states in the array.
//returns MinInfo structure containing the minimum popular vote subset
MinInfo minPopVoteAtLeast(State* states, int szStates, int start, int EVs) {
    //base case: required electoral votes are 0 or less 
    if(EVs <= 0){
        MinInfo result;
        result.subsetPVs = 0; //no popular votes needed
        result.szSomeStates = 0; //no states 
        result.someStates;
        result.sufficientEVs = true; //electoral votes are sufficient
        return result;
    }
    // base case: all states have been processed
    if(start == szStates){
        MinInfo result;
        result.subsetPVs = 0; //no popular votes due to no states
        result.szSomeStates = 0;
        result.someStates;
        result.sufficientEVs = false; 
        return result;
    }
    int EVsLeft = EVs - states[start].electoralVotes;//electoral votes remaining after current state
    //uses recursion to calculate result excluding/including the current state
    MinInfo excludeState = minPopVoteAtLeast(states, szStates, start + 1, EVs);
    MinInfo includeState = minPopVoteAtLeast(states, szStates, start + 1, EVsLeft);

    int adjustedVotes = (states[start].popularVotes / 2) + 1; //popular vote is adjusted for current state
    includeState.someStates [includeState.szSomeStates] = states[start]; //current state is added to subset 
    includeState.subsetPVs += adjustedVotes; //add the adjusted votes 
    includeState.szSomeStates++;

    if(!excludeState.sufficientEVs){
        return includeState; // includeState is returned if excluded state does not meet the requirement
    } else if(!includeState.sufficientEVs){
        return excludeState; // excludeState is returned if included state does not meet the requirement
    } else{
        // subset with the fewer popular votes is returned if both meet the requirement
        if(excludeState.subsetPVs < includeState.subsetPVs){
            return excludeState;
        } else{
            return includeState;
        }
    }
}


//calculates minimum vote to win the election
//states - array of state structs with electoral data
//szStates - number of states in array
//returns MinInfo structure containing the minimum popular vote subset
MinInfo minPopVoteToWin(State* states, int szStates) {
    int totEVs = totalEVs(states,szStates);// calculate the total number of electoral votes
    int reqEVs = totEVs/2 + 1; // calculate the required electoral votes to win
    return minPopVoteAtLeast(states, szStates, 0, reqEVs); // minPopVoteAtLeast is called to determine the minimum popular vote

}


//determines the minimum popular vote needed to win the election with enough electoral votes and uses memoization for faster performance
//states - array of State structs, szStates - number of states in array
//start -starting index for current subset
//EVs - number of electoral votes needed
//szStates- The number of states in the array.
//returns MinInfo structure containing the minimum popular vote subset
MinInfo minPopVoteAtLeastFast(State* states, int szStates, int start, int EVs, MinInfo** memo) {
    //base case: required electoral votes are 0 or less 
    if(EVs <= 0){
        MinInfo result;
        result.subsetPVs = 0;  //no popular votes needed
        result.szSomeStates = 0;//no states 
        result.someStates;
        result.sufficientEVs = true; //electoral votes are sufficient
        return result;
    }
    // base case: all states have been processed
    if(start == szStates){
        MinInfo result;
        result.subsetPVs = 0;  //no popular votes due to no states
        result.szSomeStates = 0;
        result.someStates;
        result.sufficientEVs = false;
        return result;
    }
    // if statement checks if the sepcific result is already computed in memo table
    if(memo[start][EVs].subsetPVs != -1){
        return memo[start][EVs];
    }
    int EVsLeft = EVs - states[start].electoralVotes; //electoral votes remaining after current state
    //uses recursion to calculate result excluding/including the current state
    MinInfo excludeState = minPopVoteAtLeastFast(states, szStates, start + 1, EVs, memo);
    MinInfo includeState = minPopVoteAtLeastFast(states, szStates, start + 1, EVsLeft, memo);

    int adjustedVotes = (states[start].popularVotes / 2) + 1;//finds the adjusted votes needed for current state 
    includeState.someStates[includeState.szSomeStates] = states[start];//curent state is included in includeState result
    includeState.subsetPVs += adjustedVotes;//adjusted votes added to total popular vote
    includeState.szSomeStates++; //number of states is incremented 

    MinInfo result;
    if(!excludeState.sufficientEVs){
        result = includeState; // includeState is used if excluded state does not meet the requirement
    } else if(!includeState.sufficientEVs){
        result = excludeState; // excludeState is used if included state does not meet the requirement
    } else {
        // subset with the fewer popular votes is used if both meet the requirement
        if(excludeState.subsetPVs < includeState.subsetPVs){
            result = excludeState;
        } else {
            result = includeState;
        }
    }
    memo[start][EVs] = result; //result is memoize in case it can be used in next recursions
    return result;
}


//calculates the minimum popular vote subset required to win the election
//states - pointer to an array of state structs
//szStates - number of states in the 'states' array
//returns a MinInfo struct with information about subset of states that achieve minimum popular votes
MinInfo minPopVoteToWinFast(State* states, int szStates) {
    int totEVs = totalEVs(states, szStates); //calculates total electoral votes
    int reqEVs = totEVs / 2 + 1;//calculates total electoral votes to win(required)
    //initializes table for memoization
    MinInfo** memo = (MinInfo**)malloc((szStates + 1) * sizeof(MinInfo*));
    for (int i = 0; i < szStates + 1; ++i) {
        memo[i] = (MinInfo*)malloc((reqEVs + 1) * sizeof(MinInfo));
        for (int j = 0; j < reqEVs + 1; ++j) {
            memo[i][j].subsetPVs = -1; //subset popular votes are initialized to -1
        }
    }
    MinInfo res = minPopVoteAtLeastFast(states, szStates, 0, reqEVs, memo);//minimum population vote subset is found with memoization
    for (int i = 0; i < szStates + 1; i++) {//memory allocated for the memoization is all freed
        free(memo[i]);
    }
    free(memo);
    return res;//result is returned
}


//function writes election data to a file in a specific format
//election data includes electoral votes, popular votes, electoral votes won, etc
//filenameW - filename that the data will be written to, totEVs - total electoral votes
//totalPVs - total popular votes, wonEVs- electoral votes won by the subset to win the election
//toWin - Mininfo struct with subset states
//function returns true if writing to the file is successful
bool writeSubsetData(char* filenameW, int totEVs, int totPVs, int wonEVs, MinInfo toWin) {
    FILE* fileptr = fopen(filenameW, "w"); //file is opened in writing mode
    if(fileptr == NULL){ //checks if file was opened properly
        return false; 
    }
    //election data is written to the file using the file pointer in a specific format
    fprintf(fileptr, "%d,%d,%d,%d\n", totEVs, totPVs, wonEVs, toWin.subsetPVs);
    //state details are written to the file in reverse detail
    for(int i = toWin.szSomeStates - 1; i >= 0; i--){
        State s = toWin.someStates[i];
        fprintf(fileptr, "%s,%s,%d,%d\n", s.name, s.postalCode, s.electoralVotes, (s.popularVotes / 2) + 1);
    }
    fclose(fileptr); //the file is closed 
    return true; //returns true as everything was written successfully
}
