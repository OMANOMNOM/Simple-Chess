#pragma once
class Screen
{
public:
	/*Screen class (make it an interface)
	Have two types of screen inherit, game and FTXUI
	

	Create screen()
	Display screen/switch to screen
	Delete screen()

	Considerations need to be taken regarding FTXUI and how it works
	*/
	virtual void start() = 0;
	virtual void loop() = 0;
	virtual void end() = 0;

};

