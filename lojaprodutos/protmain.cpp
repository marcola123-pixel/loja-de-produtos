/***************************************************  
Nome(s) do(a) estudante(s): Marcos Vinicius Moreira Cairo, Jennyfer Sousa Magalhães
Trabalho 
Professor(a): Nome do professor(a)]: Graziela Santos de Araujo
***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trabalho.h"  // Inclui todas as funções do arquivo único

#define MAX_PRODUTOS 1000
#define MAX_VENDAS 1000

int main() {

    unsigned int totalProdutos = 0;

    Venda vendas[MAX_VENDAS];
    int totalVendas = 0;

    char nomeArquivo[100];

    printf("Informe o nome do arquivo de produtos: ");
    scanf("%s", nomeArquivo);
    getchar(); // Consome \n após scanf
    // Verifica se o nome do arquivo foi informado

    if (strlen(nomeArquivo) == 0) {
        printf("Erro: nome do arquivo não informado.\n");
        return 1;
    }

    // Lê o arquivo de produtos
    Produto* produtos = Ler_arquivo(&totalProdutos, nomeArquivo);

    if (totalProdutos == 0) {
        printf("Erro ao carregar produtos.\n");
        return 1;
    }

    // Ordena os produtos por nome
    mergesort(0,totalProdutos, produtos);

    int opcao;
    do {
        printf("\n=== MENU ===\n");
        printf("[1] Cadastrar Venda\n");
        printf("[2] Listar vendas por data\n");
        printf("[3] Alterar estoque e preco de produto\n");
        printf("[4] Remover produto do estoque\n");
        printf("[5] Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Consome \n

        switch (opcao) {
            case 1:{
                cadastrarVenda(produtos, totalProdutos, vendas, &totalVendas);
                break;
            }
            case 2: {
                char dataDesejada[20];
                printf("Digite a data desejada (aaaa/mm/dd): ");
                scanf("%s", dataDesejada);
                getchar(); // Consome \n
                listarVendasPorData(vendas, totalVendas, dataDesejada);
                break;
            }
            case 3:{
               alterarProduto(produtos, totalProdutos);
                break;
            }
            case 4:{
                 removerProduto(produtos, &totalProdutos, vendas, totalVendas);
                break;
            }
            case 5:{
               salvarProdutos(nomeArquivo,produtos,totalProdutos);
               salvarVendas(vendas, totalVendas, produtos, totalProdutos);
               gerarNomeArquivoVendas(nomeArquivo);
                printf("Encerrando programa.\n");
                break;
            }
            default:{
                printf("Opção inválida.\n");
            }
        }

    } while (opcao != 5);

    return 0;
}
