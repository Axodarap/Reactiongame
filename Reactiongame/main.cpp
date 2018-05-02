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

// ------------------------------------------------------------ preprocessor stuff ----------------------------------------------------------------
#define BTN1_PIN 0
#define BTN2_PIN 2
#define LED1_PIN 8
#define LED2_PIN 9
#define LED_STAT_PIN 7

// ----------------------------------------------------------- fucntion prototypes ----------------------------------------------------------------
void buttonSetup();
void buttonPlayer1();
void buttonPlayer2();

// ------------------------------------------------------------- global variables -----------------------------------------------------------------
enum states
{
	PREPERATION,
	WAITING,
	LIGHT_UP,
	BTN_PRESSED,
	RESULTS,
	FINISH
};
enum states game_state = PREPERATION;
bool exit_condition = 1;
unsigned int number_of_rounds;
unsigned int current_round;
unsigned int start_time;

bool btn_player1 = false;	//to save which player triggered the interrupt --> could potentially be included in the Player class
bool btn_player2 = false;

unsigned int random_delay;

Player player1;
Player player2;

Digital_output LED_player1(LED1_PIN, LOW); //creating three output objects
Digital_output LED_player2(LED2_PIN, LOW);
Digital_output LED_status(LED_STAT_PIN, LOW);


// ------------------------------------------------------------- main code -----------------------------------------------------------------
using namespace std;

int main(void)
{
	//wiringPiSetup();	//initializing wiringPi library in Digital_output class <-- not ideal
	buttonSetup();

	string input;
	cout << "---------------- the reaction game ----------------" << endl;
	cout << "Player 1, enter your name please: " << endl;
	getline(cin, input);
	player1.set_name(input);
	cout << "Hello " << player1.get_name() << " !\n" << endl;
	cout << "Player 2, enter your name please: " << endl;
	getline(cin, input);
	player2.set_name(input);
	cout << "Hello " << player2.get_name() << " !\n" << endl;
	cout << "Set number of rounds to be played:" << endl;
	cin >> number_of_rounds; //maybe add a feature to check if input is valid
	


	while (exit_condition)
	{
		switch (game_state)
		{
			case PREPERATION:
			{
				current_round++;
				cout << "-------- ROUND " << current_round << " --------" << endl;
				cout << "Current score:  " << player1.get_name() << " [" << player1.get_score() << ":" << player2.get_score() << "] " << player2.get_name() << endl;
				delay(1500);
				cout << "GET READY!" << endl;
				delay(1500);
				cout << "GO!" << endl;
				srand(time(NULL)); //seeding rand() 
				random_delay = rand() % 5 + 5; // creating random time delay in s
				start_time = clock();

				game_state = WAITING;
			}break;

			case WAITING:
			{
				auto time_delta = (clock() - start_time)/CLOCKS_PER_SEC;
				if (time_delta > random_delay)
				{
					game_state = LIGHT_UP;
				}
				// checking if button was pressed too early will be done in the ISR
			}break;

			case LIGHT_UP:
			{
				LED_status.turn_on();
			}break;

			case BTN_PRESSED:
			{
				LED_status.turn_off();
				if (btn_player1)
				{
					player1.increase_score();
					cout << player1.get_name() << " gets a point. \n" << endl;
					LED_player1.blink();
					btn_player1 = false;
				}
				if (btn_player2)
				{
					player2.increase_score();
					cout << player2.get_name() << " gets a point. \n" << endl;
					LED_player2.blink();
					btn_player2 = false;
				}

				if (current_round == number_of_rounds)	//if current round was the last round
					game_state = RESULTS;
				else
					game_state = PREPERATION;
			}break;

			case RESULTS:
			{
				if (player1.get_score() > player2.get_score())
				{
					cout << player1.get_name() << " wins!" << endl;
				}
				else if (player1.get_score() < player2.get_score())
				{
					cout << player2.get_name() << " wins!" << endl;
				}

				else if(player1.get_score() == player2.get_score())
				{
					cout << "Guess what? It's a tie!" << endl;
				}

				cout << "Final score:  " << player1.get_name() << " [" << player1.get_score() << ":" << player2.get_score() << "] " << player2.get_name() << endl;
				game_state = FINISH;
			}break;

			case FINISH:
			{
				// yet to be written:
				//    + maybe add a feature to restart the game
			}break;
		}
	}
}

// ------------------------------------------------------------- additional functions -----------------------------------------------------------------
void buttonSetup()
{
	pinMode(BTN1_PIN, INPUT);
	pinMode(BTN2_PIN, INPUT);

	pullUpDnControl(BTN1_PIN, PUD_DOWN);
	pullUpDnControl(BTN2_PIN, PUD_DOWN);

	wiringPiISR(BTN1_PIN, INT_EDGE_RISING, &buttonPlayer1);
	wiringPiISR(BTN2_PIN, INT_EDGE_RISING, &buttonPlayer2);
}

void buttonPlayer1()
{
	if (game_state == WAITING)
	{
		cout << "Not so fast " << player1.get_name() << "!" << endl;
		btn_player2 = true;
		game_state = BTN_PRESSED;
	}
	if (game_state == LIGHT_UP)
	{
		btn_player1 = true;
		game_state = BTN_PRESSED;
	}
		
	delay(50);	//debounce time
}

void buttonPlayer2()
{
	if (game_state == WAITING)
	{
		cout << "Not so fast " << player2.get_name() << "!" << endl;
		btn_player1 = true;
		game_state = BTN_PRESSED;
	}
	if (game_state == LIGHT_UP)
	{
		btn_player2 = true;
		game_state = BTN_PRESSED;
	}
		
	delay(50);
}