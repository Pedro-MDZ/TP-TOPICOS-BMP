/*
Apellido: Luna, Josue Martiniano
DNI: 44598222
Entrega: Sí

Apellido: Mendez Mamani, Pedro
DNI: 46749197
Entrega: Sí

*/

#include "funciones_grupo.h"
#include "funciones_luna.h"
#include "funciones_mendez.h"

#define txt "[INFO]"



//MATRIZ DINAMICA

//Creacion Matriz Dinamica
void** crearMatriz(size_t tamElem, int filas, int columnas)
{
    void** matriz = malloc(sizeof(void*) * filas);
    if (!matriz) return NULL;

    for (int i = 0; i < filas; i++)
    {
        matriz[i] = malloc(tamElem * columnas);
        if (!matriz[i])
        {
            destruirMatriz(matriz, i);
            return NULL;
        }
    }

    return matriz;
}

//Destruccion Matriz Dinamica
void destruirMatriz(void** matriz, int filas)
{
    for (int i = 0; i < filas; i++)
        free(matriz[i]);
    free(matriz);
}

//FUNCIONES GRALES

//Procesar Imagen Encapsulado
int procesar_imagen(int argc, char* argv[])
{
    instrucciones inst;
    inicializar_instrucciones(&inst);

    for (int i = 1; i < argc; i++)
        CargarInstrucciones(&inst, argv[i]);

    for (int i = 0; i < inst.cant_utilidades; i++)
        ProcesarUtilidad(inst.imagenes[0], inst.utilidades[i]);

    if(verboseAct(&inst))
    {
        printf("\n%sIniciando bmpmanipuleitor...",txt);
        printf("\n%sArgumentos detectados: ",txt);
        mostrarArgumentos(argc,argv);
        printf("\n%sArgumentos aceptados: ",txt);
        mostrarInstrucciones(&inst);
    }
    if (validaCantImg(&inst))
    {
        int resultado = EXITO;
        int i = 0;
        while (i < inst.cant_filtros && resultado == EXITO)
        {
            if ((strcmp(inst.filtros[i], "concatenar-horizontal") == 0 ||
             strcmp(inst.filtros[i], "concatenar-vertical") == 0)
             && inst.cant_imagenes < 2)
            {
                printf("Error: '%s' requiere dos imagenes.\n", inst.filtros[i]);
                i++;
                continue;
            }
            resultado = ProcesarImagen(inst.imagenes[0], inst.imagenes[1], inst.filtros[i]);
            i++;
        }
        liberar_instrucciones(&inst);
        return resultado;
    }

    liberar_instrucciones(&inst);
    return EXITO;
}

//Crear imagen por filtro

int ProcesarImagen(const char* archivoEntrada,const char* archivoEntrada2,const char* filtroEntrante)
{
    //si tiene un porcentaje dividirlo el filtroEntrante para concerlo
    //validando headerBMP
    //Archivo valido
    //Si tiene un porcentaje dividirlo el filtroEntrante para conocerlo
    char copia[40];
    char* filtro = NULL;
    char* valorFiltro = NULL;
    float porcentaje;


    strcpy(copia,filtroEntrante);
    if (strchr(copia, '='))
    {
        filtro= strtok(copia, "=");//nombre filtro
        valorFiltro=strtok(NULL, "=");//valor de filtro
        porcentaje = atoi(valorFiltro);//pasar el porcentaje a entero del strtok
    }
    else
    {
        filtro=copia;
    }

    FILE *ImgOriginal = fopen(archivoEntrada, "rb");

    if (!ImgOriginal)
    {
        printf("Error abriendo archivo: %s\n", archivoEntrada);
        return ERROR_ARCHIVO;
    }

    BMPHeader header;
    DIBHeader dib;

    fread(&header, sizeof(BMPHeader), 1, ImgOriginal);
    fread(&dib, sizeof(DIBHeader), 1, ImgOriginal);


    Pixel** matriz = (Pixel**)crearMatriz(sizeof(Pixel), dib.altura, dib.ancho);
    if (!matriz)
    {
        puts("SIN MEMORIA");
        fclose(ImgOriginal);
        return ERROR_MEMORIA;
    }

    fseek(ImgOriginal, header.InicioImagen, SEEK_SET);
    LeerImagen(ImgOriginal, matriz, dib.ancho, dib.altura);

    switch(BuscarFiltro(filtro))
    {
        case FILTRO_ESCALA_GRISES:
            EscalaGris(matriz, dib.altura, dib.ancho);
            break;
        case FILTRO_NEGATIVO:
            InvertirColores(matriz, dib.altura, dib.ancho);
            break;
        case FILTRO_ESPEJAR_H:
            EspejarHorizontal(&matriz, &dib.altura, &dib.ancho);
            break;
        case FILTRO_ESPEJAR_V:
            EspejarVertical(&matriz, &dib.altura, &dib.ancho);
            break;
        case FILTRO_AUMENTAR_CONTRASTE:
            AumentoContraste(matriz, dib.altura, dib.ancho, porcentaje);
            break;
        case FILTRO_REDUCIR_CONTRASTE:
            ReduccionContraste(matriz, dib.altura, dib.ancho, porcentaje);
            break;
        case FILTRO_TONALIDAD_AZUL:
            FiltroAzulMatriz(matriz, dib.altura, dib.ancho, porcentaje);
            break;
        case FILTRO_TONALIDAD_VERDE:
            FiltroVerdeMatriz(matriz, dib.altura, dib.ancho, porcentaje);
            break;
        case FILTRO_TONALIDAD_ROJA:
            FiltroRojoMatriz(matriz, dib.altura, dib.ancho, porcentaje);
            break;
        case FILTRO_RECORTAR:
            Recortar(&matriz, &dib.altura, &dib.ancho, porcentaje);
            break;
        case FILTRO_ACHICAR:
            AchicarImagen(&matriz, &dib.altura, &dib.ancho, porcentaje);
            break;
        case FILTRO_ROTAR_DERECHA:
            RotarDerecha(&matriz, &dib.altura, &dib.ancho);
            break;
        case FILTRO_ROTAR_IZQUIERDA:
            RotarIzquierda(&matriz, &dib.altura, &dib.ancho);
            break;
        case FILTRO_COMODIN1:
            Cebratricolor(matriz, dib.altura, dib.ancho, porcentaje);
            break;
        case FILTRO_COMODIN2:
            Pixelado(matriz, dib.altura, dib.ancho, porcentaje);
            break;
        case FILTRO_CONCATENAR_H:
        {
            char nombreEntrada2[100];
            strcpy(nombreEntrada2, archivoEntrada2);
            ConcatenarHorizontal(&matriz, &dib.altura, &dib.ancho, nombreEntrada2);
            break;
        }
        case FILTRO_CONCATENAR_V:
        {
            char nombreEntrada2[100];
            strcpy(nombreEntrada2, archivoEntrada2);
            ConcatenarVertical(&matriz, &dib.altura, &dib.ancho, nombreEntrada2);
            break;
        }//ESTE DEFAULT NO DEBERIA PASAR PERO POR SI ACASO
        default:
            printf("Filtro no reconocido.\n");
            destruirMatriz((void**)matriz, dib.altura);
            fclose(ImgOriginal);
            return ERROR_ARGUMENTO;
    }
    // Guardamos
    char archivoSalida[145];
    snprintf(archivoSalida, sizeof(archivoSalida), "MIEL_%s_%s", filtro, archivoEntrada);
    FILE *ImgNueva = fopen(archivoSalida, "wb");
    if (!ImgNueva)
    {
        printf("Error abriendo archivos\n");
        fclose(ImgOriginal);
        destruirMatriz((void**)matriz, dib.altura);
        return ERROR_ARCHIVO;
    }
    fwrite(&header, sizeof(BMPHeader), 1, ImgNueva);
    fwrite(&dib, sizeof(DIBHeader), 1, ImgNueva);
    fseek(ImgNueva, header.InicioImagen, SEEK_SET);
    EscribirImagen(ImgNueva, matriz, dib.ancho, dib.altura);

    destruirMatriz((void**)matriz, dib.altura);
    fclose(ImgNueva);
    fclose(ImgOriginal);

    printf("\nFiltro '%s' aplicado. Imagen guardada como: %s\n", filtro, archivoSalida);
    return EXITO;
}

void ProcesarUtilidad(const char* archivoEntrada, const char* filtroEntrante)
{
    char copia[40];
    char* filtro = NULL;

    strcpy(copia, filtroEntrante);
    if (strchr(copia, '='))
        filtro = strtok(copia, "=");
    else
        filtro = copia;

    if (!BuscarFiltro(filtro))
    {
        printf("Utilidad '%s' no reconocida.\n", filtro);
        return;
    }

    if (strcmp(filtro, "help") == 0)
    {
        instHelp();
        return;
    }

    FILE *ImgOriginal = fopen(archivoEntrada, "rb");
    if (!ImgOriginal)
    {
        printf("Error abriendo archivo\n");
        return;
    }

    BMPHeader header;
    DIBHeader dib;
    fread(&header, sizeof(BMPHeader), 1, ImgOriginal);
    fread(&dib, sizeof(DIBHeader), 1, ImgOriginal);

    if(strcmp(filtro,"info")==0)
            {
                instInfo(&header,&dib,archivoEntrada);
                fclose(ImgOriginal);
                return;
            }
    else if(strcmp(filtro,"validar")==0)
        {
            instValidarBMP(&header,&dib);
            fclose(ImgOriginal);
            return;
        }
}

//leer imagenes
void LeerImagen(FILE* archivo, Pixel** matriz, int ancho, int alto)
{
    unsigned int padding = (4 - (ancho * BYTES_POR_PIXEL) % 4) % 4;
    unsigned char paddingBuffer[3];
    for (int i = 0; i < alto; i++)
    {
        fread(matriz[i], sizeof(Pixel), ancho, archivo);
        fread(paddingBuffer, 1, padding, archivo);
    }
}
//escribir imagenes
void EscribirImagen(FILE* archivo, Pixel** matriz, int ancho, int alto)
{
    unsigned int padding = (4 - (ancho * BYTES_POR_PIXEL) % 4) % 4;
    unsigned char paddingBuffer[3] = {0};
    for (int i = 0; i < alto; i++)
    {
        fwrite(matriz[i], sizeof(Pixel), ancho, archivo);
        fwrite(paddingBuffer, 1, padding, archivo);
    }
}

void inicializar_instrucciones(instrucciones* inst)
{
    inst->imagenes[0] = NULL;
    inst->imagenes[1] = NULL;
    inst->filtros = NULL;
    inst->utilidades = NULL;
    inst->cant_imagenes = 0;
    inst->cant_filtros = 0;
    inst->cant_utilidades = 0;
    inst->verbose = 0;
}

int agregar_imagen(instrucciones* inst, const char* imagen)
{
    if (inst->cant_imagenes >= 2)
    {
        printf("Error: No se pueden agregar mas de dos imagenes. La imagen %s no se agrego.\n", imagen);
        return ERROR_ARGUMENTO;
    }
    inst->imagenes[inst->cant_imagenes]=imagen;
    inst->cant_imagenes++;
    return EXITO;
}

int agregar_filtro(instrucciones* inst, const char* filtro)
{
    const char** nuevos_filtros = realloc(inst->filtros, (inst->cant_filtros + 1) * sizeof(char*));
    if (!nuevos_filtros) return ERROR_MEMORIA;

    inst->filtros = nuevos_filtros;
    char* copia = malloc(strlen(filtro) + 1);
    if (!copia)
        return ERROR_MEMORIA;

    strcpy(copia, filtro);

    inst->filtros[inst->cant_filtros] = copia;
    inst->cant_filtros++;
    return EXITO;
}

int agregar_utilidad(instrucciones* inst, const char* utilidad)
{
    const char** nuevas_utilidades = realloc(inst->utilidades, (inst->cant_utilidades + 1) * sizeof(char*));
    if (!nuevas_utilidades) return ERROR_MEMORIA;

    inst->utilidades = nuevas_utilidades;
    char* copia = malloc(strlen(utilidad) + 1);
    if (!copia)
        return ERROR_MEMORIA;

    strcpy(copia, utilidad);

    inst->utilidades[inst->cant_utilidades] = copia;
    inst->cant_utilidades++;
    return EXITO;
}

void liberar_instrucciones(instrucciones* inst)
{
    for(int i = 0; i < inst->cant_filtros; i++)
        free((void*)inst->filtros[i]);
    free(inst->filtros);
    free(inst->utilidades);
}

int CargarInstrucciones(instrucciones* inst, const char* cadena)
{
    char copia[40];
    char copia2[40];
    char* filtro = NULL;
    char* filtro2 = NULL;
    char* valorFiltro = NULL;
    float porcentaje = 0;
    strcpy(copia,cadena);

    //Es imagen
    if(strncmp(cadena, "--", 2) != 0)
    {
        if(validarBMP(cadena))
        {
            agregar_imagen(inst,cadena);
        return EXITO;
        }
        else
            return ERROR_ARGUMENTO;

    }
    //Flag verbose
    if(strcmp(cadena, "--verbose") == 0)
    {
        inst->verbose = 1;
        return EXITO;
    }
    //Separo el filtro del igual si tiene
    if (strchr(copia, '='))
    {
        filtro= strtok(copia, "=") + 2;
        valorFiltro=strtok(NULL, "=");
        porcentaje = atoi(valorFiltro);
        if(porcentaje <= 0 || porcentaje > 100)
        {
            printf("Error: El porcentaje debe estar entre 1 y 100. Filtro no agregado: %s\n", cadena);
            return ERROR_ARGUMENTO;
        }
    }//Sino solo el filtro
    else
        filtro=copia + 2;

    //Es utilidad
    if(BuscarUtilidad(filtro))
    {
        agregar_utilidad(inst,filtro);
        return EXITO;
    }
    //Si no esta en filtro y utilidad (q ya paso), error
    if(BuscarFiltro(filtro) == SIN_FILTRO)
    {
        printf("Filtro '%s' no reconocido.\n", filtro);
        return ERROR_ARGUMENTO;
    }
    //Verifico que no este repetido
    int fin = inst->cant_filtros;
    int repetido = 0; // bandera de si hay repetido de ese filtro
    int i = 0;
    while(i<fin && !repetido)
    {
        strcpy(copia2,inst->filtros[i]);
        if (strchr(copia2, '='))
            filtro2= strtok(copia2, "=");
        else
            filtro2=copia2;

        if (strcmp(filtro2, filtro) == 0)
        {
            printf("Error filtro: %s repetido.\n",cadena);
            repetido = 1; // encuentra un repetido y cambia bandera
        }
        i++;
    }

    if(!repetido)
        agregar_filtro(inst,cadena + 2);

    return EXITO;
}

int BuscarFiltro(const char* filtro)
{
    if (strcmp(filtro, "escala-de-grises") == 0)
        return FILTRO_ESCALA_GRISES;
    else if (strcmp(filtro, "negativo") == 0)
        return FILTRO_NEGATIVO;
    else if (strcmp(filtro, "espejar-horizontal") == 0)
        return FILTRO_ESPEJAR_H;
    else if (strcmp(filtro, "espejar-vertical") == 0)
        return FILTRO_ESPEJAR_V;
    else if (strcmp(filtro, "aumentar-contraste") == 0)
        return FILTRO_AUMENTAR_CONTRASTE;
    else if (strcmp(filtro, "reducir-contraste") == 0)
        return FILTRO_REDUCIR_CONTRASTE;
    else if (strcmp(filtro, "tonalidad-azul") == 0)
        return FILTRO_TONALIDAD_AZUL;
    else if (strcmp(filtro, "tonalidad-verde") == 0)
        return FILTRO_TONALIDAD_VERDE;
    else if (strcmp(filtro, "tonalidad-roja") == 0)
        return FILTRO_TONALIDAD_ROJA;
    else if (strcmp(filtro, "recortar") == 0)
        return FILTRO_RECORTAR;
    else if (strcmp(filtro, "achicar") == 0)
        return FILTRO_ACHICAR;
    else if (strcmp(filtro, "rotar-derecha") == 0)
        return FILTRO_ROTAR_DERECHA;
    else if (strcmp(filtro, "rotar-izquierda") == 0)
        return FILTRO_ROTAR_IZQUIERDA;
    else if(strcmp(filtro,"comodin1")==0)
        return FILTRO_COMODIN1;
    else if (strcmp(filtro, "comodin2") == 0)
        return FILTRO_COMODIN2;
    else if(strcmp(filtro,"concatenar-horizontal")==0)
        return FILTRO_CONCATENAR_H;
    else if(strcmp(filtro,"concatenar-vertical")==0)
        return FILTRO_CONCATENAR_V;
    else
        return SIN_FILTRO;
}

bool BuscarUtilidad(const char* utilidad)
{
    if (strcmp(utilidad, "info") == 0)
        return true;
    if (strcmp(utilidad, "help") == 0)
        return true;
    if (strcmp(utilidad, "validar") == 0)
        return true;
    else
        return false;
}

bool validaCantImg(instrucciones *inst)
{
    if(inst->cant_imagenes == 0)
    {
        printf("ERROR: No se ingreso ninguna imagen");
        return false;
    }
        return true;
}
