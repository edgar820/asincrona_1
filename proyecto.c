//Edgar Osvaldo Angel Mercado 
//Emmanuel Barajas Arroyo 


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define MAX_INTENTOS 8


int generarNumero();
int longitudNumero(int n);
int calcularSumaDigitos(int n);
void mostrarPistas(int secreto, int intento);



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

            case 1: 
            {
                int secreto;
                int intento;
                int intentos = 0;

                unsigned char energia = 255; 

                secreto = generarNumero();

                printf("\nSe ha generado un numero secreto entre 1 y 99999\n");
                printf("Energia: ");
                mostrarEnergia(energia);
                printf("\n");

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
                        printf("Intentos usados: %d\n", intentos);

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

                system("pause");

                break;
            }


            case 2: 
                mostrarReglas();
                system("pause");
                break;


            case 3: 
            {
                int total = ganadas + perdidas;

                printf("\n----REPORTE DE PARTIDAS---\n");

                printf("Ganadas: %d ", ganadas);
                int i;
                for(i = 0; i < ganadas; i++)
                    printf("*");

                printf("\nPerdidas: %d ", perdidas);
                for(i = 0; i < perdidas; i++)
                    printf("*");

                printf("\nTotales: %d ", total);
                for(i = 0; i < total; i++)
                    printf("*");

                printf("\n");

                system("pause");

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


//Función que genera un número aleatorio entre 1 y 99999
int generarNumero(){
    return (rand() % 99999) + 1;
}
//Función para obtener la longitud del número
//Entra por ejemplo 4567, primero se divide entre 10 y se va partiendo el número
//Hasta que este sea cero para detener el ciclo, va a ir aumentando con el contador de longitud
//Y este es el que va a decir qué longitud tiene
int longitudNumero(int n){  
    int longitud = 0;
    while(n > 0)
    {
        n /= 10;
        longitud++;
    }
    return longitud;
}
//Función que calcula la suma de los dígitos del número
int calcularSumaDigitos(int n){
    int suma = 0;
    while(n > 0)
    {
        suma += n % 10;
        n /= 10;
    }
    return suma;
}
/*
Pista: El último dígito es: 4
Pista: Tiene 5 cifras.
Pista: El número es par.
Pista: Divisible entre 7.
*/
void mostrarPistas(int secreto, int intento){
    int espar = 0;
    int ultimo_digito = secreto % 10;
    int longitud = longitudNumero(secreto);
    int suma = calcularSumaDigitos(secreto);
    if(secreto % 2 == 0){
        espar = 1;
    }else{
        espar = 0;
    }

    printf("Pista: El ultimo digito: %d\n", ultimo_digito);
    printf("Pista: Tiene %d cifras.\n", longitud);
    printf("Pista: El numero es %s.\n", (espar == 1) ? "par" : "impar");
    printf("Pista: La suma de sus digitos es %d\n", suma);

    //Pruebas de divisibilidad entre 3, 5, 7
    if(secreto % 3 == 0){
        printf("Pista: Divisible entre 3\n");
    }
    if(secreto % 5 == 0){
        printf("Pista: Divisible entre 5\n");
    }
    if(secreto % 7 == 0){
        printf("Pista: Divisible entre 7\n");
    }
    
    if(secreto > intento){
        printf("El numero secreto es MAYOR que tu intento\n");
    }else{
        printf("El numero secreto es MENOR que tu intento\n");
    }

}

//quita un 1 y pone un 0   11111111  -> 01111111
unsigned char consumirEnergia(unsigned char energia){

    energia = energia >>1;
    return energia;

}

// entero a binario   00001101  >> 7
                    //00000000 & 1 = 0  bit = 0
                    //00001101  >> 6
                    //00000000 & 1 = 0  bit = 0
                    //00001101  >> 5
                    //00000000 & 1 = 0  bit = 0
                    //00001101  >> 4
                    //00000000 & 1 = 0  bit = 0
                    //00001101  >> 3
                    //00000001 & 1 = 0  bit = 1
                    //00001101  >> 2
                    //00000011 & 1 = 0  bit = 1
                    //00001101  >> 1
                    //00000110 & 1 = 0  bit = 0
                    //00001101  >> 0 
                    //00001101 & 1 = 0  bit = 1
void mostrarEnergia(unsigned char energia){

    int i;

    for (i=7;i>=0;i--){
        int bit = (energia>>i) &1;
        printf("%d", bit);
    }


}

void mostrarReglas(){

    printf("_______________________________________________________\n");
    printf("1. OBJETIVO\n");
    printf("-------------------------------------------------------\n");
    printf("El programa genera un numero secreto entre 1 y 99999.\nTu objetivo es adivinarlo.\n");
    printf("_______________________________________________________\n");
    printf("2. INTENTOS\n");
    printf("-------------------------------------------------------\n");
    printf("Tienes como maximo 8 intentos.\n");
    printf("_______________________________________________________\n");
    printf("3. ¿COMO FUNCIONA LA ENERGIA?\n");
    printf("-------------------------------------------------------\n");
    printf("Cada intento incorrecto reduce 1.\n");
    printf("_______________________________________________________\n");
    printf("4. ¿QUE PASA CUANDO FALLAS?\n");
    printf("-------------------------------------------------------\n");
    printf("Se te dara una pista.\n");
    printf("_______________________________________________________\n");
    printf("5. ¿CUANDO SE GANA?\n");
    printf("-------------------------------------------------------\n");
    printf("Adivina antes de quedarte sin vidas.\n");
    printf("_______________________________________________________\n");
    
}

int validarEntrada(int x){


    if (x < 1 || x>99999){

        x = 0;
    }
    else{
        x = 1;
    }

    return x;

}