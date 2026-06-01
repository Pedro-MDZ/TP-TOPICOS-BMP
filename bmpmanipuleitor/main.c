#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones_grupo.h"
int main(int argc, char* argv[])
{
    instrucciones inst;
    inicializar_instrucciones(&inst);
    for(int i=1; i<argc;i++)
        CargarInstrucciones(&inst,argv[i]);
    for(int i=0; i<inst.cant_filtros;i++)
        ProcesarImagen(inst.imagenes[0],inst.imagenes[1],inst.filtros[i]);
    liberar_instrucciones(&inst);
    return 0;
}
