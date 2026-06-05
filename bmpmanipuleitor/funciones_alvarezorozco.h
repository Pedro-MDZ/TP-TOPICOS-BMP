#ifndef FUNCIONES_ALVAREZOROZCO_H
#define FUNCIONES_ALVAREZOROZCO_H

#include "funciones_grupo.h"

void RotarDerecha(Pixel*** matriz, int* filas, int* columnas);
void RotarIzquierda(Pixel*** matriz, int* filas, int* columnas);

void EspejarHorizontal(Pixel*** matriz, int *filas, int *columnas);
void EspejarVertical(Pixel*** matriz, int *filas, int *columnas);

void Recortar(Pixel*** matriz, int *filas, int *columnas,float porcentaje);
void AchicarImagen(Pixel*** matriz, int* filas, int* columnas, float porcentaje);
void ConcatenarVertical(Pixel*** matriz1, int* filas1, int* columnas1, const char* archivoEntrada);
void ConcatenarHorizontal(Pixel*** matriz1, int* filas1, int* columnas1,const char* archivoEntrada);

#endif // FUNCIONES_ALVAREZOROZCO_H