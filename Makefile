SHELL = cmd.exe
CXX = g++
TARGET = biblia_aa.dll

# 1. DIRETÃ“RIOS (Conforme seu exemplo funcional)
WX_DIR = ./wxWidgets-3.3.2 #SEU DIRETORIO INCLUDE DE WXWIDGETS
WX_INC = -I$(WX_DIR)/include -I$(WX_DIR)/lib/gcc_lib/mswu
WX_LIB_DIR = -L$(WX_DIR)/lib/gcc_lib

# 2. BIBLIOTECAS

LIBS = -lwxmsw33u_core -lwxbase33u \
       -lwxtiff -lwxjpeg -lwxpng -lwxzlib \
       -luxtheme -lmsimg32 -loleacc -lwinspool \
       -lgdiplus -lgdi32 -lshlwapi -lversion -lcomctl32 -lole32 -loleaut32 -luuid \
       -lrpcrt4 -ladvapi32 -lwsock32 -lwinmm -lcomdlg32 -luser32 -lkernel32

# 3. FLAGS 
# -finput-charset para os acentos e -shared para gerar DLL
CXXFLAGS = -std=c++17 -O2 -finput-charset=UTF-8 -fexec-charset=UTF-8 $(WX_INC)

# 4. ARQUIVOS
SRCS = $(wildcard Livro_*.cpp)
OBJS = $(SRCS:.cpp=.o)

# REGRA PRINCIPAL
$(TARGET): $(OBJS)
	$(CXX) -shared -o $(TARGET) $(OBJS) $(WX_LIB_DIR) $(LIBS)

# COMPILAÃ‡ÃƒO DOS OBJETOS
%.o: %.cpp biblia.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /f *.o $(TARGET)

# Regra para compilar o programa de teste
test: $(TARGET)
	$(CXX) teste_biblia.cpp -o teste.exe $(CXXFLAGS) $(INCLUDES) $(WX_LIB_DIR) -L. -lbiblia_aa $(LIBS)
	@echo "--------------------------------------"
	@echo "Teste compidado! Execute com: ./teste.exe"
	@echo "--------------------------------------"
