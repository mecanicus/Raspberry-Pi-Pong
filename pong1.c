/*
 * pong1.c
 *
 *  Created on: 13/4/2017
 *      Author: Carlos
 */
#include "pong1.h"


void ReseteaMatriz(tipo_pantalla *p_pantalla) {
	//ponemos la matriz entera a 0
	int i, j = 0;

	for(i=0;i<MATRIZ_ANCHO;i++) {
		for(j=0;j<MATRIZ_ALTO;j++) {
			p_pantalla->matriz[i][j] = 0;
		}
	}
}

void ReseteaMarcador(tipo_marcador *p_marcador) {
	//empieza 0:0
	p_marcador->j1 = 0;
	p_marcador->j2 = 0;


}

void ReseteaPelota(tipo_pelota *p_pelota) {
	// Pelota inicialmente en el centro de la pantalla
	p_pelota->x = MATRIZ_ANCHO/2 - 1;
	p_pelota->y = MATRIZ_ALTO/2;

	// Trayectoria inicial
	p_pelota->yv = 0;
	p_pelota->xv = 1;

}

void ReseteaRaquetaInf(tipo_raqueta *p_raqueta) {
	// Raqueta inicialmente en el centro de la pantalla
	p_raqueta->x = 0;
	p_raqueta->y = MATRIZ_ALTO/2;
	p_raqueta->ancho = RAQUETA_ANCHO;
	p_raqueta->alto = RAQUETA_ALTO;
}

void ReseteaRaquetaSup(tipo_raqueta *p_raqueta) {
	// Raqueta inicialmente en el centro de la pantalla
	p_raqueta->y = MATRIZ_ALTO/2;
	p_raqueta->x = MATRIZ_ANCHO - 1;
	p_raqueta->ancho = RAQUETA_ANCHO;
	p_raqueta->alto = RAQUETA_ALTO;
}

void PintaPantallaPorTerminal  (tipo_pantalla *p_pantalla) {
	//pintamos la pantalla por terminal
	int i, j=0;
	puts("[PANTALLA]\n");
	for(i=0;i<MATRIZ_ALTO;i++) {
				for(j=0;j<MATRIZ_ANCHO;j++) {
					printf("%d",p_pantalla->matriz[j][i]);
				}
				printf("\n");

	}
}

void PintaMensajeInicialPantalla (tipo_pantalla *p_pantalla, tipo_pantalla *p_pantalla_inicial) {
	//pintamos el mensaje inicial
	int i,j = 0;
	for(i=0;i<MATRIZ_ANCHO;i++) {
			for(j=0;j<MATRIZ_ALTO;j++) {
				p_pantalla->matriz[i][j] = p_pantalla_inicial->matriz[i][j];
			}
	    }
}


/*void GolPong(tipo_pong *p_pong, int j)
 * Metodo al que se llama cuando hay un gol
 * se pinta el mensaje de gol y se actualiza
 * el marcador resetenado las figuras
 * */
void GolPong(tipo_pong *p_pong, int j) {
	static tipo_pantalla mensaje_inicial = { {
			{0,1,1,1,1,1,0},
			{0,1,0,1,0,1,0},
			{0,1,1,1,0,1,0},
			{0,0,0,0,0,0,0},
			{0,1,1,1,1,1,0},
			{0,1,0,0,0,1,0},
			{0,1,1,1,1,1,0},
			{0,0,0,0,0,0,0},
			{0,1,1,1,1,1,0},
			{0,1,0,0,0,0,0},
	} };
	ReseteaMatriz((tipo_pantalla*)(&(p_pong->pantalla)));
	ReseteaPelota((tipo_pelota*)(&(p_pong->pelota)));
	ReseteaRaquetaSup((tipo_raqueta*)(&(p_pong->raquetasup)));
	ReseteaRaquetaInf((tipo_raqueta*)(&(p_pong->raquetainf)));
	if (j == 1){
		p_pong->marcador.j1++;
	}else if (j == 2){
		p_pong->marcador.j2++;
	}
	PintaMensajeGolPantalla(&(p_pong->pantalla), &mensaje_inicial);
}

void PintaMensajeGolPantalla (tipo_pantalla *p_pantalla, tipo_pantalla *p_pantalla_inicial) {
	//pinta el mensaje de gol por la pantalla
	int i,j = 0;
	for(i=0;i<MATRIZ_ANCHO;i++) {
			for(j=0;j<MATRIZ_ALTO;j++) {
				p_pantalla->matriz[i][j] = p_pantalla_inicial->matriz[i][j];
			}
	    }
}


void PintaRaqueta(tipo_raqueta *p_raqueta, tipo_pantalla *p_pantalla) {
	//pinta la raqueta por la pantalla
	int i, j = 0;
	for(i=0;i<RAQUETA_ANCHO;i++) {
		for(j=0;j<RAQUETA_ALTO;j++) {
			if (( (p_raqueta->x+i >= 0) && (p_raqueta->x+i < MATRIZ_ANCHO) ) &&
					( (p_raqueta->y+j >= 0) && (p_raqueta->y+j < MATRIZ_ALTO) ))
				p_pantalla->matriz[p_raqueta->x+i][p_raqueta->y+j] = 1;
		}
	}
}

void PintaPelota(tipo_pelota *p_pelota, tipo_pantalla *p_pantalla) {
	//pinta la pelota por la pantalla
	// igual que en arkanopi
	if( (p_pelota->x >= 0) && (p_pelota->x < MATRIZ_ANCHO) ) {
		if( (p_pelota->y >= 0) && (p_pelota->y < MATRIZ_ALTO) ) {
			p_pantalla->matriz[p_pelota->x][p_pelota->y] = 1;
		}
		else {
			printf("\n\nPROBLEMAS!!!! posicion y=%d de la pelota INVALIDA!!!\n\n", p_pelota->y);
			fflush(stdout);
		}
	}
	else {
		printf("\n\nPROBLEMAS!!!! posicion x=%d de la pelota INVALIDA!!!\n\n", p_pelota->x);
		fflush(stdout);
	}
}

void ActualizaPantallaPong(tipo_pong* p_pong) {
	//reseteamos la matriz y pintamos todo el resto, las dos raquetas y la pelota
	ReseteaMatriz((tipo_pantalla*)(&(p_pong->pantalla)));
	PintaPelota(&(p_pong->pelota), &(p_pong->pantalla));
	PintaRaqueta(&(p_pong->raquetasup), &(p_pong->pantalla));
	PintaRaqueta(&(p_pong->raquetainf), &(p_pong->pantalla));
}

void InicializaPong(tipo_pong *p_pong) {
	//pintamos mensaje inicial y reseteamos todo el resto
	static tipo_pantalla mensaje_inicial = { {
			{0,0,0,0,0,0,0},
			{0,0,0,1,0,0,0},
			{1,1,0,1,1,0,0},
			{1,1,0,0,1,1,0},
			{0,0,0,0,0,1,1},
			{0,0,0,0,0,1,1},
			{1,1,0,0,1,1,0},
			{1,1,0,1,1,0,0},
			{0,0,0,1,0,0,0},
			{0,0,0,0,0,0,0},
	} };
	ReseteaMatriz((tipo_pantalla*)(&(p_pong->pantalla)));
	ReseteaPelota((tipo_pelota*)(&(p_pong->pelota)));
	ReseteaRaquetaSup((tipo_raqueta*)(&(p_pong->raquetasup)));
	ReseteaRaquetaInf((tipo_raqueta*)(&(p_pong->raquetainf)));
	ReseteaMarcador((tipo_marcador*)(&(p_pong->marcador)));
	PintaMensajeInicialPantalla(&p_pong->pantalla, &mensaje_inicial);
}




