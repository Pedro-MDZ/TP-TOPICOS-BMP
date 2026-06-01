/*
Apellido: Luna, Josue Martiniano
DNI: 44598222
Entrega: Sí

Apellido: Alvarez Orozco, Bautista
DNI: 46091703
Entrega: Sí

Apellido: Espindola, Facundo Alejandro
DNI: 44587968
Entrega: No
*/
#ifndef FUNCIONES_GRUPO_H
#define FUNCIONES_GRUPO_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#pragma pack(1)

#define TODO_OK 0
#define BYTES_POR_PIXEL 3



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
    size_t cant_imagenes;
    size_t cant_filtros;
}instrucciones;

void ProcesarImagen(const char* archivoEntrada,const char* archivoEntrada2, const char* filtro);

void** crearMatriz(size_t tamElem, int filas, int columnas);

void destruirMatriz(void** matriz, int filas);

void LeerImagen(FILE* archivo, Pixel** matriz, int ancho, int alto);

void EscribirImagen(FILE* archivo, Pixel** matriz, int ancho, int alto);

void inicializar_instrucciones(instrucciones* inst);

void agregar_imagen(instrucciones* inst, const char* imagen);

void agregar_filtro(instrucciones* inst, const char* filtro);

void liberar_instrucciones(instrucciones* inst);

void CargarInstrucciones(instrucciones* inst, const char* cadena);

bool BuscarFiltro(const char* supuestofiltro);

#endif // FUNCIONES_GRUPO_H

