#include "winkey.h"

int	main(void)
{
	// Get a handle to the specified standard device (stdin, stdout, stderr)
	HANDLE	hInput = GetStdHandle(STD_INPUT_HANDLE);

	/* 
		Describes an input event in the console input buffer.
		Can be read from the input buffer by using the ReadConsoleInput or PeekConsoleInput function.
		OR
		Written to the input buffer by using the WriteConsoleInput function.
	*/
	INPUT_RECORD	inputRecord;

	// Used to received the number of input records read.
	DWORD	event;

	// Open file
	std::ofstream	file;
	file.open("file.log", ios::in | ios::out);
	std::string	buffer;
	while (1)
	{
		// Read data from a console input buffer and removes it from the buffer.
		ReadConsoleInput(hInput, &inputRecord, 1, &event);
		if (inputRecord.EventType == KEY_EVENT && inputRecord.Event.KeyEvent.bKeyDown) {
			// Get the last clicked char
			char ch = inputRecord.Event.KeyEvent.uChar.AsciiChar;

			// Get the keycode 
			WORD	vkKey = inputRecord.Event.KeyEvent.wVirtualKeyCode;

			if (vkKey == VK_RETURN)
			{
				std::cout << "Return" << std::endl;
				file << buffer << std::endl;
				buffer.clear();
			}
			else if (vkKey == VK_ESCAPE)
			{
				std::cout << "Escape" << std::endl;
				file.close();
				break;
			}
			else if (vkKey == VK_BACK && !buffer.empty())
			{
				std::cout << "Backspace" << std:endl;
				buffer.pop_back();
				std::cout << "\b \b";
			}
			else if (ch != 0)
			{
				buffer += ch;
				std::cout << ch;
			}
		}
	}
	return 0;
}