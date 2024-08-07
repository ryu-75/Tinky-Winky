# Compiler
CL				= cl.exe

# Flags compiler
CL_FLAGS		= /EHsc /Wall /WX

# Source files
SRCS			= source/tinky.cpp \
					source/process.cpp \
					source/command.cpp\
					source/utils.cpp
			
# Object files
OBJS			=	source/tinky.obj \
					source/process.obj \
					source/command.obj \
					source/utils.obj

LIBS = Advapi32.lib

source/tinky.obj: source/tinky.cpp
			$(CL) $(CLFLAGS) /c source/tinky.cpp /Fo$@

source/command.obj: source/command.cpp
			$(CL) $(CLFLAGS) /c source/command.cpp /Fo$@

source/process.obj: source/process.cpp
			$(CL) $(CLFLAGS) /c source/process.cpp /Fo$@

source/utils.obj: source/utils.cpp
			$(CL) $(CLFLAGS) /c source/utils.cpp /Fo$@
# Exec name
TARGET			= svc.exe

$(TARGET)		: $(OBJS)
					$(CL) $(CLFLAGS) $(OBJS) /Fe$(TARGET) $(LIBS)

all				: $(TARGET)

clean			: 
					@if exist $(TARGET) del /Q $(TARGET)
					@if exist .\\source\\tinky.obj del .\\source\\tinky.obj
					@if exist .\\source\\command.obj del .\\source\\command.obj
					@if exist .\\source\\process.obj del .\\source\\process.obj
					@if exist .\\source\\utils.obj del .\\source\\utils.obj


re				: clean all






