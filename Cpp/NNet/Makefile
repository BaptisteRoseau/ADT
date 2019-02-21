#######################################################
###				CONFIGURATION
#######################################################

SRC_DIR = src
TST_DIR = tst
BLD_DIR = build

CC			   = g++
CFLAGS		   = -Wall -Wextra -g

SRC_FILES	   = $(wildcard $(SRC_DIR)/*.cpp)
SRC_OBJ	       = $(SRC_FILES:%.cpp=%.o)
TST_FILES	   = $(wildcard $(TST_DIR)/*.cpp)
TST_OBJ	       = $(TST_FILES:%.cpp=%.o)

#######################################################
###				DEFAULT MAKE COMMAND
#######################################################

all: build

#######################################################
###				MAKE INSTRUCTIONS / HELP
#######################################################

help:
	@echo -e \
	======================================================================	'\n'\
		'\t' Shynamo : Neural Net class                           			'\n'\
	======================================================================	'\n'\
	'\n'Available commands:													'\n'\
		'\t' make     '\t' '\t' Compiler votre bibliothèque et les tests.   '\n'\
		'\t' make check    '\t' Exécuter les tests, avec des valeurs raisonnables pour les tests qui veulent des arguments en ligne de commande.'\n'\
		'\t' make valgrind '\t' Exécuter les tests sous valgrind.           '\n'\
		'\t' make help	   '\t' Show the availables commands				'\n'\
		'\t' make clean    '\t' Clean all generated objects and binairies	'\n'

#######################################################
###				MAKE BUILD
#######################################################

build: $(SRC_OBJ) $(TST_OBJ)
	@mkdir -p $(BLD_DIR)
	for t_obj in $(TST_OBJ); do \
		tmp=`echo $${t_obj} | cut -d'/' -f 2 | cut -d'.' -f 1` ; \
		$(CC) $(SRC_OBJ) $${t_obj} -o $(BLD_DIR)/$${tmp} ;\
	done

#######################################################
###				MAKE CHECK
#######################################################

check: build
	@for t_obj in $(TST_OBJ); do \
		tmp=`echo $${t_obj} | cut -d'/' -f 2 | cut -d'.' -f 1` ; \
		echo "\033[1;33m\nExecuting $${tmp}\033[0m"; \
		$(BLD_DIR)/$${tmp} $(ARGS);\
	done

#######################################################
###				MAKE VALGRIND
#######################################################

valgrind: build
	@for t_obj in $(TST_OBJ); do \
		tmp=`echo $${t_obj} | cut -d'/' -f 2 | cut -d'.' -f 1` ; \
		echo "\033[1;33m\nExecuting $${tmp}\033[0m"; \
		valgrind $(BLD_DIR)/$${tmp} $(ARGS);\
	done

#######################################################
###				MAKE CLEAN
#######################################################

clean:
	@echo Starting cleanup...
	@find . -type f -name '*.o' -delete
	@find . -type f -name '*.so' -delete
	@rm -rf $(BLD_DIR)/*
	@echo Cleanup complete.


#######################################################
###				OBJECTS FILES
#######################################################

%_pthread.o : %.cpp
	$(CC) -DUSE_PTHREAD -c $(CFLAGS) $(CPPFLAGS) $< -o $@ -lpthread

%.o : %.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
