MessageIdTypedef=DWORD

SeverityNames=(Success=0x0:STATUS_SEVERITY_SUCCESS
    Informational=0x1:STATUS_SEVERITY_INFORMATIONAL
    Warning=0x2:STATUS_SEVERITY_WARNING
    Error=0x3:STATUS_SEVERITY_ERROR
    )


FacilityNames=(System=0x0:FACILITY_SYSTEM
    Runtime=0x2:FACILITY_RUNTIME
    Stubs=0x3:FACILITY_STUBS
    Io=0x4:FACILITY_IO_ERROR_CODE
)

LanguageNames=(English=0x409:MSG00409)

; // The following are message definitions.
; // Succes messages 

MessageId=0
Severity=Success
Facility=Runtime
SymbolicName=SVC_INSTALLED_SUCCESS
Language=English
Success: Ticky service installed correctly.
.

MessageId=1
Severity=Success
Facility=Runtime
SymbolicName=SVC_STARTED_SUCCESS
Language=English
Success: Ticky service started correctly.
.

MessageId=2
Severity=Success
Facility=Runtime
SymbolicName=SVC_STOPPED_SUCCESS
Language=English
Success: Ticky service stopped correctly.
.

MessageId=3
Severity=Success
Facility=Runtime
SymbolicName=SVC_DELETED_SUCCESS
Language=English
Success: Ticky service deleted correctly.
.

; // Error messages 

MessageId=20
Severity=Error
Facility=Runtime
SymbolicName=SVC_INSTALLED_ERROR
Language=English
Error: The service could not be installed.
.

MessageId=21
Severity=Error
Facility=Runtime
SymbolicName=SVC_STARTED_ERROR
Language=English
Error: The service could not be started.
.

MessageId=22
Severity=Error
Facility=Runtime
SymbolicName=SVC_STOPPED_ERROR
Language=English
Error: The service could not be stopped.
.

MessageId=23
Severity=Error
Facility=Runtime
SymbolicName=SVC_DELETED_ERROR
Language=English
Error: The service could not be deleted.
.

; // Informational messages

MessageId=10
Severity=Informational
Facility=Runtime
SymbolicName=SVC_ALREADY_INSTALLED
Language=English
Info: The service is already installed.
.

MessageId=11
Severity=Informational
Facility=Runtime
SymbolicName=SVC_ALREADY_STARTED
Language=English
Info: The service is already started.
.

MessageId=12
Severity=Informational
Facility=Runtime
SymbolicName=SVC_ALREADY_STOPPED
Language=English
Info: The service is already stop.
.

MessageId=13
Severity=Informational
Facility=Runtime
SymbolicName=SVC_ALREADY_DELETED
Language=English
Info: The service is already delete.
.

; // A message file must end with a period on its own line
; // followed by a blank line.