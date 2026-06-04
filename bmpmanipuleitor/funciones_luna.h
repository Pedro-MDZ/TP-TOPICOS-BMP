#ifndef FUNCIONES_LUNA_H
#define FUNCIONES_LUNA_H

#include "funciones_grupo.h"



#endif // FUNCIONES_LUNA_H


void FiltroVerdeMatriz(Pixel** matriz, int filas, int columnas, float porcentaje);
void FiltroAzulMatriz(Pixel** matriz, int filas, int columnas, float porcentaje);
void FiltroRojoMatriz(Pixel** matriz, int filas, int columnas, float porcentaje);

void EscalaGris(Pixel** matriz, int filas, int columnas);

void AumentoContraste(Pixel** matriz, int filas, int columnas, float porcentaje);
void ReduccionContraste(Pixel** matriz, int filas, int columnas,float porcentaje);
void Cebratricolor(Pixel** matriz, int filas, int columnas, float porcentaje);
void instInfo(BMPHeader *header, DIBHeader *dheader,char *nombreImagen);
void instHelp(void);
