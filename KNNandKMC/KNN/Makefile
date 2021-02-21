CC=g++
SRC:= $(KNNandKMC_ROOT)
CFLAGS:= -std=c++11 -DEUCLID -DNOTWRITE
INCLUDE_DIR:=$(PWD)/include/*
all: main
main : $(SRC)/KNN/src/knn.cc 
	$(CC) $(CFLAGS) $(SRC)/KNN/src/knn.cc  -o main -I$(INCLUDE_DIR) -L$(KNNandKMC_ROOT)/lib -I$(KNNandKMC_ROOT)/include -ldata
# $(KNNandKMC_ROOT)/src/dataframe.o : $(KNNandKMC_ROOT)/src/dataframe.cc
# 	$(CC) $(CFLAGS) -c $(KNNandKMC_ROOT)/src/dataframe.cc
clean:
	rm -rf main