# Compiler
CL				= cl.exe

# Flags compiler
CL_FLAGS		= /EHsc /Wall /W3 

# Source files
SRCS			= source/winkey.cpp 
			
# Object files
OBJS			=	source/winkey.obj

# Lib
LIBS = user32.lib

source/winkey.obj: source/winkey.cpp
			$(CL) $(CL_FLAGS) /c source/winkey.cpp /Fo$@

# Exec name
TARGET			= winkey.exe

$(TARGET)		: $(OBJS)
					$(CL) $(CL_FLAGS) $(OBJS) /Fe$(TARGET) $(LIBS)

all				: $(TARGET)

clean			: 
					@if exist $(TARGET) del /Q $(TARGET)
					@if exist .\\source\\*.obj del .\\source\\*.obj
					@if exist file.log del file.log

re				: clean all






