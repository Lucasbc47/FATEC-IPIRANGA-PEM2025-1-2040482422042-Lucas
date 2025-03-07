/*-------------------------------------------------------*
 * Disciplina: Programação Estruturada e Modular         *
 *          Prof. Veríssimo                              *
 *--------------------------------------------------------*
 * Objetivo do Programa: Gestão de Estoque               *
 * Data: 04/03/2025                                      *
 * Autor: Lucas Barboza                                  *
 *--------------------------------------------------------*/

//  ̶U̶m̶ ̶e̶x̶e̶r̶c̶í̶c̶i̶o̶ ̶n̶ã̶o̶ ̶c̶o̶m̶p̶l̶e̶x̶o̶,̶ ̶p̶o̶r̶é̶m̶ ̶t̶r̶a̶b̶a̶l̶h̶o̶s̶o̶.̶.̶.̶ 
//  Eu compliquei as coisas, NÃO TENHO IDEIA DO PORQUê 😂

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Struct que representa um Produto
typedef struct Produto
{
    char codigo[5]; // Código do produto (ex: "S123")
    int quantidade; // Quantidade do produto
} Produto;

// Protótipo
void mostrar_ruas(Produto armazem[3][1][10]);
void adicionar_estoque(Produto armazem[3][1][10], int posicao[], char codigo[], int quantidade);
void retirar_estoque(Produto armazem[3][1][10], int posicao[], int quantidade);
int *analisar_posicao(char gondola[]);
int validar_codigo(char codigo[]);

int main()
{
    // Matriz Multidimensional 3D (3 ruas x 1 camada x 10 gondolas)
    Produto armazem[3][1][10];
    // Inicializa o armazém com todas as gôndolas vazias
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            for (int k = 0; k < 10; k++)
            {
                strcpy(armazem[i][j][k].codigo, ""); // Código vazio
                armazem[i][j][k].quantidade = 0;     // Quantidade zero
            }
        }
    }

    char gon[3];
    char codigo[5];

    int quantidade;
    int pos;

    char cont = 'S';

    // Loop principal do programa
    while (toupper(cont) == 'S')
    {
        system("cls");
        char escolha;
        puts("Insira a operacao com seu respectivo numero:");
        puts("- [1] ADICIONAR PRODUTO --");
        puts("- [2] RETIRAR PRODUTO --");
        puts("- [3] VER ARMAZEM --");
        puts("- [4] SAIR DO PROGRAMA --");
        puts(">>: ");
        scanf(" %c", &escolha);

        // Lógica para cada opção do menu
        if (escolha == '1')
        {
            // - [1] ADICIONAR PRODUTO --
            system("cls");
            char option;

            // Dados de entrada para a estocagem
            printf("Insira a rua [A-C]: ");
            scanf(" %c", &option);
            printf("Insira a pos (0-9): ");
            scanf("%d", &pos);

            if (pos < 0 || pos > 9)
            {
                printf("pos inválida! Deve ser entre 0 e 9.\n");
                printf("\nPressione ENTER para continuar...");
                getchar(); // Espera o usuário pressionar ENTER
                getchar();
                continue;
            }

            gon[0] = toupper(option);
            gon[1] = pos + '0';
            gon[2] = '\0';

            int *posicao = analisar_posicao(gon);
            if (posicao == NULL)
            {
                printf("[ERRO]: Entrada invalida!\n");
                printf("\nPressione ENTER para continuar...");
                getchar(); // Espera o usuário pressionar ENTER
                getchar();
                continue;
            }

            printf("Insira o codigo do produto (ex: S123): ");
            scanf("%4s", codigo); // evitando buffer overflow
            if (!validar_codigo(codigo))
            {
                printf("[ERRO] Codigo invalido! Formato: LNNN (ex: S123)\n");
                printf("\nPressione ENTER para continuar...");
                getchar(); // Espera o usuário pressionar ENTER
                getchar();
                continue;
            }
            printf("Insira a quantidade: ");
            scanf("%d", &quantidade);

            adicionar_estoque(armazem, posicao, codigo, quantidade);
            printf("\nPressione ENTER para continuar...");
            getchar(); // Espera o usuário pressionar ENTER
            getchar();
            free(posicao);
            system("cls");
        }

        else if (escolha == '2')
        {
            // - [2] RETIRAR PRODUTO --
            system("cls");
            char option;
            // Dados de entrada para a estocagem
            printf("Insira a rua [A-C]: ");
            scanf(" %c", &option);
            printf("Insira a pos (0-9): ");
            scanf("%d", &pos);

            if (pos < 0 || pos > 9)
            {
                printf("[ERRO]: pos invalida! Deve ser entre 0 e 9.\n");
                printf("\nPressione ENTER para continuar...");
                getchar(); // Espera o usuário pressionar ENTER
                getchar();
                continue;
            }

            gon[0] = toupper(option);
            gon[1] = pos + '0';
            gon[2] = '\0';

            int *posicao = analisar_posicao(gon);
            if (posicao == NULL)
            {
                printf("[ERRO]: Entrada invalida!\n");
                printf("\nPressione ENTER para continuar...");
                getchar(); // Espera o usuário pressionar ENTER
                getchar();
                continue;
            }

            printf("Insira a quantidade: ");
            scanf("%d", &quantidade);

            retirar_estoque(armazem, posicao, quantidade);
            free(posicao);
            printf("\nPressione ENTER para continuar...");
            getchar(); // Espera o usuário pressionar ENTER
            getchar();
            system("cls");
        }

        else if (escolha == '3')
        {
            // - [3] VER ARMAZEM --
            mostrar_ruas(armazem);
            printf("\nPressione ENTER para continuar...");
            getchar();
            getchar();
        }

        else if (escolha == '4')
        {
            // - [4] SAIR DO PROGRAMA --
            puts("Saindo...");
            break;
        }
        else
        {
            puts("Opcao invalida!\n");
            printf("\nPressione ENTER para continuar...");
            getchar(); // Espera o usuário pressionar ENTER
            getchar();
        }
    }

    return 0;
}

// Função que verifica se o código do produto segue o formato LNNN (1 letra + 3 números)
int validar_codigo(char codigo[])
{
    if (strlen(codigo) != 4)
        return 0; // O código deve ter 4 caracteres
    if (!isalpha(codigo[0]))
        return 0; // O primeiro caractere deve ser uma letra
    for (int i = 1; i < 4; i++)
    {
        if (!isdigit(codigo[i]))
            return 0; // Os próximos 3 caracteres devem ser números
    }
    return 1;
}

// Função para exibir o conteúdo do armazém
void mostrar_ruas(Produto armazem[3][1][10]) // 3x1x10
{
    for (int i = 0; i < 3; i++)
    {
        char rua = (i == 0 ? 'A' : (i == 1 ? 'B' : 'C'));
        printf("Rua %c: { ", rua);
        for (int j = 0; j < 1; j++)
        {
            for (int k = 0; k < 10; k++)
            {
                if (strcmp(armazem[i][j][k].codigo, "") == 0)
                    printf("___ ");
                else
                    printf("%s [%d] ", armazem[i][j][k].codigo, armazem[i][j][k].quantidade);
            }
        }
        printf("}\n");
    }
}

// Função para adicionar um produto ao estoque
// Pode incrementar ou adicionar um novo produto
void adicionar_estoque(Produto armazem[3][1][10], int posicao[], char codigo[], int quantidade)
{
    int rua = posicao[0];
    int pos = posicao[1];

    // Verifica se o código já existe em outra gôndola
    for (int i = 0; i < 3; i++)
    {
        for (int k = 0; k < 10; k++)
        {
            if (strcmp(armazem[i][0][k].codigo, codigo) == 0 && (i != rua || k != pos))
            {
                printf("[ERRO] Produto %s ja existe na gondola %c%d!\n", codigo, (i == 0 ? 'A' : (i == 1 ? 'B' : 'C')), k);
                return;
            }
        }
    }

    // Se a posição já contém um produto, atualiza se for o mesmo; caso contrário, mostra erro
    if (strcmp(armazem[rua][0][pos].codigo, "") != 0)
    {
        if (strcmp(armazem[rua][0][pos].codigo, codigo) == 0) // se nao tem nada, basta incrementar..
        {
            armazem[rua][0][pos].quantidade += quantidade;
            printf("Estoque do produto %s atualizado para %d unidades.\n",
                   codigo, armazem[rua][0][pos].quantidade);
        }
        else
        {
            printf("[ERRO]: Gondola %c%d já está ocupada pelo produto %s.\n",
                   (rua == 0 ? 'A' : (rua == 1 ? 'B' : 'C')), pos, armazem[rua][0][pos].codigo);
        }
    }
    else
    {
        // Se estiver vazia, insere o novo produto
        strcpy(armazem[rua][0][pos].codigo, codigo);
        armazem[rua][0][pos].quantidade = quantidade;
        printf("Produto %s estocado na gondola %c%d com %d unidades.\n",
               codigo, (rua == 0 ? 'A' : (rua == 1 ? 'B' : 'C')), pos, quantidade);
    }
}

// Função de retirada de estoque
// Retira uma quantidade do estoque e, se necessário, esvazia a gôndola
void retirar_estoque(Produto armazem[3][1][10], int posicao[], int quantidade)
{
    int rua = posicao[0];
    int pos = posicao[1];

    // Verifica se a gôndola está vazia
    if (strcmp(armazem[rua][0][pos].codigo, "") == 0)
    {
        printf("[ERRO] Gondola vazia!\n");
        return;
    }
    // Verifica se a quantidade solicitada é válida
    if (armazem[rua][0][pos].quantidade >= quantidade)
    {
        armazem[rua][0][pos].quantidade -= quantidade; // remove
        printf("Retirada realizada. Nova quantidade: %d\n", armazem[rua][0][pos].quantidade);

        // Se a quantidade chegar a zero, esvazia a gondola / acabou
        if (armazem[rua][0][pos].quantidade == 0)
        {
            strcpy(armazem[rua][0][pos].codigo, ""); // removendo o codigo, ou seja copiamos um literal vazio.
            printf("Gondola %c%d esvaziada.\n", (rua == 0 ? 'A' : (rua == 1 ? 'B' : 'C')), pos);
        }
    }
    else
    {
        // Não tem como retirar 30 pacotes de café de um estoque que só tem 15! 🤣
        printf("[ERRO] Quantidade insuficiente em estoque!\n");
    }
}

// Função para analisar a pos informada (ex: "A5") e retornar os índices correspondentes
// Converte uma string de posição (ex: "A5") em índices da matriz [rua, pos]
int *analisar_posicao(char gondola[])
{
    int index;
    switch (gondola[0])
    {
    case 'A':
        index = 0;
        break; // Rua A = índice 0
    case 'B':
        index = 1;
        break; // Rua B = índice 1
    case 'C':
        index = 2;
        break; // Rua C = índice 2
    default:
        return NULL; // Entrada inválida
    }

    int *result = malloc(2 * sizeof(int));
    if (!result)
        return NULL;

    result[0] = index;            // Índice da rua
    result[1] = gondola[1] - '0'; // Índice da posição
    return result;
}