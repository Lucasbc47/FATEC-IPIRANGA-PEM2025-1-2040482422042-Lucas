/*-------------------------------------------------------*
 * Disciplina: Programação Estruturada e Modular         *
 *          Prof. Veríssimo                              *
 *--------------------------------------------------------*
 * Objetivo do Programa: Recursividade                   *
 * Data: 26/03/2025                                      *
 * Autor: Lucas Barboza                                  *
 *--------------------------------------------------------*/

#include <stdio.h>
#include <windows.h>

// Função recursiva para listar arquivos e pastas com hierarquia (subdiretórios)
void listar_arquivos_recursivo(const char *diretorio, int nivel)
// A medida que o nível aumenta, mais recuos com \t são adicionados
{
    WIN32_FIND_DATA find_data;
    // WIN32_FIND_DATA é uma estrutura que contém informações sobre um arquivo ou diretório

    HANDLE h_find;
    // HANDLE é um ponteiro indentificador para um objeto dinâmico da API do Windows

    // MAX_PATH é uma constante que define o tamanho máximo de um caminho de arquivo no Windows
    // no caso é 260 caracteres
    char caminho_busca[MAX_PATH];
    char subdiretorio[MAX_PATH];

    // snprintf é uma função que formata e armazena uma string em um buffer
    // O buffer é o primeiro argumento, o segundo argumento é o tamanho do buffer
    // O terceiro argumento é o formato da string, e os argumentos seguintes são os valores a serem formatados
    // Usamos ele para evitar buffer overflow
    snprintf(caminho_busca, MAX_PATH, "%s\\*", diretorio);

    // Buffer é uma área de memória usada para armazenar dados temporariamente durante transferências.
    // Buffer overflow é um erro de programação que ocorre quando
    // um programa tenta armazenar mais dados em um buffer do que ele foi projetado para armazenar.
    h_find = FindFirstFile(caminho_busca, &find_data);

    if (h_find != INVALID_HANDLE_VALUE)
    // INVALID_HANDLE_VALUE - objeto inválido, não funcionou
    // Se diferente, logo funcionou
    {
        do
        {
            // Ignora as pastas "." e ".." -- não queremos listar o diretório atual mais de uma vez
            if (strcmp(find_data.cFileName, ".") == 0 || strcmp(find_data.cFileName, "..") == 0)
            {
                continue;
            }

            // Imprime recuo proporcional ao nível de profundidade
            for (int i = 0; i < nivel; i++)
            {
                printf("\t");
            }

            // Exibe o nome do arquivo ou diretório
            printf("|-- %s", find_data.cFileName);

            // Verifica se é um diretório, o FindFirstFile tem operações bitwise para verificar os atributos do arquivo
            // FILE_ATTRIBUTE_DIRECTORY - atributo de diretório
            // FILE_ATTRIBUTE_NORMAL - atributo normal
            if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                printf(" [PASTA]\n");

                // Monta o caminho completo do subdiretório
                snprintf(subdiretorio, MAX_PATH, "%s\\%s", diretorio, find_data.cFileName);

                // Chama a função recursivamente para listar os arquivos e pastas dentro do subdiretório
                listar_arquivos_recursivo(subdiretorio, nivel + 1);
            }
            else
            {
                printf(" [ARQUIVO]\n");
            }
        } while (FindNextFile(h_find, &find_data)); // enquanto existir arquivos ou pastas

        // Devemos fechar o handle após o uso
        FindClose(h_find);
    }
    else
    {
        printf("Erro ao abrir o diretório: %s\n", diretorio);
    }
}

int main()
{
    char diretorio_inicial[MAX_PATH];

    printf("Digite o caminho do diretorio inicial: ");
    scanf("%s", diretorio_inicial);

    printf("Explorando a arvore de diretorios em: %s\n", diretorio_inicial);
    listar_arquivos_recursivo(diretorio_inicial, 0);

    return 0;
}
