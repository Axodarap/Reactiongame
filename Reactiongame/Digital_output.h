#pragma once
#include <wiringPi.h>
#include "IDigitalOut.h"


class Digital_output final : public IDigital_output
{
public:
	Digital_output();
	Digital_output(int pin, bool state);
	bool return_current_state() override;
	void turn_on() override;
	void turn_off() override;
	void blink();


private:
	int pin_;
	bool state_;	//saves current state (on/off)
};

//bla adding to test stuff