#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define BBLU "\e[1;34m"
#define BCYN "\e[1;36m"

#define COLOR_RESET "\e[0m"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct map
{
    char *key;
    char *value;
} Map;

char *obtener_color(int longitud, Map map[longitud], char *key)
{
    int i;
    for (i = 0; i < longitud; i++)
    {
        if (strcmp(map[i].key, key) == 0)
        {
            return map[i].value;
        }
    }
    return NULL;
}

void proceso()
{
    Map colores[] = {
        {"ROJO", BRED},
        {"VERDE", BGRN},
        {"AZUL", BBLU},
        {"AMARILLO", BYEL},
        {"CIAN", BCYN}};

    char palabras[5][100];
    char colores_ingresados[5][9];
    int i;
    for (i = 0; i < 5; i++)
    {
        char *cod_color = NULL;
        do
        {
            printf("Ingrese un color: ");
            scanf("%s", colores_ingresados[i]);
            cod_color = obtener_color(5, colores, colores_ingresados[i]);
            if (cod_color == NULL)
            {
                printf("Color no valido.\n");
            }
        } while (cod_color == NULL);

        printf("Ingrese una palabra: ");
        scanf("%s", palabras[i]);
    }

    for (i = 0; i < 5; i++)
    {
        printf("%s %s", obtener_color(5, colores, colores_ingresados[i]), palabras[i]);
    }

    printf("%s\n", COLOR_RESET);
}

int main()
{
    proceso();
    return 0;
}
