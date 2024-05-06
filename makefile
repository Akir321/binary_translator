CXX = g++
CXX_FLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline\
 -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default\
 -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy\
 -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op\
 -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual\
 -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing\
 -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG\
 -D_EJUDGE_CLIENT_SIDE

SRC_DIR = source/
OBJ_DIR = object/
DMP_DIR = gr_dump/
LOG_DIR = log/

INCLUDE =                                   \
		$(SRC_DIR)cmd_enum.h        \
		$(SRC_DIR)commands.h        \
	  	$(SRC_DIR)errors.h          \
	  	$(SRC_DIR)html_logfile.h    \
	  	$(SRC_DIR)translator.h      \

OBJECT  =                                   \
		$(OBJ_DIR)translator.o      \
		$(OBJ_DIR)main_translator.o \
		$(OBJ_DIR)html_logfile.o    \
			



all: translator

translator: $(OBJECT)
	$(CXX)  $(OBJECT) -o $@ $(CXX_FLAGS)


$(OBJ_DIR)main_translator.o: $(SRC_DIR)main_translator.cpp  $(INCLUDES)
	$(CXX) -c $< -o $@ $(CXX_FLAGS)

$(OBJ_DIR)translator.o:      $(SRC_DIR)translator.cpp       $(INCLUDES)
	$(CXX) -c $< -o $@ $(CXX_FLAGS)

$(OBJ_DIR)html_logfile.o:    $(SRC_DIR)html_logfile.cpp     $(SRC_DIR)html_logfile.h
	$(CXX) -c $< -o $@ $(CXX_FLAGS)


.PHONY: clean clean_logs

clean:
	rm $(OBJECT) translator

clean_logs:
	rm $(LOG_DIR)*.html
