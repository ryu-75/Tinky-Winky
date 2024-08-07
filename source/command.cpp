#include "../tinky.h"


DWORD	SvcInstall(SC_HANDLE& scm, TCHAR* path)
{
	SC_HANDLE	schService;

	// Create the service
	schService = CreateService(
		scm,						// SCM Database
		SVCNAME,					// name of service
		SVCNAME,					// service name to display
		SERVICE_ALL_ACCESS,			// desired access
		SERVICE_WIN32_OWN_PROCESS,	// service type
		SERVICE_DEMAND_START,		// start type
		SERVICE_ERROR_NORMAL,		// error control type
		path,						// path to service's binary
		NULL,						// no load ordering group
		NULL,						// no tag identifier
		NULL,						// no dependencies
		NULL,						// LocalSystem account
		NULL);						// no password

	if (schService == NULL)
	{
		printf("%d: Service is already exists\n", GetLastError());
		CLOSESERVICE(scm);
		return 1;
	}
	printf("Service installed successfully\n");
	CLOSESERVICE(schService);
	CLOSESERVICE(scm);
	return 0;
}

DWORD	SvcStart(SC_HANDLE scm, char* path) {
	SC_HANDLE	schService;
	SERVICE_STATUS_PROCESS	ssStatus;
	DWORD dwBytesNeeded;

	schService = OpenService(
		scm,				// SCM Database
		SVCNAME,			// name of service
		SERVICE_ALL_ACCESS	// full access
	);

	if (schService) {
		const char* arg[] = { path };

		// Attempt to start the service
		if (!StartService(schService, 1, arg))
		{
			DWORD	err = GetLastError();

			if (err == ERROR_SERVICE_ALREADY_RUNNING)
				printf("The service is already running\n");
			else
				printf("%d: Start or control request not respond\n", GetLastError());
			CLOSESERVICE(schService);
			CLOSESERVICE(scm);
			return 1;
		}
		if (!QueryServiceStatusEx(schService, SC_STATUS_PROCESS_INFO, (LPBYTE)&ssStatus, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded))
			printf("Service %s started correctly\n", SVCNAME);
		if (!CLOSESERVICE(scm)) {
			printf("CloseServiceHandle failed (%d)\n", GetLastError());
			return 1;
		}
		return 0;
	}
	else
		printf("%d: Service is not installed\n", GetLastError());
	return 1;
}

DWORD	SvcStop(SC_HANDLE scm)
{
	SERVICE_STATUS_PROCESS	ssp;
	SC_HANDLE	schService;

	schService = OpenService(
		scm,
		SVCNAME,
		SERVICE_STOP
	);

	if (schService)
	{
		if (ssp.dwCurrentState == SERVICE_STOPPED)
		{
			printf("Service is already stopped\n");
			CLOSESERVICE(scm);
			CLOSESERVICE(schService);
			return 1;
		}

		while (ssp.dwCurrentState == SERVICE_STOP_PENDING)
		{
			printf("Service stop pending...\n");

			if (ssp.dwCurrentState == SERVICE_STOPPED)
			{
				printf("Service stopped successfully\n");
				CLOSESERVICE(scm);
				CLOSESERVICE(schService);
				return 0;
			}
		}
		printf("Hey\n");

	}
	else
	{
		printf("%d: The service doesn't exist\n", GetLastError());
		return 1;
	}
	return 1;
}