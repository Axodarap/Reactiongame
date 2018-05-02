#pragma once
#include <string>
using namespace std;

class Player
{
	
public:
	Player();
	Player(string name);
	void increase_score();
	int get_score();
	void set_name(string name);
	string get_name();


private:
	string name_;
	unsigned int score_;
};