/*-------------------------------------------------------*
 *                      FATEC Ipiranga                    *
 * Disciplina: Programaçao Estruturada e Modular          *
 *          Prof. Veríssimo                               *
 *--------------------------------------------------------*
 * Objetivo do Programa: Funções com Ponteiro             *
 * Data - 07/03/2025                                      *
 * Autor: Lucas Barboza                                   *
 *--------------------------------------------------------*/

// arr = {5, 10, 3, 8, 15}

void imprimir_end_arr(int *arr);
void buscar_maior_elemento_arr(int *arr);
int somar_elementos_arr(int *arr);

#include <stdio.h>

#define TAM_ARR_FIXO 5

int main()
{

    int arr[] = {5, 10, 3, 8, 15};

    // Endereço contido em array
    imprimir_end_arr(arr);

    // Mostrar maior elemento
    mostrar_maior_elemento_arr(arr);
    
    // Soma dos elementos
    int somatoria = somar_elementos_arr(arr);
    printf("[>] somatoria dos elementos eh=%d", somatoria);


    return 0;
}


void imprimir_end_arr(int *arr){
    printf("[>] endereco do array=0x%d\n", &arr);
}

void buscar_maior_elemento_arr(int *arr){
    int *ptr = arr;
    int maior = *ptr;
    for (int i=1; i < TAM_ARR_FIXO; i++){
        ptr++;
        if (*ptr > maior){
            maior = *ptr;
        }
    }
    printf("[>]  maior elemento do arr=%d\n", maior);
}

int somar_elementos_arr(int *arr){
    int soma = 0;
    for (int i=0; i < TAM_ARR_FIXO; i++){
        soma += *(arr+i);
    }
    return soma;
}
