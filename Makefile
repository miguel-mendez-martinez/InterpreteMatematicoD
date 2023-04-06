# Opciones de compilación: muestra todos los warnings (-Wall)
CC=gcc -Wall

# Carpeta das cabeceras
HEADER_FILES_DIR = .

# Opciones de compilación: indica donde están los ficheros .h
INCLUDES = -I $(HEADER_FILES_DIR)

# Nombre del ejecutable
OUTPUT = interMatD23

# Ficheros .h
LIB_HEADERS = definiciones.h tablaSimbolos.h abb.h lex.yy.h analizadorSintactico.h

# Ficheros .c
SRCS = main.c tablaSimbolos.c abb.c lex.yy.c analizadorSintactico.c 

# Ficheros .o: todos los .o con un análogo .c en SRCS
OBJS = $(SRCS:.c=.o)

FLEX_FILE = flex.l

# REGLA 1: genera el ejecutable, dependencia de los .o
# Tras geneerarlos borra los .o
$(OUTPUT): $(OBJS)
	$(CC) -o $(OUTPUT) $(OBJS)
	rm *.o

# REGRA 2: geneera los .o cuando se necesita, dependencia de los .c e .h
# $@ es el nombre del fichero que se geneera con la regla (.o)
# $< es el nombre del primer prerrequisito (el archivo .c cullo .o se está generando)
%.o: %.c $(LIB_HEADERS)
	$(CC) -c -o $@ $< $(INCLUDES)

#regla 3, creacion del flex
flex:
	flex $(FLEX_FILE)

# REGLA 4: borra el executable
clean:
	rm -f $(OUTPUT)