#ifndef FUNCIONES_MENDEZ_H
#define FUNCIONES_MENDEZ_H

#include "funciones_grupo.h"

void RotarDerecha(Pixel*** matriz, int* filas, int* columnas,int verbose);
void RotarIzquierda(Pixel*** matriz, int* filas, int* columnas,int verbose);

void EspejarHorizontal(Pixel*** matriz, int *filas, int *columnas,int verbose);
void EspejarVertical(Pixel*** matriz, int *filas, int *columnas,int verbose);

void Recortar(Pixel*** matriz, int *filas, int *columnas,float porcentaje,int verbose);
void AchicarImagen(Pixel*** matriz, int* filas, int* columnas, float porcentaje,int verbose);
void ConcatenarVertical(Pixel*** matriz1, int* filas1, int* columnas1, const char* archivoEntrada,int verbose);
void ConcatenarHorizontal(Pixel*** matriz1, int* filas1, int* columnas1,const char* archivoEntrada,int verbose);

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
