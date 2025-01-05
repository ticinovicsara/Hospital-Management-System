SOURCES_DIR = Sources
HEADERS_DIR = Headers
OBJECTS_DIR = Objects

CC = gcc
CFLAGS = -c -I$(HEADERS_DIR) -Wall -Wextra -std=c99
LDFLAGS = 

SOURCES = $(wildcard $(SOURCES_DIR)/*.c)
OBJECTS = $(patsubst $(SOURCES_DIR)/%.c, $(OBJECTS_DIR)/%.o, $(SOURCES))
EXEC = hospital

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC) $(LDFLAGS)

$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.c
	@mkdir -p $(OBJECTS_DIR)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS_DIR)/*.o $(EXEC)

.PHONY: clean