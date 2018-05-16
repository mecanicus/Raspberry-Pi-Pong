#include "arkanoPi_1.h"
#include "fsm.h"



static /*volatile*/ tipo_juego juego;

//------------------------------------------------------
// FUNCIONES DE ACCION
//------------------------------------------------------
enum fsm_state {
	WAIT_START=0,
	WAIT_PUSH=1,
	WAIT_END=2,
};
int columna=0;
int debounceTime=DEBOUNCE_TIME;
static tmr_t* tmrt;
static tmr_t* tmrp;

int col[7] = {0,1,2,3,4,7,23};

volatile int flags = 0;
//volatile int flagc= 0;
void delay_until (unsigned int next) {
	unsigned int now = millis();

	if (next > now) {
		delay (next - now);
	}
}
int CompruebaTeclaPulsada (fsm_t* this) {//este metodo devuelve un 1 si el flag que comprueba esta activado
	//asi la matriz de estados es capaz de saber los flags que han sido activados
	int result;

	piLock (FLAGS_KEY);
	result = (flags & FLAG_TECLA);
	piUnlock (FLAGS_KEY);

	return result;
}

int CompruebaTeclaPelota (fsm_t* this) {//este metodo devuelve un 1 si el flag que comprueba esta activado
	//asi la matriz de estados es capaz de saber los flags que han sido activados
	int result;

	piLock (FLAGS_KEY);
	result = (flags & FLAG_PELOTA);
	piUnlock (FLAGS_KEY);

	return result;
}

int CompruebaTeclaRaquetaIzquierda (fsm_t* this) {//este metodo devuelve un 1 si el flag que comprueba esta activado
	//asi la matriz de estados es capaz de saber los flags que han sido activados
	int result;

	piLock (FLAGS_KEY);
	result = (flags & FLAG_RAQUETA_IZQUIERDA);
	piUnlock (FLAGS_KEY);

	return result;
}
int CompruebaTeclaRaquetaIzquierda_2 (fsm_t* this) {//este metodo devuelve un 1 si el flag que comprueba esta activado
	//asi la matriz de estados es capaz de saber los flags que han sido activados
	int result;

	piLock (FLAGS_KEY);
	result = (flags & FLAG_RAQUETA_IZQUIERDA_2);
	piUnlock (FLAGS_KEY);

	return result;
}

int CompruebaTeclaRaquetaDerecha (fsm_t* this) {//este metodo devuelve un 1 si el flag que comprueba esta activado
	//asi la matriz de estados es capaz de saber los flags que han sido activados
	int result;

	piLock (FLAGS_KEY);
	result = (flags & FLAG_RAQUETA_DERECHA);
	piUnlock (FLAGS_KEY);

	return result;
}
int CompruebaTeclaRaquetaDerecha_2 (fsm_t* this) {//este metodo devuelve un 1 si el flag que comprueba esta activado
	//asi la matriz de estados es capaz de saber los flags que han sido activados
	int result;

	piLock (FLAGS_KEY);
	result = (flags & FLAG_RAQUETA_DERECHA_2);
	piUnlock (FLAGS_KEY);

	return result;
}

int CompruebaFinalJuego (fsm_t* this) {//este metodo devuelve un 1 si el flag que comprueba esta activado
	//asi la matriz de estados es capaz de saber los flags que han sido activados
	int result;

	piLock (FLAGS_KEY);
	result = (flags & FLAG_FINAL_JUEGO);
	piUnlock (FLAGS_KEY);

	return result;
}


/* void InicializaJuego (fsm_t *fsm): funcion encargada de llevar a cabo
 la oportuna inicializaci髇 de toda variable o estructura de datos
 que resulte necesaria para el desarrollo del juego.*/
void InicializaJuego (fsm_t *fsm) {
	piLock (FLAGS_KEY);
	flags &= ~FLAG_TECLA;
	piUnlock (FLAGS_KEY);

	piLock (STD_IO_BUFFER_KEY);
	ActualizaPantallaPong(&juego.pong);
	PintaPantallaPorTerminal(&juego.pong.pantalla);
	piUnlock (STD_IO_BUFFER_KEY);



}

/* void MueveRaquetaIzquierda (fsm_t *fsm): funcion
 * encargda de mover la raqueta izquierda hacia arriba*/
void MueveRaquetaIzquierda(fsm_t *fsm) {

	piLock (FLAGS_KEY);
	flags &= ~FLAG_RAQUETA_IZQUIERDA;
	flags &= ~FLAG_TECLA;
	piUnlock (FLAGS_KEY);

	if(juego.pong.raquetasup.y>-2){
		juego.pong.raquetasup.y--;

	}
	piLock (STD_IO_BUFFER_KEY);
	ActualizaPantallaPong(&juego.pong);
	PintaPantallaPorTerminal(&juego.pong.pantalla);
	piUnlock (STD_IO_BUFFER_KEY);
}

/* void MueveRaquetaIzquierda_2 (fsm_t *fsm): funcion
 * encargda de mover la raqueta derecha hacia arriba*/
void MueveRaquetaIzquierda_2(fsm_t *fsm) {

	piLock (FLAGS_KEY);
	flags &= ~FLAG_RAQUETA_IZQUIERDA_2;
	flags &= ~FLAG_TECLA;
	piUnlock (FLAGS_KEY);

	if(juego.pong.raquetainf.y>-2){
		juego.pong.raquetainf.y--;

	}
	piLock (STD_IO_BUFFER_KEY);
	ActualizaPantallaPong(&juego.pong);
	PintaPantallaPorTerminal(&juego.pong.pantalla);
	piUnlock (STD_IO_BUFFER_KEY);
}

/* void MueveRaquetaDerecha (fsm_t *fsm): funcion
 * encargda de mover la raqueta izquierda hacia abajo*/
void MueveRaquetaDerecha(fsm_t *fsm) {

	piLock (FLAGS_KEY);
	flags &= ~FLAG_RAQUETA_DERECHA;
	flags &= ~FLAG_TECLA;
	piUnlock (FLAGS_KEY);

	if(juego.pong.raquetasup.y<6){
		juego.pong.raquetasup.y++;

	}
	piLock (STD_IO_BUFFER_KEY);
	ActualizaPantallaPong(&juego.pong);
	PintaPantallaPorTerminal(&juego.pong.pantalla);
	piUnlock (STD_IO_BUFFER_KEY);
}

/* void MueveRaquetaDerecha_2 (fsm_t *fsm): funcion
 * encargda de mover la raqueta derecha hacia abajo*/
void MueveRaquetaDerecha_2(fsm_t *fsm) {

	piLock (FLAGS_KEY);
	flags &= ~FLAG_RAQUETA_DERECHA_2;
	flags &= ~FLAG_TECLA;
	piUnlock (FLAGS_KEY);

	if(juego.pong.raquetainf.y<6){
		juego.pong.raquetainf.y++;

	}
	piLock (STD_IO_BUFFER_KEY);
	ActualizaPantallaPong(&juego.pong);
	PintaPantallaPorTerminal(&juego.pong.pantalla);
	piUnlock (STD_IO_BUFFER_KEY);
}

/*void MarcaGol (int i): funcion encargada de
 * llevar a cabo todo lo necesario cuando se marca un gol */
void MarcaGol (int i){
	GolPong(&juego.pong, i);//metodo que realmente cambia el marcador e imprime el mensaje
	sleep(2);//damos dos segundos de impresion del mensaje de gol
	if (juego.pong.marcador.j1 == 3 || juego.pong.marcador.j2 == 3){
		flags |= FLAG_FINAL_JUEGO;//si alguno de los usuarios llega a 3 goles se acaba la partida
	}
}
/* void MovimientoPelota (fsm_t *fsm): funci髇 encargada de actualizar la
 *posici髇 de la pelota en funci髇 de la direccion de esta, asi como de los obstaculos.
 *el proceso a seguir es igual que en el arkano solo que con la horientacion en horizontal */
void MovimientoPelota (fsm_t *fsm) {//SI SE LLEGA A LA FILA 0 O 6 HAY QUE CONTAR GOL NO ACABAR EL JUEGO METODO GOOOOLL

		piLock (FLAGS_KEY);
		flags &= ~FLAG_PELOTA;
		flags &= ~FLAG_TECLA;
		piUnlock (FLAGS_KEY);

		switch (juego.pong.pelota.x){

		case 0:
			MarcaGol (2);
		break;

		case 1:
			if(juego.pong.pelota.xv == +1){
				if (juego.pong.pelota.y == 6 && juego.pong.pelota.yv == 1){
					juego.pong.pelota.y--;
					juego.pong.pelota.x += juego.pong.pelota.xv;
					juego.pong.pelota.yv = -1;
				}else if (juego.pong.pelota.y == 0 && juego.pong.pelota.yv == -1){
					juego.pong.pelota.y++;
					juego.pong.pelota.x += juego.pong.pelota.xv;
					juego.pong.pelota.yv = +1;
				}else{
					juego.pong.pelota.x += juego.pong.pelota.xv;
					juego.pong.pelota.y += juego.pong.pelota.yv;
				}
			}else{
				if (juego.pong.pelota.yv ==  0){
					if(juego.pong.pelota.y == juego.pong.raquetainf.y+1){
						juego.pong.pelota.x++;
						juego.pong.pelota.xv = 1;
					}else if(juego.pong.pelota.y == juego.pong.raquetainf.y){
						if (juego.pong.pelota.y == 0){
							juego.pong.pelota.x++;
							juego.pong.pelota.y++;
							juego.pong.pelota.xv = +1;
							juego.pong.pelota.yv = +1;
						}else{
							juego.pong.pelota.x++;
							juego.pong.pelota.y--;
							juego.pong.pelota.xv = 1;
							juego.pong.pelota.yv = -1;
						}
					}else if(juego.pong.pelota.y == juego.pong.raquetainf.y+2){
						if (juego.pong.pelota.y == 6){
							juego.pong.pelota.x++;
							juego.pong.pelota.y--;
							juego.pong.pelota.xv = 1;
							juego.pong.pelota.yv = -1;
						}else{
							juego.pong.pelota.x++;
							juego.pong.pelota.y++;
							juego.pong.pelota.xv = 1;
							juego.pong.pelota.yv = 1;
						}
					}else{
						juego.pong.pelota.x--;
					}
				}else if(juego.pong.pelota.yv == 1){
					if(juego.pong.pelota.y == juego.pong.raquetainf.y-1){
						if(juego.pong.pelota.y != 0){
							juego.pong.pelota.y--;
							juego.pong.pelota.yv = -1;
							juego.pong.pelota.xv = 1;
							juego.pong.pelota.x++;
						}else{
							juego.pong.pelota.y++;
							juego.pong.pelota.yv = +1;
							juego.pong.pelota.xv = +1;
							juego.pong.pelota.x++;
						}
					}else if(juego.pong.pelota.y == juego.pong.raquetainf.y){
						juego.pong.pelota.x++;
						juego.pong.pelota.yv = 0;
						juego.pong.pelota.xv = 1;
					}else if(juego.pong.pelota.y == juego.pong.raquetainf.y+1){
						if (juego.pong.pelota.y == 6){
							juego.pong.pelota.x++;
							juego.pong.pelota.y--;
							juego.pong.pelota.xv = 1;
							juego.pong.pelota.yv = -1;
						}else{
							juego.pong.pelota.x++;
							juego.pong.pelota.y++;
							juego.pong.pelota.xv = 1;
							juego.pong.pelota.yv = 1;
						}
					}else if(juego.pong.pelota.y == 6 && juego.pong.raquetainf.y == 4){
						juego.pong.pelota.yv = 0;
						juego.pong.pelota.xv = 1;
						juego.pong.pelota.x++;
					}else if(juego.pong.pelota.y == 6 && juego.pong.raquetainf.y == 3){
						juego.pong.pelota.xv = 1;
						juego.pong.pelota.yv = -1;
						juego.pong.pelota.y --;
						juego.pong.pelota.x++;
					}else{
						if(juego.pong.pelota.y==6){
							juego.pong.pelota.y--;
							juego.pong.pelota.x--;
						}else{

							juego.pong.pelota.y++;
							juego.pong.pelota.x--;
						}
					}
				}else{
					if(juego.pong.pelota.y == juego.pong.raquetainf.y+3){
						if(juego.pong.pelota.y != 6){
							juego.pong.pelota.y++;
							juego.pong.pelota.yv = 1;
							juego.pong.pelota.xv = 1;
							juego.pong.pelota.x++;
						}else{
							juego.pong.pelota.y--;
							juego.pong.pelota.yv = -1;
							juego.pong.pelota.xv = +1;
							juego.pong.pelota.x++;
						}
					}else if(juego.pong.pelota.y == juego.pong.raquetainf.y+2){
						juego.pong.pelota.x++;
						juego.pong.pelota.yv = 0;
						juego.pong.pelota.xv = 1;
					}else if(juego.pong.pelota.y == juego.pong.raquetainf.y+1){
						if (juego.pong.pelota.y == 0){
							juego.pong.pelota.x++;
							juego.pong.pelota.y++;
							juego.pong.pelota.xv = 1;
							juego.pong.pelota.yv = 1;
						}else{
							juego.pong.pelota.x++;
							juego.pong.pelota.y--;
							juego.pong.pelota.xv = 1;
							juego.pong.pelota.yv = -1;
						}
					}else if(juego.pong.pelota.y == 0 && juego.pong.raquetainf.y == 0){
						juego.pong.pelota.yv = 0;
						juego.pong.pelota.xv = 1;
						juego.pong.pelota.x++;
					}else if(juego.pong.pelota.y == 0 && juego.pong.raquetainf.y == 1){
						juego.pong.pelota.xv = 1;
						juego.pong.pelota.yv = 1;
						juego.pong.pelota.y++;
						juego.pong.pelota.x++;
					}else{
						if(juego.pong.pelota.y==0){
							juego.pong.pelota.y++;
							juego.pong.pelota.x--;
						}else{

							juego.pong.pelota.y--;
							juego.pong.pelota.x--;
						}
					}
				}
			}
			break;

		case 2:
			if (juego.pong.pelota.y == 6 && juego.pong.pelota.yv == 1){
				juego.pong.pelota.y--;
				juego.pong.pelota.x += juego.pong.pelota.xv;
				juego.pong.pelota.yv = -1;
			}else if (juego.pong.pelota.y == 0 && juego.pong.pelota.yv == -1){
				juego.pong.pelota.y++;
				juego.pong.pelota.x += juego.pong.pelota.xv;
				juego.pong.pelota.yv = +1;
			}else{
				juego.pong.pelota.x += juego.pong.pelota.xv;
				juego.pong.pelota.y += juego.pong.pelota.yv;
			}

			break;

		case 3:
			if (juego.pong.pelota.y == 6 && juego.pong.pelota.yv == 1){
				juego.pong.pelota.y--;
				juego.pong.pelota.x += juego.pong.pelota.xv;
				juego.pong.pelota.yv = -1;
			}else if (juego.pong.pelota.y == 0 && juego.pong.pelota.yv == -1){
				juego.pong.pelota.y++;
				juego.pong.pelota.x += juego.pong.pelota.xv;
				juego.pong.pelota.yv = +1;
			}else{
				juego.pong.pelota.x += juego.pong.pelota.xv;
				juego.pong.pelota.y += juego.pong.pelota.yv;
			}

			break;

		case 4:
			if (juego.pong.pelota.y == 6 && juego.pong.pelota.yv == 1){
				juego.pong.pelota.y--;
				juego.pong.pelota.x += juego.pong.pelota.xv;
				juego.pong.pelota.yv = -1;
			}else if (juego.pong.pelota.y == 0 && juego.pong.pelota.yv == -1){
				juego.pong.pelota.y++;
				juego.pong.pelota.x += juego.pong.pelota.xv;
				juego.pong.pelota.yv = +1;
			}else{
				juego.pong.pelota.x += juego.pong.pelota.xv;
				juego.pong.pelota.y += juego.pong.pelota.yv;
			}

			break;

		case 5:
			if (juego.pong.pelota.y == 6 && juego.pong.pelota.yv == 1){
				juego.pong.pelota.y--;
				juego.pong.pelota.x += juego.pong.pelota.xv;
				juego.pong.pelota.yv = -1;
			}else if (juego.pong.pelota.y == 0 && juego.pong.pelota.yv == -1){
				juego.pong.pelota.y++;
				juego.pong.pelota.x += juego.pong.pelota.xv;
				juego.pong.pelota.yv = +1;
			}else{
				juego.pong.pelota.x += juego.pong.pelota.xv;
				juego.pong.pelota.y += juego.pong.pelota.yv;
			}

			break;

		case 6:
			if (juego.pong.pelota.y == 6 && juego.pong.pelota.yv == 1){
				juego.pong.pelota.y--;
				juego.pong.pelota.x += juego.pong.pelota.xv;
				juego.pong.pelota.yv = -1;
			}else if (juego.pong.pelota.y == 0 && juego.pong.pelota.yv == -1){
				juego.pong.pelota.y++;
				juego.pong.pelota.x += juego.pong.pelota.xv;
				juego.pong.pelota.yv = +1;
			}else{
				juego.pong.pelota.x += juego.pong.pelota.xv;
				juego.pong.pelota.y += juego.pong.pelota.yv;
			}

			break;

		case 7:
			if (juego.pong.pelota.y == 6 && juego.pong.pelota.yv == 1){
				juego.pong.pelota.y--;
				juego.pong.pelota.x += juego.pong.pelota.xv;
				juego.pong.pelota.yv = -1;
			}else if (juego.pong.pelota.y == 0 && juego.pong.pelota.yv == -1){
				juego.pong.pelota.y++;
				juego.pong.pelota.x += juego.pong.pelota.xv;
				juego.pong.pelota.yv = +1;
			}else{
				juego.pong.pelota.x += juego.pong.pelota.xv;
				juego.pong.pelota.y += juego.pong.pelota.yv;
			}

			break;

		case 8:
			if(juego.pong.pelota.xv == -1){
				if (juego.pong.pelota.y == 6 && juego.pong.pelota.yv == 1){
					juego.pong.pelota.y--;
					juego.pong.pelota.x += juego.pong.pelota.xv;
					juego.pong.pelota.yv = -1;
				}else if (juego.pong.pelota.y == 0 && juego.pong.pelota.yv == -1){
					juego.pong.pelota.y++;
					juego.pong.pelota.x += juego.pong.pelota.xv;
					juego.pong.pelota.yv = +1;
				}else{
					juego.pong.pelota.x += juego.pong.pelota.xv;
					juego.pong.pelota.y += juego.pong.pelota.yv;
				}
			}else{
				if (juego.pong.pelota.yv ==  0){ // Va recto para la derecha
					if(juego.pong.pelota.y == juego.pong.raquetasup.y+1){ // Se choca con el medio
						juego.pong.pelota.x--;
						juego.pong.pelota.xv = -1;
					}else if(juego.pong.pelota.y == juego.pong.raquetasup.y){
						if (juego.pong.pelota.y == 0){
							juego.pong.pelota.x--;
							juego.pong.pelota.y++;
							juego.pong.pelota.xv = -1;
							juego.pong.pelota.yv = +1;
						}else{
							juego.pong.pelota.x--;
							juego.pong.pelota.y--;
							juego.pong.pelota.xv = -1;
							juego.pong.pelota.yv = -1;
						}
					}else if(juego.pong.pelota.y == juego.pong.raquetasup.y+2){
						if (juego.pong.pelota.y == 6){
							juego.pong.pelota.x--;
							juego.pong.pelota.y--;
							juego.pong.pelota.xv = -1;
							juego.pong.pelota.yv = -1;
						}else{
							juego.pong.pelota.x--;
							juego.pong.pelota.y++;
							juego.pong.pelota.xv = -1;
							juego.pong.pelota.yv = 1;
						}
					}else{
						juego.pong.pelota.x++;
					}
				}else if(juego.pong.pelota.yv == 1){
					if(juego.pong.pelota.y == juego.pong.raquetasup.y-1){
						if(juego.pong.pelota.y != 0){
							juego.pong.pelota.y--;
							juego.pong.pelota.yv = -1;
							juego.pong.pelota.xv = -1;
							juego.pong.pelota.x--;
						}else{
							juego.pong.pelota.y++;
							juego.pong.pelota.yv = +1;
							juego.pong.pelota.xv = -1;
							juego.pong.pelota.x--;
						}
					}else if(juego.pong.pelota.y == juego.pong.raquetasup.y){
						juego.pong.pelota.x--;
						juego.pong.pelota.yv = 0;
						juego.pong.pelota.xv = -1;
					}else if(juego.pong.pelota.y == juego.pong.raquetasup.y+1){
						if (juego.pong.pelota.y == 6){
							juego.pong.pelota.x--;
							juego.pong.pelota.y--;
							juego.pong.pelota.xv = -1;
							juego.pong.pelota.yv = -1;
						}else{
							juego.pong.pelota.x--;
							juego.pong.pelota.y++;
							juego.pong.pelota.xv = -1;
							juego.pong.pelota.yv = 1;
						}
					}else if(juego.pong.pelota.y == 6 && juego.pong.raquetasup.y == 4){
						juego.pong.pelota.yv = 0;
						juego.pong.pelota.xv = -1;
						juego.pong.pelota.x--;
					}else if(juego.pong.pelota.y == 6 && juego.pong.raquetasup.y == 3){
						juego.pong.pelota.xv = -1;
						juego.pong.pelota.yv = -1;
						juego.pong.pelota.y --;
						juego.pong.pelota.x--;
					}else{
						if(juego.pong.pelota.y==6){
							juego.pong.pelota.y--;
							juego.pong.pelota.x++;
						}else{

							juego.pong.pelota.y++;
							juego.pong.pelota.x++;
						}
					}
				}else{
					if(juego.pong.pelota.y == juego.pong.raquetasup.y+3){
						if(juego.pong.pelota.y != 6){
							juego.pong.pelota.y++;
							juego.pong.pelota.yv = 1;
							juego.pong.pelota.xv = -1;
							juego.pong.pelota.x--;
						}else{
							juego.pong.pelota.y--;
							juego.pong.pelota.yv = -1;
							juego.pong.pelota.xv = -1;
							juego.pong.pelota.x--;
						}
					}else if(juego.pong.pelota.y == juego.pong.raquetasup.y+2){
						juego.pong.pelota.x--;
						juego.pong.pelota.y--;
						juego.pong.pelota.yv = 0;
						juego.pong.pelota.xv = -1;
					}else if(juego.pong.pelota.y == juego.pong.raquetasup.y+1){
						if (juego.pong.pelota.y == 0){
							juego.pong.pelota.x--;
							juego.pong.pelota.y++;
							juego.pong.pelota.xv = -1;
							juego.pong.pelota.yv = 1;
						}else{
							juego.pong.pelota.x--;
							juego.pong.pelota.y--;
							juego.pong.pelota.xv = -1;
							juego.pong.pelota.yv = -1;
						}
					}else if(juego.pong.pelota.y == 0 && juego.pong.raquetasup.y == 0){
						juego.pong.pelota.yv = 0;
						juego.pong.pelota.xv = -1;
						juego.pong.pelota.x--;
					}else if(juego.pong.pelota.y == 0 && juego.pong.raquetasup.y == 1){
						juego.pong.pelota.xv = -1;
						juego.pong.pelota.yv = 1;
						juego.pong.pelota.y++;
						juego.pong.pelota.x--;
					}else{
						if(juego.pong.pelota.y==0){
							juego.pong.pelota.y++;
							juego.pong.pelota.x++;
						}else{

							juego.pong.pelota.y--;
							juego.pong.pelota.x++;
						}
					}
				}
			}
			break;

		case 9:
				MarcaGol (1);
		break;
		}
		piLock (STD_IO_BUFFER_KEY);
		ActualizaPantallaPong(&juego.pong);
		PintaPantallaPorTerminal(&juego.pong.pantalla);
		piUnlock (STD_IO_BUFFER_KEY);
}


/* void FinalJuego (fsm_t *fsm): funci贸n encargada de mostrar en la ventana de
* terminal los mensajes necesarios para informar acerca del resultado del juego.*/
void FinalJuego (fsm_t *fsm) {
	piLock (FLAGS_KEY);
	flags &= ~FLAG_FINAL_JUEGO;
	flags &= ~FLAG_TECLA;
	piUnlock (FLAGS_KEY);

	piLock (STD_IO_BUFFER_KEY);
	if (juego.pong.marcador.j1 > juego.pong.marcador.j2){
		printf ("GANADOR JUGADOR 1, RESULTADO %d = %d", juego.pong.marcador.j1, juego.pong.marcador.j2 );
	}else{
		printf ("GANADOR JUGADOR 2, RESULTADO %d = %d", juego.pong.marcador.j2, juego.pong.marcador.j1 );
	}
	piUnlock (STD_IO_BUFFER_KEY);


}

/*void ReseteaJuego (void): funci贸n encargada de llevar a cabo la
* reinicializaci贸n de cuantas variables o estructuras resulten
* necesarias para dar comienzo a una nueva partida.*/
void ReseteaJuego (fsm_t *fsm) {
	piLock (FLAGS_KEY);
	flags &= ~FLAG_FINAL_JUEGO;
	flags &= ~FLAG_TECLA;
	piUnlock (FLAGS_KEY);

	InicializaPong(&juego.pong);//metodo que pinta el mensaje por pantalla e inicializa el juego correctamente
	piLock (STD_IO_BUFFER_KEY);
	PintaPantallaPorTerminal(&juego.pong.pantalla);
	piUnlock (STD_IO_BUFFER_KEY);

}

//------------------------------------------------------
// FUNCIONES DE INICIALIZACION
//------------------------------------------------------

/* int systemSetup (void): procedimiento de configuracion del sistema.
* configura el uso de posibles librerias ,
* configurar las interrupciones externas asociadas a los pines GPIO,
* configurar las interrupciones peri贸dicas y sus correspondientes temporizadores,
* crear, si fuese necesario, los threads adicionales que pueda requerir el sistema*/
int systemSetup (void) {

	wiringPiSetupGpio();
	piLock (FLAGS_KEY);
	flags = 0;
	piUnlock (FLAGS_KEY);
	//inicia timers
	tmrt = tmr_new (refrescar);
	tmrp = tmr_new (flagPelota);
	tmr_startms (tmrt, 1);
	tmr_startms (tmrp, 1000);
	//filas
	pinMode(0,OUTPUT);
	pinMode(1,OUTPUT);
	pinMode(2,OUTPUT);
	pinMode(3,OUTPUT);
	pinMode(4,OUTPUT);
	pinMode(7,OUTPUT);
	pinMode(23,OUTPUT);
	//columnas
	pinMode(22,OUTPUT);
	pinMode(18,OUTPUT);
	pinMode(17,OUTPUT);
	pinMode(14,OUTPUT);
	//botones
	pinMode (GPIO_BUTTONDER, INPUT);
	pinMode (GPIO_BUTTONIZQ, INPUT);
	wiringPiISR (GPIO_BUTTONDER, INT_EDGE_FALLING, boton_izquierda);
	wiringPiISR (GPIO_BUTTONIZQ, INT_EDGE_FALLING, boton_derecha);

	pinMode (GPIO_BUTTONDER_2, INPUT);
	pinMode (GPIO_BUTTONIZQ_2, INPUT);
	wiringPiISR (GPIO_BUTTONDER_2, INT_EDGE_FALLING, boton_izquierda_2);
	wiringPiISR (GPIO_BUTTONIZQ_2, INT_EDGE_FALLING, boton_derecha_2);

	return 1;

}

/*static void flagPelota (union sigval value)
 * aqui se activa el flag del snake cada segundo
 */
static void flagPelota (union sigval value){
	piLock (FLAGS_KEY);
	flags |=FLAG_PELOTA;
	piUnlock (FLAGS_KEY);
	tmr_startms (tmrp, 1000);
}


void boton_izquierda(void){
	if (millis () < debounceTime) {
	debounceTime = millis () + DEBOUNCE_TIME ;
	return;
	}
	piLock (FLAGS_KEY);
	flags |=FLAG_RAQUETA_IZQUIERDA;
	flags |= FLAG_TECLA;
	piUnlock (FLAGS_KEY);
	while (digitalRead (GPIO_BUTTONIZQ) == HIGH) {
	delay (1) ;
	}
	debounceTime = millis () + DEBOUNCE_TIME ;

}
void boton_derecha(void){
	if (millis () < debounceTime) {
	debounceTime = millis () + DEBOUNCE_TIME ;
	return;
	}
	piLock (FLAGS_KEY);
	flags |=FLAG_RAQUETA_DERECHA;
	flags |= FLAG_TECLA;
	piUnlock (FLAGS_KEY);
	while (digitalRead (GPIO_BUTTONDER) == HIGH) {
	delay (1) ;
	}
	debounceTime = millis () + DEBOUNCE_TIME ;

}
void boton_izquierda_2(void){
	if (millis () < debounceTime) {
	debounceTime = millis () + DEBOUNCE_TIME ;
	return;
	}
	piLock (FLAGS_KEY);
	flags |=FLAG_RAQUETA_IZQUIERDA_2;
	flags |= FLAG_TECLA;
	piUnlock (FLAGS_KEY);
	while (digitalRead (GPIO_BUTTONIZQ_2) == HIGH) {
	delay (1) ;
	}
	debounceTime = millis () + DEBOUNCE_TIME ;

}
void boton_derecha_2(void){
	if (millis () < debounceTime) {
	debounceTime = millis () + DEBOUNCE_TIME ;
	return;
	}
	piLock (FLAGS_KEY);
	flags |=FLAG_RAQUETA_DERECHA_2;
	flags |= FLAG_TECLA;
	piUnlock (FLAGS_KEY);
	while (digitalRead (GPIO_BUTTONDER_2) == HIGH) {
	delay (1) ;
	}
	debounceTime = millis () + DEBOUNCE_TIME ;

}



static void  refrescar(union sigval value){


	int i;
	int c= 9 - (columna%10);

	for(i=0;i<7;i++){


		if(juego.pong.pantalla.matriz[c][i] == 1){
			digitalWrite(col[i], LOW);
		}else{
			digitalWrite(col[i], HIGH);
		}

	}
	//col
	digitalWrite(14,c & 0x01);
	digitalWrite(17,c & 0x02);
	digitalWrite(18,c & 0x04);
	digitalWrite(22,c & 0x08);
	tmr_startms (tmrt, 1);
	columna++;
}

int main () {
	unsigned int next;

	fsm_trans_t tabla_juego[] = {
			{ WAIT_START,   CompruebaTeclaPulsada,  WAIT_PUSH, InicializaJuego},
			{ WAIT_PUSH,   CompruebaTeclaRaquetaIzquierda,  WAIT_PUSH, MueveRaquetaIzquierda},
			{ WAIT_PUSH,   CompruebaTeclaRaquetaIzquierda_2,  WAIT_PUSH, MueveRaquetaIzquierda_2},
			{ WAIT_PUSH,   CompruebaTeclaPelota,  WAIT_PUSH, MovimientoPelota},
			{ WAIT_PUSH,   CompruebaTeclaRaquetaDerecha,  WAIT_PUSH, MueveRaquetaDerecha },
			{ WAIT_PUSH,   CompruebaTeclaRaquetaDerecha_2,  WAIT_PUSH, MueveRaquetaDerecha_2},
			{ WAIT_PUSH,   CompruebaFinalJuego,  WAIT_END, FinalJuego},
			{ WAIT_END,   CompruebaTeclaPulsada,  WAIT_START, ReseteaJuego},
			{ -1, NULL, -1, NULL },
	};


	fsm_t* juego_fsm = fsm_new (WAIT_START, tabla_juego, NULL);
	// Configuracion e inicializacion del sistema

	systemSetup();
	ReseteaJuego(juego_fsm);
	/*fsm_setup (juego_fsm);*/

	next = millis();
	while (1) {
		fsm_fire (juego_fsm);
		next += CLK_MS;
		delay_until (next);
	}

	fsm_destroy (juego_fsm);


}
