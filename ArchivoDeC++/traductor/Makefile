SRC = src
INC = include
OBJ = obj
BIN = bin
CXX = g++
CPPFLAGS = -Wall -g  -I $(INC) -c


all: $(BIN)/pruebatraductor

# ************ Generación de documentación ******************
documentacion:
	doxygen doc/doxys/Doxyfile

	
# ************ Compilación de módulos ************
$(BIN)/pruebatraductor:$(OBJ)/pruebatraductor.o $(OBJ)/palabra.o $(OBJ)/traductor.o
	$(CXX) $(OBJ)/pruebatraductor.o $(OBJ)/palabra.o $(OBJ)/traductor.o -o $(BIN)/pruebatraductor

$(OBJ)/pruebatraductor.o:$(SRC)/pruebatraductor.cpp 
	$(CXX) $(CPPFLAGS) $(SRC)/pruebatraductor.cpp -o $(OBJ)/pruebatraductor.o

$(OBJ)/palabra.o:$(SRC)/palabra.cpp 
	$(CXX) $(CPPFLAGS) $(SRC)/palabra.cpp -o $(OBJ)/palabra.o 

$(OBJ)/traductor.o:$(SRC)/traductor.cpp
	$(CXX) $(CPPFLAGS) $(SRC)/traductor.cpp -o $(OBJ)/traductor.o


# ************ Limpieza ************
clean :
	-rm $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~

mrproper : clean
	-rm $(BIN)/* doc/html/*
