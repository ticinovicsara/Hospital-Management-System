EXEC = hospital

SOURCES_DIR = Sources
HEADERS_DIR = Headers
OBJECTS_DIR = Objects

CC = gcc
CFLAGS = -Wall -I$(HEADERS_DIR)

SOURCES = $(SOURCES_DIR)/main.c $(SOURCES_DIR)/patient.c $(SOURCES_DIR)/read_files.c $(SOURCES_DIR)/help_functions.c $(SOURCES_DIR)/doctor.c

OBJECTS = $(SOURCES:$(SOURCES_DIR)/%.c=$(OBJECTS_DIR)/%.o)

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SOURCES_DIR)/*.o $(EXEC)

$(OBJECTS_DIR):
	mkdir -p $(OBJECTS_DIR)