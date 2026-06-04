#include "funciones_grupo.h"
#include "funciones_luna.h"
#define GRUPO "MIEL"
#define INTEGRANTE1 " DNI - APELLIDO, Nombre"
#define INTEGRANTE2 " DNI - APELLIDO, Nombre"
#define INTEGRANTE3 " DNI - APELLIDO, Nombre"
#define PROY "bmpmanipuleitor.exe"


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

            if (val < 10)  // L�nea roja
            {
                int aumento = matriz[i][j].rojo + (matriz[i][j].rojo * (porcentaje / 100));
                matriz[i][j].rojo = (aumento > 255) ? 255 : aumento;
            }
            else if (val < 2 * 10)  // L�nea verde
            {
                int aumento = matriz[i][j].verde + (matriz[i][j].verde * (porcentaje / 100));
                matriz[i][j].verde = (aumento > 255) ? 255 : aumento;
            }
            else  // L�nea azul
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

void instHelp(void)
{
    printf("\nGRUPO: %s",GRUPO);
    printf("\nINTEGRANTES: \n%s\n%s\n%s",INTEGRANTE1,INTEGRANTE2,INTEGRANTE3);
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


    return;
}

void Pixelado(Pixel** matriz, int filas, int columnas, float porcentaje)
{
    int tamBloque = (int)porcentaje;
    if (tamBloque < 1) tamBloque = 1;
 
    for (int i = 0; i < filas; i += tamBloque)
    {
        for (int j = 0; j < columnas; j += tamBloque)
        {
            // Calcular el promedio R, G, B del bloque
            long sumaR = 0, sumaG = 0, sumaB = 0;
            int cant = 0;
 
            for (int bi = i; bi < i + tamBloque && bi < filas; bi++)
            {
                for (int bj = j; bj < j + tamBloque && bj < columnas; bj++)
                {
                    sumaR += matriz[bi][bj].rojo;
                    sumaG += matriz[bi][bj].verde;
                    sumaB += matriz[bi][bj].azul;
                    cant++;
                }
            }
 
            unsigned char promedioR = (unsigned char)(sumaR / cant);
            unsigned char promedioG = (unsigned char)(sumaG / cant);
            unsigned char promedioB = (unsigned char)(sumaB / cant);
 
            // Pintar todo el bloque con ese promedio
            for (int bi = i; bi < i + tamBloque && bi < filas; bi++)
            {
                for (int bj = j; bj < j + tamBloque && bj < columnas; bj++)
                {
                    matriz[bi][bj].rojo  = promedioR;
                    matriz[bi][bj].verde = promedioG;
                    matriz[bi][bj].azul  = promedioB;
                }
            }
        }
    }
}

void Solarizacion(Pixel** matriz, int filas, int columnas, float porcentaje)
{
    int umbral = (int)(porcentaje * 255.0f / 100.0f);
 
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            if (matriz[i][j].rojo > umbral)
                matriz[i][j].rojo = 255 - matriz[i][j].rojo;
 
            if (matriz[i][j].verde > umbral)
                matriz[i][j].verde = 255 - matriz[i][j].verde;
 
            if (matriz[i][j].azul > umbral)
                matriz[i][j].azul = 255 - matriz[i][j].azul;
        }
    }
}