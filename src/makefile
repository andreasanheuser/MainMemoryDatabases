OBJDIR = ../obj
OBJS = $(addprefix $(OBJDIR)/, main.o table.o column.o measure.o stringExtensions.o tableSchema.o datejd.o simplecharcontainer.o dbhandler.o database.o )
OUT = database

CC = g++-4.8
# for compilation under OSX - no longer needed with OSX 10.9
#UNAME_S := $(shell uname -s)
#ifeq ($(UNAME_S),Darwin)
#	CC = g++
#endif

CFLAGS = -std=c++0x -c -Wall -O3
LDFLAGS = -Wall

all: $(OUT)

#database: main.o table.o column.o $(OBJDIR)/measure.o $(OBJDIR)/stringExtensions.o tableSchema.o $(OBJDIR)/datejd.o
#	$(CC) $(LDFLAGS) tableSchema.o table.o column.o $(OBJDIR)/measure.o $(OBJDIR)/stringExtensions.o $(OBJDIR)/datejd.o main.o -o $(OUT)

$(OUT): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(OUT)

$(OBJDIR)/main.o: main.cpp datastore/dbhandler.h
	$(CC) $(CFLAGS) main.cpp -o $(OBJDIR)/main.o

$(OBJDIR)/table.o: datastore/table.cpp datastore/table.h datastore/column.cpp datastore/column.h
	$(CC) $(CFLAGS) datastore/table.cpp -o $(OBJDIR)/table.o

$(OBJDIR)/column.o: datastore/column.cpp datastore/column.h datastore/tableSchema.h datastore/tableSchema.cpp
	$(CC) $(CFLAGS) datastore/column.cpp -o $(OBJDIR)/column.o

$(OBJDIR)/tableSchema.o: datastore/tableSchema.cpp datastore/tableSchema.h
	$(CC) $(CFLAGS) datastore/tableSchema.cpp -o $(OBJDIR)/tableSchema.o

$(OBJDIR)/measure.o: tools/measure.cpp
	$(CC) $(CFLAGS) tools/measure.cpp -o $(OBJDIR)/measure.o

$(OBJDIR)/stringExtensions.o: tools/stringExtensions.cpp
	$(CC) $(CFLAGS) tools/stringExtensions.cpp -o $(OBJDIR)/stringExtensions.o

$(OBJDIR)/datejd.o: datastore/datejd.cpp
	$(CC) $(CFLAGS) datastore/datejd.cpp -o $(OBJDIR)/datejd.o

$(OBJDIR)/simplecharcontainer.o: datastore/simplecharcontainer.cpp
	$(CC) $(CFLAGS) datastore/simplecharcontainer.cpp -o $(OBJDIR)/simplecharcontainer.o

$(OBJDIR)/dbhandler.o: datastore/dbhandler.cpp datastore/database.h
	$(CC) $(CFLAGS) datastore/dbhandler.cpp -o $(OBJDIR)/dbhandler.o

$(OBJDIR)/database.o: datastore/database.cpp datastore/table.h
	$(CC) $(CFLAGS) datastore/database.cpp -o $(OBJDIR)/database.o




clean:
	@rm -f ../obj/*.o database
