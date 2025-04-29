#include <stdio.h>
#include <string.h>

#define NUM_EQUIPOS 4
#define NUM_PARTIDOS 6
#define MAX_NOMBRE 50

char nombres[NUM_EQUIPOS][MAX_NOMBRE];
int nombres_ingresados = 0;
int puntos[NUM_EQUIPOS] = {0};
int goles_favor[NUM_EQUIPOS] = {0};
int goles_contra[NUM_EQUIPOS] = {0};
int partidos[NUM_PARTIDOS][2] = {
    {0, 1}, {0, 2}, {0, 3},
    {1, 2}, {1, 3}, {2, 3}
};
int partido_jugado[NUM_PARTIDOS] = {0};

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int esDigito(char c) {
    return c >= '0' && c <= '9';
}

int esNumeroPositivo(const char *cadena) {
    for (int i = 0; cadena[i] != '\0'; i++) {
        if (!esDigito(cadena[i])) {
            return 0;
        }
    }
    return 1;
}

int leerGoles(const char* mensaje) {
    char entrada[20];
    int valor;
    while (1) {
        printf("%s", mensaje);
        if (fgets(entrada, sizeof(entrada), stdin)) {
            size_t len = strlen(entrada);
            if (entrada[len - 1] == '\n') {
                entrada[len - 1] = '\0';
            }
            if (esNumeroPositivo(entrada)) {
                sscanf(entrada, "%d", &valor);
                return valor;
            }
        }
        printf("Entrada invalida. Ingrese un numero entero positivo.\n");
    }
}

int leerOpcion(const char* mensaje) {
    char entrada[10];
    int valor;
    while (1) {
        printf("%s", mensaje);
        if (fgets(entrada, sizeof(entrada), stdin)) {
            if (entrada[strlen(entrada) - 1] == '\n') {
                entrada[strlen(entrada) - 1] = '\0';
            }
            if (esNumeroPositivo(entrada)) {
                sscanf(entrada, "%d", &valor);
                return valor;
            }
        }
        printf("Opcion invalida.\n");
    }
}

void ingresarNombres() {
    if (nombres_ingresados) {
        printf("\nLos equipos ya fueron ingresados. Esta opcion solo puede usarse una vez.\n");
        return;
    }

    printf("\nIngrese los nombres de los equipos:\n");
    for (int i = 0; i < NUM_EQUIPOS; i++) {
        while (1) {
            printf("Equipo %d: ", i + 1);
            if (fgets(nombres[i], MAX_NOMBRE, stdin)) {
                size_t len = strlen(nombres[i]);
                if (len > 0 && nombres[i][len - 1] == '\n') {
                    nombres[i][len - 1] = '\0';
                }
                if (strlen(nombres[i]) > 0) break;
            }
            printf("Nombre no valido. Intente nuevamente.\n");
        }
    }
    nombres_ingresados = 1;
    printf("Equipos registrados correctamente.\n");
}

void jugarPartido(int numero) {
    if (!nombres_ingresados) {
        printf("Primero debe ingresar los equipos (opcion 1).\n");
        return;
    }

    if (numero < 1 || numero > NUM_PARTIDOS) {
        printf("Numero de partido invalido.\n");
        return;
    }
    if (partido_jugado[numero - 1]) {
        printf("Este partido ya fue ingresado.\n");
        return;
    }

    int i = numero - 1;
    int eq1 = partidos[i][0];
    int eq2 = partidos[i][1];

    printf("\nPartido %d: %s vs %s\n", numero, nombres[eq1], nombres[eq2]);

    int gol1 = leerGoles("Goles de equipo 1: ");
    int gol2 = leerGoles("Goles de equipo 2: ");

    goles_favor[eq1] += gol1;
    goles_contra[eq1] += gol2;

    goles_favor[eq2] += gol2;
    goles_contra[eq2] += gol1;

    if (gol1 > gol2)
        puntos[eq1] += 3;
    else if (gol2 > gol1)
        puntos[eq2] += 3;
    else {
        puntos[eq1] += 1;
        puntos[eq2] += 1;
    }

    partido_jugado[numero - 1] = 1;
    printf("Resultado guardado correctamente.\n");
}

void mostrarTabla() {
    printf("\n--- Tabla de posiciones ---\n");
    printf("%-20s %6s %6s %6s %6s\n", "Equipo", "Puntos", "GF", "GC", "GD");
    for (int i = 0; i < NUM_EQUIPOS; i++) {
        int gd = goles_favor[i] - goles_contra[i];
        printf("%-20s %6d %6d %6d %6d\n", nombres[i], puntos[i], goles_favor[i], goles_contra[i], gd);
    }
}

void mostrarFinalistas() {
    if (!nombres_ingresados) {
        printf("Primero debe ingresar los equipos (opcion 1).\n");
        return;
    }

    mostrarTabla();

    int orden[NUM_EQUIPOS] = {0, 1, 2, 3};

    // Ordenar por puntos y luego por gol diferencia
    for (int i = 0; i < NUM_EQUIPOS - 1; i++) {
        for (int j = i + 1; j < NUM_EQUIPOS; j++) {
            int pi = puntos[orden[i]];
            int pj = puntos[orden[j]];
            int di = goles_favor[orden[i]] - goles_contra[orden[i]];
            int dj = goles_favor[orden[j]] - goles_contra[orden[j]];

            if (pj > pi || (pj == pi && dj > di)) {
                int temp = orden[i];
                orden[i] = orden[j];
                orden[j] = temp;
            }
        }
    }

    printf("\n--- Equipos clasificados a la final ---\n");
    for (int i = 0; i < 2; i++) {
        int idx = orden[i];
        int dif = goles_favor[idx] - goles_contra[idx];
        printf("%d. %s (Puntos: %d, GD: %d)\n", i + 1, nombres[idx], puntos[idx], dif);
    }
}

int main() {
    int opcion;
    do {
        printf("\n--- Menu ---\n");
        printf("1. Ingresar los equipos\n");
        printf("2. Partido 1\n");
        printf("3. Partido 2\n");
        printf("4. Partido 3\n");
        printf("5. Partido 4\n");
        printf("6. Partido 5\n");
        printf("7. Partido 6\n");
        printf("8. Los equipos clasificados a la final e imprimir los goles diferencia\n");
        printf("9. Salir\n");

        opcion = leerOpcion("Seleccione una opcion: ");

        switch (opcion) {
            case 1: ingresarNombres(); break;
            case 2: jugarPartido(1); break;
            case 3: jugarPartido(2); break;
            case 4: jugarPartido(3); break;
            case 5: jugarPartido(4); break;
            case 6: jugarPartido(5); break;
            case 7: jugarPartido(6); break;
            case 8: mostrarFinalistas(); break;
            case 9: printf("Saliendo del programa...\n"); break;
            default: printf("Opcion invalida.\n");
        }

    } while (opcion != 9);

    return 0;
}
