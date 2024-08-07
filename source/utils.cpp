#include "../tinky.h"

VOID	writeLogsToFile(const std::wstring& logMessage)
{
	OutputDebugStringW(logMessage.c_str());
}