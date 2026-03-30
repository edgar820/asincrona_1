//Edgar Osvaldo Angel Mercado 
//Emmanuel Barajas Arroyo 


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define MAX_INTENTOS 8

// funciones persona 1
int generarNumero();
int longitudNumero(int n);
int calcularSumaDigitos(int n);
void mostrarPistas(int secreto, int intento);

// funciones persona 2
unsigned char consumirEnergia(unsigned char energia);
void mostrarEnergia(unsigned char energia);
void mostrarReglas();
int validarEntrada(int x);


int main()
{
    int opcion;

    int ganadas = 0;
    int perdidas = 0;

    srand(time(NULL)); // inicializa números aleatorios

    do
    {
        printf("\n==== MENU ====\n");
        printf("1. Iniciar juego\n");
        printf("2. Mostrar reglas\n");
        printf("3. Ver grafico de ganados y perdidos\n");
        printf("4. Salir\n");
        printf("Selecciona una opcion: ");
        scanf("%d", &opcion);

        switch(opcion)
        {

            case 1: // INICIAR JUEGO
            {
                int secreto;
                int intento;
                int intentos = 0;

                unsigned char energia = 255; // 11111111

                secreto = generarNumero();

                printf("\nSe ha generado un numero secreto entre 1 y 99999\n");

                while(intentos < MAX_INTENTOS && energia > 0)
                {
                    printf("\nIntento #%d\n", intentos + 1);
                    printf("Ingresa un numero: ");
                    scanf("%d", &intento);

                    if(validarEntrada(intento) == 0)
                    {
                        printf("ERROR: Debes ingresar un numero entre 1 y 99999\n");
                        continue;
                    }

                    intentos++;

                    if(intento == secreto)
                    {
                        printf("\n¡Felicidades! Adivinaste el numero.\n");
                        printf("El numero secreto era: %d\n", secreto);

                        ganadas++;
                        break;
                    }

                    printf("\nNo es correcto...\n");

                    mostrarPistas(secreto, intento);

                    energia = consumirEnergia(energia);

                    printf("Energia: ");
                    mostrarEnergia(energia);
                }

                if(energia == 0 || intentos == MAX_INTENTOS)
                {
                    if(intento != secreto)
                    {
                        printf("\nTe has quedado sin energia.\n");
                        printf("El numero secreto era: %d\n", secreto);

                        perdidas++;
                    }
                }

                printf("\nPresiona una tecla para continuar...\n");
                getchar();
                getchar();

                break;
            }


            case 2: // REGLAS
                mostrarReglas();
                break;


            case 3: // GRAFICO
            {
                int total = ganadas + perdidas;

                printf("\n----REPORTE DE PARTIDAS---\n");

                printf("Ganadas: %d ", ganadas);
                for(int i = 0; i < ganadas; i++)
                    printf("*");

                printf("\nPerdidas: %d ", perdidas);
                for(int i = 0; i < perdidas; i++)
                    printf("*");

                printf("\nTotales: %d ", total);
                for(int i = 0; i < total; i++)
                    printf("*");

                printf("\n");

                printf("\nPresiona una tecla para continuar...\n");
                getchar();
                getchar();

                break;
            }


            case 4:
                printf("Saliendo del programa...\n");
                break;


            default:
                printf("Opcion invalida\n");
        }

    } while(opcion != 4);

    return 0;
}


