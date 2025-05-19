/*-------------------------------------------------------*
* Disciplina: Programaçao Estruturada e Modular          *
*          Prof. Veríssimo                               *
*--------------------------------------------------------*
* Objetivo do Programa: Algoritmos de Ordenação!         *
* Data - 19/05/2025                                      * 
* Autor: Lucas Barboza                                   *
*--------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h> // para uso de malloc e free

// diretivas de processamento condicional exclusivamente para limpar a tela
#ifdef _WIN32
#include <windows.h>
#define LIMPAR_TELA system("cls")
#else
#define LIMPAR_TELA system("clear")
#endif

// melhor caso: O(n)
// pior caso: O(n^2)
void bubble_sort(int *arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        // externo
        for (int j = 0; j < n - i - 1; j++)
        {
            // interno
            if (*(arr + j) > *(arr + j + 1))
            {
                // pointer swap
                int temp = *(arr + j);
                *(arr + j) = *(arr + j + 1);
                *(arr + j + 1) = temp;
            }
        }
    }
}

// melhor caso: O(n)
// pior caso: O(n^2)
void insertion_sort(int *arr, int n)
{
    int i, j, chave;
    for (i = 1; i < n; i++)
    {
        chave = *(arr + i);
        j = i - 1;

        while (j >= 0 && *(arr + j) > chave)
        {
            *(arr + j + 1) = *(arr + j);
            j = j - 1;
        }
        *(arr + j + 1) = chave;
    }
}

// funcao para reutilizacao
void imprimir_array(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", *(arr + i));
    }
    printf("\n");
}

int main()
{
    int n;
    int *numeros;
    int opcao;
    int continuar = 1;

    while (continuar)
    {
        LIMPAR_TELA;

        printf("-- ALGORITMOS DE ORDENACAO --\n\n");
        printf("Insira o tamanho do array: ");
        scanf("%d", &n);

        // malloc: aloca memória para n inteiros.
        // eh necessario liberar após sua utilização com o free()
        // como tambem a possibilidade de falha na alocação, retornando NULL
        numeros = (int *)malloc(n * sizeof(int));

        if (numeros == NULL)
        {
            printf("Erro: NULL");
            return 1;
        }

        printf("Digite os n %d numeros \n", n);
        for (int i = 0; i < n; i++)
        {
            printf("n-%d: ", i + 1);
            scanf("%d", numeros + i);
        }

        LIMPAR_TELA;
        puts("-- ALGORITMOS DE ORDENACAO --");
        puts("[1] Bubble Sort");
        puts("[2] Insertion Sort");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            printf("\nBubble Sort selecionado\n");
            printf("\nArray original: ");
            imprimir_array(numeros, n);
            bubble_sort(numeros, n);
            printf("\nArray ordenado: ");
            imprimir_array(numeros, n);
        }
        else if (opcao == 2)
        {
            printf("\nINSERTION SORT\n");
            printf("\nArray original: ");
            imprimir_array(numeros, n);
            insertion_sort(numeros, n);
            printf("\nArray ordenado: ");
            imprimir_array(numeros, n);
        }
        else
        {
            puts("\nOpcao invalida");
            free(numeros);
            printf("\nPressione ENTER para continuar...");
            getchar();
            getchar();
            continue;
        }

        // aqui liberamos a memoria alocada para evitar vazamento
        free(numeros);

        printf("\nContinuar? [1] Sim | [0] Nao: ........\n");
        scanf("%d", &continuar);
    }

    return 0;
}