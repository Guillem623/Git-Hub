#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMERO_CARTAS 52
#define NUMERO_VALORES 13
#define MAX_CARTAS_MANO 10

char *valores[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
char *pintas[] = {"Corazones", "Diamantes", "Picas", "Tréboles"};

typedef struct {
    char *valor;
    char *pinta;
    int valorNumerico;
} Carta;

void barajar(Carta baraja[]);
void inicializarBaraja(Carta baraja[]);
void mostrarCarta(Carta carta);
int sumarMano(Carta mano[], int numCartas);
Carta repartirCarta(Carta baraja[], int *indiceBaraja);

int main() {
    Carta baraja[NUMERO_CARTAS];
    Carta manoJugador[MAX_CARTAS_MANO];
    int numCartasJugador = 0;
    int sumaJugador = 0;
    int indiceBaraja = 0;
    char opcion;

    inicializarBaraja(baraja);
    barajar(baraja);

    printf("Bienvenido al Blackjack!\n");

    // Repartir dos cartas iniciales
    manoJugador[numCartasJugador++] = repartirCarta(baraja, &indiceBaraja);
    manoJugador[numCartasJugador++] = repartirCarta(baraja, &indiceBaraja);
    sumaJugador = sumarMano(manoJugador, numCartasJugador);

    printf("Tus cartas:\n");
    for (int i = 0; i < numCartasJugador; i++) {
        mostrarCarta(manoJugador[i]);
    }
    printf("Suma total: %d\n", sumaJugador);

    while (sumaJugador < 21) {
        printf("¿Quieres otra carta? (s/n): ");
        scanf(" %c", &opcion);

        if (opcion == 's' || opcion == 'S') {
            manoJugador[numCartasJugador++] = repartirCarta(baraja, &indiceBaraja);
            sumaJugador = sumarMano(manoJugador, numCartasJugador);

            printf("Nueva carta:\n");
            mostrarCarta(manoJugador[numCartasJugador - 1]);
            printf("Suma total: %d\n", sumaJugador);
        } else {
            break;
        }
    }

    if (sumaJugador == 21) {
        printf("¡Blackjack! Has ganado.\n");
    } else if (sumaJugador > 21) {
        printf("Te has pasado. Fin del juego.\n");
    } else {
        printf("Te has plantado con %d. Fin del juego.\n", sumaJugador);
    }

    return 0;
}

void inicializarBaraja(Carta baraja[]) {
    for (int i = 0; i < NUMERO_CARTAS; i++) {
        baraja[i].valor = valores[i % NUMERO_VALORES];
        baraja[i].pinta = pintas[i / NUMERO_VALORES];
        baraja[i].valorNumerico = (i % NUMERO_VALORES) + 1;
        if (baraja[i].valorNumerico > 10) baraja[i].valorNumerico = 10;
        if (i % NUMERO_VALORES == NUMERO_VALORES - 1) baraja[i].valorNumerico = 11;
    }
}

void barajar(Carta baraja[]) {
    srand(time(NULL));
    for (int i = 0; i < NUMERO_CARTAS; i++) {
        int j = rand() % NUMERO_CARTAS;
        Carta temp = baraja[i];
        baraja[i] = baraja[j];
        baraja[j] = temp;
    }
}

void mostrarCarta(Carta carta) {
    printf("  %s de %s\n", carta.valor, carta.pinta);
}

Carta repartirCarta(Carta baraja[], int *indiceBaraja) {
    return baraja[(*indiceBaraja)++];
}

int sumarMano(Carta mano[], int numCartas) {
    int suma = 0, numAsos = 0;
    for (int i = 0; i < numCartas; i++) {
        suma += mano[i].valorNumerico;
        if (mano[i].valorNumerico == 11) {
            numAsos++;
        }
    }

    while (suma > 21 && numAsos > 0) {
        suma -= 10;
        numAsos--;
    }

    return suma;
}
