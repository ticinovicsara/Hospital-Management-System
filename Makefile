EXEC = hospital

SOURCES_DIR = Sources
HEADERS_DIR = Headers
OBJECTS_DIR = Objects
USER_ACTIONS_DIR = UserActions

CC = gcc
CFLAGS = -Wall -I$(HEADERS_DIR)

SOURCES = $(SOURCES_DIR)/main.c \
          $(SOURCES_DIR)/patient.c \
          $(SOURCES_DIR)/read_files.c \
          $(SOURCES_DIR)/help_functions.c \
          $(SOURCES_DIR)/doctor.c \
          $(USER_ACTIONS_DIR)/handle_patient.c \
		  $(USER_ACTIONS_DIR)/hanle_emergency.c

OBJECTS = $(patsubst $(SOURCES_DIR)/%.c, $(OBJECTS_DIR)/%.o, \
          $(filter $(SOURCES_DIR)/%, $(SOURCES))) \
          $(patsubst $(USER_ACTIONS_DIR)/%.c, $(OBJECTS_DIR)/%.o, \
          $(filter $(USER_ACTIONS_DIR)/%, $(SOURCES)))


$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.c
	@mkdir -p $(OBJECTS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJECTS_DIR)/%.o: $(USER_ACTIONS_DIR)/%.c
	@mkdir -p $(OBJECTS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS_DIR) $(EXEC)