#ifndef FUNCIONES_LUNA_H
#define FUNCIONES_LUNA_H

#include "funciones_grupo.h"

void FiltroVerdeMatriz(Pixel** matriz, int filas, int columnas, float porcentaje);
void FiltroAzulMatriz(Pixel** matriz, int filas, int columnas, float porcentaje);
void FiltroRojoMatriz(Pixel** matriz, int filas, int columnas, float porcentaje);

void EscalaGris(Pixel** matriz, int filas, int columnas);
void InvertirColores(Pixel** matriz, int filas, int columnas);

void AumentoContraste(Pixel** matriz, int filas, int columnas, float porcentaje);
void ReduccionContraste(Pixel** matriz, int filas, int columnas,float porcentaje);
void Cebratricolor(Pixel** matriz, int filas, int columnas, float porcentaje);


void Pixelado(Pixel** matriz, int filas, int columnas, float porcentaje);
void Solarizacion(Pixel** matriz, int filas, int columnas, float porcentaje);

#endif // FUNCIONES_LUNA_H
//>>>>>>> f2aab2a4875a0c92088026a025c0a0a29471f2be
