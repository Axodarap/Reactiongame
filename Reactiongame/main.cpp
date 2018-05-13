/*
################################################
##                                            ##
##       Reactiongame v 1.0                   ##
##       by Michaela Neuhold & Jakob Soukup   ## 
##                                            ##
##		 18.04.2018                           ##
##                                            ##
################################################
*/

#include "Digital_output.h"
#include <iostream>
#include "Player.h"
#include "game.h"

bool btn1 = false;
bool btn2 = false;	//cant't find a way to get this to work without global variables


// ----------------------------- function prototypes ------------------------------------
string register_player(int num);
void buttonSetup();

//---------------------------------- functions ------------------------------------------
void main()
{
	//setting up the hardware
	buttonSetup();

	//registering players
	Player p1(register_player(1));
	Player p2(register_player(2));

	cout << "Set number of rounds to be played:" << endl;
	int num_rounds;
	cin >> num_rounds;
	
	game react(num_rounds, p1, p2);	//creating game object

	if(react.current_rnd() > react.num_rnds)	//checking if round cap has been reached
	{
		react.finish();
		return;
	}

	react.play_round();

	
	
}

string register_player(int num)
{
	string input;
	cout << "Player " << num <<", enter your name please: " << endl;
	getline(cin, input);

	return input;
}

void buttonSetup()
{
	constexpr int btn1_pin = 1;
	constexpr int btn2_pin = 2;

	pinMode(btn1_pin, INPUT);
	pinMode(btn2_pin, INPUT);

	pullUpDnControl(btn1_pin, PUD_DOWN);
	pullUpDnControl(btn2_pin, PUD_DOWN);

	wiringPiISR(btn1_pin, INT_EDGE_RISING, &buttonPlayer1);
	wiringPiISR(btn2_pin, INT_EDGE_RISING, &buttonPlayer2);
}

void buttonPlayer1()
{
	if(!btn1)
	{
		btn1 = true;
	}
}

void buttonPlayer2()
{ 
	if(!btn2)
	{
		btn2 = true;
	}
}