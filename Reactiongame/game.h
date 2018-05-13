#pragma once
#include "Player.h"
#include "Enums.h"

#include <iostream>
#include <string>


class game{
public:
	game(int num_rounds, Player p1, Player p2);
	int num_rnds() const;
	int current_rnd() const;
	void finish();
	void play_round();
	Game_state game_state() const;

private:
	Player p1_;
	Player p2_;
	int num_rounds_;
	int current_round_;
	unsigned int rand_delay_;
	unsigned int start_time_;
	Game_state game_state_;
	
};