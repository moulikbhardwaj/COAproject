CC = gcc
CFLAGS = -Wall -Wextra -Werror

DIR_SRC = src
DIR_OBJ = obj
DIR_BIN = bin
DIR_DATA= data

execFolder = emmulatorCOproject/application.

SIMULATOR = $(addprefix $(DIR_BIN)/,simulator.out)
ASSEMBLER = $(addprefix $(DIR_BIN)/,assembler.out)

DIR_ASSEMBLER_SRC = $(addprefix $(DIR_SRC),/assembler)
DIR_ASSEMBLER_OBJECTS = $(addprefix $(DIR_OBJ),/assembler)

DIR_SIMULATOR_SRC = $(addprefix $(DIR_SRC),/simulator)
DIR_SIMULATOR_OBJECTS = $(addprefix $(DIR_OBJ),/simulator)

DIR_EXTRAS_SRC = $(addprefix $(DIR_SRC),/extras)

ASSEMBLER_SOURCES = $(wildcard $(DIR_ASSEMBLER_SRC)/*.c)
ASSEMBLER_OBJECTS = $(patsubst $(DIR_ASSEMBLER_SRC)/%.c,$(DIR_ASSEMBLER_OBJECTS)/%.o, $(ASSEMBLER_SOURCES))
ASSEMBLER_HEADERS = $(wildcard $(DIR_ASSEMBLER_SRC)/*.h)

SIMULATOR_SOURCES = $(wildcard $(DIR_SIMULATOR_SRC)/*.c)
SIMULATOR_OBJECTS = $(patsubst $(DIR_SIMULATOR_SRC)/%.c,$(DIR_SIMULATOR_OBJECTS)/%.o, $(SIMULATOR_SOURCES))
SIMULATOR_HEADERS = $(wildcard $(DIR_SIMULATOR_SRC)/*.h)

EXTRAS_SOURCES = $(wildcard $(DIR_EXTRAS_SRC)/*.c)
EXTRAS_OBJECTS = $(patsubst $(DIR_EXTRAS_SRC)/%.c, $(DIR_BIN)/%.out, $(EXTRAS_SOURCES))

DIRS = $(DIR_ASSEMBLER_OBJECTS) $(DIR_ASSEMBLER_SRC) $(DIR_BIN) $(DIR_OBJ) $(DIR_SIMULATOR_OBJECTS) $(DIR_SIMULATOR_SRC) $(DIR_SRC) $(DATA)

all: $(DIRS) $(ASSEMBLER) $(SIMULATOR) $(EXTRAS_OBJECTS)

$(ASSEMBLER): $(ASSEMBLER_OBJECTS)
	$(CC) $(ASSEMBLER_OBJECTS) -o $(ASSEMBLER)

$(SIMULATOR): $(SIMULATOR_OBJECTS)
	$(CC) $(SIMULATOR_OBJECTS) -o $(SIMULATOR)


$(DIR_ASSEMBLER_OBJECTS)/%.o:$(DIR_ASSEMBLER_SRC)/%.c $(ASSEMBLER_HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ -g

$(DIR_SIMULATOR_OBJECTS)/%.o:$(DIR_SIMULATOR_SRC)/%.c $(SIMULATOR_HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ -g


$(DIRS): 
	mkdir -p $@

$(DIR_BIN)/%.out: $(DIR_EXTRAS_SRC)/%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm  -f $(DIR_BIN)/*
	rm -f $(DIR_SIMULATOR_OBJECTS)/*
	rm -f $(DIR_ASSEMBLER_OBJECTS)/*
	rm -f $(DIR_DATA)/binFile
	rm -f $(DIR_DATA)/opFile
	rm -f $(DIR_DATA)/symbolTable.txt
	rm -f $(DIR_DATA)/ramDump
	rm -f $(DIR_DATA)/ramDump.parsed

Assemble: $(ASSEMBLER)
	./$(ASSEMBLER) $(DIR_DATA)/code.myAsm $(DIR_DATA)/binFile $(DIR_DATA)/symbolTable.txt

Simulate: Assemble $(SIMULATOR)
	./${SIMULATOR} $(DIR_DATA)/binFile $(DIR_DATA)/opFile $(DIR_DATA)/symbolTable.txt $(DIR_DATA)/ramDump

RamDump: Simulate $(EXTRAS_OBJECTS)
	$(DIR_BIN)/opener.out $(DIR_D
	
RunLinux32:
	$(execFolder)linux32/emmulatorCOproject data/opFile assets/arrow.jpeg assets/arrowcopy.jpeg 

RunLinux64:
	$(execFolder)linux64/emmulatorCOproject data/opFile assets/arrow.jpeg assets/arrowcopy.jpeg 

RunWindows32:
	$(execFolder)windows32/emmulatorCOproject.exe data/opFile assets/arrow.jpeg assets/arrowcopy.jpeg 

RunWindows64:
	$(execFolder)windows64/emmulatorCOproject.exe data/opFile assets/arrow.jpeg assets/arrowcopy.jpeg 

