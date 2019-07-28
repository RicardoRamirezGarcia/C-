SRC = src
INC = include
OBJ = obj
BIN = bin
CXX = g++
CPPFLAGS = -Wall -g  -I$(INC) -c

OBJETOS = testdiccionario cantidad_letras  testconjuntoletras letras

all: $(OBJETOS)

# COMPILACION
$(OBJETOS):
	$(CXX) -o $(BIN)/$@ $(SRC)/$@.cpp -I$(INCLUDE) $(CPPFLAGS)

# ************ Generación de documentación ******************
documentacion:
	doxygen doc/doxys/Doxyfile

# ************ Limpieza ************
clean :
	-rm $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~

mrproper : clean
	-rm $(BIN)/* doc/html/*