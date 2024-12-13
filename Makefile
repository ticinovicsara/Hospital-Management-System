EXEC = hospital

SOURCES_DIR = Sources
HEADERS_DIR = Headers
SEED_DIR = Seed

CC = gcc
CFLAGS = -Wall -I$(HEADERS_DIR)

SOURCES = $(SOURCES_DIR)/main.c $(SOURCES_DIR)/patient.c $(SOURCES_DIR)/read_files.c

OBJECTS = $(SOURCES:.c=.o)

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

$(SOURCES_DIR)/%.o: $(SOURCES_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SOURCES_DIR)/*.o $(EXEC)
