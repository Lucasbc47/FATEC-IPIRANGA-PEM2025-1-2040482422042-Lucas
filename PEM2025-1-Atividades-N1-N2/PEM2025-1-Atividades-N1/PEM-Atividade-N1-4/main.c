/*-------------------------------------------------------*
 * Disciplina: Programação Estruturada e Modular         *
 *          Prof. Veríssimo                              *
 *--------------------------------------------------------*
 * Objetivo do Programa: Recursividade                   *
 * Data: 26/03/2025                                      *
 * Autor: Lucas Barboza                                  *
 *--------------------------------------------------------*/

#include <stdio.h>
#include <Windows.h>

/*
 * Função recursiva para listar arquivos e pastas com hierarquia (subdiretórios)
 * Busca arquivos e diretórios;
 * Para cada diretório encontrado, chama a si mesma com nível + 1;
 * A medida que o nível aumenta, o recuo com tabulação também aumenta;
 */
void listar_arquivos_recursivo(const char *diretorio, int nivel, int *num_diretorios, int *num_arquivos)
{
    /*
     * Argumentos:
     * - diretorio: caminho do diretório a ser listado
     * - nivel: nível de profundidade na hierarquia (0 para o diretório inicial)
     * - num_diretorios: ponteiro para o contador de diretórios
     * - num_arquivos: ponteiro para o contador de arquivos

     * Retorno:
     * - void: nenhum
     */
    WIN32_FIND_DATA dados_arquivo;
    HANDLE handle_busca;

    /* WIN32_FIND_DATA é uma estrutura que contém informações sobre um arquivo ou diretório
     * HANDLE é um ponteiro indentificador para um objeto dinâmico da API do Windows
     * MAX_PATH é uma constante que define o tamanho máximo de um caminho de arquivo no Windows
     * no caso é 260 caracteres
     */
    char caminho_busca[MAX_PATH];
    char subdiretorio[MAX_PATH];

    /* snprintf é uma função que formata e armazena uma string em um buffer
     * O buffer é o primeiro argumento, o segundo argumento é o tamanho do buffer
     * O terceiro argumento é o formato da string, e os argumentos seguintes são os valores a serem formatados
     * Usamos ele para evitar buffer overflow
     */
    snprintf(caminho_busca, MAX_PATH, "%s\\*", diretorio);

    /* Buffer é uma área de memória usada para armazenar dados temporariamente durante transferências.
    * Buffer overflow é um erro de programação que ocorre quando
    * um programa tenta armazenar mais dados em um buffer do que ele foi projetado para armazenar.

    * FindFirstFile inicia uma busca por arquivos que correspondam ao padrão
    * O primeiro argumento é o caminho do arquivo,
    * o segundo é um ponteiro para a estrutura WIN32_FIND_DATA
    * para termos acesso aos atributos do arquivo
    */
    handle_busca = FindFirstFile(caminho_busca, &dados_arquivo);

    if (handle_busca != INVALID_HANDLE_VALUE)
    /* Primeiro caso base
     * INVALID_HANDLE_VALUE - objeto inválido; ou seja,
     * não foi possível abrir o diretório/arquivo
     * Se o handle_busca for diferente de INVALID_HANDLE_VALUE,
     * significa que o diretório/arquivo foi aberto com sucesso
     */
    {
        do
        {
            // Se for diretório atual ou pai será ignorada para que não fique repetindo o mesmo diretório
            // Não é possível comparar strings com == ou != pois são ponteiros, logo retornariam endereços
            // Pra isso, em C usamos o strcmp, função que compara duas strings
            if (strcmp(dados_arquivo.cFileName, ".") == 0 || strcmp(dados_arquivo.cFileName, "..") == 0)
            {
                // Ignora, e prossegue para o próximo arquivo/diretório
                continue;
            }

            // Imprime recuo proporcional ao nível de profundidade
            for (int i = 0; i < nivel; i++)
            {
                printf("\t"); // \t: caracter de TAB/tabulação
            }

            // Exibe o nome do arquivo ou diretório
            printf("|-- %s", dados_arquivo.cFileName);

            // Verifica se é um diretório, o FindFirstFile tem operações bitwise para verificar os atributos do arquivo
            // FILE_ATTRIBUTE_DIRECTORY - atributo de diretório
            // FILE_ATTRIBUTE_NORMAL - atributo normal
            if (dados_arquivo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                printf(" [PASTA]\n");
                (*num_diretorios)++; // Incrementa o número de diretórios via referência

                // Monta o caminho completo do subdiretório
                snprintf(subdiretorio, MAX_PATH, "%s\\%s", diretorio, dados_arquivo.cFileName);

                // A recursividade só existe quando encontramos um diretório
                // Chamamos a função novamente, passando o subdiretório e o nível + 1
                listar_arquivos_recursivo(subdiretorio, nivel + 1, num_diretorios, num_arquivos);
            }
            else
            {
                printf(" [ARQUIVO]\n");
                (*num_arquivos)++; // Incrementa o número de arquivoos via referência
            }
        } while (FindNextFile(handle_busca, &dados_arquivo));
        // Caso base da recursão, FindNextFile continua a busca por arquivos e diretórios
        // enquanto houver arquivos ou pastas a serem listados

        // Se não houver mais arquivos ou pastas, FindNextFile retorna 0 e a recursão termina
        // Devemos fechar o handle após o uso
        FindClose(handle_busca);

        // Garantindo que o número total de arquivos e diretórios seja exibido apenas uma vez
        // Se o nível for 0, significa que estamos na chamada inicial da função
        if (nivel == 0)
        {
            printf("\n[>>] Total de arquivos: %d\n", *num_arquivos);
            printf("[>>] Total de diretorios: %d\n", *num_diretorios);
        }
    }
    else
    {
        printf("Erro ao abrir o diretório: %s\n", diretorio);
    }
}

int main()
{
    // MAX_PATH é a constante que é 260 caracteres
    // O tamanho máximo do caminho do diretório aceito no Windows
    char diretorio_inicial[MAX_PATH];

    // Contadores para que o exercício fique mais interessante
    int num_diretorios = 0;
    int num_arquivos = 0;

    puts("[>>] Digite o caminho do diretorio:\n");
    scanf("%s", diretorio_inicial);
    listar_arquivos_recursivo(diretorio_inicial, 0, &num_diretorios, &num_arquivos);
    // nível começa em 0

    return 0;
}
