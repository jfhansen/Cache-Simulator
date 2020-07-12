# A simple makefile for the simulator

DIR = ./src
ODIR = ./build
CXX_FLAGS = -O3 -march=native -mtune=native -flto -fuse-linker-plugin --std=c++2a
CXX = g++
LINKER_FLAGS = -lprotobuf

main : main.o
	$(CXX) main.o -o $(ODIR)/main

test_access: test_access.o access.o
	$(CXX) test_access.o access.o -o $(ODIR)/test_access
	mv ./test_access.o $(ODIR)/test_access.o
	mv ./access.o $(ODIR)/access.o

driver : driver.o cache_config.o
	$(CXX) driver.o cache_config.o -o $(ODIR)/driver
	mv ./driver.o $(ODIR)/driver.o
	mv ./cache_config.o $(ODIR)/cache_config.o

main.o : $(DIR)/main.cpp
	$(CXX) -c $(DIR)/main.cpp

driver.o : $(DIR)/driver.cpp
	$(CXX) -c $(DIR)/driver.cpp

test_access.o : $(DIR)/test_access.cpp
	$(CXX) -c $(DIR)/test_access.cpp

access.o : $(DIR)/access.cpp
	$(CXX) -c $(DIR)/access.cpp

cache_config.o : $(DIR)/cache_config.cpp
	$(CXX) -c $(DIR)/cache_config.cpp

clean :
	rm -rf main
	rm -rf *.o