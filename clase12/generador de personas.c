#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct ficha
{
	char genero[2];
	char pnombre[50];
	char snombre[50];
	char papellido[50];
	char sapellido[50];
	char nombreyapellido[102];
	char apellidoynombre[102];
	int edad;
	int ci;
	char ciudad[25];
} Ficha;

void cargar_alumnos(Ficha alumnos[], int a);
void imprimir_lista(Ficha alumnos[], int x);
int generarNroCedula(Ficha alumnos[], int a);

int main()
{
	int n;
	srand(time(NULL));
	n = rand() % 39 + 10;
	Ficha alumnos[n];
	cargar_alumnos(alumnos, n);
	imprimir_lista(alumnos, n);

	return 0;
}

void imprimir_lista(Ficha alumnos[], int x)
{
	int i = 0;
	for (i = 0; i < x; i++)
	{
		printf("\n%s %s %s %s %s %s %d %d", alumnos[i].genero, alumnos[i].pnombre, alumnos[i].snombre, alumnos[i].papellido, alumnos[i].sapellido, alumnos[i].ciudad, alumnos[i].ci, alumnos[i].edad);
	}
}

void cargar_alumnos(Ficha alumnos[], int a)
{

	int i, s;
	for (i = 0; i < a; i++)
	{
		Ficha F;
		char nombre_hombre[][25] = {"ADRIAN", "ALBERTO", "ALEJANDRO", "ALVARO", "ANDRES", "ANGEL", "ANTONIO", "CARLOS", "DANIEL", "DAVID", "DIEGO", "EDUARDO", "ENRIQUE", "FERNANDO", "FRANCISCO", "IVAN", "JAVIER", "JESUS", "JOAQUIN", "JORGE", "JOSE", "JUAN", "LUIS", "MANUEL", "MIGUEL", "OSCAR", "PABLO", "PEDRO", "RAFAEL", "RAMON", "RAUL", "RUBEN", "SANTIAGO", "SERGIO", "VICENTE", "VICTOR"};
		char nombre_mujer[][25] = {"ANA", "ANDREA", "ANGELA", "ANTONIA", "BEATRIZ", "CARMEN", "CONCEPCION", "CRISTINA", "DOLORES", "ELENA", "ENCARNACION", "FRANCISCA", "IRENE", "ISABEL", "JOSEFA", "JUANA", "JULIA", "LAURA", "LUCIA", "MANUELA", "MARIA", "MARTA", "MERCEDES", "MONICA", "MONTSERRAT", "NURIA", "PATRICIA", "PAULA", "PILAR", "RAQUEL", "ROCIO", "ROSA", "ROSARIO", "SARA", "SILVIA", "TERESA"};
		char pos_apellidos[][25] = {"ALONSO", "ALVAREZ", "BLANCO", "CANO", "CASTILLO", "CASTRO", "CORTES", "DELGADO", "DIAZ", "DOMINGUEZ", "FERNANDEZ", "GARCIA", "GARRIDO", "GIL", "GOMEZ", "GONZALEZ", "GUERRERO", "GUTIERREZ", "HERNANDEZ", "IGLESIAS", "JIMENEZ", "LOPEZ", "LOZANO", "MARIN", "MARTIN", "MARTINEZ", "MEDINA", "MOLINA", "MORALES", "MORENO", "MUNOZ", "NAVARRO", "NUNEZ", "ORTEGA", "ORTIZ", "PEREZ", "RAMIREZ", "RAMOS", "RODRIGUEZ", "ROMERO", "RUBIO", "RUIZ", "SANCHEZ", "SANTOS", "SANZ", "SERRANO", "SUAREZ", "TORRES", "VAZQUEZ"};
		char ciudad[][25] = {"ASUNCION", "LAMBARE", "CAACUPE", "ITAUGUA", "MARIANO ROQUE ALONSO", "CAPIATA", "LUQUE", "SAN LORENZO"};
		char nombres[25];
		char apellidos[25];
		s = rand() % 2;
		if (s == 0)
		{
			strcpy(F.genero, "M");

			strcpy(F.pnombre, nombre_hombre[s]);
			do
			{
				s = rand() % 36;
				strcpy(F.snombre, nombre_hombre[s]);
			}

			while (strcmp(F.snombre, F.pnombre) == 0);
		}
		else
		{
			strcpy(F.genero, "F");
			s = rand() % 36;
			strcpy(F.pnombre, nombre_mujer[s]);
			do
			{
				s = rand() % 36;
				strcpy(F.snombre, nombre_mujer[s]);
			} while (strcmp(F.snombre, F.pnombre) == 0);
		}
		s = rand() % 49;
		strcpy(F.papellido, pos_apellidos[s]);
		s = rand() % 49;
		strcpy(F.sapellido, pos_apellidos[s]);
		sprintf(nombres, "%s %s", F.pnombre, F.snombre);
		sprintf(apellidos, "%s %s", F.papellido, F.sapellido);
		sprintf(F.nombreyapellido, "%s %s", nombres, apellidos);
		sprintf(F.apellidoynombre, "%s, %s", apellidos, nombres);
		s = rand() % 8;
		strcpy(F.ciudad, ciudad[s]);
		F.edad = rand() % 6 + 20;
		F.ci = generarNroCedula(alumnos, a);
		alumnos[i] = F;
	}
}

int generarNroCedula(Ficha alumnos[], int a)
{
	int ci = 0, i = 0, b = 1;

	ci = 2500000 + ((rand() % 1871) * (rand() % 1871) - 641);
	for (i = 0; i < a; i++)
	{
		if (alumnos[i].ci == ci)
		{
			ci = 2500000 + ((rand() % 1871) * (rand() % 1871) - 641);
			i = 0;
		}
	}
	return ci;
}
