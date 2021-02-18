CC=g++
INCLUDE_DIR:=$(KMEANS_ROOT)/include
SOURCE_DIR:=$(KMEANS_ROOT)/src
CFLAGS:=-shared -std=c++11 -g
LIB_DATA:= libdata.so
all : $(LIB_DATA)
$(LIB_DATA): libdir objdir obj/data_handler.o obj/data.o
	$(CC) $(CFLAGS) -o $(KMEANS_ROOT)/lib/$(LIB_DATA) obj/*.o
	rm -r $(KMEANS_ROOT)/obj
libdir:
	mkdir -p $(KMEANS_ROOT)/lib
objdir:
	mkdir -p $(KMEANS_ROOT)/obj
obj/data_handler.o : $(SOURCE_DIR)/data_handler.cc
	$(CC) -fPIC $(CFLAGS) -o obj/data_handler.o -I$(INCLUDE_DIR) -c $(SOURCE_DIR)/data_handler.cc
obj/data.o : $(SOURCE_DIR)/data.cc
	$(CC) -fPIC $(CFLAGS) -o obj/data.o -I$(INCLUDE_DIR) -c $(SOURCE_DIR)/data.cc
clean:
	rm -r $(KMEANS_ROOT)/lib
	rm -r $(KMEANS_ROOT)/obj
# nếu chưa có KMEANS_ROOT thì gõ lệnh
# export KMEANS_ROOT=$PWD