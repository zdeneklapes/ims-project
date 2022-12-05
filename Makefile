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
	$(MAKE) -C $(DIR_BUILD)

run:
	$(MAKE) -C $(DIR_BUILD)
	./$(DIR_BUILD)/$(EXECUTABLE) $(PROGRAM_ARGS)

clean:
	./start.sh -c
