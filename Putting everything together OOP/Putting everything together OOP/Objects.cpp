#include "Objects.h"

int Object::s_Time = 690; //The start time of the game in minutes where 0 is midnight.
int* Object::s_pTime = &s_Time;
bool Object::s_RadiatorAttatchedToFloor = true; //Track if radiator is attatched to the floor.
int Object::s_EmptyHands = 2; //Track how many hands can be used to pick things up.
bool Object::s_Handcuffed = true; //Track if handcuffs are on the user.
bool Object::s_RoomExamined = false; //Track if the room has been examined by the user.
bool Object::s_BagSearched = false; //Track if the bag has been examined by the user.
bool Object::s_CarryingRadiator = false; //Track if the user is carrying the radiator.
bool Object::s_CarryingHandcuffs = false; //Track if the user is carrying the handcuffs.
bool Object::s_CarryingHandgun = false; //Track if the user is carrying the handgun.
bool Object::s_Called911 = false; //Track if the user called 911.
int Object::s_TimeCalledPolice = 32767; //Initially set to a very high default value to indicate that they were not called.

void Object::examine()
{
	cout << m_ExamineText;
	s_Time += m_ExamineTime;
	return;
}

void Object::listCommands()
{
	cout << m_CommandList << endl;
	return;
}

void Object::setExamineText(string examineText)
{
	m_ExamineText = examineText;
	return;
}

void Object::setExamineTime(int examineTime)
{
	m_ExamineTime = examineTime;
}

void Object::setCommandList(string commandList)
{
	m_CommandList = commandList;
}

void Object::breakRadiator()
{
	if (s_RadiatorAttatchedToFloor) //If the user hasn't done this before, detatch the radiator.
	{
		cout << "After significant effort, you manage to break the radiator off of the wall and are now able to move arround the room, dragging it with you.\n";
		s_Time += 15;
		s_RadiatorAttatchedToFloor = false; //This allows the player to use the command, examine room, and move around the room.
	}
	else if (s_Handcuffed) //If the user has done this before, provide a useless message based on if they are handcuffed that tries to lead them towards getting the handcuffs off.
	{
		cout << "The radiator is already detatched from the wall and you are dragging it with you.\n";
		s_Time += 1;
	}
	else
	{
		cout << "The radiator is already detatched from the wall and you are able to move around the room freely.\n";
		s_Time += 1;
	}
}

void Object::pickUp()
{
	if (s_RadiatorAttatchedToFloor) //If attatched to the floor still, they can't pick it up.
	{
		cout << "The radiator is attatched to the wall and you are unable to pick it up.\n";
		s_Time += 5;
	}
	else if (s_CarryingRadiator) //If already carrying it, they can't pick it up again.
	{
		cout << "You are already carying the radiator.\n";
		s_Time += 1;
	}
	else if (s_EmptyHands < 2) //It requires 2 hands to pick up.  They drop it otherwise.
	{
		cout << "Your attepmt to pick up the radiator, but drop it.  Your hands are too full already.";
		s_Time += 1;
	}
	else //Conditions met to pick up the radiator.
	{
		cout << "You pick up the radiator.\n";
		s_Time += 1;
		s_EmptyHands = 0;
		s_CarryingRadiator = true;
	}
}

void Object::drop()
{
	if (Object::s_CarryingRadiator) //Conditions met to drop the radiator.
	{
		cout << "You put down the radiator.\n";
		Object::s_EmptyHands = 2;
		Object::s_Time += 1;
	}
	else //Provide useless message for trying to drop the radiator when they weren't holding it.
	{
		cout << "You are not carying the radiator.\n";
	}
}