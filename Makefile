EXEC = hospital

SOURCES_DIR = Sources
HEADERS_DIR = Headers
OBJECTS_DIR = Objects

CC = gcc

SOURCES = $(SOURCES_DIR)/main.c \
          $(SOURCES_DIR)/read_files.c \
          $(SOURCES_DIR)/patient.c \
          $(SOURCES_DIR)/doctor.c \
          $(SOURCES_DIR)/help_functions.c \
          $(SOURCES_DIR)/emergency_case.c \
          $(SOURCES_DIR)/appointment.c \
          $(SOURCES_DIR)/handle_patient.c \
          $(SOURCES_DIR)/handle_emergency.c \
          $(SOURCES_DIR)/menu_doctor.c \
          $(SOURCES_DIR)/menu_patient.c \
          $(SOURCES_DIR)/menu_emergency.c


OBJECTS = $(patsubst $(SOURCES_DIR)/%.c, $(OBJECTS_DIR)/%.o, $(SOURCES))

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.c
	$(CC) -c -I$(HEADERS_DIR) $< -o $@

clean:
	rm -rf $(OBJECTS_DIR)/*.o $(EXEC)
