.PHONY: all install uninstall clean dvi dist tests gcov_report rebuild open_app

# =========================================== VAR ==================================================

CXX = g++
CXX_FLAGS = -Wall -Werror -Wextra -std=c++17 -lgtest -lgtest_main --coverage
OS = $(shell uname -s)
PROJECT_NAME = MazeCaves
APP = ../app
BUILD = ../build
REPORT = ../report
DOCUMENTATION = ../documentation
DIST = ../dist

ifeq ($(OS), Darwin)
	OPEN = open
else
	OPEN = xdg-open
endif

# ========================================= TARGETS ================================================

all: install open_app

install:
	@echo "Building application..."
	@cmake MazeCaves -B $(BUILD)
	@cd $(BUILD) && make
	@echo "Application build."
	@echo "Moving application to folder '$(APP)'..."
	@mkdir -p $(APP)
	@mv $(BUILD)/$(PROJECT_NAME) ./$(APP)/
	@echo "Done.\n"
	@echo "Create link on Desktop..."
	@-ln -s $(APP)/$(PROJECT_NAME) ~/Desktop/
	@echo "Installation complete!"

open_app: ../app
	@./$(APP)/$(PROJECT_NAME)

uninstall: ../app
	@echo "Uninstalling start..."
	@-rm -rf $(APP) ~/Desktop/$(PROJECT_NAME)
	@echo "Uninstalling success"

tests:
	@-rm $(shell find . -name "*.gc*")
	@echo "Tests start..."
	$(CXX) $(shell find MazeCaves/Cave MazeCaves/Maze MazeCaves/Matrix tests -name "*.cc") $(CXX_FLAGS) -o test
	@./test
	@-rm check_test_save.txt SavedCave.txt
	@mv *maze.gc* MazeCaves/Maze
	@mv *maze_solver.gc* MazeCaves/Maze
	@mv *cave.gc* MazeCaves/Cave
	@echo "Tests done"

gcov_report: tests
	@echo "Make report..."
	@mkdir -p $(REPORT)
	@lcov -t ./test -o $(REPORT)/test.info --no-external -c -d MazeCaves/Maze -d MazeCaves/Cave
	@genhtml -o $(REPORT)/report_html $(REPORT)/test.info
	@echo "Report is complete"
	@$(OPEN) $(REPORT)/report_html/index.html



dist: clean
	@mkdir -p $(DIST)
	@tar -cvzf $(DIST)/source_code.tar.gz .
	@echo "The archive was successfully created on the path '$(DIST)'"

dvi:
	@doxygen Doxyfile
	@cp -r images $(DOCUMENTATION)/html
	@$(OPEN) $(DOCUMENTATION)/html/index.html

clean:
	@echo "Cleaning..."
	@-rm -rf $(shell find .. \( -name "*.gc*" -or -name "*build*" -or -name "test" -or -name "report" -or -name "dist" -or -name "logs" -or -name "documentation" \))
	@echo "Clean is done"

rebuild: clean all

# ========================================== STYLE =================================================

style: clean
	@clang-format -n -style=google $(shell find . \( -name "*.cc" -or -name "*.h"  -or -name "*.c" -or -name "*.cpp" \))
	@clang-format -i -style=google $(shell find . \( -name "*.cc" -or -name "*.h"  -or -name "*.c" -or -name "*.cpp" \))
