# Compiler
CL				= cl.exe

# Flags compiler
CL_FLAGS		= /EHsc /Wall /W3

# Source files
SRCS			= source/ticky.cpp \
					source/process.cpp \
					source/command.cpp \
					source/serviceHandle.cpp \
					source/manageErrorService.cpp
			
# Object files
OBJS			=	source/ticky.obj \
					source/process.obj \
					source/command.obj \
					source/serviceHandle.obj \
					source/manageErrorService.obj


# Lib
LIBS = Advapi32.lib

# Journalistic message
SAMPLE_NAME		=	sample.mc

# Journalistic compiling
SAMPLE_MC		=	mc -U $(SAMPLE_NAME)	# Use tool message compiler 'mc' to generate '.h' files and '.rc' from 'sample.mc'. '.mc' containing messages definition
SAMPLE_RC		=	rc -r sample.rc			# Generate a ressources files compiled '.res' from 'sample.rc'
LINK_FLAGS		=	/MACHINE:x86
DLL				=	link $(LINK_FLAGS) -dll -noentry -out:sample.dll sample.res	# This command uses linker tool 'link' to bind 'sample.res' and generate a DLL named 'sample.ddl'. '-noentry' option indicate DDL haven't an entry point, it's typical for DDL events messages.'

create_sample	:	
					$(SAMPLE_MC) 
					$(SAMPLE_RC) 
					@if not exist sample.dll $(DLL)

source/ticky.obj: source/ticky.cpp
			$(CL) $(CL_FLAGS) /c source/ticky.cpp /Fo$@

source/command.obj: source/command.cpp
			$(CL) $(CL_FLAGS) /c source/command.cpp /Fo$@

source/process.obj: source/process.cpp
			$(CL) $(CL_FLAGS) /c source/process.cpp /Fo$@

source/serviceHandle.obj: source/serviceHandle.cpp
			$(CL) $(CL_FLAGS) /c source/serviceHandle.cpp /Fo$@

source/manageErrorService.obj: source/manageErrorService.cpp
			$(CL) $(CL_FLAGS) /c source/manageErrorService.cpp /Fo$@

# Exec name
TARGET			= svc.exe

$(TARGET)		: $(OBJS)
					$(CL) $(CL_FLAGS) $(OBJS) /Fe$(TARGET) $(LIBS)

all				: create_sample $(TARGET)

clean			: 
					@if exist $(TARGET) del /Q $(TARGET)
					@if exist .\\source\\*.obj del .\\source\\*.obj
					@if exist sample.dll del sample.dll
					@if exist sample.rc del sample.rc
					@if exist sample.res del sample.res
					@if exist sample.h del sample.h

re				: clean all






