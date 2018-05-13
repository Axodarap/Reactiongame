#pragma once
#include <string>
using namespace std;

class Player
{
	
public:
	Player(string name);
	void increase_score();
	void reset_score();
	int get_score();
	string get_name();


private:
	string name_;
	unsigned int score_;
};