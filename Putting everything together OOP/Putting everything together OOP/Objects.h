#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Object
{
public:
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

	void setCommandList(string commandList);
	void examine();
	void listCommands();
	void setExamineText(string examineText);
	void setExamineTime(int examineTime);
	void breakRadiator();
	void pickUp();
	void drop();
private:
	
	string m_ExamineText;
	int m_ExamineTime;
	string m_CommandList;
};