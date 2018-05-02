#pragma once


class IDigital_output
{
public:
	virtual void turn_on() = 0;
	virtual void turn_off() = 0;
	virtual bool return_current_state() = 0;

	virtual ~IDigital_output() = 0;
};