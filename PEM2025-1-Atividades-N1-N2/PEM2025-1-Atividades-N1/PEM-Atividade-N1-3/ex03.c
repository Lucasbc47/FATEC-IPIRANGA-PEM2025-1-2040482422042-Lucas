/*-------------------------------------------------------*
 * Disciplina: Programação Estruturada e Modular         *
 *          Prof. Veríssimo                              *
 *--------------------------------------------------------*
 * Objetivo do Programa: Gestão de Estoque (Refatorado)   *
 * Data: 15/03/2025                                      *
 * Autor: Lucas Barboza                                  *
 *--------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Diretivas de pre-processamento
#define TOTAL_RUAS 3
#define TOTAL_CAMADAS 1
#define TOTAL_GONDOLAS 10
#define TAMANHO_CODIGO 5

// Struct que representa um Produto
typedef struct Produto
{
    char codigo[TAMANHO_CODIGO]; // Código do produto (ex: "S123")
    int quantidade;              // Quantidade do produto
} Produto;

// Protótipos das funções
void limpar_tela(void);
void mostrar_armazem(Produto (*armazem)[TOTAL_CAMADAS][TOTAL_GONDOLAS]);
void adicionar_estoque(Produto (*armazem)[TOTAL_CAMADAS][TOTAL_GONDOLAS], const int *posicao, const char *codigo, int quantidade);
void retirar_estoque(Produto (*armazem)[TOTAL_CAMADAS][TOTAL_GONDOLAS], const int *posicao, int quantidade);
int *analisar_posicao(const char *gondola);
int validar_codigo(const char *codigo);
void inicializar_armazem(Produto (*armazem)[TOTAL_CAMADAS][TOTAL_GONDOLAS]);
char obter_letra_rua(int indice);
void exibir_menu(void); // modularizar ao máximo
int processar_opcao_menu(char escolha, Produto (*armazem)[TOTAL_CAMADAS][TOTAL_GONDOLAS]);
void pausar_programa(void);

// Ponto de entrada do programa
int main()
{
    // Matriz Multidimensional 3D (3 ruas x 1 camada x 10 gondolas)
    Produto armazem[TOTAL_RUAS][TOTAL_CAMADAS][TOTAL_GONDOLAS];

    // Inicializa    o armazém com todas as gôndolas vazias
    inicializar_armazem(armazem);

    char continuar = 'S';

    // Loop principal do programa
    while (toupper(continuar) == 'S')
    {
        limpar_tela();
        exibir_menu();

        char escolha;
        printf(">>: ");
        scanf(" %c", &escolha);

        // Processa a opção selecionada
        if (processar_opcao_menu(escolha, armazem) == 0)
        {
            break; // Sair do programa
        }
    }

    return 0;
}

// Função para inicializar o armazém
void inicializar_armazem(Produto (*armazem)[TOTAL_CAMADAS][TOTAL_GONDOLAS])
{
    for (int i = 0; i < TOTAL_RUAS; i++)
    {
        for (int j = 0; j < TOTAL_CAMADAS; j++)
        {
            for (int k = 0; k < TOTAL_GONDOLAS; k++)
            {
                strcpy(armazem[i][j][k].codigo, ""); // Código vazio
                armazem[i][j][k].quantidade = 0;     // Quantidade zero
            }
        }
    }
}

// Função para exibir o menu principal
void exibir_menu(void)
{
    puts("Insira a operacao com seu respectivo numero:");
    puts("- [1] ADICIONAR PRODUTO --");
    puts("- [2] RETIRAR PRODUTO --");
    puts("- [3] VER ARMAZEM --");
    puts("- [4] SAIR DO PROGRAMA --");
}

// Função para processar a opção selecionada no menu
int processar_opcao_menu(char escolha, Produto (*armazem)[TOTAL_CAMADAS][TOTAL_GONDOLAS])
{
    switch (escolha)
    {
    case '1':
    {
        // ADICIONAR PRODUTO
        limpar_tela();

        char rua_letra;
        int posicao_gondola;
        char codigo[TAMANHO_CODIGO];
        int quantidade;
        char gon[3];

        printf("Insira a rua [A-C]: ");
        scanf(" %c", &rua_letra);
        printf("Insira a pos (0-9): ");
        scanf("%d", &posicao_gondola);

        if (posicao_gondola < 0 || posicao_gondola > 9)
        {
            printf("Posição inválida! Deve ser entre 0 e 9.\n");
            pausar_programa();
            return 1;
        }

        gon[0] = toupper(rua_letra);
        gon[1] = posicao_gondola + '0';
        gon[2] = '\0';

        int *posicao = analisar_posicao(gon);
        if (posicao == NULL)
        {
            printf("[ERRO]: Entrada invalida!\n");
            pausar_programa();
            return 1;
        }

        printf("Insira o codigo do produto (ex: S123): ");
        scanf("%4s", codigo); // evitando buffer overflow
        if (!validar_codigo(codigo))
        {
            printf("[ERRO] Codigo invalido! Formato: LNNN (ex: S123)\n");
            pausar_programa();
            free(posicao);
            return 1;
        }

        printf("Insira a quantidade: ");
        scanf("%d", &quantidade);

        adicionar_estoque(armazem, posicao, codigo, quantidade);
        free(posicao);
        pausar_programa();
        break;
    }
    case '2':
    {
        // RETIRAR PRODUTO
        limpar_tela();

        char rua_letra;
        int posicao_gondola;
        int quantidade;
        char gon[3];

        printf("Insira a rua [A-C]: ");
        scanf(" %c", &rua_letra);
        printf("Insira a pos (0-9): ");
        scanf("%d", &posicao_gondola);

        if (posicao_gondola < 0 || posicao_gondola > 9)
        {
            printf("[ERRO]: Posição invalida! Deve ser entre 0 e 9.\n");
            pausar_programa();
            return 1;
        }

        gon[0] = toupper(rua_letra);
        gon[1] = posicao_gondola + '0';
        gon[2] = '\0';

        int *posicao = analisar_posicao(gon);
        if (posicao == NULL)
        {
            printf("[ERRO]: Entrada invalida!\n");
            pausar_programa();
            return 1;
        }

        printf("Insira a quantidade: ");
        scanf("%d", &quantidade);

        retirar_estoque(armazem, posicao, quantidade);
        free(posicao);
        pausar_programa();
        break;
    }
    case '3':
    {
        // VER ARMAZEM
        mostrar_armazem(armazem);
        pausar_programa();
        break;
    }
    case '4':
    {
        // SAIR DO PROGRAMA
        puts("Saindo...");
        return 0;
    }
    default:
    {
        puts("Opcao invalida!\n");
        pausar_programa();
        break;
    }
    }
    return 1;
}

// Função para pausar o programa e aguardar o usuário
void pausar_programa(void)
{
    printf("\nPressione ENTER para continuar...");
    getchar(); // Consome possível '\n' no buffer
    getchar(); // Espera o usuário pressionar ENTER
}

// Função para chamar "clear" ou "cls"
void limpar_tela(void)
{
// O terminal lotado é péssimo de visualizar informação
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Função que verifica se o código do produto segue o formato LNNN (1 letra + 3 números)
int validar_codigo(const char *codigo)
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

// Função para converter índice numérico da rua para letra (A, B ou C)
char obter_letra_rua(int indice)
{
    return 'A' + indice;
}

// Função para exibir o conteúdo do armazém
void mostrar_armazem(Produto (*armazem)[TOTAL_CAMADAS][TOTAL_GONDOLAS])
{
    for (int i = 0; i < TOTAL_RUAS; i++)
    {
        char rua = obter_letra_rua(i);
        printf("Rua %c: { ", rua);

        for (int k = 0; k < TOTAL_GONDOLAS; k++)
        {
            if (strcmp(armazem[i][0][k].codigo, "") == 0)
                printf("___ ");
            else
                printf("%s [%d] ", armazem[i][0][k].codigo, armazem[i][0][k].quantidade);
        }

        printf("}\n");
    }
}

// Função para adicionar um produto ao estoque
// Pode incrementar ou adicionar um novo produto
void adicionar_estoque(Produto (*armazem)[TOTAL_CAMADAS][TOTAL_GONDOLAS], const int *posicao, const char *codigo, int quantidade)
{
    int rua = posicao[0];
    int pos = posicao[1];

    // Verifica se o código já existe em outra gôndola
    for (int i = 0; i < TOTAL_RUAS; i++)
    {
        for (int k = 0; k < TOTAL_GONDOLAS; k++)
        {
            if (strcmp(armazem[i][0][k].codigo, codigo) == 0 && (i != rua || k != pos))
            {
                printf("[ERRO] Produto %s ja existe na gondola %c%d!\n",
                       codigo, obter_letra_rua(i), k);
                return;
            }
        }
    }

    // Se a posição já contém um produto, atualiza se for o mesmo; caso contrário, mostra erro
    if (strcmp(armazem[rua][0][pos].codigo, "") != 0)
    {
        if (strcmp(armazem[rua][0][pos].codigo, codigo) == 0)
        {
            armazem[rua][0][pos].quantidade += quantidade;
            printf("Estoque do produto %s atualizado para %d unidades.\n",
                   codigo, armazem[rua][0][pos].quantidade);
        }
        else
        {
            printf("[ERRO]: Gondola %c%d já está ocupada pelo produto %s.\n",
                   obter_letra_rua(rua), pos, armazem[rua][0][pos].codigo);
        }
    }
    else
    {
        // Se estiver vazia, insere o novo produto
        strcpy(armazem[rua][0][pos].codigo, codigo);
        armazem[rua][0][pos].quantidade = quantidade;
        printf("Produto %s estocado na gondola %c%d com %d unidades.\n",
               codigo, obter_letra_rua(rua), pos, quantidade);
    }
}

// Função de retirada de estoque
// Retira uma quantidade do estoque e, se necessário, esvazia a gôndola
void retirar_estoque(Produto (*armazem)[TOTAL_CAMADAS][TOTAL_GONDOLAS], const int *posicao, int quantidade)
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

        // Se a quantidade chegar a zero, esvazia a gondola
        if (armazem[rua][0][pos].quantidade == 0)
        {
            strcpy(armazem[rua][0][pos].codigo, "");
            printf("Gondola %c%d esvaziada.\n", obter_letra_rua(rua), pos);
        }
    }
    else
    {
        printf("[ERRO] Quantidade insuficiente em estoque!\n");
    }
}

// Função para analisar a posição informada (ex: "A5") e retornar os índices correspondentes
int *analisar_posicao(const char *gondola)
{
    int indice_rua;

    switch (gondola[0])
    {
    case 'A':
        indice_rua = 0;
        break; // Rua A = índice 0
    case 'B':
        indice_rua = 1;
        break; // Rua B = índice 1
    case 'C':
        indice_rua = 2;
        break; // Rua C = índice 2
    default:
        return NULL; // Entrada inválida
    }

    int *result = malloc(2 * sizeof(int));
    if (!result)
        return NULL;

    result[0] = indice_rua;       // Índice da rua
    result[1] = gondola[1] - '0'; // Índice da posição
    return result;
}