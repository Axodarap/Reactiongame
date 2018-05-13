#include "Digital_output.h"


Digital_output::Digital_output(int pin, bool state) : pin_{ pin }, state_{ state }
{
	wiringPiSetup();
	pinMode(pin_, OUTPUT);
	digitalWrite(pin_, state_);
}

bool Digital_output::return_current_state()
{
	return digitalRead(pin_);
}

void Digital_output::turn_on()
{
	state_ = true;
	digitalWrite(pin_, HIGH);

}

void Digital_output::turn_off()
{
	state_ = false;
	digitalWrite(pin_, LOW);
}

void Digital_output::blink() const
{
	for(int i=0; i<3; i++)
	{
		digitalWrite(pin_, HIGH);
		delay(500);
		digitalWrite(pin_, LOW);
		delay(500);
	}
	
}
