all: cliente balcao medico

cliente: cliente.c estruturas.h
	gcc -o cliente cliente.c

balcao: balcao.c estruturas.h
	gcc -o balcao balcao.c -pthread

medico: medico.c estruturas.h
	gcc -o medico medico.c -pthread

clean:
	rm -rf *.o *~ cliente balcao medico
