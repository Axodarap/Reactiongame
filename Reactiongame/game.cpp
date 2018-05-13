#include "game.h"


game::game(int num_rounds, Player p1, Player p2):num_rounds_{num_rounds},p1_{p1},p2_{p2},current_round_{1},rand_delay_{0},start_time_{0},game_state_{Game_state::waiting}
{
}

int game::num_rnds() const
{
	return num_rounds_;
}

int game::current_rnd() const
{
	return current_round_;

}



void game::finish()
{
}

void game::play_round()
{
	constexpr int range = 5;
	constexpr int offset = 5;
	
	srand(time(NULL)); //seeding rand() 
	rand_delay_ = rand() % range + offset; // creating random time delay in s
	cout << "-------- ROUND " << current_round_ << " --------" << endl;
	start_time_ = clock();
}

Game_state game::game_state() const
{
	return game_state_;
}





