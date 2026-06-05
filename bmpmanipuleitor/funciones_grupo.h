/*
Apellido: Luna, Josue Martiniano
DNI: 44598222
Entrega: Sí

Apellido: Mendez Mamani, Pedro
DNI: 46749197
Entrega: Sí

*/
#ifndef FUNCIONES_GRUPO_H
#define FUNCIONES_GRUPO_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#pragma pack(1)

#define BYTES_POR_PIXEL 3

#define EXITO 0
#define ERROR_ARGUMENTO 1
#define ERROR_ARCHIVO 2
#define ERROR_MEMORIA 3
#define ERROR_FORMATO 4

#define SIN_FILTRO -1
#define FILTRO_ESCALA_GRISES 10
#define FILTRO_NEGATIVO 11
#define FILTRO_ESPEJAR_H 12
#define FILTRO_ESPEJAR_V 13
#define FILTRO_AUMENTAR_CONTRASTE 14
#define FILTRO_REDUCIR_CONTRASTE 15
#define FILTRO_TONALIDAD_AZUL 16
#define FILTRO_TONALIDAD_VERDE 17
#define FILTRO_TONALIDAD_ROJA 18
#define FILTRO_RECORTAR 19
#define FILTRO_ACHICAR 20
#define FILTRO_ROTAR_DERECHA 21
#define FILTRO_ROTAR_IZQUIERDA 22
#define FILTRO_COMODIN1 23
#define FILTRO_COMODIN2 24
#define FILTRO_CONCATENAR_H 25
#define FILTRO_CONCATENAR_V 26

typedef struct {
    unsigned short tipo;
    unsigned int tamArch;
    unsigned short reservado1;
    unsigned short reservado2;
    unsigned int InicioImagen;
}BMPHeader;

typedef struct {
    unsigned int tamanio;
    int ancho;
    int altura;
    unsigned short planos;
    unsigned short tamPunto;
    unsigned int compresion;
    unsigned int tamImg;
    int resolHorizontal;
    int resolVertical;
    unsigned int tamTabCol;
    unsigned int contColores;
}DIBHeader;


typedef struct {
    unsigned char azul;
    unsigned char verde;
    unsigned char rojo;
}Pixel;

typedef struct{
    const char* imagenes[2];
    const char** filtros;
    const char** utilidades;
    size_t cant_imagenes;
    size_t cant_filtros;
    size_t cant_utilidades;
    int verbose;
}instrucciones;

int procesar_imagen(int argc, char* argv[]);

void ProcesarUtilidad(const char* archivoEntrada,const char* utilidad);

int ProcesarImagen(const char* archivoEntrada,const char* archivoEntrada2, const char* filtro);

void** crearMatriz(size_t tamElem, int filas, int columnas);

void destruirMatriz(void** matriz, int filas);

void LeerImagen(FILE* archivo, Pixel** matriz, int ancho, int alto);

void EscribirImagen(FILE* archivo, Pixel** matriz, int ancho, int alto);

void inicializar_instrucciones(instrucciones* inst);

int agregar_imagen(instrucciones* inst, const char* imagen);

int agregar_filtro(instrucciones* inst, const char* filtro);

int agregar_utilidad(instrucciones* inst, const char* utilidad);

void liberar_instrucciones(instrucciones* inst);

int CargarInstrucciones(instrucciones* inst, const char* cadena);

bool BuscarFiltro(const char* supuestofiltro);

int BuscarFiltro1(const char* supuestofiltro);

bool BuscarUtilidad(const char* utilidad);

bool validaCantImg(instrucciones *inst);





#endif // FUNCIONES_GRUPO_H

