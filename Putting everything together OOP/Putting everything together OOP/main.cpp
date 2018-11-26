//Interactive fiction.
#include <iostream>
#include <string>
#include "functions.h"
#include "Objects.h"
using namespace std;

int main()
{
	Object blah;
	Object radiator;
	radiator.setExamineText("The radiator is old and slightly rusted.\n");
	radiator.setExamineTime(1);
	radiator.setCommandList("Available commands for radiator: examine, break, pick up, drop\n");
	displayIntroduction();
	displayTime(Object::s_pTime);
	string command; //Stores the command for the object the user wants to interact with.
	string object; //Stores the object the user wants to interact with.
	getUserCommandAndObject("What will you do?\n", command, object); //Get the first command and object from the user.
																	 //game loop
	bool gameOver = false; //If gameOver is true, the player WINS!!!
	while (Object::s_Time < 730 and gameOver != true) //Reapeat until the time has progressed to 730 or the the game has ended for another reason.

											//Below is a large if, else if logic structure.  It is used to determine what to output for the user and how to change the game's logic state based on the user's command and object inputs.

	{
		if (object == "radiator")
		{
			if (command == "examine" || command == "look at" || command == "view")
			{
				radiator.examine();
			}
			else if (command == "move" || command == "remove" || command == "break")
			{
				radiator.breakRadiator();
			}
			else if (command == "pick up")
			{
				radiator.pickUp();
			}
			else if (command == "drop" || command == "put down")
			{
				radiator.drop();
			}
			else if (command == "list commands for" || command == "list commands" || command == "commands for" || command == "commands")
			{
				radiator.listCommands();
			}
			else //Any other command for radiator is unrecognized.
			{
				didntRecognizeCommand(command);
			}
		}
		else if (object == "handcuffs")
		{
			if (command == "examine" || command == "look at" || command == "view")
			{
				cout << "A standard pair of handcuffs.\n";
				Object::s_Time += 1;
			}
			else if (command == "pick up" || command == "take")
			{
				if (Object::s_Handcuffed) //Can't pick up if still handcuffed.
				{
					cout << "The handcuffs are still attatched to your hands.  You are unable to pick them up.\n";
					Object::s_Time += 1;
				}
				else
				{
					if (Object::s_CarryingHandcuffs) //Can't pick up if already carrying.
					{
						cout << "You are already carrying the handcuffs.\n";
						Object::s_Time += 1;
					}
					else //Meets the conditions to pick up the handcuffs.
					{
						cout << "You pick up the handcuffs\n";
						Object::s_CarryingHandcuffs = true;
						Object::s_Time += 1;
					}
				}
			}
			else if (command == "drop" || command == "put down")
			{
				if (Object::s_CarryingHandcuffs) //Meets the conditions to drop the handcuffs.
				{
					cout << "You put down the handcuffs.\n";
					Object::s_EmptyHands += 1;
					Object::s_Time += 1;
				}
				else //Not carrying them, gives useless message.
				{
					cout << "You are not carying the handcuffs.\n";
					Object::s_Time += 1;
				}
			}
			else if (command == "unlock")
			{
				if (Object::s_Handcuffed)
				{
					if (Object::s_BagSearched) //Can only unlock the handcuffs if you know where the key is which is inside the bag.
					{
						cout << "You unlock the handcuffs.\n";
						Object::s_Handcuffed = false;
						Object::s_Time += 3;
					}
					else //Otherwise, you have no way to unlock them.
					{
						cout << "You have no way of unlocking the handcuffs.\n";
						Object::s_Time += 1;
					}
				}
				else
				{
					cout << "The handcuffs are already unlocked.\n";
					Object::s_Time += 1;
				}
			}
			else if (command == "list commands for" || command == "list commands" || command == "commands for" || command == "commands")
			{
				cout << "Available commands for handcuffs: examine, pick up, drop, unlock\n";
			}
			else //Any other command for handcuffs is unrecognized.
			{
				didntRecognizeCommand(command);
			}
		}
		else if (object == "room")
		{
			if (command == "examine" || command == "look at" || command == "view")
			{
				if (Object::s_RadiatorAttatchedToFloor) //Can't move around the room until the radiator is disconected from the floor.
				{
					cout << "You can not see or reach the rest of the room.\n";
					Object::s_Time += 1;
				}
				else
				{
					cout << "In the room, there is a phone, a bag and a door.\n";
					Object::s_RoomExamined = true;
					Object::s_Time += 5;
				}
			}
			else if (command == "list commands for" || command == "list commands" || command == "commands for" || command == "commands")
			{
				cout << "Available commands for room: examine\n";
			}
			else //Any other command for room is unrecognized.
			{
				didntRecognizeCommand(command);
			}
		}
		else if (object == "bag" && Object::s_RoomExamined)
		{
			if (command == "examine" || command == "look at" || command == "view")
			{
				if (Object::s_BagSearched)
				{
					cout << "There is nothing else of note in the bag.\n";
					Object::s_Time += 1;
				}
				else
				{
					cout << "The bag contains a gun and a handcuff key.\n";
					Object::s_BagSearched = true; //Give the player access to the command unlock handcuffs and access to the handgun.
					Object::s_Time += 1;
				}
			}
			else if (command == "list commands for" || command == "list commands" || command == "commands for" || command == "commands")
			{
				cout << "Available commands for bag: examine\n";
			}
			else //Any other command for  is unrecognized.
			{
				didntRecognizeCommand(command);
			}

		}
		else if (object == "handgun" && Object::s_BagSearched)
		{
			if (command == "examine" || command == "look at" || command == "view")
			{
				cout << "Loaded.  Safety off.  Round in the chamber.  Ready to fire.\n";
			}
			else if (command == "pick up" || command == "take")
			{
				if (Object::s_CarryingHandgun) //Already carrying it.
				{
					cout << "You are already carrying the handgun.\n";
					Object::s_Time += 1;
				}
				else
				{
					if (Object::s_EmptyHands >= 1) //If you have enough empty hands, you meet the conditions to pick it up.
					{
						cout << "You pick up the handgun.\n";
						Object::s_EmptyHands -= 1;
						Object::s_Time += 1;
					}
					else //Don't have enough empty hands.
					{
						cout << "Your attepmt to pick up the handgun, but drop it.  Your hands are too full already.";
						Object::s_Time += 1;
					}
				}
			}
			else if (command == "drop" || command == "put down")
			{
				if (Object::s_CarryingHandgun) //Meets the conditions to drop the handgun.
				{
					cout << "You put down the handgun.\n";
					Object::s_EmptyHands += 1;
					Object::s_Time += 1;
				}
				else
				{
					cout << "You are not carying the handgun.\n";
					Object::s_Time += 1;
				}
			}
			else if (command == "list commands for" || command == "list commands" || command == "commands for" || command == "commands")
			{
				cout << "Available commands for handgun: examine, pick up, drop\n"; //List the currently available commands for the object.
			}
			else //Any other command for handgun is unrecognized.
			{
				didntRecognizeCommand(command);
			}

		}
		else if (object == "phone" && Object::s_RoomExamined)
		{
			if (command == "examine" || command == "look at" || command == "view")
			{
				cout << "A typical phone found in a hotel room.\n";
				Object::s_Time += 1;
			}
			else if (command == "use" || command == "call")
			{
				bool waitingForValidInput = true;
				while (waitingForValidInput) //Repeats until a valid input is entered.
				{
					cout << "Would you like to call 911 or the front desk? (type 911 or front desk)\n";
					string userAnswer; //Stores the user's answer to the above question.
					userAnswer = getInput();
					// If the user wants to call 911, they will win at the end if the end is >= 20 minutes from the time they called.
					if (userAnswer == "911")
					{
						Object::s_Called911 = true; //Determines if the program will calculate the time the user called 911 at the end of the time limit.
						waitingForValidInput = false;
						cout << "You inform the police of your situation and hang up the phone.\n";
						Object::s_TimeCalledPolice = Object::s_Time; //Used to calculate if 911 was called at least 20 minutes before the game was over.
						Object::s_Time += 5;
						//Note that removing the radiator takes 15 minutes and examining the room takes 5 minutes.  If the user does anything else before calling 911, they will not win from it.
					}
					else if (userAnswer == "front desk") //The user will inform their captor by calling the front desk and will loose immediatly.
					{
						cout << "You inform the front desk of your situation and hang up the phone.\n"
							<< "The front desk clerk informs you that they will be right up to help.\n";
						Object::s_Time = 730; //Changes the time to immediatly end the game.
						waitingForValidInput = false;
					}
					else //If anything other than 911 or front desk is entered, repeat the waitingForValidInput loop.
					{
						cout << "\nInvalid input.\n\n";
					}
				}
			}
			else if (command == "list commands for" || command == "list commands" || command == "commands for" || command == "commands")
			{
				cout << "Available commands for phone: examine, use\n";
			}
			else //Any other command for phone is unrecognized.
			{
				didntRecognizeCommand(command);
			}

		}
		else if (object == "door" && Object::s_RoomExamined)
		{
			if (command == "examine" || command == "look at" || command == "view")
			{
				cout << "A typical hotel room door.\n";
				Object::s_Time += 1;
			}
			else if (command == "use" || command == "open")
			{
				if (Object::s_Handcuffed) //If still handcuffed to the radiator and dragging it around, the user can't leave.
				{
					cout << "You won't make it far dragging around a radiator.\n";
					Object::s_Time += 1;
				}
				else //The user wins the game.
				{
					cout << "You leave the hotel and never look back.\n"; //The user wins.
					gameOver = true; //Prevents any of the logic after the game loop from executing.  Aka, prevents other endings.
				}
			}
			else if (command == "list commands for" || command == "list commands" || command == "commands for" || command == "commands")
			{
				cout << "Available commands for : examine, use\n";
			}
			else //Any other command for door is unrecognized.
			{
				didntRecognizeCommand(command);
			}

		}
		//This is a placeholder for adding new objects into the game.
		else if (object == "" && Object::s_RoomExamined)
		{
			if (command == "examine" || command == "look at" || command == "view")
			{
				cout << ".\n";
				Object::s_Time += 1;
			}
			else if (command == "pick up" || command == "take")
			{

			}
			else if (command == "drop" || command == "put down")
			{

			}
			else if (command == "list commands for" || command == "list commands" || command == "commands for" || command == "commands")
			{
				cout << "Available commands for : examine, pick up, drop\n";
			}
			else
			{
				didntRecognizeCommand(command);
			}

		}
		else if (object == "objects")
		{
			if (command == "list" || command == "list of")
			{
				if (Object::s_RoomExamined) //Only list the object in the room if they player has examined the room.
				{
					if (Object::s_BagSearched) //Only list the objects in the bag if it has been searched.
					{
						cout << "objects: room, radiator, handcuffs, bag, phone, door, handgun\n";
					}
					else
					{
						cout << "objects: room, radiator, handcuffs, bag, phone, door\n";
					}
				}
				else //If the room hasn't been searched, list the starting known objects.
				{
					cout << "objects: room, radiator, handcuffs\n";
				}
			}
			else if (command == "list commands for" || command == "list commands" || command == "commands for" || command == "commands")
			{
				cout << "Available commands for objects: list\n";
			}
			else //Any other command for objects is unrecognized.
			{
				didntRecognizeCommand(command);
			}
		}
		//Because of the way commands and objects are determined by the getUserCommandAndObject function, one word actions that you would expect to be alled commands are recognized as objects.
		else if (object == "wait")
		{
			cout << "You paitiently wait a few minutes.";
			Object::s_Time += 5;
		}
		else if (object == "help")
		{
			cout << "To interact with the objects in the room, enter the command for that object followed by the object. (command object)\n"
				<< "To see all objects currently available to you, type \"list objects\".\n"
				<< "To see the commands for an object, type \"commands for \" followed by the objects name.  For example, \"commands for room\".\n"
				<< "Type \"wait\" to wait 5 minutes.\n";
		}
		//This is a placeholder for adding new objects into the game.
		else if (object == "")
		{
			if (command == "examine" || command == "look at" || command == "view")
			{
				cout << ".\n";
				Object::s_Time += 1;
			}
			else if (command == "pick up" || command == "take")
			{

			}
			else if (command == "drop" || command == "put down")
			{

			}
			else if (command == "list commands for" || command == "list commands" || command == "commands for" || command == "commands")
			{
				cout << "Available commands for : examine, pick up, drop\n";
			}
			else
			{
				didntRecognizeCommand(command);
			}

		}
		else //Any other object is unrecognized.
		{
			cout << "Didn't regognize the object, " << object << ".";
		}

		cout << "----------------------------------------------------\n";

		if (gameOver != true) //If the player did not win yet, get a new command and object.
		{
			displayTime(Object::s_pTime);
			getUserCommandAndObject("What will you do next?\n", command, object); //Get all subsequent commands and objects.  Once each time the game loop repeats.
		}
	}
	if (Object::s_TimeCalledPolice <= 710) //If the player called the police in time, they will win.
	{
		gameOver = true; //Player wins.
		cout << "The police arive and escort you home.\n";
	}
	if (gameOver != true) //If player did not win until now, they will loose.  There is no way to win after the captor enters the room.
	{
		cout << "A tall figure enters the dark room.\n";
		if (Object::s_CarryingHandgun)
		{
			//Ask if they will shoot.  If so, they go to prison for shooting the front desk clerk.  Otherwise they are killed.
			bool waitingForValidInput = true;
			while (waitingForValidInput) //Repeats until a valid input is entered.
			{
				cout << "Will you shoot? (type yes or no)\n";
				string userAnswer; //Stores the user's answer to the above question.
				cin >> userAnswer;
				if (userAnswer == "yes" || userAnswer == "Yes" || userAnswer == "YES") //If yes is entered, they shoot the person who entered the room and they loose.
				{
					cout << "BANG!....The figure drops to the floor in a pool of blood.\n"
						<< "You rush out of the room.  Who did I just shoot?\n"
						<< "Later that week, you are arrested for murder.\n\n";
					waitingForValidInput = false;
				}
				else if (userAnswer == "no" || userAnswer == "No" || userAnswer == "NO") //If they don't shoot, they are killed.
				{
					waitingForValidInput = false;
				}
				else //If anything other than yes or no is entered, repeat the waitingForValidInput loop.
				{
					cout << "\nInvalid input.\n\n";
				}
			}
		}
		cout << "You loose.\n";
	}
	system("pause");
	return 0;
}