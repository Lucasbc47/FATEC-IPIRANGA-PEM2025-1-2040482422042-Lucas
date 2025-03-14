/*-------------------------------------------------------*
* Disciplina: Programaçao Estruturada e Modular          *
*          Prof. Veríssimo                               *
*--------------------------------------------------------*
* Objetivo do Programa: Calcular notas e exibir media    *
* Data - 21/02/2025                                      * 
* Autor: Lucas Barboza                                   *
*--------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <windows.h> // Apenas para sistemas Windows (configuração de codificação)

#define CANDIDATOS 50  // Número máximo de candidatos
#define NOME 20        // Tamanho máximo para o nome

// Função para limpar o buffer do teclado
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para ordenar um vetor de floats em ordem crescente (Selection Sort)
void ordenar_arr(float arr[], int n) {
    int i, j, indice_min;
    for (i = 0; i < n - 1; i++) {
        indice_min = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[indice_min]) {
                indice_min = j;
            }
        }
        // Troca de valores
        float temp = arr[i];
        arr[i] = arr[indice_min];
        arr[indice_min] = temp;
    }
}

// Função para somar as notas centrais do vetor, descartando os extremos
// "esq" e "dir" indicam quantos elementos descartar do início e do fim (neste caso, 1 de cada lado)
float soma_notas_centrais(float arr[], int tamanho, int esq, int dir) {
    float soma = 0;
    for (int i = esq; i < tamanho - dir; i++) {
        soma += arr[i];
    }
    return soma;
}

int main() {
    // Configura a saída para UTF-8 (necessário apenas em Windows)
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    char candidatos[CANDIDATOS][NOME];
    // candidatos[0]["Maria"]
    float notas_finais[CANDIDATOS];
    // notas_finais[0] = [10, 10, 10, 10, 10, 10]

    int num_cand;

    printf("Insira quantos candidatos:\n");
    scanf("%d", &num_cand);
    limpar_buffer();

    if (num_cand < 1 || num_cand > CANDIDATOS) {
        printf("Número de candidatos inválido. Mínimo: 1 - Máximo: %d\n", CANDIDATOS);
        return 1;
    }

    for (int i = 0; i < num_cand; i++) {
        // Leitura do nome do candidato
        printf("Insira o nome do candidato n%d: ", i + 1);
        fgets(candidatos[i], NOME, stdin);
        candidatos[i][strcspn(candidatos[i], "\r\n")] = '\0';

        // Processamento das notas da Prova Escrita (PE) – 4 notas
        float PE[4];
        printf("Insira as notas (4 - PE): ");
        scanf("%f %f %f %f", &PE[0], &PE[1], &PE[2], &PE[3]);
        limpar_buffer();
        ordenar_arr(PE, 4);
        // Soma dos elementos centrais (descarte a menor e a maior)
        float PE_central = soma_notas_centrais(PE, 4, 1, 1);

        // Processamento das notas da Análise Curricular (AC) – 5 notas
        float AC[5];
        printf("Insira as notas (5 - AC): ");
        scanf("%f %f %f %f %f", &AC[0], &AC[1], &AC[2], &AC[3], &AC[4]);
        limpar_buffer();
        ordenar_arr(AC, 5);
        float AC_central = soma_notas_centrais(AC, 5, 1, 1);

        // Processamento das notas da Prova Prática (PP) – 10 notas
        float PP[10];
        printf("Insira as notas (10 - PP): ");
        for (int k = 0; k < 10; k++) {
            scanf("%f", &PP[k]);
        }
        limpar_buffer();
        ordenar_arr(PP, 10);
        float PP_central = soma_notas_centrais(PP, 10, 1, 1);

        // Processamento das notas da Entrevista em Banca (EB) – 3 notas
        float EB[3];
        printf("Insira as notas (3 - EB): ");
        scanf("%f %f %f", &EB[0], &EB[1], &EB[2]);
        limpar_buffer();
        ordenar_arr(EB, 3);
        float EB_central = soma_notas_centrais(EB, 3, 1, 1);

        // Cálculo da Nota Final (NF) usando os pesos propostos
        // NF = (PE_central * 0.3) + (AC_central * 0.1) + (PP_central * 0.4) + (EB_central * 0.2)
        notas_finais[i] = (PE_central * 0.3) + (AC_central * 0.1) + (PP_central * 0.4) + (EB_central * 0.2);
    }

    // Ordena os candidatos em ordem decrescente da nota final (usando Selection Sort)
    for (int i = 0; i < num_cand - 1; i++) {
        int indice_maior = i;
        for (int j = i + 1; j < num_cand; j++) {
            if (notas_finais[j] > notas_finais[indice_maior]) {
                indice_maior = j;
            }
        }
        if (indice_maior != i) {
            // Troca de notas finais
            float temp_nota = notas_finais[i];
            notas_finais[i] = notas_finais[indice_maior];
            notas_finais[indice_maior] = temp_nota;
            // Troca de nomes dos candidatos
            char temp_nome[NOME];
            strcpy(temp_nome, candidatos[i]);
            strcpy(candidatos[i], candidatos[indice_maior]);
            strcpy(candidatos[indice_maior], temp_nome);
        }
    }

    // Exibe os 15 melhores candidatos ou todos, se houver menos de 15
    int top = (num_cand < 15) ? num_cand : 15;
    printf("\n -- TOP 15 --\n");
    for (int i = 0; i < top; i++) {
        printf("%d. %s - Nota Final: %.2f\n", i + 1, candidatos[i], notas_finais[i]);
    }

    return 0;
}