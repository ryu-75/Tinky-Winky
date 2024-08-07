#include "../tinky.h"

SERVICE_STATUS			gSvcStatus;
SERVICE_STATUS_HANDLE	gSvcStatusHandle;
HANDLE					ghSvcStopEvent = NULL;

// Entry point for the process
//
// Parameters: None
//
// Return value:
//	None, defaults to 0 (zero)
//

DWORD	ret = 0;

int	_tmain(int argc, char* argv[]) 
{
	if (argc >= 2 && (std::strcmp(argv[1], "install") && 
						std::strcmp(argv[1], "start") &&
							std::strcmp(argv[1], "stop") &&
								std::strcmp(argv[1], "delete")))
	{
		printf("Usage: %s <command>\nCommands:\n\tinstall\n\tstart\n\tstop\n\tdelete\n", (std::strrchr(argv[0], '\\')) + 1);
		return 1;
	}
	else if (argc <= 1) 
	{
		// Execute main service
		SERVICE_TABLE_ENTRYW	serviceTableEntry[] =
		{
			{(LPWSTR)SVCNAME, (LPSERVICE_MAIN_FUNCTIONW) svcMain},
			{NULL, NULL}
		};

		if (!StartServiceCtrlDispatcherW(serviceTableEntry)) {
			printf("SSCD failed (%lu)\n", GetLastError());
			return 1;
		}
	}

	SC_HANDLE	schSCManager = OpenSCManager(
		NULL,		// Local machine
		NULL,		// default service database
		SC_MANAGER_ALL_ACCESS	// All access
	);

	if (schSCManager == NULL) 
	{
		ret = GetLastError();
		if (ret == ERROR_ACCESS_DENIED)
			printf("Error: Access denied. Execute the program with privilege access\n");
		else
			printf("OpenSCManager failed (%d)\n", GetLastError());
		return 1;
	} else 
	{
		SC_HANDLE	schService;
		TCHAR	fullPath[MAX_PATH];
		TCHAR	path[MAX_PATH];

		if (!GetModuleFileName(NULL, fullPath, MAX_PATH))
		{
			printf("Cannot install service (%d)\n", GetLastError());
			return 1;
		}

		StringCbPrintf(path, MAX_PATH, TEXT("\"%s\""), fullPath);

		if (std::strcmp(argv[1], "install") == 0)
		{
			/*
				If command-line parameter is "install", install the service.
				Otherwise, the service is probably being started by the SCM.
			*/
			SvcInstall(schSCManager, path);
			//createProcess(argv[1]);
			return 0;
		}
	}
}
