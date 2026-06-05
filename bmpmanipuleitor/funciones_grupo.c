/*
Apellido: Luna, Josue Martiniano
DNI: 44598222
Entrega: Sí

Apellido: Alvarez Orozco, Bautista
DNI: 46091703
Entrega: Sí

Apellido: Espindola, Facundo Alejandro
DNI: 44587968
Entrega: No
*/

#include "funciones_grupo.h"
#include "funciones_luna.h"
#include "funciones_mendez.h"



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

//Crear imagen por filtro

void ProcesarImagen(const char* archivoEntrada,const char* archivoEntrada2,const char* filtroEntrante)
{
    //si tiene un porcentaje dividirlo el filtroEntrante para concerlo
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

    //FUNCION BUSQUEDA DE FILTROS
    if(BuscarFiltro(filtro))
    {

        char archivoSalida[145];
        char nombreEntrada[100];
            strcpy(nombreEntrada, archivoEntrada);



            FILE *ImgOriginal = fopen(archivoEntrada, "rb");

            if (!ImgOriginal)
            {
                printf("Error abriendo archivos\n");
                return;
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
                return;
            }

            fseek(ImgOriginal, header.InicioImagen, SEEK_SET);
            LeerImagen(ImgOriginal, matriz, dib.ancho, dib.altura);

            if (strcmp(filtro, "escala-de-grises") == 0)
                EscalaGris(matriz, dib.altura, dib.ancho);
            else if (strcmp(filtro, "espejar-horizontal") == 0)
                EspejarHorizontal(&matriz, &dib.altura, &dib.ancho);
            else if (strcmp(filtro, "espejar-vertical") == 0)
                EspejarVertical(&matriz, &dib.altura, &dib.ancho);
            else if (strcmp(filtro, "aumentar-contraste") == 0)
                AumentoContraste(matriz, dib.altura, dib.ancho, porcentaje);
            else if (strcmp(filtro, "reducir-contraste") == 0)
                ReduccionContraste(matriz, dib.altura, dib.ancho, porcentaje);
            else if (strcmp(filtro, "tonalidad-azul") == 0)
                FiltroAzulMatriz(matriz, dib.altura, dib.ancho, porcentaje);
            else if (strcmp(filtro, "tonalidad-verde") == 0)
                FiltroVerdeMatriz(matriz, dib.altura, dib.ancho, porcentaje);
            else if (strcmp(filtro, "tonalidad-roja") == 0)
                FiltroRojoMatriz(matriz, dib.altura, dib.ancho, porcentaje);
            else if (strcmp(filtro, "recortar") == 0)
                Recortar(&matriz, &dib.altura, &dib.ancho, porcentaje);
            else if (strcmp(filtro, "achicar") == 0)
                AchicarImagen(&matriz, &dib.altura, &dib.ancho, porcentaje);
            else if (strcmp(filtro, "rotar-derecha") == 0)
                RotarDerecha(&matriz, &dib.altura, &dib.ancho);
            else if (strcmp(filtro, "rotar-izquierda") == 0)
                RotarIzquierda(&matriz, &dib.altura, &dib.ancho);
            else if(strcmp(filtro,"comodin1")==0)
                Cebratricolor(matriz, dib.altura, dib.ancho, porcentaje);
            else if (strcmp(filtro, "comodin2") == 0)
                Pixelado(matriz, dib.altura, dib.ancho, porcentaje);
            else if (strcmp(filtro, "comodin3") == 0)
                Solarizacion(matriz, dib.altura, dib.ancho, porcentaje);
            else if(strcmp(filtro,"concatenar-horizontal")==0 && archivoEntrada2 != NULL)
                ConcatenarHorizontal(&matriz, &dib.altura, &dib.ancho,archivoEntrada2);
            else if(strcmp(filtro,"concatenar-vertical")==0 && archivoEntrada2!= NULL)
                ConcatenarVertical(&matriz, &dib.altura, &dib.ancho,archivoEntrada2);
            else if(strcmp(filtro,"info")==0)
            {
                fclose(ImgOriginal);
                destruirMatriz((void**)matriz, dib.altura);
                return;
            }
            else if(strcmp(filtro,"help")==0)
            {
                fclose(ImgOriginal);
                destruirMatriz((void**)matriz, dib.altura);
                return;
            }
            else if(strcmp(filtro,"validar")==0)
            {
                fclose(ImgOriginal);
                destruirMatriz((void**)matriz, dib.altura);
                return;
            }



            // Guardamos
            if(archivoEntrada2==NULL && (strcmp(filtro,"concatenar-horizontal")==0||strcmp(filtro,"concatenar-vertical")==0))
            {
                printf("Error: Filtro '%s' requiere un segundo archivo de entrada.\n", filtro);
                fclose(ImgOriginal);
                destruirMatriz((void**)matriz, dib.altura);
                return;
            }
            else
            {
                snprintf(archivoSalida, sizeof(archivoSalida), "MIEL_%s_%s", filtro, nombreEntrada);
                FILE *ImgNueva = fopen(archivoSalida, "wb");
                if (!ImgNueva)
                {
                    printf("Error abriendo archivos\n");
                    fclose(ImgOriginal);
                    destruirMatriz((void**)matriz, dib.altura);
                    return;
                }
                fwrite(&header, sizeof(BMPHeader), 1, ImgNueva);
                fwrite(&dib, sizeof(DIBHeader), 1, ImgNueva);
                fseek(ImgNueva, header.InicioImagen, SEEK_SET);
                EscribirImagen(ImgNueva, matriz, dib.ancho, dib.altura);

                destruirMatriz((void**)matriz, dib.altura);
                fclose(ImgNueva);
                fclose(ImgOriginal);

                printf("\nFiltro '%s' aplicado. Imagen guardada como: %s\n", filtro, archivoSalida);
            }
    }
    else
        printf("Filtro '%s' no reconocido.\n", filtro);
}

void ProcesarUtilidad(const char* archivoEntrada, const char* filtroEntrante)
{
    char copia[40];
    char* filtro = NULL;

    strcpy(copia,filtroEntrante);
    if (strchr(copia, '='))
    {
        filtro= strtok(copia, "=");//nombre filtro
    }
    else
    {
        filtro=copia;

    }
    if(BuscarFiltro(filtro))
    {
        char nombreEntrada[100];
        strcpy(nombreEntrada, archivoEntrada);
        FILE *ImgOriginal = fopen(archivoEntrada, "rb");
        if (!ImgOriginal)
        {
            printf("Error abriendo archivos\n");
            return;
        }

        BMPHeader header;
        DIBHeader dib;

        fread(&header, sizeof(BMPHeader), 1, ImgOriginal);
        fread(&dib, sizeof(DIBHeader), 1, ImgOriginal);

        if(strcmp(filtro,"info")==0)
            {
                instInfo(&header,&dib,nombreEntrada);
                fclose(ImgOriginal);
                return;
            }
        else if(strcmp(filtro,"help")==0)
            {
                instHelp();
                fclose(ImgOriginal);
                return;
            }
        else if(strcmp(filtro,"validar")==0)
        {
            instValidarBMP(&header,&dib);
            fclose(ImgOriginal);
            return;
        }
        else
            return;//ARREGLAR: TIENE QUE DEVOLVER UN CODIGO DE ERROR
    }
    else
        printf("Utilidad '%s' no reconocido.\n", filtro);


    return;
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

//FILTROS


void InvertirColores(Pixel** matriz, int filas, int columnas)
{
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            matriz[i][j].rojo  = 255 - matriz[i][j].rojo;
            matriz[i][j].verde = 255 - matriz[i][j].verde;
            matriz[i][j].azul  = 255 - matriz[i][j].azul;
        }
    }
}


void inicializar_instrucciones(instrucciones* inst)
{
    inst->imagenes[0] = NULL;
    inst->imagenes[1] = NULL;
    inst->filtros = NULL;
    inst->cant_imagenes = 0;
    inst->cant_filtros = 0;
}

void agregar_imagen(instrucciones* inst, const char* imagen)
{
    if (inst->cant_imagenes >= 2)
    {
        printf("Error: No se pueden agregar mas de dos imagenes. La imagen %s no se agrego.\n", imagen);
        return;
    }
    inst->imagenes[inst->cant_imagenes]=imagen;
    inst->cant_imagenes++;
    return ;
}

void agregar_filtro(instrucciones* inst, const char* filtro)
{
    const char** nuevos_filtros = realloc(inst->filtros, (inst->cant_filtros + 1) * sizeof(char*));
    if (!nuevos_filtros) return ;

    inst->filtros = nuevos_filtros;
    inst->filtros[inst->cant_filtros] = filtro;
    inst->cant_filtros++;
    return ;
}

void liberar_instrucciones(instrucciones* inst)
{
    free(inst->filtros);
}

void CargarInstrucciones(instrucciones* inst, const char* cadena)
{
    int fin= inst->cant_filtros;
    char copia[40];
    char copia2[40];
    char* filtro = NULL;
    char* filtro2 = NULL;
    char* valorFiltro = NULL;
    float porcentaje = 0;
    strcpy(copia,cadena);
    if (strchr(copia, '='))
    {
        filtro= strtok(copia, "=");
        valorFiltro=strtok(NULL, "=");//valor de filtro
        porcentaje = atoi(valorFiltro);
        if(porcentaje <= 0 || porcentaje > 100)
        {
            printf("Error: El porcentaje debe estar entre 1 y 100. Filtro no agregado: %s\n", cadena);
            return;
        }
    }
    else
    {
        filtro=copia;
    }
    if (strncmp(cadena, "--", 2) == 0)
    {
        int repetido = 0; // bandera de si hay repetido de ese filtro
        for (int i = 0; i < fin; i++)
        {
            strcpy(copia2,inst->filtros[i]);
            if (strchr(copia2, '='))
            {
                filtro2= strtok(copia2, "=");

            }
            else
            {
                filtro2=copia2;
            }
            if (strcmp(filtro2, filtro + 2) == 0)
            {
                printf("Error filtro: %s repetido\n",cadena);
                repetido = 1; // encuentra un repetido y cambia bandera
                break;
            }
        }
        if (!repetido) //si no esta repetido lo hace al filtro cuando lo lee
        {
            agregar_filtro(&(*inst),cadena + 2);
        }
    }
    else if(validarImagen(cadena))
    {
        agregar_imagen(&(*inst),cadena);
    }
    else return;
}

bool BuscarFiltro(const char* filtro)
{
    if (strcmp(filtro, "escala-de-grises") == 0)
        return true;
    else if (strcmp(filtro, "espejar-horizontal") == 0)
        return true;
    else if (strcmp(filtro, "espejar-vertical") == 0)
        return true;
    else if (strcmp(filtro, "aumentar-contraste") == 0)
        return true;
    else if (strcmp(filtro, "reducir-contraste") == 0)
        return true;
    else if (strcmp(filtro, "tonalidad-azul") == 0)
        return true;
    else if (strcmp(filtro, "tonalidad-verde") == 0)
        return true;
    else if (strcmp(filtro, "tonalidad-roja") == 0)
        return true;
    else if (strcmp(filtro, "recortar") == 0)
        return true;
    else if (strcmp(filtro, "achicar") == 0)
        return true;
    else if (strcmp(filtro, "rotar-derecha") == 0)
        return true;
    else if (strcmp(filtro, "rotar-izquierda") == 0)
        return true;
    else if(strcmp(filtro,"concatenar-horizontal")==0)
        return true;
    else if(strcmp(filtro,"concatenar-vertical")==0)
        return true;
    else if(strcmp(filtro,"comodin1")==0)
        return true;
    else if (strcmp(filtro, "comodin2") == 0)
        return true;
    else if (strcmp(filtro, "comodin3") == 0)
        return true;
        else if(strcmp(filtro,"info")==0)
        return true;
    else if(strcmp(filtro, "help") == 0)
        return true;
    else if(strcmp(filtro, "validar") == 0)
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


