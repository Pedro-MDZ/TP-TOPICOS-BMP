#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones_grupo.h"

int main(int argc, char* argv[])
{
/*<<<<<<< HEAD
    instrucciones inst;
    inicializar_instrucciones(&inst);
    for(int i=1; i<argc;i++)
        CargarInstrucciones(&inst,argv[i]);//argumentos detectados
    for(int i=0; i<inst.cant_filtros;i++)
        ProcesarUtilidad(inst.imagenes[0],inst.filtros[i]);
    if(validaCantImg(&inst))
    {
        for(int i=0; i<inst.cant_filtros;i++)
        ProcesarImagen(inst.imagenes[0],inst.imagenes[1],inst.filtros[i]);//cargando archivo
    }
    liberar_instrucciones(&inst);
    return 0;
=======*/
    // Procesar los argumentos y aplicar filtros
    return procesar_imagen(argc, argv);
//>>>>>>> f2aab2a4875a0c92088026a025c0a0a29471f2be
}
