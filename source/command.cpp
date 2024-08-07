#include "../tinky.h"


VOID SvcInstall(SC_HANDLE &scm, TCHAR* path)
{
	SC_HANDLE	schSCManager;
	SC_HANDLE	schService;

	// Get a handle to the SCM database
	// Open specified System Control Manager database
	schSCManager = OpenSCManagerA(
		NULL,					// local computer
		NULL,					// ServicesActive database
		SC_MANAGER_ALL_ACCESS	// full acces rights
	);

	if (schSCManager == NULL)
	{
		printf("OpenSCManager failed (%d)\n", GetLastError());
		return;
	}

	// Create the service

	schService = CreateService(
		schSCManager,				// SCM Database
		SVCNAME,					// name of service
		SVCNAME,					// service name to display
		SERVICE_ALL_ACCESS,			// desired access
		SERVICE_WIN32_OWN_PROCESS,	// service type
		SERVICE_DEMAND_START,		// start type
		SERVICE_ERROR_NORMAL,		// error control type
		path,					// path to service's binary
		NULL,						// no load ordering group
		NULL,						// no tag identifier
		NULL,						// no dependencies
		NULL,						// LocalSystem account
		NULL);						// no password

	if (schService == NULL)
	{
		printf("CreateService failed (%d)\n", GetLastError());
		CloseServiceHandle(schSCManager);
		return;
	}
	printf("Service installed successfully\n");
	CloseServiceHandle(schService);
	CloseServiceHandle(schSCManager);
}