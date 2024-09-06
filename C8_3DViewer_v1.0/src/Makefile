PROJECTNAME = viewer3d

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -g -pedantic
GCOVFLAGS = -fprofile-arcs -ftest-coverage
OS = $(shell uname -s)
LINUX_FLAGS = -lsubunit -lrt -lpthread -lm
TESTFLAGS = -lcheck -lm -lpthread -o
LIBS = -lcheck
TARGET = s21_3dviewer.a

BUILD_DIR = build
CORE_DIR = core
UI_DIR = view
TESTS_DIR = tests
MODELS_DIR = models

SRC = $(wildcard $(CORE_DIR)/*.c)
OBJ = $(patsubst $(CORE_DIR)/%.c,%.o, ${SRC})
TEST_SRC = $(wildcard $(TESTS_DIR)/*.c)

ifeq ($(OS), Linux)
	OPEN_CMD = xdg-open
	GREEN='\033[0;32m'
	NC='\033[0m'
else
	OPEN_CMD = open
	GREEN=\033[0;32m
	NC=\033[0m
endif

all: test gcov_report install run

$(TARGET): ${SRC}
	@$(CC) -c $(CFLAGS) $(SRC)
	@ar rc $@ $(OBJ)
	@ranlib $@
	@echo "${GREEN}The library was created${NC}"

install:
	@mkdir -p $(BUILD_DIR)
	@cd $(UI_DIR) && qmake && make && make clean && rm Makefile && cd ../
	@mv $(UI_DIR)/$(PROJECTNAME).app $(BUILD_DIR)
	@echo "${GREEN}The program was installed${NC}"

uninstall:
	@rm -rf $(BUILD_DIR)
	@echo "${GREEN}The program was uninstalled${NC}"

dvi:
	@open README.md

dist:
	@mkdir -p $(PROJECTNAME)
	@mkdir -p $(PROJECTNAME)/src
	@cp -R $(UI_DIR) $(CORE_DIR) $(MODELS_DIR) Makefile README.md $(PROJECTNAME)/src
	@tar cvzf $(PROJECTNAME).tgz $(PROJECTNAME)
	@rm -rf $(PROJECTNAME)
	@echo "${GREEN}The program was archived${NC}"

test: $(TARGET)
ifeq ($(OS), Darwin)
	@$(CC) $(CFLAGS) $(GCOVFLAGS) $(TESTS_DIR)/test.c ${SRC} -o test $(LIBS) -lm
else
	@$(CC) $(CFLAGS) $(GCOVFLAGS) $(TESTS_DIR)/test.c ${SRC} -o test $(LIBS) $(LINUX_FLAGS)
endif
	@echo "${GREEN}The results of unit tests${NC}"
	@./test

gcov_report: test
	@lcov -t "test" -o test.info --no-external -c -d .
	@genhtml -o report test.info
	@$(OPEN_CMD) ./report/index.html
	@echo "${GREEN}The report is ready${NC}"

run:
	@$(OPEN_CMD) $(BUILD_DIR)/$(PROJECTNAME).app

leaks_at_exit: test
	@CK_FORK=no leaks -atExit -- ./test

valgrind: test
	@CK_FORK=no valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test

leaks:
ifeq ($(OS), Darwin)
	@make leaks_at_exit
else
	@make valgrind
endif

style:
	@clang-format -style=Google -n $(CORE_DIR)/*.c $(CORE_DIR)/*.h $(UI_DIR)/*.cpp $(UI_DIR)/*.h $(TESTS_DIR)/*.c
	@echo "${GREEN}Codestyle check is completed${NC}"

style_fix:
	@clang-format -style=Google -i $(CORE_DIR)/*.c $(CORE_DIR)/*.h $(UI_DIR)/*.cpp $(UI_DIR)/*.h $(TESTS_DIR)/*.c
	@echo "${GREEN}Codestyle was fixed${NC}"

clean:
	@rm -rf *.o *.gcda *.gcno *.info *test report $(TESTS_DIR)/*.o *.dSYM *.a
	@echo "${GREEN}Unneccesary files in . were deleted${NC}"

fclean: clean
	@rm -rf $(UI_DIR)/*.o $(UI_DIR)/*.ui_*.h $(UI_DIR)/moc_* $(UI_DIR)/Makefile $(UI_DIR)/$(PROJECTNAME).app
	@echo "${GREEN}Unneccesary files in . and ./$(UI_DIR) were deleted${NC}"

.PHONY: all install uninstall dvi dist $(TARGET) test gcov_report run leaks_at_exit valgrind leaks style style_fix clean fclean
