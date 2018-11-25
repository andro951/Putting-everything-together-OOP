#include <iostream>
#include <string>
#include "functions.h"
using namespace std;
//Display a simple opening message.
void displayIntroduction()
{
	cout << "You wake up in a dark room.\n"
		<< "You aren't sure where you are or how you got there.\n"
		<< "You soon realize that you are in a hotel room.\n"
		<< "You try to get up, but your hands are handcuffed to the radiator.\n\n\n"


		<< "To interact with the objects in the room, enter the command for that object followed by the object. (command object)\n"
		<< "To see all objects currently available to you, type \"list objects\".\n"
		<< "To see the commands for an object, type \"commands for \" followed by the objects name.  For example, \"commands for room\".\n"
		<< "Type \"wait\" to wait 5 minutes.\n"
		<< "Type \"help\" to redisplay this information.\n\n"
		<< "Your only hint is to do things as you would actually do them.\n\n";
}

//Convert the time into a standard format and display it.
void displayTime(int& time)
{
	//time is in minutes.
	int days = time / 3600; //calculate the number of days from time. (range from 0-infinite) (not used in this program.)
	int hours = (time % 3600) / 60; //calculate the number of hours from time. (range from 0-23)
	int minutes = time % 60; //calculate the number of minutes. (range from 0-59)
	cout << "The current time is: ";
	if (hours % 12 < 10) //Convert hours from 24 hour to 12 hour time. If it is < 10, output a zero to make it look like a clock would.
	{
		cout << "0";
	}
	cout << hours % 12; //Convert hours from 24 hour to 12 hour time and output it.
	if (minutes < 10) //If minutes are < 10, output a zero to make it look like a clock would.
	{
		cout << "0";
	}
	cout << minutes;
	if (hours > 12) //If hours is > 12, display PM.
	{
		cout << " PM\n";
	}
	else //If <12, display AM.
	{
		cout << " AM\n";
	}
}

//Get a command and object from the user with one cin and seperate them.
void getUserCommandAndObject(string prompt, string& command, string& object)
{
	string userText = "";
	cout << prompt;
	userText = getInput();
	for (unsigned int i = 0; i < userText.length(); i++)
	{
		userText[i] = tolower(userText[i]); //Convert each letter in userText to lowercase.
	}
	command = "";
	object = "";
	string backwardsObject = ""; //Stores the object backwards temporarily.
	bool determinedObject = false; //Tracks if a whitespace has been reach in userText.
	int determinedObjectAt; //Tracks where the first whitespace was reached in userText.
	string blank = " "; //Prevents an issue with compairing " ", a const char to another char.
						//The user is asked to input a command followed by an assosiated object.  The user is told that the object can only be one word.  This for loop creates string object and string command from string userText.
	for (int i = userText.length() - 1; i > -1; i--) //Starting from the end of userText, look at each char.  Until a whitespace is found, add the char to backwardsObject.  Once a whitespace is found, make the command and object.
	{
		if (userText[i] == blank[0] && determinedObject != true) //2nd Once you reach a space, the object has been determined.  Stop adding characters to backwardsObject.
		{
			determinedObject = true;
			determinedObjectAt = i;
		}
		else if (determinedObject == true) //3rd 
		{
			for (int k = backwardsObject.length() - 1; k > -1; k--) //use backwardsObject to make object.
			{
				object += backwardsObject[k];
			}
			for (int j = 0; j < determinedObjectAt; j++) //The rest of userText is used to make command.
			{
				command += userText[j];
			}
			return; //The program has determined the command and object and does not provide any further value by continuing.  End the program.
		}
		else //1st Starting from the end of the string, userText, add characters to backwardsObject until you reach a space.
		{
			backwardsObject += userText[i];
		}
		if (i == 0 && object == "") //Sometimes the user will input 1 word with no whitespaces.  If that happens, the object is userText. (command is blank)
		{
			object = userText;
		}
	}
	return; //The program has evaluated all of the char in userText.  End the program.
}

//Display a simple message when recieveing an unrecoginzed command.
void didntRecognizeCommand(string command)
{
	cout << "Didn't regognize the command, " << command << ".\n";
}

string getInput()
{
	string userInput;
	do //Prevents the user from inputting a blank command and an bug that would create a blank command when useing use phone.
	{
		getline(cin, userInput, '\n'); //Allows the user to input whitespaces which cin does not.
	} while (userInput == "");
	return userInput;
}