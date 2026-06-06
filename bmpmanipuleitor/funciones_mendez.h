#ifndef FUNCIONES_MENDEZ_H
#define FUNCIONES_MENDEZ_H

#include "funciones_grupo.h"

int RotarDerecha(Pixel*** matriz, int* filas, int* columnas,int verbose);
int RotarIzquierda(Pixel*** matriz, int* filas, int* columnas,int verbose);

int EspejarHorizontal(Pixel*** matriz, int *filas, int *columnas,int verbose);
int EspejarVertical(Pixel*** matriz, int *filas, int *columnas,int verbose);

int Recortar(Pixel*** matriz, int *filas, int *columnas,float porcentaje,int verbose);
int AchicarImagen(Pixel*** matriz, int* filas, int* columnas, float porcentaje,int verbose);
int ConcatenarVertical(Pixel*** matriz1, int* filas1, int* columnas1, const char* archivoEntrada,int verbose);
int ConcatenarHorizontal(Pixel*** matriz1, int* filas1, int* columnas1,const char* archivoEntrada,int verbose);

void instInfo(BMPHeader *header, DIBHeader *dheader,const char *nombreImagen);
void instHelp(void);
void instValidarBMP(BMPHeader *header, DIBHeader *dheader);
bool validarBMP(const char* imagen);
bool validarImagen(const char* imagen);
int verboseAct(instrucciones* inst);
void mostrarArgumentos(int argc,char* argv[]);
void mostrarInstrucciones(instrucciones* inst);
void validarVerbose(const char* imagen);

#endif // FUNCIONES_MENDEZ_H
