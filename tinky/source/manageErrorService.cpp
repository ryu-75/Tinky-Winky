#include "../ticky.h"

void	startServiceManageError(DWORD err)
{
	switch (err)
	{
	case ERROR_SERVICE_ALREADY_RUNNING:
		printf("%d: The service is already running.\n", err);
		LogEvent(SVCNAME, SVC_ALREADY_STARTED, EVENTLOG_INFORMATION_TYPE, TEXT("Info: The service is already running."));
		break;

	case ERROR_ACCESS_DENIED:
		printf("%d: Handle doesn't have the required access rights.\n", err);
		LogEvent(SVCNAME, SVC_STARTED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: Handle doesn't have the required access rights."));
		break;

	case ERROR_SERVICE_DISABLED:
		printf("%d: The service is disabled.\n", err);
		LogEvent(SVCNAME, SVC_STARTED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: The service is disabled."));
		break;

	case ERROR_INVALID_HANDLE:
		printf("%d: The handle is invalid.\n", err);
		LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: The handle is invalid."));
		break;

	case ERROR_PATH_NOT_FOUND:
		printf("%d: Binary files not found.\n", err);
		LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: Binary files not found."));
		break;

	case ERROR_SERVICE_DATABASE_LOCKED:
		printf("%d: The service database is locked.\n", err);
		LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: The service database is locked."));
		break;

	case ERROR_SERVICE_DEPENDENCY_DELETED:
		printf("%d: The service depends on a non-existent service.\n", err);
		LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: The service depends on a non-existent service."));
		break;

	case ERROR_SERVICE_DEPENDENCY_FAIL:
		printf("%d: The service depends on a service that failed to start.\n", err);
		LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: The service depends on a service that failed to start."));
		break;

	case ERROR_SERVICE_LOGON_FAILED:
		printf("%d: The service failed to start due to a logon error.\n", err);
		LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: The service failed to start due to a logon error."));
		break;

	case ERROR_SERVICE_MARKED_FOR_DELETE:
		printf("%d: The service is marked for deletion.\n", err);
		LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: The service is marked for deletion."));
		break;

	case ERROR_SERVICE_NO_THREAD:
		printf("%d: Unable to create a service thread.\n", err);
		LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: Unable to create a service thread."));
		break;

	case ERROR_SERVICE_REQUEST_TIMEOUT:
		printf("%d: The service process started but did not respond.\n", err);
		LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: The service process started but did not respond."));
		break;

	default:
		printf("%d: An unexpected error occurred.\n", err);
		LogEvent(SVCNAME, SVC_STARTED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: An unexpected error occurred."));
		break;
	}
}

void	controlServiceManageError(DWORD err)
{
	switch (err)
	{
	case ERROR_ACCESS_DENIED:
		printf("%d: Handle doesn't have the required access rights.\n", err);
		LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: Handle doesn't have the required access rights."));
		break;

	case ERROR_DEPENDENT_SERVICES_RUNNING:
		printf("%d: The service cannot be stopped; stop dependent services first.\n", err);
		LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: The service cannot be stopped; stop dependent services first."));
		break;

	case ERROR_INVALID_HANDLE:
		printf("%d: The handle is invalid.\n", err);
		LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: The handle is invalid."));
		break;

	case ERROR_INVALID_PARAMETER:
		printf("%d: The `cbSize` parameter in SERVICE_STATUS_PROCESS is invalid.\n", err);
		LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: The `cbSize` parameter in SERVICE_STATUS_PROCESS is invalid."));
		break;

	case ERROR_INVALID_SERVICE_CONTROL:
		printf("%d: The requested control code is invalid or not supported by the service.\n", err);
		LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: The requested control code is invalid or not supported by the service."));
		break;

	case ERROR_SERVICE_CANNOT_ACCEPT_CTRL:
		printf("%d: The control code cannot be sent.\n", err);
		LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: The control code cannot be sent."));
		break;

	case ERROR_SERVICE_NOT_ACTIVE:
		printf("%d: The service is not currently running.\n", err);
		LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: The service is not currently running."));
		break;

	case ERROR_SERVICE_REQUEST_TIMEOUT:
		printf("%d: The service process started but did not respond.\n", err);
		LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: The service process started but did not respond."));
		break;

	case ERROR_SHUTDOWN_IN_PROGRESS:
		printf("%d: The system is shutting down.\n", err);
		LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: The system is shutting down."));
		break;

	default:
		printf("%d: An unexpected error occurred while stopping the service.\n", err);
		LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: An unexpected error occurred while stopping the service."));
		break;
	}
}

void	queryServiceStatusExManageError(DWORD err)
{
	switch (err)
	{
	case ERROR_ACCESS_DENIED:
		printf("%d: Handle doesn't have the required access rights.\n", err);
		LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: Handle doesn't have the required access rights."));
		break;

	case ERROR_INVALID_HANDLE:
		printf("%d: The handle is invalid.\n", err);
		LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: The handle is invalid."));
		break;

	case ERROR_INSUFFICIENT_BUFFER:
		printf("%d: The buffer is too small for the structure.\n", err);
		LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: The buffer is too small for the structure."));
		break;

	case ERROR_INVALID_PARAMETER:
		printf("%d: The `cbSize` parameter in SERVICE_STATUS_PROCESS is invalid.\n", err);
		LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: The `cbSize` parameter in SERVICE_STATUS_PROCESS is invalid."));
		break;

	case ERROR_INVALID_LEVEL:
		printf("%d: The `infoLevel` parameter contains an uninitialized value.\n", err);
		LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: The `infoLevel` parameter contains an uninitialized value."));
		break;

	case ERROR_SHUTDOWN_IN_PROGRESS:
		printf("%d: The system is shutting down.\n", err);
		LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: The system is shutting down."));
		break;

	default:
		printf("%d: An unexpected error occurred.\n", err);
		LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: An unexpected error occurred."));
		break;
	}
}

void	openServiceManageError(DWORD err)
{
	switch (err)
	{
	case ERROR_ACCESS_DENIED:
		printf("%d: Handle does not have the required access.\n", err);
		LogEvent(SVCNAME, SVC_INSTALLED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Handle does not have the required access."));
		break;

	case ERROR_INVALID_HANDLE:
		printf("%d: The specified handle is invalid.\n", err);
		LogEvent(SVCNAME, SVC_INSTALLED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("The specified handle is invalid."));
		break;

	case ERROR_INVALID_NAME:
		printf("%d: The service name is invalid.\n", err);
		LogEvent(SVCNAME, SVC_INSTALLED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("The service name is invalid."));
		break;

	case ERROR_SERVICE_DOES_NOT_EXIST:
		printf("%d: The specified service does not exist.\n", err);
		LogEvent(SVCNAME, SVC_INSTALLED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("The specified service does not exist."));
		break;

	default:
		printf("%d: An unexpected error occurred.\n", err);
		LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: An unexpected error occurred."));
		break;
	}
}

void	createServiceManageError(DWORD err)
{
	switch (err)
	{
	case ERROR_ACCESS_DENIED:
		printf("%d: Handle does not have the required access.\n", err);
		LogEvent(SVCNAME, SVC_INSTALLED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Handle does not have the required access."));
		break;

	case ERROR_INVALID_HANDLE:
		printf("%d: The specified handle is invalid.\n", err);
		LogEvent(SVCNAME, SVC_INSTALLED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("The specified handle is invalid."));
		break;

	case ERROR_INVALID_NAME:
		printf("%d: The service name is invalid.\n", err);
		LogEvent(SVCNAME, SVC_INSTALLED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("The service name is invalid."));
		break;

	case ERROR_CIRCULAR_DEPENDENCY:
		printf("%d: A circular service dependency was specified.\n", err);
		LogEvent(SVCNAME, SVC_INSTALLED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("A circular service dependency was specified."));
		break;

	case ERROR_DUPLICATE_SERVICE_NAME:
		printf("%d: The display name already exists in the SCM database.\n", err);
		LogEvent(SVCNAME, SVC_INSTALLED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("The display name already exists in the SCM database."));
		break;

	case ERROR_INVALID_PARAMETER:
		printf("%d: A specified parameter is invalid.\n", err);
		LogEvent(SVCNAME, SVC_INSTALLED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("A specified parameter is invalid."));
		break;

	case ERROR_INVALID_SERVICE_ACCOUNT:
		printf("%d: The specified user account in `lpServiceStartName` does not exist.\n", err);
		LogEvent(SVCNAME, SVC_INSTALLED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("The specified user account in `lpServiceStartName` does not exist."));
		break;

	case ERROR_SERVICE_EXISTS:
		printf("%d: The specified service already exists in the database.\n", err);
		LogEvent(SVCNAME, SVC_INSTALLED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("The specified service already exists in the database."));
		break;

	case ERROR_SERVICE_MARKED_FOR_DELETE:
		printf("%d: The service is marked for deletion.\n", err);
		LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: The service is marked for deletion."));
		break;

	default:
		printf("%d: An unexpected error occurred.\n", err);
		LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: An unexpected error occurred."));
		break;
	}
}

void	deleteServiceManageError(DWORD err)
{
	switch (err)
	{
	case ERROR_ACCESS_DENIED:
		printf("%d: Handle does not have DELETE access.\n", err);
		LogEvent(SVCNAME, SVC_INSTALLED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Handle does not have DELETE access."));
		break;

	case ERROR_INVALID_HANDLE:
		printf("%d: The specified handle is invalid.\n", err);
		LogEvent(SVCNAME, SVC_INSTALLED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("The specified handle is invalid."));
		break;

	case ERROR_SERVICE_MARKED_FOR_DELETE:
		printf("%d: The service is already marked for deletion.\n", err);
		LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: The service is already marked for deletion."));
		break;

	default:
		printf("%d: An unexpected error occurred.\n", err);
		LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: An unexpected error occurred."));
		break;
	}
}
