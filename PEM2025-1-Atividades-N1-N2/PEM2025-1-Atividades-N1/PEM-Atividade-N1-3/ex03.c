/*-------------------------------------------------------*
 *                      FATEC Ipiranga                    *
 * Disciplina: Programaçao Estruturada e Modular          *
 *          Prof. Veríssimo                               *
 *--------------------------------------------------------*
 * Objetivo do Programa: Funções com Ponteiro             *
 * Data - 07/03/2025                                      *
 * Autor: Lucas Barboza                                   *
 *--------------------------------------------------------*/

#include <stdio.h>

/*
    O especificador de formato correto para
    imprimir ponteiros é o %p..
*/

// Diretivas de pre-processamento
#define TAM_ARR_FIXO 5

// Prototipo de funções
void imprimir_end_arr(int *arr);
void busc_maior_elemento_arr(int *arr);
void modificar_arr(int *arr);
void mostrar_pos_memoria(int *arr);
int somar_elementos_arr(int *arr);

int main()
{
    int arr[] = {5, 10, 3, 8, 15};

    // Endereço contido em array
    imprimir_end_arr(arr);

    // Mostrar maior elemento
    busc_maior_elemento_arr(arr);

    // Soma dos elementos (somar e mostrar)
    int somatoria = somar_elementos_arr(arr);
    printf("[>] somatoria dos elementos eh=%d\n", somatoria);

    // Modificar o array
    modificar_arr(arr);

    // Mostrar posições de memória
    mostrar_pos_memoria(arr);

    return 0;
}

// 1. Endereço do array
void imprimir_end_arr(int *arr)
{
    printf("[>] endereco do primeiro elemento do array=%p\n", (void *)arr);
}

// 2. Maior elemento do array
void busc_maior_elemento_arr(int *arr)
{
    int *ptr = arr;
    int maior = *ptr;
    for (int i = 1; i < TAM_ARR_FIXO; i++)
    {
        ptr++;
        if (*ptr > maior)
        {
            maior = *ptr;
        }
    }
    printf("[>] maior elemento do arr=%d\n", maior);
}

// 3. Somar elementos do array
int somar_elementos_arr(int *arr)
{
    int soma = 0;
    for (int i = 0; i < TAM_ARR_FIXO; i++)
    {
        soma += *(arr + i);
    }
    return soma;
}

// 4. Modificar o array
void modificar_arr(int *arr)
{
    int novo_arr[TAM_ARR_FIXO] = {10, 20, 6, 16, 30};
    for (int i = 0; i < TAM_ARR_FIXO; i++)
    {
        *(arr + i) = *(novo_arr + i);
    }
}

// 5. Mostrar a posição da memória para um determinado ciclo de processamento
void mostrar_pos_memoria(int *arr)
{
    printf("[>] Posicoes de memoria do array:\n");
    for (int i = 0; i < TAM_ARR_FIXO; i++)
    {
        printf("arr[%d] = %d - end: [%p]\n", i, arr[i], (void *)(arr + i));
    }
}
