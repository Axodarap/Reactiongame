#include "Player.h"

Player::Player() : name_{"Batman"}
{
}

Player::Player(string name) : name_{ name }
{
}

void Player::increase_score()
{
	score_++;
}

int Player::get_score()
{
	return score_;
}

void Player::set_name(string name)
{
	name_ = name;
}

string Player::get_name()
{
	return name_;
}
