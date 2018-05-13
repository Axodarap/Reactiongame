#include "Player.h"


Player::Player(string name) : name_{ name }, score_{0}
{
}

void Player::increase_score()
{
	score_++;
}

void Player::reset_score()
{
	score_ = 0;
}

int Player::get_score()
{
	return score_;
}


string Player::get_name()
{
	return name_;
}
