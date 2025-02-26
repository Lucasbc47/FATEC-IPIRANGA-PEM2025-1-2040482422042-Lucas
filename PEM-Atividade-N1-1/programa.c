// Autor: Lucas Barboza Costa
// PEM-Atividade N1-1:Variáveis Compostas Homogêneas

/*
    O uso de struct aqui poderia diminuir muitas linhas
    e facilitar entendimento do código.
    Porém como não foi abordado em aula (ainda), optei por não
    colocar..
*/


#include <stdio.h>
#include <string.h>  // strcpy, strcspn
#include <windows.h> // para mostrar cedilha e outros

#define CANDIDATOS 50 // max num: candidatos
#define NOME 20       // max char: nome

// Região de memória temporária para funções I/O
void limpar_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void ordenar_arr(float arr[], int n)
{
    // Selection Sort: onde n: tam do array
    int i, j, i_minimo;
    // Loop externo, primeiro numero
    for (int i = 0; i < n - 1; i++)
    {
        i_minimo = i;
        // Loop interno, numero adiante
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[i_minimo])
            {
                i_minimo = j;
            }
        }
        // encontramos o primeiro, partimos pro proximo
        float temp = arr[i];
        arr[i] = arr[i_minimo];
        arr[i_minimo] = temp;
    }
}

// Calculando a média aritmética de um subconjunto central de um array ordenado
// Remove os extremos, basicamente.
float media_notas_centrais(float arr[], int tamanho, int esq, int dir)
{
    float soma = 0;
    int notas_validas = tamanho - esq - dir;
    for (int i = esq; i < tamanho - dir; i++)
    {
        soma += arr[i];
    }
    return soma / notas_validas;
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    char candidatos[CANDIDATOS][NOME];
    float notas_finais[CANDIDATOS];

    int num_cand;

    printf("Insira quantos candidatos....\n");
    scanf("%d", &num_cand);
    getchar();

    if (num_cand < 1 || num_cand > 50)
    {
        printf("Minimo: 1 - Max: 50");
        return 1;
    }

    for (int i = 0; i < num_cand; i++)
    {
        // Leitura do nome dos candidatos
        printf("Insira o nome do candidato n%d: ", i + 1);
        fgets(candidatos[i], NOME, stdin);
        candidatos[i][strcspn(candidatos[i], "\r\n")] = '\0';

        // Ler notas PE
        float PE[4];
        printf("Insira as notas (4 - PE): ");
        scanf("%f %f %f %f", &PE[0], &PE[1], &PE[2], &PE[3]);
        limpar_buffer();

        ordenar_arr(PE, 4);
        float PE_FINAL = media_notas_centrais(PE, 4, 1, 1);

        // Ler notas AC
        float AC[5];
        printf("Insira as notas (5 - AC): ");
        scanf("%f %f %f %f %f", &AC[0], &AC[1], &AC[2], &AC[3], &AC[4]);
        limpar_buffer();

        ordenar_arr(AC, 5);
        float AC_FINAL = media_notas_centrais(AC, 5, 1, 1);

        // Ler notas PP
        float PP[10];
        printf("Insira as notas (10 - PP): ");
        for (int k = 0; k < 10; k++)
        {
            scanf("%f", &PP[k]);
        }
        limpar_buffer();

        ordenar_arr(PP, 10);
        float PP_FINAL = media_notas_centrais(PP, 10, 1, 1);

        // Ler notas EB
        float EB[3];
        printf("Insira as notas (3 - EB): ");
        scanf("%f %f %f", &EB[0], &EB[1], &EB[2]);
        limpar_buffer();

        ordenar_arr(EB, 3);
        float EB_FINAL = media_notas_centrais(EB, 3, 1, 1);

        // NF = (PE * 0,3) + (AC * 0,1) + (PP * 0,4) + (EB * 0,2);
        notas_finais[i] = (PE_FINAL * 0.3) + (AC_FINAL * 0.1) + (PP_FINAL * 0.4) + (EB_FINAL * 0.2);
    }

    // Ordenar os candidatos decrescente
    for (int i = 0; i < num_cand - 1; i++)
    {
        int maior_num = i;
        for (int j = i + 1; j < num_cand; j++)
        {
            if (notas_finais[j] > notas_finais[maior_num])
            {
                maior_num = j;
            }
        }
        if (maior_num != i)
        {
            // Trocar notas
            float temp_nota = notas_finais[i];
            notas_finais[i] = notas_finais[maior_num];
            notas_finais[maior_num] = temp_nota;

            // Trocar nomes
            char temp_nome[NOME];
            strcpy(temp_nome, candidatos[i]);
            strcpy(candidatos[i], candidatos[maior_num]);
            strcpy(candidatos[maior_num], temp_nome);
        }
    }

    // Exibir os top 15.
    int top = (num_cand < 15) ? num_cand : 15;
    printf("\n -- TOP 15 --\n");
    for (int i = 0; i < top; i++)
    {
        printf("%d. %s - nota final: %.2f\n", i + 1, candidatos[i], notas_finais[i]);
    }
    return 0;
}
