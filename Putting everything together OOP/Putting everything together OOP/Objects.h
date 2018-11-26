#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Object
{
public:
	//Comments explaining the static variables can be found in Objects.cpp.
	static int s_Time;
	static int* s_pTime;
	static bool s_RadiatorAttatchedToFloor;
	static int s_EmptyHands;
	static bool s_Handcuffed;
	static bool s_RoomExamined;
	static bool s_BagSearched;
	static bool s_CarryingRadiator;
	static bool s_CarryingHandcuffs;
	static bool s_CarryingHandgun;
	static bool s_Called911;
	static int s_TimeCalledPolice;

	void setCommandList(string commandList); //Set the string that is displayed for the object when commands for object is input as the command object.
	void examine(); //Display a simple description of the object.
	void listCommands(); //Display the string set by setCommandsList.
	void setExamineText(string examineText); //Set the description of the object.
	void setExamineTime(int examineTime); //Set the ammount of time required to examine the object.
	void breakRadiator(); //Breaks the radiator and allows the player to move around the room.
	void pickUp(); //The player picks up the object if is was previously broken.
	void drop(); //The player drops the object if they were holding it.
private:
	//Private used to prevent other these variables from being directly manipulated without accesing the class's member functions.
	string m_ExamineText; //Stores the examine text for the object.
	int m_ExamineTime; //Stores the time requiered to examine the object.
	string m_CommandList; //Stores the list of available commands for the object.
};