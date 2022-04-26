/*  Created 3/18/2021

    Purpose of the program is to receive multiple time inputs from the user
    and add up the time. This is the updated version of time adder v1.0.0.
    This version can handle more input compared to the previous 3.

    The expected input will be in the format min:sec.
    For example, "12:34" would be considered valid input.

    Valid input examples would be:
        12+34+54
        12:00 + 13
        14 + 10:00
        11:00
        12:34 + 13:00 + 41:00
        1+++15

    Invalid input would be:
        gdgrefer (random letters)
        11:11+12:12+11::::10 (A lot of colons)

    Additional Notes:
    The input ":1" would be considered to be 1 second instead of 10 minutes.
    The reason for this is decision is because "1:" would be considered 1 minute.
    Time inputted without a colon will be considered seconds instead of minutes.

    Update 3/23/2022
        Added clc/clear command to clear the console (does not use system commands).
*/

#include <iostream> //cout
#include <vector>
#include <string>
#include <math.h>   //pow
#include <cctype>
#include <algorithm> //remove_if
#include <windows.h> //HANDLE

//Initializing Functions
std::vector<int> getInput(std::vector<int> time);
bool isValid(std::string userInput);
void printTime(std::vector<int> time);
std::vector<int> secToMin(std::vector<int> time);
std::vector<int> convertTime(std::vector<int> time, std::string userInput);
std::vector<int> addTime(std::vector<int> time, std::string timeToAdd);
void cls(HANDLE hConsole);


//Main getting input from user
int main() {
    std::cout << "Custom program by Kttra. Made to add time for user.\nInput 0 if you want to reset the time.\n" << '\n';

    //Initializing Variables
    std::vector<int> time = {0,0};

    //Asking for user input over and over
    do{
        time = getInput(time);
        time = secToMin(time);
        printTime(time);
    }while(true);
}

//Gets input from the user
std::vector<int> getInput(std::vector<int> time){
    std::string userInput;

    std::cout << "Enter time (min:sec): ";
    getline(std::cin, userInput);
    //scanf("%02d:%02d", &min, &sec); another way to get input in specific format, but much more limiting

    //Remove spaces from user's input
    userInput.erase(remove_if(userInput.begin(), userInput.end(), ::isspace), userInput.end());

    //User's input is 0, return
    if(userInput.length() == 1 && userInput[0] == '0'){
        std::cout << "Reset time to: ";
        return {0,0};
    }

    //Check for valid input
    bool validInput = isValid(userInput);

    //Returns the time if input is valid, if not, return previous time
    if(validInput){
        time = convertTime(time, userInput);
        return time;
    }
    //Clear the console
    else if(userInput == "clc" || userInput == "clear"){
        //Can clear with system command but generally better to not use system commands
        HANDLE hStdout;
        hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        cls(hStdout);

        return time;
    }
    else{
        std::cout << "Invalid input!" << '\n';
        return time;
    }
}

//Checks if input is valid.
bool isValid(std::string userInput){
    int length = userInput.length();

    //Exits as requested by user
    if(userInput == "quit" || userInput == "q"){
        exit(0);
    }

    //Check to see if there's any invalid input
    for(int i = 0; i < length; i++){
        if(userInput[i] == '1' || userInput[i] == '2' || userInput[i] == '3' || userInput[i] == '4' || userInput[i] == '5' ||
           userInput[i] == '6' || userInput[i] == '7' || userInput[i] == '8' || userInput[i] == '9' || userInput[i] == '0' ||
           userInput[i] == ':' || userInput[i] == '.' || userInput[i] == '+'){
        }
        else{
            //returns false because input is invalid
            return false;
        }
    }

    return true;
}

//Prints the time, Hours:Minutes:Seconds
void printTime(std::vector<int> time){
    //time/60 = quotient
    //Dividend/divisor - quotient
    int quotient, remainder;

    //Calculates the quotient and remainder
    quotient = time[0]/60;
    remainder = time[0]%60;


    //If it is over a hour
    if(quotient > 0){
        std::cout << quotient << " hrs " << remainder << " mins " << time[1] << " secs" << '\n';
    }
    //If it is only a single hour
    else if(quotient == 1){
        std::cout << quotient << " hr " << remainder << " mins " << time[1] << " secs" << '\n';
    }
    //If it is 0 hours
    else{
        std::cout << time[0] << " mins " << time[1] << " secs" << '\n';
    }
    std::cout << '\n';
}

//Converts userInput to integer form and then adds it up into the time std::vector
std::vector<int> convertTime(std::vector<int> time, std::string userInput){
    //userInput[i] - '0' <-- quick way to convert character to int
    int index = 0;
    std::string timeToAdd;
    int length = userInput.length();

    for(int i = 0; i < length; i++){
        if(userInput[i] == '+'){
            //Separates the string into parts
            timeToAdd = userInput.substr(index, i-index);
            index = i+1;
            time = addTime(time, timeToAdd);
        }
    }
    timeToAdd = userInput.substr(index, length);
    time = addTime(time, timeToAdd);

    return time;
}

//Adds the times together one by one
std::vector<int> addTime(std::vector<int> time, std::string timeToAdd){
    int length = timeToAdd.length();
    int colonIndex = -1;

    //Checks for colon or dot
    for(int i = 0; i < length; i++){
        if(timeToAdd[i] == ':' || timeToAdd[i] == '.'){
            //There is more than one colon or dot in this time
            if(colonIndex > 0){
                std::cout << "Invalid input detected." << '\n';
                return time;
            }
            colonIndex = i;
        }
    }

    //The time is in seconds (Ex: :1, :2, :3, etc.)
    if(colonIndex == 0){
        for(int i = 1; i < length; i++){
            time[1] = time[1] + (timeToAdd[i] - '0')*pow(10,length-i-1);
        }
    }
    //The time is in seconds (Ex: 1, 2, 3, etc.)
    else if(colonIndex == -1){
        for(int i = 0; i < length; i++){
            time[1] = time[1] + (timeToAdd[i] - '0')*pow(10,length-i-1);
        }
    }
    //The time is in minutes and seconds (Ex: 12:34, 56:78, etc.)
    else{
        for(int i = 0; i < colonIndex; i++){
            time[0] = time[0] + (timeToAdd[i] - '0')*pow(10, colonIndex-i-1);
        }
        //Calculating the Amount of seconds
        for(int i = colonIndex + 1; i < length; i++){
            time[1] = time[1] + (timeToAdd[i] - '0')*pow(10,length-i-1);
        }
    }

    return time;
}

//Converts the seconds to minutes if the seconds is greater than 60
std::vector<int> secToMin(std::vector<int> time){
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

//Clearing console without system commands
void cls(HANDLE hConsole){
   COORD coordScreen = {0, 0};    // home for the cursor
   DWORD cCharsWritten;
   CONSOLE_SCREEN_BUFFER_INFO csbi;
   DWORD dwConSize;

    // Get the number of character cells in the current buffer.

   if(!GetConsoleScreenBufferInfo(hConsole, &csbi))
      return;
   dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

   // Fill the entire screen with blanks.

   if(!FillConsoleOutputCharacter(hConsole, (TCHAR) ' ',
      dwConSize, coordScreen, &cCharsWritten))
      return;

   // Get the current text attribute.

   if(!GetConsoleScreenBufferInfo( hConsole, &csbi))
      return;

   // Set the buffer's attributes accordingly.

   if(!FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
      dwConSize, coordScreen, &cCharsWritten))
      return;

   // Put the cursor at its home coordinates.

   SetConsoleCursorPosition(hConsole, coordScreen);
}
