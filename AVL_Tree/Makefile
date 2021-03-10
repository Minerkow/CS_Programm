
CC  = g++
CXX = g++
LD  = g++

RM = rm -rf

OPTIM_FLAGS = -O3
GTEST_FLAGS = -lgtest -pthread -g
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
LD_GCOV_FLAGS = -lgcov

BROWSER = google-chrome
LCOV_OUT_FOLDER = out

FLAGS  = OPTIM_FLAGS=$(OPTIM_FLAGS)

INC = -I $(INC_DIR)

CFLAGS 	 = $(OPTIM_FLAGS) $(GTEST_FLAGS) $(GCOV_FLAGS) $(INC)
CXXFLAGS = $(OPTIM_FLAGS) $(GTEST_FLAGS) $(GCOV_FLAGS)
LDFLAGS  = $(LD_GCOV_FLAGS)

TEST_DIR = test
LYB_DIR = source
INC_DIR = ./headers
WORK_FILES = $(LYB_DIR)/%.d $(LYB_DIR)/%.gcda $(LYB_DIR)/%.gcna $(TEST_DIR)/%.d $(TEST_DIR)/%.gcda $(TEST_DIR)/%.gcna

OBJS = main.o ./$(LYB_DIR)/AVL_Tree.o ./$(LYB_DIR)/AVL_Iterator.o ./$(TEST_DIR)/TestHelper.o
TEST_OBJS = ./$(TEST_DIR)/main.o ./$(LYB_DIR)/AVL_Tree.o ./$(LYB_DIR)/AVL_Iterator.o ./$(TEST_DIR)/avlTests.o ./$(TEST_DIR)/TestHelper.o
TEST_CC = ./$(TEST_DIR)/main.c ./$(LYB_DIR)/AVL_Tree.c ./$(LYB_DIR)/AVL_Iterator.c ./$(TEST_DIR)/avlTests.c ./$(TEST_DIR)/TestHelper.c


#-----------------------------------------------------------------

all: main
	echo $(FLAGS)

main: $(OBJS)
	$(CC) -MD $(CFLAGS) -o $@  $^

%.o: %.c
	${CC} -c $^ -o $@ -MD $(CFLAGS)

#-----------------------------------------------------------------

test_build: $(TEST_OBJS)
	$(LD) -o $@ $^ $(CFLAGS) -MD

%.o: %.cpp
	${CC} -c $^ -o $@ -MD $(CFLAGS)

%.o: %.c
	${CC} -c $^ -o $@ -MD $(CFLAGS) -D TEST

#-----------------------------------------------------------------
coverage : source/AVL_Iterator.c source/AVL_Tree.c
	gcov $^ -o $(LYB_DIR) -n

#	lcov --capture --directory . --output-file coverage.info
#	genhtml coverage.info -o $(LCOV_OUT_FOLDER)
#	$(BROWSER) $(LCOV_OUT_FOLDER)/index.html

clean:
	$(RM) main.out main test.out test_build $(OBJS) $(TEST_OBJS) $(WORK_FILES) $(LCOV_OUT_FOLDER)

-include $(OBJ:.o=.d)

.PHONY: clean all tests valgrind
