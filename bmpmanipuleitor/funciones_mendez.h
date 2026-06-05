#ifndef FUNCIONES_MENDEZ_H
#define FUNCIONES_MENDEZ_H

#include "funciones_grupo.h"

int RotarDerecha(Pixel*** matriz, int* filas, int* columnas);
int RotarIzquierda(Pixel*** matriz, int* filas, int* columnas);

int EspejarHorizontal(Pixel*** matriz, int *filas, int *columnas);
int EspejarVertical(Pixel*** matriz, int *filas, int *columnas);

int Recortar(Pixel*** matriz, int *filas, int *columnas,float porcentaje);
int AchicarImagen(Pixel*** matriz, int* filas, int* columnas, float porcentaje);
int ConcatenarVertical(Pixel*** matriz1, int* filas1, int* columnas1, const char* archivoEntrada);
int ConcatenarHorizontal(Pixel*** matriz1, int* filas1, int* columnas1,const char* archivoEntrada);

void instInfo(BMPHeader *header, DIBHeader *dheader,const char *nombreImagen);
void instHelp(void);
void instValidarBMP(BMPHeader *header, DIBHeader *dheader);
bool validarBMP(const char* imagen);
bool validarImagen(const char* imagen);
int verboseAct(instrucciones* inst);
void mostrarArgumentos(int argc,char* argv[]);
void mostrarInstrucciones(instrucciones* inst);

#endif // FUNCIONES_MENDEZ_H
