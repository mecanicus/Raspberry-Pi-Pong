/*
 * pong1.h
 *
 *  Created on: 13/4/2017
 *      Author: Carlos
 */
#ifndef PONG1_H_
#define PONG1_H_

#include <stdio.h>

#define MATRIZ_ANCHO 	10
#define MATRIZ_ALTO 	7
#define RAQUETA_ANCHO 	1
#define RAQUETA_ALTO 	3
#define GOL_MAX		 	3

typedef struct {
	// Posicion
	int x;
	int y;
	// Forma
	int ancho;
	int alto;
} tipo_raqueta;

typedef struct {
	// Posicion
	int x;
	int y;
	// Trayectoria
	int xv;
	int yv;
} tipo_pelota;

typedef struct {
	int matriz[MATRIZ_ANCHO][MATRIZ_ALTO];
} tipo_pantalla;

typedef struct {
	int j1;
	int j2;
} tipo_marcador;

typedef struct {
	tipo_raqueta raquetasup;
	tipo_raqueta raquetainf;
	tipo_pelota pelota;
	tipo_pantalla pantalla;
	tipo_marcador marcador;
} tipo_pong;

void ReseteaMatriz(tipo_pantalla *p_pantalla);
void ReseteaMarcador(tipo_marcador *p_marcador);
void ReseteaPelota(tipo_pelota *p_pelota) ;
void ReseteaRaquetaInf(tipo_raqueta *p_raqueta);
void ReseteaRaquetaSup(tipo_raqueta *p_raqueta);
void PintaPantallaPorTerminal  (tipo_pantalla *p_pantalla);
void PintaMensajeInicialPantalla (tipo_pantalla *p_pantalla, tipo_pantalla *p_pantalla_inicial);
void GolPong(tipo_pong *p_pong, int j);
void PintaMensajeGolPantalla (tipo_pantalla *p_pantalla, tipo_pantalla *p_pantalla_inicial);
void PintaRaqueta(tipo_raqueta *p_raqueta, tipo_pantalla *p_pantalla);
void PintaPelota(tipo_pelota *p_pelota, tipo_pantalla *p_pantalla);
void ActualizaPantallaPong(tipo_pong* p_pong);
void InicializaPong(tipo_pong *p_pong);

#endif /* PONG1_H_ */
