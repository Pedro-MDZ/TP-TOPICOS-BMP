#include "funciones_grupo.h"
#include "funciones_mendez.h"

#define GRUPO "MIEL"
#define INTEGRANTE1 " DNI - APELLIDO, Nombre"
#define INTEGRANTE2 " 46749197 - MENDEZ, Pedro"
#define PROY "bmpmanipuleitor.exe"
#define VALIDO "ARCHIVO VALIDO - Listo para procesar"
#define INVALIDO "ARCHIVO INVALIDO - No se puede procesar"




int RotarDerecha(Pixel*** matriz, int* filas, int* columnas)
{
    int nuevoAlto = *columnas;
    int nuevoAncho = *filas;

    Pixel** nuevaMatriz = (Pixel**)crearMatriz(sizeof(Pixel), nuevoAlto, nuevoAncho);
    if (!nuevaMatriz)
    {
        puts("Error al rotar: sin memoria");
        return ERROR_MEMORIA;
    }

    for (int i = 0; i < *filas; i++)
    {
        for (int j = 0; j <*columnas; j++)
        {
            nuevaMatriz[*columnas - 1 - j][i] = (*matriz)[i][j];
        }
    }

    destruirMatriz((void**)*matriz,*filas);
    *matriz = nuevaMatriz;
    *filas = nuevoAlto;
    *columnas = nuevoAncho;
    return EXITO;
}

int RotarIzquierda(Pixel*** matriz, int* filas, int* columnas)
{
    int nuevoAlto = *columnas;
    int nuevoAncho = *filas;

    Pixel** nuevaMatriz = (Pixel**)crearMatriz(sizeof(Pixel), nuevoAlto, nuevoAncho);
    if (!nuevaMatriz)
    {
        puts("Error al rotar: sin memoria");
        return ERROR_MEMORIA;
    }

    for (int i = 0; i < *filas; i++)
    {
        for (int j = 0; j <*columnas; j++)
        {
            nuevaMatriz[j][*filas - 1 - i] = (*matriz)[i][j];
        }
    }

    destruirMatriz((void**)*matriz,*filas);
    *matriz = nuevaMatriz;
    *filas = nuevoAlto;
    *columnas = nuevoAncho;
    return EXITO;
}

int EspejarHorizontal(Pixel*** matriz, int *filas, int *columnas)
{

    int nuevoAlto = *filas;
    int nuevoAncho = *columnas;

    Pixel** nuevaMatriz = (Pixel**)crearMatriz(sizeof(Pixel), nuevoAlto, nuevoAncho);
    if (!nuevaMatriz)
    {
        puts("Error al espejar-horizontal: sin memoria");
        return ERROR_MEMORIA;
    }

    for (int i = 0; i < *filas; i++)
    {
        for (int j = 0; j < *columnas; j++)
        {

            nuevaMatriz[i][j] = (*matriz)[i][*columnas - 1 - j];
        }
    }


    destruirMatriz((void**)*matriz, *filas);

    *matriz = nuevaMatriz;
    *filas = nuevoAlto;
    *columnas = nuevoAncho;
    return EXITO;
}


int EspejarVertical(Pixel*** matriz, int *filas, int *columnas)
{

    int nuevoAlto = *filas;
    int nuevoAncho = *columnas;

    Pixel** nuevaMatriz = (Pixel**)crearMatriz(sizeof(Pixel), nuevoAlto, nuevoAncho);
    if (!nuevaMatriz)
    {
        puts("Error al espejar-horizontal: sin memoria");
        return ERROR_MEMORIA;
    }

    for (int i = 0; i < *filas; i++)
    {
        for (int j = 0; j < *columnas; j++)
        {

            nuevaMatriz[i][j] = (*matriz)[*filas - 1 -i][j];
        }
    }


    destruirMatriz((void**)*matriz, *filas);

    *matriz = nuevaMatriz;
    *filas = nuevoAlto;
    *columnas = nuevoAncho;
    return EXITO;
}

int Recortar(Pixel*** matriz, int *filas, int *columnas, float porcentaje)
{
    porcentaje= porcentaje/100;
    int nuevasFilas = (*filas) * porcentaje;
    int nuevasColumnas = (*columnas) * porcentaje;


    int margenSuperior = 0;
    int margenIzquierdo = 0;

    Pixel** nuevaMatriz = (Pixel**)crearMatriz(sizeof(Pixel), nuevasFilas, nuevasColumnas);

    if (!nuevaMatriz)
    {
        puts("Error al recortar: sin memoria.");
        return ERROR_MEMORIA;
    }


    for (int i = 0; i < nuevasFilas; i++)
    {
        for (int j = 0; j < nuevasColumnas; j++)
        {
            nuevaMatriz[i][j] = (*matriz)[i + margenSuperior][j + margenIzquierdo];
        }
    }

    destruirMatriz((void**)*matriz, *filas);

    *matriz = nuevaMatriz;
    *filas = nuevasFilas;
    *columnas = nuevasColumnas;
    return EXITO;
}


int AchicarImagen(Pixel*** matriz, int* filas, int* columnas, float porcentaje)
{
    int nuevasFilas = (*filas * porcentaje) / 100;
    int nuevasColumnas = (*columnas * porcentaje) / 100;


    Pixel** matrizReducida = (Pixel**)crearMatriz(sizeof(Pixel), nuevasFilas, nuevasColumnas);

    if (!matrizReducida)
    {
        printf("Error al achicar: sin memoria.");
        return ERROR_MEMORIA;
    }

    float factorFila = (float)(*filas) / nuevasFilas;
    float factorColumna = (float)(*columnas) / nuevasColumnas;

    for (int i = 0; i < nuevasFilas; i++)
    {
        for (int j = 0; j < nuevasColumnas; j++)
        {

            int origI = (int)(i * factorFila);
            int origJ = (int)(j * factorColumna);


            if (origI >= *filas)
                origI = *filas - 1;
            if (origJ >= *columnas)
                origJ = *columnas - 1;

            matrizReducida[i][j] = (*matriz)[origI][origJ];
        }
    }

    destruirMatriz((void**)*matriz, *filas);

    *matriz= matrizReducida;
    *filas = nuevasFilas;
    *columnas = nuevasColumnas;
    return EXITO;
}



int ConcatenarVertical(Pixel*** matriz1, int* filas1, int* columnas1,const char* archivoEntrada)
{
    FILE *ImgSegunda = fopen(archivoEntrada, "rb");

        if (!ImgSegunda)
        {
            printf("Error abriendo archivos\n");
            return ERROR_ARCHIVO;
        }

        BMPHeader header;
        DIBHeader dib;

        fread(&header, sizeof(BMPHeader), 1, ImgSegunda);
        fread(&dib, sizeof(DIBHeader), 1, ImgSegunda);

        Pixel** matriz2 = (Pixel**)crearMatriz(sizeof(Pixel), dib.altura, dib.ancho);
        if (!matriz2)
        {
            puts("Error al concatenar vertical: sin memoria.");
            fclose(ImgSegunda);
            return ERROR_MEMORIA;
        }

        fseek(ImgSegunda, header.InicioImagen, SEEK_SET);
        LeerImagen(ImgSegunda, matriz2, dib.ancho, dib.altura);

    int nuevasFilas = *filas1 + dib.altura;
    int nuevasColumnas = (*columnas1 > dib.ancho) ? *columnas1 : dib.ancho;

    Pixel** matrizFinal = (Pixel**)crearMatriz(sizeof(Pixel), nuevasFilas, nuevasColumnas);
    if (!matrizFinal)
    {
        puts("Error al concatenar vertical: sin memoria.");
        destruirMatriz((void**)matriz2, dib.altura);
        fclose(ImgSegunda);
        return ERROR_MEMORIA;
    }

    Pixel Relleno = {0, 165, 255}; //// Naranja

    // Copiar la primera imagen (arriba)
    for (int i = 0; i < *filas1; i++)
    {
        for (int j = 0; j < nuevasColumnas; j++)
        {
            if (j < *columnas1)
                matrizFinal[i][j] = (*matriz1)[i][j];
            else
                matrizFinal[i][j] = Relleno;
        }
    }

    // Copiar la segunda imagen (abajo)
    for (int i = 0; i < dib.altura; i++)
    {
        for (int j = 0; j < nuevasColumnas; j++)
        {
            if (j < dib.ancho)
                matrizFinal[i + *filas1][j] = matriz2[i][j];
            else
                matrizFinal[i + *filas1][j] = Relleno;
        }
    }

    destruirMatriz((void**)(*matriz1), *filas1);

    *matriz1 = matrizFinal;
    *filas1 = nuevasFilas;
    *columnas1 = nuevasColumnas;

    destruirMatriz((void**)matriz2, dib.altura);
    fclose(ImgSegunda);
    return EXITO;
}

int ConcatenarHorizontal(Pixel*** matriz1, int* filas1, int* columnas1,const char* archivoEntrada)
{
    FILE *ImgSegunda = fopen(archivoEntrada, "rb");

        if (!ImgSegunda)
        {
            printf("Error abriendo archivos\n");
            return ERROR_ARCHIVO;
        }

        BMPHeader header;
        DIBHeader dib;

        fread(&header, sizeof(BMPHeader), 1, ImgSegunda);
        fread(&dib, sizeof(DIBHeader), 1, ImgSegunda);

        Pixel** matriz2 = (Pixel**)crearMatriz(sizeof(Pixel), dib.altura, dib.ancho);
        if (!matriz2)
        {
            puts("Error al concatenar horizontal: sin memoria.");
            fclose(ImgSegunda);
            return ERROR_MEMORIA;
        }

        fseek(ImgSegunda, header.InicioImagen, SEEK_SET);
        LeerImagen(ImgSegunda, matriz2, dib.ancho, dib.altura);

    int nuevasFilas = (*filas1 > dib.altura) ? *filas1 : dib.altura;
    int nuevasColumnas = *columnas1 + dib.ancho;

    Pixel** matrizFinal = (Pixel**)crearMatriz(sizeof(Pixel), nuevasFilas, nuevasColumnas);
    if (!matrizFinal)
    {
        puts("Error al concatenar horizontal: sin memoria.");
        destruirMatriz((void**)matriz2, dib.altura);
        fclose(ImgSegunda);
        return ERROR_MEMORIA;
    }

    Pixel Relleno = {128, 0, 128}; //// Violeta

    ////// Copiar la primera imagen (izquierda)
    for (int i = 0; i < *columnas1; i++)
    {
        for (int j = 0; j < nuevasFilas; j++)
        {
            if (j < *filas1)
                matrizFinal[j][i] = (*matriz1)[j][i];
            else
                matrizFinal[j][i] = Relleno;
        }
    }

    /////Copiar la segunda imagen (derecha)
    for (int i = 0; i < dib.ancho; i++)
    {
        for (int j = 0; j < nuevasFilas; j++)
        {
            if (j < dib.altura)
                matrizFinal[j][i + *columnas1] = matriz2[j][i];
            else
                matrizFinal[j][i + *columnas1] = Relleno;
        }
    }

    destruirMatriz((void**)(*matriz1), *filas1);

    *matriz1 = matrizFinal;
    *filas1 = nuevasFilas;
    *columnas1 = nuevasColumnas;

    destruirMatriz((void**)matriz2, dib.altura);
    fclose(ImgSegunda);
    return EXITO;
}

void instInfo(BMPHeader *header, DIBHeader *dheader,const char *nombreImagen)
{
    unsigned int padding = ((dheader->ancho * BYTES_POR_PIXEL) % 4);
    printf("\nArchivo: %s",nombreImagen);
    printf("\nTamanio del archivo: %d bytes",header->tamArch);
    printf("\nDimensiones: %d x %d",dheader->ancho,dheader->altura);
    printf("\nProfundidad: %d bits",dheader->tamPunto);
    printf("\nCompresion: %d ",dheader->compresion);
    printf("\nOffset de datos: %d bytes",(int)(sizeof(BMPHeader)+sizeof(DIBHeader)));
    printf("\nTamanio de la imagen: %d bytes",dheader->tamImg);
    printf("\nPadding por fila: %d bytes",padding);
}

void instHelp(void)
{
    printf("\nGRUPO: %s",GRUPO);
    printf("\nINTEGRANTES: \n%s\n%s",INTEGRANTE1,INTEGRANTE2);
    printf("\nUSO: \n%s\t--negativo",PROY);
    printf("\n%s\t--escala-de-grises",PROY);
    printf("\n%s\t--espejar-horizontal",PROY);
    printf("\n%s\t--espejar-vertical",PROY);
    printf("\n%s\t--aumentar-contraste=X",PROY);
    printf("\n%s\t--reducir-contraste=X",PROY);
    printf("\n%s\t--tonalidad-azul=X",PROY);
    printf("\n%s\t--tonalidad-verde=X",PROY);
    printf("\n%s\t--tonalidad-roja=X",PROY);
    printf("\n%s\t--recortar=X",PROY);
    printf("\n%s\t--achicar=X",PROY);
    printf("\n%s\t--rotar-derecha",PROY);
    printf("\n%s\t--rotar-izquierda",PROY);
    printf("\n%s\t--concatenar-horizontal",PROY);
    printf("\n%s\t--concatenar-vertical",PROY);
    printf("\nEJEMPLO: \n%s --rotar-derecha imagen1.bmp",PROY);
    printf("\nFILTRO: --comodin1=X Crea un patron de los 3 colores primarios en diagonal con X como intensidad");
    printf("\nFILTRO: --comodin2=X Pixelea la imagen con bloques tomando un promedio de los colores por bloque, con X se decide el tam de bloque");
    printf("\nFILTRO: --comodin3=X Crea un patron de los 3 colores primarios en diagonal con el ancho de X para las columnas");


    return;
}

void instValidarBMP(BMPHeader *header, DIBHeader *dheader)
{
    printf("\n\nValidando imagen.bmp...");
    if(header->tipo != 0x4D42)
    {
        printf("\nSignature BMP invalido");
        printf("\n%s",INVALIDO);
        return;
    }
    else
        printf("\nSignature BMP valido");

    if(dheader->tamPunto != 24)
    {
        printf("\nProfundidad de %d bits, esperada 24 bits",dheader->tamPunto);
        printf("\n%s",INVALIDO);
        return;
    }
    else
        printf("\nProfundidad de 24 bits correcta");
    if(dheader->compresion != 0)
    {
        printf("\nCompresion: Comprimido, se necesita que no este comprimido");
        printf("\n%s",INVALIDO);
        return;
    }
    else
        printf("\nCompresion: No comprimido");
    if(header->tipo == 0x4D42 && dheader->tamPunto == 24 && dheader->compresion == 0)
        printf("\n%s",VALIDO);

    return;
}

bool validarImagen(const char* imagen)
{
    FILE *Img = fopen(imagen, "rb");
    if (!Img)
        {
            printf("\nError abriendo archivos");
            return false;
        }
    BMPHeader header;
    DIBHeader dib;
    fread(&header, sizeof(BMPHeader), 1, Img);
    fread(&dib, sizeof(DIBHeader), 1, Img);
    if(header.tipo == 0x4D42 && dib.tamPunto == 24 && dib.compresion == 0 && dib.ancho >= 1 && dib.altura >=1)
    {
        fclose(Img);
        return true;
    }
    else
    {
        fclose(Img);
        return false;
    }
}

bool validarBMP(const char* imagen)
{
    FILE *Img = fopen(imagen, "rb");
    if (!Img)
        {
            printf("\nError abriendo archivos");
            return false;
        }
    BMPHeader header;
    fread(&header, sizeof(BMPHeader), 1, Img);
    if(header.tipo == 0x4D42)
    {
        fclose(Img);
        return true;
    }
    else
    {
        fclose(Img);
        return false;
    }
}

int verboseAct(instrucciones* inst)
{
    return inst->verbose;
}

void mostrarArgumentos(int argc,char* argv[])
{
    for(int i=1;i<argc;i++)
    {
        printf("%s\t",*(argv+i));
    }
    return;
}

void mostrarInstrucciones(instrucciones* inst)
{
    for(int i=0;i<inst->cant_imagenes;i++)
    {
        printf("%s\t",*((inst->imagenes)+i));
    }
    for(int i=0;i<inst->cant_filtros;i++)
    {
        printf("--%s\t",*((inst->filtros)+i));
    }
    for(int i=0;i<inst->cant_utilidades;i++)
    {
        printf("--%s\t",*((inst->utilidades)+i));
    }

    return;
}
