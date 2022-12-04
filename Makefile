###############################################################################
# Makefile
# Řešení IMS-Projekt
# Datum: 2022-10-20
# Autori: Zdenek Lapes (xlapes02), FIT
#    	  Andrej Binovsky (xbinov00), FIT
###############################################################################
DIR_BUILD=build
EXECUTABLE=bread_factory
RM=rm -rfd

.PHONY: cmake
cmake:
	$(RM) $(DIR_BUILD)
	mkdir $(DIR_BUILD)
	cd build && cmake ..
	$(MAKE) build

.PHONY: build
build:
	$(MAKE) -C $(DIR_BUILD)

run: build
	./$(DIR_BUILD)/$(EXECUTABLE)

clean:
	./start.sh -c
