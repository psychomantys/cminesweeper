
FONTES= Campo_Minado.c

DOC_DIR=./doc
DOXY_CONF=./Doxyfile
CC=gcc

EXECUTAVEL=main

DEBUG=yes
ifeq ($(DEBUG),yes)
DFLAGS=-O0 -g -pg
else
DFLAGS=-DNDEBUG
endif

CFLAGS= -c -O2 -Wall $(DFLAGS)
LDFLAGS= -O2 -Wall $(DFLAGS) -lm

OBJETOS=$(patsubst %.c,%.o,$(FONTES))
HEADERS=$(patsubst %.c,%.h,$(FONTES))

all: main.c $(FONTES) $(EXECUTAVEL)

$(EXECUTAVEL): main.o $(OBJETOS)
	$(CC) $(LDFLAGS) main.o $(OBJETOS) -o $@

%.o : %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -o $@ 

# Limpa objetos e o executavel
clean:
	rm -rf main.o $(OBJETOS) $(EXECUTAVEL) gmon.out

# Limpa tudo que foi gerado.
distclean: clean
	rm -rf $(DOC_DIR) tags

# Gera documentação para o codigo
doc: $(DOC_DIR)/html/index.html $(DOXY_CONF) $(FONTES) $(HEADERS)
	doxygen

$(DOC_DIR)/html/index.html: $(FONTES) $(HEADERS)

#cria tags do codigo
tags: $(FONTES) $(HEADERS)
	ctags --language-force=c --c-kinds=+p --fields=+iaS --extra=+q $(FONTES) $(HEADERS)

