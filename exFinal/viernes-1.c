#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_CLIENTES 2500
#define MAX_NOMBRES 10
#define MAX_APELLIDOS 10

const char *primer_nombres[MAX_NOMBRES] = {"Juan", "Pedro", "Carlos", "Luis", "Miguel", "Jose", "Ana", "Maria", "Carmen", "Luisa"};
const char *segundo_nombres[MAX_NOMBRES] = {"Jose", "Luis", "Antonio", "Miguel", "Fernando", "Pablo", "Rosa", "Elena", "Teresa", "Patricia"};
const char *primer_apellidos[MAX_APELLIDOS] = {"Gomez", "Perez", "Lopez", "Martinez", "Sanchez", "Garcia", "Rodriguez", "Fernandez", "Gonzalez", "Hernandez"};
const char *segundo_apellidos[MAX_APELLIDOS] = {"Diaz", "Morales", "Cruz", "Ramos", "Gutierrez", "Jimenez", "Mendoza", "Vargas", "Torres", "Ruiz"};
const char *generos[2] = {"M", "F"};

typedef struct {
    int id_cliente;
    char primer_nombre[50];
    char segundo_nombre[50];
    char primer_apellido[50];
    char segundo_apellido[50];
    char genero[2];
    int ci;
    int saldo_guaranies;
    int deuda_guaranies;
    double saldo_dolares;
    double deuda_dolares;
} Cliente;

void generar_datos() {
    srand(time(NULL));
    FILE *entrada = fopen("entrada.txt", "w");
    if (entrada == NULL) {
        printf("Error al abrir el archivo.\n");
        exit(1);
    }

    for (int i = 0; i < NUM_CLIENTES; i++) {
        int id_cliente = i + 1;
        const char *primer_nombre = primer_nombres[rand() % MAX_NOMBRES];
        const char *segundo_nombre = segundo_nombres[rand() % MAX_NOMBRES];
        const char *primer_apellido = primer_apellidos[rand() % MAX_APELLIDOS];
        const char *segundo_apellido = segundo_apellidos[rand() % MAX_APELLIDOS];
        const char *genero = generos[rand() % 2];
        int ci = 1000000 + rand() % 9000000;
        int saldo_guaranies = rand() % 1000000001;
        int deuda_guaranies = rand() % 1000000001;

        fprintf(entrada, "%d %s %s %s %s %s %d %d %d\n", id_cliente, primer_nombre, segundo_nombre, primer_apellido, segundo_apellido, genero, ci, saldo_guaranies, deuda_guaranies);
    }

    fclose(entrada);
    printf("Archivo 'entrada.txt' generado con éxito.\n");
}

int solicitar_cotizacion() {
    int cotizacion_dolar;
    printf("Ingrese la cotización del dólar: ");
    scanf("%d", &cotizacion_dolar);
    return cotizacion_dolar;
}

void leer_datos(Cliente clientes[], int cotizacion_dolar) {
    FILE *entrada = fopen("entrada.txt", "r");
    if (entrada == NULL) {
        printf("Error al abrir el archivo 'entrada.txt'.\n");
        exit(1);
    }

    for (int i = 0; i < NUM_CLIENTES; i++) {
        fscanf(entrada, "%d %s %s %s %s %s %d %d %d",
               &clientes[i].id_cliente,
               clientes[i].primer_nombre,
               clientes[i].segundo_nombre,
               clientes[i].primer_apellido,
               clientes[i].segundo_apellido,
               clientes[i].genero,
               &clientes[i].ci,
               &clientes[i].saldo_guaranies,
               &clientes[i].deuda_guaranies);
        clientes[i].saldo_dolares = (double) clientes[i].saldo_guaranies / cotizacion_dolar;
        clientes[i].deuda_dolares = (double) clientes[i].deuda_guaranies / cotizacion_dolar;
    }

    fclose(entrada);
}

void generar_reproceso(Cliente clientes[]) {
    FILE *reproceso = fopen("reproceso.txt", "w");
    if (reproceso == NULL) {
        printf("Error al abrir el archivo 'reproceso.txt'.\n");
        exit(1);
    }

    for (int i = 0; i < NUM_CLIENTES; i++) {
        fprintf(reproceso, "%d %s %s %s %s %s %d %.2f %.2f %.2f %.2f\n",
                clientes[i].id_cliente,
                clientes[i].primer_nombre,
                clientes[i].segundo_nombre,
                clientes[i].primer_apellido,
                clientes[i].segundo_apellido,
                clientes[i].genero,
                clientes[i].ci,
                clientes[i].saldo_guaranies,
                clientes[i].saldo_dolares,
                clientes[i].deuda_guaranies,
                clientes[i].deuda_dolares);
    }

    fclose(reproceso);
    printf("Archivo 'reproceso.txt' generado con éxito.\n");
}

int comparar_saldo(const void *a, const void *b) {
    Cliente *clienteA = (Cliente *)a;
    Cliente *clienteB = (Cliente *)b;
    return clienteB->saldo_guaranies - clienteA->saldo_guaranies;
}

int comparar_deuda(const void *a, const void *b) {
    Cliente *clienteA = (Cliente *)a;
    Cliente *clienteB = (Cliente *)b;
    return clienteA->deuda_guaranies - clienteB->deuda_guaranies;
}

void generar_estadisticas(Cliente clientes[], int cotizacion_dolar) {
    FILE *estadistica = fopen("estadistica.txt", "w");
    if (estadistica == NULL) {
        printf("Error al abrir el archivo 'estadistica.txt'.\n");
        exit(1);
    }

    qsort(clientes, NUM_CLIENTES, sizeof(Cliente), comparar_saldo);
    fprintf(estadistica, "**Los treinta primeros clientes que tienen mayor saldo:**\n");
    fprintf(estadistica, "ID_Cliente | Saldo_Guaranies\n");
    fprintf(estadistica, "-----------|----------------\n");
    for (int i = 0; i < 30; i++) {
        fprintf(estadistica, "%d | %d\n", clientes[i].id_cliente, clientes[i].saldo_guaranies);
    }

    qsort(clientes, NUM_CLIENTES, sizeof(Cliente), comparar_deuda);
    fprintf(estadistica, "\n**Los quince clientes que menos deben a la empresa:**\n");
    fprintf(estadistica, "ID_Cliente | Deuda_Guaranies\n");
    fprintf(estadistica, "-----------|----------------\n");
    for (int i = 0; i < 15; i++) {
        fprintf(estadistica, "%d | %d\n", clientes[i].id_cliente, clientes[i].deuda_guaranies);
    }

    long long total_saldo_guaranies = 0;
    long long total_deuda_guaranies = 0;
    double total_saldo_dolares = 0;
    double total_deuda_dolares = 0;

    for (int i = 0; i < NUM_CLIENTES; i++) {
        total_saldo_guaranies += clientes[i].saldo_guaranies;
        total_deuda_guaranies += clientes[i].deuda_guaranies;
        total_saldo_dolares += clientes[i].saldo_dolares;
        total_deuda_dolares += clientes[i].deuda_dolares;
    }

    fprintf(estadistica, "\n**Total de dinero depositado en guaraníes y dólares:**\n");
    fprintf(estadistica, "Total_Guaranies: %lld\n", total_saldo_guaranies);
    fprintf(estadistica, "Total_Dolares: %.2f\n", total_saldo_dolares);

    fprintf(estadistica, "\n**Total de dinero que deben los clientes en guaraníes y dólares:**\n");
    fprintf(estadistica, "Total_Deuda_Guaranies: %lld\n", total_deuda_guaranies);
    fprintf(estadistica, "Total_Deuda_Dolares: %.2f\n", total_deuda_dolares);

    fclose(estadistica);
    printf("Archivo 'estadistica.txt' generado con éxito.\n");
}

int main() {
    Cliente clientes[NUM_CLIENTES];

    // Generar archivo de entrada con datos aleatorios
    generar_datos();

    // Solicitar la cotización del dólar al usuario
    int cotizacion_dolar = solicitar_cotizacion();

    // Leer los datos del archivo de entrada
    leer_datos(clientes, cotizacion_dolar);

    // Generar el archivo reproceso con los datos convertidos a dólares
    generar_reproceso(clientes);

    // Generar las estadísticas
    generar_estadisticas(clientes, cotizacion_dolar);

    return 0;
}