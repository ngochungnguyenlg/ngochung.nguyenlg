CC=g++
INCLUDE_DIR:=$(KNNandKMC_ROOT)/include
SOURCE_DIR:=$(KNNandKMC_ROOT)/src
CFLAGS:=-shared -std=c++11 -g -Wall -pedantic -W
LIB_DATA:= libdata.so
LIB_DATAFRAME:= libframe.so

all_2 : $(LIB_DATAFRAME)
$(LIB_DATAFRAME): libdir objdir obj/dataframe.o
	$(CC) $(CFLAGS) -o $(KNNandKMC_ROOT)/lib/$(LIB_DATAFRAME) obj/dataframe.o
	rm -r $(KNNandKMC_ROOT)/obj/dataframe.o
all_1 : $(LIB_DATA)
$(LIB_DATA): libdir objdir obj/data_handler.o obj/data.o
	$(CC) $(CFLAGS) -o $(KNNandKMC_ROOT)/lib/$(LIB_DATA) obj/*.o
	rm -r $(KNNandKMC_ROOT)/obj/*
libdir:
	mkdir -p $(KNNandKMC_ROOT)/lib
objdir:
	mkdir -p $(KNNandKMC_ROOT)/obj
obj/data_handler.o : $(SOURCE_DIR)/data_handler.cc
	$(CC) -fPIC $(CFLAGS) -o obj/data_handler.o -I$(INCLUDE_DIR) -c $(SOURCE_DIR)/data_handler.cc
obj/data.o : $(SOURCE_DIR)/data.cc
	$(CC) -fPIC $(CFLAGS) -o obj/data.o -I$(INCLUDE_DIR) -c $(SOURCE_DIR)/data.cc
obj/dataframe.o:  $(SOURCE_DIR)/dataframe.cc $(INCLUDE_DIR)/dataframe.hpp
	$(CC) -fPIC $(CFLAGS) -o obj/dataframe.o -I$(INCLUDE_DIR) -c $(SOURCE_DIR)/dataframe.cc
clean:
	rm -r $(KNNandKMC_ROOT)/lib
	rm -r $(KNNandKMC_ROOT)/obj
# nếu chưa có KNNandKMC_ROOT thì gõ lệnh
# export KNNandKMC_ROOT=$PWD