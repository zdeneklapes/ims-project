DIR_BUILD=build
EXECUTABLE=bread_factory
RM=rm -rfd

all:
	$(RM) $(DIR_BUILD)
	mkdir $(DIR_BUILD)
	cd build && cmake .. && make

run:
	./$(DIR_BUILD)/$(EXECUTABLE)

clean:
	./start.sh -c
