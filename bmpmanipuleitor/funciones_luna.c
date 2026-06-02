#include "funciones_grupo.h"
#include "funciones_luna.h"


void FiltroVerdeMatriz(Pixel** matriz, int filas, int columnas, float porcentaje)
{
    for(int i = 0; i < filas; i++)
    {
        for(int j = 0; j < columnas; j++)
        {
            int aumento = matriz[i][j].verde + (matriz[i][j].verde * (porcentaje/100));
            matriz[i][j].verde = (aumento > 255) ? 255 : aumento;
        }
    }
}

void FiltroAzulMatriz(Pixel** matriz, int filas, int columnas, float porcentaje)
{
    for(int i = 0; i < filas; i++)
    {
        for(int j = 0; j < columnas; j++)
        {
            int aumento = matriz[i][j].azul + (matriz[i][j].azul * (porcentaje/100));
            matriz[i][j].azul = (aumento > 255) ? 255 : aumento;
        }
    }
}

void FiltroRojoMatriz(Pixel** matriz, int filas, int columnas, float porcentaje)
{
    for(int i = 0; i < filas; i++)
    {
        for(int j = 0; j < columnas; j++)
        {
            int aumento = matriz[i][j].rojo + (matriz[i][j].rojo * (porcentaje/100));
            matriz[i][j].rojo = (aumento > 255) ? 255 : aumento;
        }
    }
}

void EscalaGris(Pixel** matriz, int filas, int columnas)
{
    unsigned char gris;
    for(int i = 0; i < filas; i++)
    {
        for(int j = 0; j < columnas; j++)
        {
            // Calcular el valor gris (con redondeo)
            gris = ((matriz[i][j].rojo * 0.3)+(matriz[i][j].verde * 0.59)+(matriz[i][j].azul * 0.11)) ;
            matriz[i][j].rojo = gris;
            matriz[i][j].verde = gris;
            matriz[i][j].azul = gris;
        }
    }
}

void AumentoContraste(Pixel** matriz, int filas, int columnas, float porcentaje)
{
    int valor,nuevoValor;
    float factor= 1.0 + (porcentaje/100); //cuanto mas de contraste
    for(int i = 0; i < filas; i++)
    {
        for(int j = 0; j < columnas; j++)
        {
            //rojo
            valor= matriz[i][j].rojo;
            nuevoValor = ((valor - 128)* factor + 128);
            if (nuevoValor > 255)
                nuevoValor = 255;
            if (nuevoValor < 0)
                nuevoValor = 0;
            matriz[i][j].rojo=(unsigned char)nuevoValor;
            //verde
            valor=matriz[i][j].verde;
            nuevoValor = ((valor - 128)* factor + 128);
            if (nuevoValor > 255)
                nuevoValor = 255;
            if (nuevoValor < 0)
                nuevoValor = 0;
            matriz[i][j].verde=(unsigned char)nuevoValor;
            //azul
            valor=matriz[i][j].azul;
            nuevoValor = ((valor - 128)* factor + 128);
            if (nuevoValor > 255)
                nuevoValor = 255;
            if (nuevoValor < 0)
                nuevoValor = 0;
            matriz[i][j].azul=(unsigned char)nuevoValor;

        }
    }
}

void ReduccionContraste(Pixel** matriz, int filas, int columnas, float porcentaje)
{
    int valor,nuevoValor;
    float factor = 1.0 -(porcentaje/100); //valor debajo del 1 es para menos, asi se acerca mas al gris
    for(int i = 0; i < filas; i++)
    {
        for(int j = 0; j < columnas; j++)
        {
            //rojo
            valor=matriz[i][j].rojo;
            nuevoValor = ((valor - 128)* factor + 128);
            if (nuevoValor > 255)
                nuevoValor = 255;
            if (nuevoValor < 0)
                nuevoValor = 0;
            matriz[i][j].rojo=(unsigned char)nuevoValor;
            //verde
            valor=matriz[i][j].verde;
            nuevoValor = ((valor - 128)* factor + 128);
            if (nuevoValor > 255)
                nuevoValor = 255;
            if (nuevoValor < 0)
                nuevoValor = 0;
            matriz[i][j].verde=(unsigned char)nuevoValor;
            //azul
            valor=matriz[i][j].azul;
            nuevoValor = ((valor - 128)* factor + 128);
            if (nuevoValor > 255)
                nuevoValor = 255;
            if (nuevoValor < 0)
                nuevoValor = 0;
            matriz[i][j].azul=(unsigned char)nuevoValor;

        }
    }
}

void Cebratricolor(Pixel** matriz, int filas, int columnas, float porcentaje)
{
    int ciclo = 3 * 10;

    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            int val = (i + j) % ciclo;

            if (val < 10)  // Línea roja
            {
                int aumento = matriz[i][j].rojo + (matriz[i][j].rojo * (porcentaje / 100));
                matriz[i][j].rojo = (aumento > 255) ? 255 : aumento;
            }
            else if (val < 2 * 10)  // Línea verde
            {
                int aumento = matriz[i][j].verde + (matriz[i][j].verde * (porcentaje / 100));
                matriz[i][j].verde = (aumento > 255) ? 255 : aumento;
            }
            else  // Línea azul
            {
                int aumento = matriz[i][j].azul + (matriz[i][j].azul * (porcentaje / 100));
                matriz[i][j].azul = (aumento > 255) ? 255 : aumento;
            }
        }
    }
}

void instInfo(BMPHeader *header, DIBHeader *dheader,char *nombreImagen)
{
    unsigned int padding = (4 - (dheader->ancho * BYTES_POR_PIXEL) % 4) % 4;
    printf("\nArchivo: %s",nombreImagen);
    printf("\nTamanio del archivo: %d bytes",header->tamArch);
    printf("\nDimensiones: %d x %d",dheader->ancho,dheader->altura);
    printf("\nProfundidad: %d bits",dheader->tamPunto);
    printf("\nCompresion: %d ",dheader->compresion);
    printf("\nOffset de datos: %d bytes",(int)(sizeof(BMPHeader)+sizeof(DIBHeader)));
    printf("\nTamanio de la imagen: %d bytes",dheader->tamImg);
    printf("\nPadding por fila: %d bytes",padding);
}
