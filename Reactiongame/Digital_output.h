#pragma once
#include <wiringPi.h>



class Digital_output{

public:
	Digital_output(int pin, bool state);
	bool return_current_state();
	void turn_on();
	void turn_off();
	void blink() const;


private:
	int pin_;
	bool state_;	//saves current state (on/off)
};
