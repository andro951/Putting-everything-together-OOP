#pragma once
#include <string>
using namespace std;
void displayIntroduction(); //Display a simple opening message.
void displayTime(int& time); //Convert the time into a standard format and display it.
void getUserCommandAndObject(string prompt, string& command, string& object); //Get a command and object from the user with one cin and seperate them.
void didntRecognizeCommand(string command); //Display a simple message when recieveing an unrecoginzed command.
string getInput(); //Use getline to get an input from the user.  Will repeat until userText is not blank.