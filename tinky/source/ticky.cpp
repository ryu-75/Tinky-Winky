#include "../ticky.h"

SERVICE_STATUS			gSvcStatus = { 0 };
SERVICE_STATUS_HANDLE	gSvcStatusHandle;
HANDLE					ghSvcStopEvent = NULL;
DWORD					eventId = 0;

// Entry point for the process
//
// Parameters: None
//
// Return value:
//	None, defaults to 0 (zero)
//

DWORD	ret = -1;

int	_tmain(int argc, char* argv[]) 
{
	if (argc >= 2 && (
							std::strcmp(argv[1], "install") &&
							std::strcmp(argv[1], "start") &&
							std::strcmp(argv[1], "stop") &&
							std::strcmp(argv[1], "delete")))
	{
		printf("Usage: %s <command>\nCommands:\n\tinstall\n\tstart\n\tstop\n\tdelete\n", (std::strrchr(argv[0], '\\')) + 1);
		return 0;
	}
	else if (argc <= 1)
	{
		SERVICE_TABLE_ENTRY	serviceTableEntry[] =
		{
			{SVCNAME, (LPSERVICE_MAIN_FUNCTION)SvcMain},
			{NULL, NULL}
		};

		if (!StartServiceCtrlDispatcher(serviceTableEntry)) {
			printf("%d: Service controller connection failed\n", GetLastError());
			LogEvent(SVCNAME, SVC_STARTED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Service controller connection failed"));
			return 0;
		}
	}

	SC_HANDLE	schSCManager = OpenSCManager(
		NULL,		// Local machine
		NULL,		// default service database
		SC_MANAGER_ALL_ACCESS	// All access
	);

	if (!schSCManager)
	{
		ret = GetLastError();
		if (ret == ERROR_ACCESS_DENIED)
			printf("Error: Access denied. Execute the program with privilege access\n");
		else
			printf("OpenSCManager failed (%d)\n", GetLastError());
		return 0;
	}

	TCHAR	fullPath[MAX_PATH];
	TCHAR	path[MAX_PATH];
	
	if (!GetModuleFileName(NULL, fullPath, MAX_PATH))
	{
		printf("%d: Cannot install the service\n", GetLastError());
		return 0;
	}

	StringCbPrintf(path, MAX_PATH, TEXT("\"%s\""), fullPath);

	if (!std::strcmp(argv[1], "install"))
		SvcInstall(schSCManager, path);
	if (!std::strcmp(argv[1], "start"))
		ret = SvcStart(schSCManager, path);
	if (!std::strcmp(argv[1], "stop"))
		ret = SvcStop(schSCManager);
	if (!std::strcmp(argv[1], "delete"))
		ret = SvcDelete(schSCManager);
	if (!ret)
	{
		printf("An error occured during the installation (%d)\n", GetLastError());
		return 0;
	}
	CLOSESERVICE(schSCManager);
	return 1;
}
