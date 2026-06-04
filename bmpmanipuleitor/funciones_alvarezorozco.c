#include "funciones_grupo.h"
#include "funciones_alvarezorozco.h"



void RotarDerecha(Pixel*** matriz, int* filas, int* columnas)
{
    int nuevoAlto = *columnas;
    int nuevoAncho = *filas;

    Pixel** nuevaMatriz = (Pixel**)crearMatriz(sizeof(Pixel), nuevoAlto, nuevoAncho);
    if (!nuevaMatriz)
    {
        puts("Error al rotar: sin memoria");
        return;
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
}

void RotarIzquierda(Pixel*** matriz, int* filas, int* columnas)
{
    int nuevoAlto = *columnas;
    int nuevoAncho = *filas;

    Pixel** nuevaMatriz = (Pixel**)crearMatriz(sizeof(Pixel), nuevoAlto, nuevoAncho);
    if (!nuevaMatriz)
    {
        puts("Error al rotar: sin memoria");
        return;
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
}

void EspejarHorizontal(Pixel*** matriz, int *filas, int *columnas)
{

    int nuevoAlto = *filas;
    int nuevoAncho = *columnas;

    Pixel** nuevaMatriz = (Pixel**)crearMatriz(sizeof(Pixel), nuevoAlto, nuevoAncho);
    if (!nuevaMatriz)
    {
        puts("Error al espejar-horizontal: sin memoria");
        return;
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
}


void EspejarVertical(Pixel*** matriz, int *filas, int *columnas)
{

    int nuevoAlto = *filas;
    int nuevoAncho = *columnas;

    Pixel** nuevaMatriz = (Pixel**)crearMatriz(sizeof(Pixel), nuevoAlto, nuevoAncho);
    if (!nuevaMatriz)
    {
        puts("Error al espejar-horizontal: sin memoria");
        return;
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
}

void Recortar(Pixel*** matriz, int *filas, int *columnas, float porcentaje)
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
        return;
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
}


void AchicarImagen(Pixel*** matriz, int* filas, int* columnas, float porcentaje)
{
    int nuevasFilas = (*filas * porcentaje) / 100;
    int nuevasColumnas = (*columnas * porcentaje) / 100;


    Pixel** matrizReducida = (Pixel**)crearMatriz(sizeof(Pixel), nuevasFilas, nuevasColumnas);

    if (!matrizReducida)
    {
        printf("Error al achicar: sin memoria.");
        return;
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

}



void ConcatenarVertical(Pixel*** matriz1, int* filas1, int* columnas1,const char* archivoEntrada)
{
    FILE *ImgSegunda = fopen(archivoEntrada, "rb");

        if (!ImgSegunda)
        {
            printf("Error abriendo archivos\n");
            fclose(ImgSegunda);
            return;
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
            return;
        }

        fseek(ImgSegunda, header.InicioImagen, SEEK_SET);
        LeerImagen(ImgSegunda, matriz2, dib.ancho, dib.altura);

    int nuevasFilas = *filas1 + dib.altura;
    int nuevasColumnas = (*columnas1 > dib.ancho) ? *columnas1 : dib.ancho;

    Pixel** matrizFinal = (Pixel**)crearMatriz(sizeof(Pixel), nuevasFilas, nuevasColumnas);
    if (!matrizFinal)
    {
        puts("Error al concatenar vertical: sin memoria.");
        fclose(ImgSegunda);
        return;
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
}

void ConcatenarHorizontal(Pixel*** matriz1, int* filas1, int* columnas1,const char* archivoEntrada)
{
    FILE *ImgSegunda = fopen(archivoEntrada, "rb");

        if (!ImgSegunda)
        {
            printf("Error abriendo archivos\n");
            fclose(ImgSegunda);
            return;
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
            return;
        }

        fseek(ImgSegunda, header.InicioImagen, SEEK_SET);
        LeerImagen(ImgSegunda, matriz2, dib.ancho, dib.altura);

    int nuevasFilas = (*filas1 > dib.altura) ? *filas1 : dib.altura;
    int nuevasColumnas = *columnas1 + dib.ancho;

    Pixel** matrizFinal = (Pixel**)crearMatriz(sizeof(Pixel), nuevasFilas, nuevasColumnas);
    if (!matrizFinal)
    {
        puts("Error al concatenar horizontal: sin memoria.");
        fclose(ImgSegunda);
        return;
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
}
