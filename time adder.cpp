/*  Created 10/15/2021

    Purpose of the program is to receive multiple time inputs from the user
    and add up the time.

    The expected input will be in the format min:sec.
    For example, "12:34" would be considered valid input.

    Valid input examples would be:
        12+34+54
        12:00 + 13
        14 + 10:00
        11:00
        12:34 + 13:00 + 41:00

    Invalid input would be:
        14 + 10:00 + 10:00
        10:00 + 14 + 10:00
        12:30 + 12:30 + 12:30
        gdgrefer

    Updated 10/20/2021
        Added the ability to input '+'
*/

#include <iostream> //cout
#include <vector>
#include <string>
#include <math.h>   //pow
#include <cctype>
#include <algorithm> //remove_if

//Initializing Functions
using namespace std;
vector<int> getInput(int* colonIndex, vector<int> time);
int isValid(string userInput);
void printTime(vector<int> time);
vector<int> secToMin(vector<int> time);
vector<int> addInputs(vector<int> time, string userInput);
vector<int> addSpecialCase(vector<int> time, string userInput);
vector<int> simpleAdd(vector<int> time, string userInput);


//Main getting input from user
int main() {
    std::cout << "Custom program by Kttra. Made to add time for user.\nInput 0 if you want to reset the time.\n" << endl;

    //Initializing Variables
    vector<int> time = {0,0};
    int colonIndex = 0;

    //Asking for user input over and over
    do{
        time = getInput(&colonIndex, time);
        printTime(time);
    }while(true);
}

//Checking for correct index
vector<int> getInput(int* colonIndex, vector<int> time){
    string userInput;

    std::cout << "Enter time (min:sec): ";
    getline(cin, userInput);
    //scanf("%02d:%02d", &min, &sec);
    //Remove spaces from user's input
    userInput.erase(remove_if(userInput.begin(), userInput.end(), ::isspace), userInput.end());

    *colonIndex = isValid(userInput);

    switch(*colonIndex){
    //No colon and valid input
    case 0:
        //Calculating the amount of seconds, input was just a number without any colons
        for(int i = 0; i < userInput.length(); i++){
            time[1] = time[1] + (userInput[i] - '0')*pow(10,userInput.length()-i-1);
        }
        return secToMin(time);
        break;
    //Invalid input
    case -1:
        cout << "Invalid input!\n";
        return  time;
        break;
    //User wants to reset time, 0 was inputted
    case -2:
        cout << "Time reset\n";
        return {0,0};
        break;
    //User wants to add inputs
    case -3:
        return addInputs(time, userInput);
        break;
    //Valid input
    default:
        //Calculating the amount of minutes
        for(int i = 0; i < *colonIndex; i++){
            time[0] = time[0] + (userInput[i] - '0')*pow(10,*colonIndex-i-1);
        }

        //Calculating the Amount of seconds
        for(int i = *colonIndex + 1; i < userInput.length(); i++){
            time[1] = time[1] + (userInput[i] - '0')*pow(10,userInput.length()-i-1);
        }

        return secToMin(time);
    }

}

//Checks if input is valid. Returns 0 is there is no colon. Returns -1 is input is invalid. Returns colon index if it exists
int isValid(string userInput){
    int colonIndex = 0;

    //User's input is 0, return -2;
    if(userInput.length() == 1 && userInput[0] == '0'){
        return -2;
    }
    else if(userInput == "quit" || userInput == "q"){
        exit(0);
    }

    //Check if userinput is value and determine where the colon is
    for(int i = 0; i < userInput.length(); i++){
        if(userInput[i] == '1' || userInput[i] == '2' || userInput[i] == '3' || userInput[i] == '4' || userInput[i] == '5' ||
           userInput[i] == '6' || userInput[i] == '7' || userInput[i] == '8' || userInput[i] == '9' || userInput[i] == '0'||
           userInput[i] == ':' || userInput[i] == '.' || userInput[i] == '+'){

            //If Colon Exists change the index
            if(userInput[i] == ':' || userInput[i] == '.'){
                //Making sure if there has ever previously been a detected '+'
                if(colonIndex != -3){
                    colonIndex = i;
                }
            }
            //'+' is found, returning -3 to signal user wants to add times
            else if(userInput[i] == '+'){
                colonIndex = -3;
            }
        }
        else{
            //returns -1 b/c input is invalid
            return colonIndex = -1;
        }
    }

    //Returns colon index, returns 0 if no colon/dot index is found
    return colonIndex;
}

//Prints the time
void printTime(vector<int> time){
    //time/60 = quotient
    //Dividend/divisor - quotient
    int quotient, remainder;

    //Calculates the quotient and remainder
    quotient = time[0]/60;
    remainder = time[0]%60;

    if(quotient > 0){
        cout << quotient << " hrs " << remainder << " mins " << time[1] << " secs" << endl;
    }
    else if(quotient == 1){
        cout << quotient << " hr " << remainder << " mins " << time[1] << " secs" << endl;
    }
    else{
        cout << time[0] << " mins " << time[1] << " secs" << endl;
    }
}

//Converts the seconds to minutes if the seconds is greater than 60
vector<int> secToMin(vector<int> time){
    //Returns the time if no change is needed
    if(time[1] < 60){
        return time;
    }

    //time/60 = quotient
    //Dividend/divisor - quotient
    int quotient, remainder;

    //Calculates the quotient and remainder
    quotient = time[1]/60;
    remainder = time[1]%60;

    //Recalculates the actual time
    time[0] = time[0] + quotient;
    time[1] = remainder;

    return time;
}

//Adds inputs, 12:00 + 13:00, or 12:00 + 12
vector<int> addInputs(vector<int> time, string userInput){
    vector<int> addIndex = {-1};
    vector<int> colIndex = {};

    //Checking the indexes of '+', 0 index initially
    for(int i=0; i<userInput.length(); ++i) {
      if(userInput[i] == '+') {
         addIndex.push_back(i);
        }
    }
    addIndex.push_back(userInput.length());

    //Checking the indexes of ':' or '.'
    for(int i=0; i<userInput.length(); ++i) {
      if(userInput[i] == ':' || userInput[i] == '.') {
         colIndex.push_back(i);
        }
    }

    //Mix-match with the number of operations needed and the number of colons
    if(colIndex.size() != addIndex.size()-1){
        if(colIndex.size() == 0){
            return simpleAdd(time, userInput);
        }
        //Input was something like 12:00 + 11; colons were on left hand side of addition sign
        if(colIndex[0] < addIndex[1]){
            colIndex.push_back(userInput.length());
        }
        //Input was something like 11 + 12:00, colons were on right side of addition sign
        else{
            return addSpecialCase(time, userInput);
        }
    }

    //Function not made to calculate multiple additions
    if(addIndex.size() != 3){
        cout << "Invalid input!" << endl;
        return time;
    }

    //Loops for how much times we need to add times together
    for(int i = 0; i < addIndex.size() - 1; i++){
        //Calculating the amount of minutes for first loop, seconds for 2nd loop
        for(int j = addIndex[i] + 1; j < colIndex[i]; j++){
            time[i] = time[i] + (userInput[j] - '0')*pow(10,colIndex[i]-j-1);
        }

        //Calculating the Amount of seconds
        for(int j = colIndex[i] + 1; j < addIndex[i+1]; j++){
            time[1] = time[1] + (userInput[j] - '0')*pow(10,addIndex[i+1]-j-1);
        }
    }

    return secToMin(time);
}

//Special case
//Input was something like 11 + 12:00, colons were on right side of addition sign
vector<int> addSpecialCase(vector<int> time, string userInput){
    vector<int> addIndex = {-1};
    vector<int> colIndex = {};

    //Checking the indexes of '+', -1 index initially, and string length
    for(int i=0; i<userInput.length(); ++i) {
      if(userInput[i] == '+') {
         addIndex.push_back(i);
        }
    }
    addIndex.push_back(userInput.length());

    //Function not made to calculate multiple additions
    if(addIndex.size() != 3){
        cout << "Invalid input!" << endl;
        return time;
    }

    //Checking the indexes of ':' or '.'
    for(int i=0; i<userInput.length(); ++i) {
      if(userInput[i] == ':' || userInput[i] == '.') {
         colIndex.push_back(i);
        }
    }

        int i = 0;
        //Left side seconds, 12, the one without colon/dot
        for(int j = addIndex[i] + 1; j < addIndex[i+1]; j++){
            time[1] = time[1] + (userInput[j] - '0')*pow(10,addIndex[i+1]-j-1);
        }
        //Right side, minutes 12:00
        for(int j = addIndex[i+1] + 1; j < colIndex[i]; j++){
            time[0] = time[0] + (userInput[j] - '0')*pow(10,colIndex[i]-j-1);
        }

        //Calculating the Amount of seconds, right side 12:00
        for(int j = colIndex[i] + 1; j < userInput.length(); j++){
            time[1] = time[1] + (userInput[j] - '0')*pow(10,userInput.length()-j-1);
        }


    return secToMin(time);
}

//Adding seconds together, input had no colons Ex: 12+13+45
vector<int> simpleAdd(vector<int> time, string userInput){
    vector<int> addIndex = {-1};

    //Checking the indexes of '+', -1 index initially, and string length
    for(int i=0; i<userInput.length(); ++i) {
      if(userInput[i] == '+') {
         addIndex.push_back(i);
        }
    }
    addIndex.push_back(userInput.length());

    //Loops for how much times we need to add times together
    for(int i = 0; i < addIndex.size() - 1; i++){
        for(int j = addIndex[i] + 1; j < addIndex[i+1]; j++){
            time[1] = time[1] + (userInput[j] - '0')*pow(10,addIndex[i+1]-j-1);
        }
    }

    return secToMin(time);
}

