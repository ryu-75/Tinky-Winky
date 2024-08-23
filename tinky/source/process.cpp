#include "../ticky.h"

DWORD	findProcessById(const char* svcName)
{
	HANDLE	hSnapshot;
	PROCESSENTRY32	processEntry;
	BOOL	hResult;
	DWORD	pid;

	// snapshot of all processes in the system
	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hSnapshot)
		return 1;

	// initializing size: needed for using Process32First
	processEntry.dwSize = sizeof(PROCESSENTRY32);
	hResult = Process32First(hSnapshot, &processEntry);

	if (!hResult) 
	{
		printf("Process32First failed (%d)\n", GetLastError());
		CloseHandle(hSnapshot);
		return 1;
	}
	// retrieve information about the processes
	// and exit if unsuccessful
	do {
		// if we find the process: return process ID
		if (!std::strcmp(svcName, processEntry.szExeFile))
		{
			pid = processEntry.th32ProcessID;
			break;
		}
	} while (Process32Next(hSnapshot, &processEntry));
	CloseHandle(hSnapshot);
	return (pid);
}

void	killProcessById(DWORD pid) {
	HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);

	if (hProcess == NULL)
	{
		printf("OpenProcess failed (%d)\n", GetLastError());
		return;
	}
	if (!TerminateProcess(hProcess, 1))
		printf("TerminateProcess failed (%d)\n", GetLastError());
	CloseHandle(hProcess);
}

//Not sure with this yet
void	createProcess(const char* arg)
{
	STARTUPINFO	si;
	PROCESS_INFORMATION	pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcess(
		NULL,				// No module name (use command line)
		(LPSTR)arg,		// Command line
		NULL,				// Process handle not inheritable
		NULL,				// Thread handle not inheritable
		FALSE,				// Set handle inheritance to FALSE
		0,					// No creation flags
		NULL,				// Use parent's environment block
		NULL,				// Use parent's starting directory
		&si,				// Pointer to STARTUPINFO structure
		&pi					// Pointe to PROCESS_INFORMATION structure
	))
	{
		printf("CreateProcess failed %d\n", GetLastError());
		return;
	}

	// Wait until child process exits
	WaitForSingleObject(pi.hProcess, INFINITE);

	// Close process and thread handles
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}
