# A simple makefile for the simulator

DIR = ./src
ODIR = ./build
CXX_FLAGS = --std=c++2a #-O3 -march=native -mtune=native -flto -fuse-linker-plugin --std=c++2a
CXX = g++
LINKER_FLAGS = -lprotobuf

driver : driver.o cache_sim.o cache_config.o access.o cache.o cache_set.o
	$(CXX) driver.o cache_sim.o cache_config.o access.o cache.o cache_set.o -o $(ODIR)/driver
	mv ./driver.o $(ODIR)/driver.o
	mv ./cache_sim.o $(ODIR)/cache_sim.o
	mv ./cache_config.o $(ODIR)/cache_config.o
	mv ./access.o $(ODIR)/access.o
	mv ./cache.o $(ODIR)/cache.o
	mv ./cache_set.o $(ODIR)/cache_set.o

test_cacheset : test_cacheset.o cache_set.o access.o
	$(CXX) test_cacheset.o cache_set.o access.o $(CXX_FLAGS) -o $(ODIR)/main
	mv ./test_cacheset.o $(ODIR)/test_cacheset.o
	mv ./cache_set.o $(ODIR)/cache_set.o
	mv ./access.o $(ODIR)/access.o

test_access: test_access.o access.o
	$(CXX) test_access.o access.o -o $(ODIR)/test_access
	mv ./test_access.o $(ODIR)/test_access.o
	mv ./access.o $(ODIR)/access.o

test_frontend: test_frontend.o cache_config.o
	$(CXX) test_frontend.o cache_config.o -o $(ODIR)/driver
	mv ./test_frontend.o $(ODIR)/test_frontend.o
	mv ./cache_config.o $(ODIR)/cache_config.o

test_cacheset.o : $(DIR)/test_cacheset.cpp
	$(CXX) -c $(DIR)/test_cacheset.cpp $(CXX_FLAGS)

driver.o : $(DIR)/driver.cpp
	$(CXX) -c $(DIR)/driver.cpp $(CXX_FLAGS)

test_access.o : $(DIR)/test_access.cpp
	$(CXX) -c $(DIR)/test_access.cpp $(CXX_FLAGS)

test_frontend.o : $(DIR)/test_frontend.cpp
	$(CXX) -c $(DIR)/test_frontend.cpp $(CXX_FLAGS)

access.o : $(DIR)/access.cpp
	$(CXX) -c $(DIR)/access.cpp $(CXX_FLAGS)

cache_config.o : $(DIR)/cache_config.cpp
	$(CXX) -c $(DIR)/cache_config.cpp $(CXX_FLAGS)

cache_set.o : $(DIR)/cache_set.cpp
	$(CXX) -c $(DIR)/cache_set.cpp $(CXX_FLAGS)

cache.o : $(DIR)/cache.cpp
	$(CXX) -c $(DIR)/cache.cpp $(CXX_FLAGS)

cache_sim.o : $(DIR)/cache_sim.cpp
	$(CXX) -c $(DIR)/cache_sim.cpp $(CXX_FLAGS)

clean :
	rm -rf main
	rm -rf *.o