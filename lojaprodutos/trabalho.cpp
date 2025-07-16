#include "trabalho.h"
#include <stdio.h>  //Para printf,scanf,fgets
#include <stdlib.h> //Para malloc,calloc,free
#include <string.h> //Para strcmp,strcpy,strlen,strcpn
#include <time.h>   // Para obter hora do sistema
#include <locale.h>
#define MAX 100
#define NOMES 50                // Número máximo de strings (nomes)
#define MAX_CHAR_PER_STRING 100 // Tamanho máximo de cada string (incluindo o terminador nulo '\0')

void intercala(unsigned int p, unsigned int q, unsigned int r, Produto *arr)
{

    unsigned int i, j, k;
    unsigned int temp = r - p;
    // Aloca um array temporário de Produtos
    Produto *w = (Produto *)calloc(temp, sizeof(Produto));
    if (w == NULL)
    {
        printf("Erro ao alocar memória para o array temporário.\n");
        exit(EXIT_FAILURE);
    }

    // // Aloca memória para cada Produto dentro do array temporário 'w'
    for (unsigned int idx = 0; idx < temp; ++idx)
    {
        w[idx].nome = (char *)calloc(MAX_CHAR_PER_STRING, sizeof(char));
        if (w[idx].nome == NULL)
        {
            // Libera memória já alocada para evitar vazamentos em caso de falha
            for (unsigned int prev_idx = 0; prev_idx < idx; ++prev_idx)
            {
                free(w[prev_idx].nome);
            }
            free(w);
            printf("Erro ao alocar memória para o nome do produto.\n");
            exit(EXIT_FAILURE);
        }
    }

    i = p; // Ponteiro para a primeira sub-lista
    j = q; // Ponteiro para a segunda sub-lista
    k = 0; // Ponteiro para o array temporário 'w'

    // Compara e copia strings para o array temporário 'w'
    while (i < q && j < r)
    {
        // strcmp retorna <0 se arr[i] vem antes de arr[j] alfabeticamente
        if (strcmp(arr[i].nome, arr[j].nome) < 0)
        {
            w[k].codigo = arr[i].codigo; // Copia o Produto* arr[i] para w[k]
            w[k].estoque = arr[i].estoque;
            strcpy(w[k].nome, arr[i].nome);
            w[k].preco = arr[i].preco;
            w[k].usadoEmVenda = arr[i].usadoEmVenda;

            i++;
        }
        else
        {
            w[k].codigo = arr[j].codigo; // Copia o Produto* arr[j] para w[k]
            w[k].estoque = arr[j].estoque;
            strcpy(w[k].nome, arr[j].nome);
            w[k].preco = arr[j].preco;
            w[k].usadoEmVenda = arr[j].usadoEmVenda;
            j++;
        }
        k++;
    }

    // Copia os elementos restantes da primeira sub-lista, se houver
    while (i < q)
    {
        w[k].codigo = arr[i].codigo;
        w[k].estoque = arr[i].estoque;
        strcpy(w[k].nome, arr[i].nome);
        w[k].preco = arr[i].preco;
        w[k].usadoEmVenda = arr[i].usadoEmVenda;
        i++;
        k++;
    }
    // Copia os elementos restantes da segunda sub-lista, se houver
    while (j < r)
    {
        w[k].codigo = arr[j].codigo;
        w[k].estoque = arr[j].estoque;
        strcpy(w[k].nome, arr[j].nome);
        w[k].preco = arr[j].preco;
        w[k].usadoEmVenda = arr[j].usadoEmVenda;
        j++;
        k++;
    }

    // Copia os elementos ordenados do array temporário 'w' de volta para o array original 'arr'
    for (i = p; i < r; i++)
    {
        strcpy(arr[i].nome, w[i - p].nome); // Copia a string de w para arr, ajustando o índice
        arr[i].codigo = w[i - p].codigo;
        arr[i].estoque = w[i - p].estoque;
        arr[i].preco = w[i - p].preco;
        arr[i].usadoEmVenda = w[i - p].usadoEmVenda;
    }

    // Libera a memória alocada para as strings e para o array temporário 'w'
    // for (unsigned int idx = 0; idx < (r - p); ++idx)
    // {
    //     free(w[idx]);
    // }
    free(w);
}

// Função mergesort recursiva para ordenar um array de Produtos
// p: índice inicial da porção do array a ser ordenada
// r: índice final (exclusivo) da porção do array a ser ordenada
// arr[]: O array de ponteiros para produtos a ser ordenado
void mergesort(unsigned int p, unsigned int r, Produto *arr)
{
    unsigned int q; // Ponto médio
    if (p < r - 1)
    {                            // Se a sub-lista tiver mais de um elemento
        q = (p + r) / 2;         // Calcula o ponto médio
        mergesort(p, q, arr);    // Ordena a primeira metade
        mergesort(q, r, arr);    // Ordena a segunda metade
        intercala(p, q, r, arr); // Intercala as duas metades ordenadas
    }
}

Produto *Ler_arquivo(unsigned int *n, char *nomeArquivo)
{
    FILE *ent = fopen(nomeArquivo, "r");
    if (ent == NULL)
    {
        printf("arquivo nao pode ser aberto\n");
        return NULL; // Retorna NULL se o arquivo não puder ser aberto
    }
    else
    {
        fscanf(ent, "%d", n);
        Produto *produtos = (Produto *)calloc(*n, sizeof(Produto));
        if (produtos == NULL)
        {
            printf("Erro ao alocar memória para produtos.\n");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < *n; i++)
        {
            produtos[i].nome = (char *)calloc(MAX_CHAR_PER_STRING, sizeof(char));
            fscanf(ent, "%d%s%f%d", &produtos[i].codigo, produtos[i].nome, &produtos[i].preco, &produtos[i].estoque);
        }

        fclose(ent);
        return produtos; // Retorna o vetor de produtos alocado
    }
}

// Função para exibir os produtos disponíveis
void listarProdutos(Produto *produtos, unsigned int n)
{
    printf("\nProdutos disponíveis:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Codigo: %d | Nome: %s | Preco: R$ %.2f | Estoque: %d\n",
               produtos[i].codigo, produtos[i].nome, produtos[i].preco, produtos[i].estoque);
    }
}

// Função para buscar produto por codigo
int buscarProduto(Produto *produtos, unsigned int n, int codigo)
{
    for (int i = 0; i < n; i++)
    {
        if (produtos[i].codigo == codigo)
            return i;
    }
    return -1;
}

// Função para registrar data e hora atuais
void obterDataHora(char *dataStr, Horario *horaStruct)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(dataStr, "%04d/%02d/%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    horaStruct->hora = tm.tm_hour;
    horaStruct->minuto = tm.tm_min;
    horaStruct->segundo = tm.tm_sec;
}

// Função para adicionar item na lista encadeada (início da lista)
void adicionarItem(ItemVenda **lista, int codigo, float preco, int quantidade)
{
    ItemVenda *novo = (ItemVenda *)malloc(sizeof(ItemVenda));
    novo->codigoProduto = codigo;
    novo->precoVenda = preco;
    novo->quantidade = quantidade;
    novo->prox = *lista;
    *lista = novo;
}

// Função principal para cadastrar uma venda
void cadastrarVenda(Produto *produtos, unsigned int n, Venda *vendas, int *totalVendas)
{
    Venda novaVenda;
    novaVenda.itens = NULL;
    novaVenda.total = 0;

    obterDataHora(novaVenda.data, &novaVenda.hora);

    printf("\nDigite o CPF do cliente: ");
    scanf(" %[^\n]", novaVenda.cpf);

    while (1)
    {
        listarProdutos(produtos, n);
        int codigo, qtd;
        printf("Digite o codigo do produto (ou -1 para finalizar): ");
        scanf("%d", &codigo);
        if (codigo == -1)
            break;

        int indice = buscarProduto(produtos, n, codigo);
        if (indice == -1)
        {
            printf("Produto não encontrado!\n");
            continue;
        }

        printf("Digite a quantidade: ");
        scanf("%d", &qtd);

        if (qtd > produtos[indice].estoque)
        {
            printf("Estoque insuficiente. Disponível: %d\n", produtos[indice].estoque);
            printf("Deseja comprar essa quantidade disponível? (s/n): ");
            char opcao;
            scanf(" %c", &opcao);
            if (opcao == 's' || opcao == 'S')
            {
                qtd = produtos[indice].estoque;
            }
            else
            {
                continue;
            }
        }

        // Adiciona item à lista e atualiza total e estoque
        adicionarItem(&novaVenda.itens, produtos[indice].codigo, produtos[indice].preco, qtd);
        novaVenda.total += produtos[indice].preco * qtd;
        produtos[indice].estoque -= qtd;
    }

    printf("Venda finalizada! Valor total: R$ %.2f\n", novaVenda.total);

    vendas[*totalVendas] = novaVenda; // Adiciona a nova venda ao vetor de vendas
    (*totalVendas)++; // Incrementa o total de vendas
}

// Função para listar vendas realizadas em uma data específica
void listarVendasPorData(Venda *vendas, int totalVendas, const char *dataDesejada)
{
    int encontrou = 0;

    printf("\nVendas realizadas em %s:\n", dataDesejada);

    for (int i = 0; i < totalVendas; i++)
    {
        if (strcmp(vendas[i].data, dataDesejada) == 0)
        {
            printf("Hora: %02d:%02d:%02d\n",
                   vendas[i].hora.hora,
                   vendas[i].hora.minuto,
                   vendas[i].hora.segundo);
            printf("CPF: %s\n", vendas[i].cpf);
            printf("Valor total da venda: R$ %.2f\n", vendas[i].total);
            encontrou = 1;
        }
    }

    if (!encontrou)
    {
        printf("Nenhuma venda registrada nesta data.\n");
    }
}

// Função para alterar preco e adicionar estoque de um produto
void alterarProduto(Produto *produtos, unsigned int n)
{
    int codigo;
    printf("\nDigite o codigo do produto a ser alterado: ");
    scanf("%d", &codigo);

    int indice = buscarProduto(produtos, n, codigo);
    if (indice == -1)
    {
        printf("Produto não encontrado.\n");
        return;
    }

    // Exibe dados atuais
    printf("Produto encontrado:\n");
    printf("Nome: %s\n", produtos[indice].nome);
    printf("Preco atual: R$ %.2f\n", produtos[indice].preco);
    printf("Estoque atual: %d\n", produtos[indice].estoque);

    // Lê novo preco e quantidade a adicionar
    float novoPreco;
    int quantidadeAdicional;

    printf("Digite o novo preco: R$ ");
    scanf("%f", &novoPreco);
    printf("Digite a quantidade a ser adicionada ao estoque: ");
    scanf("%d", &quantidadeAdicional);

    // Atualiza os dados
    produtos[indice].preco = novoPreco;
    produtos[indice].estoque += quantidadeAdicional;

    printf("Produto atualizado com sucesso.\n");
}

// Função para verificar se um produto foi vendido em alguma venda
int produtoFoiVendido(Venda *vendas, int totalVendas, int codigoProduto)
{
    for (int i = 0; i < totalVendas; i++)
    {
        ItemVenda *atual = vendas[i].itens;
        while (atual != NULL)
        {
            if (atual->codigoProduto == codigoProduto)
            {
                return 1; // Produto encontrado em uma venda
            }
            atual = atual->prox;
        }
    }
    return 0; // Nunca foi vendido
}

// Função para remover produto do vetor, caso não tenha sido vendido
void removerProduto(Produto *produtos, unsigned int *n, Venda *vendas, int totalVendas)
{
    int codigo;
    printf("\nDigite o codigo do produto a ser removido: ");
    scanf("%d", &codigo);

    int indice = buscarProduto(produtos, *n, codigo);
    if (indice == -1)
    {
        printf("Produto não encontrado.\n");
        return;
    }

    // Verifica se o produto foi vendido
    if (produtoFoiVendido(vendas, totalVendas, codigo))
    {
        printf("Erro: Este produto já foi vendido e não pode ser removido.\n");
        return;
    }

    printf("Produto '%s' removido com sucesso.\n", produtos[indice].nome);

    // Remove o produto do vetor, deslocando os demais à esquerda
    for (int i = indice; i < *n - 1; i++)
    {
        produtos[i] = produtos[i + 1];
    }

    (*n)--; // Diminui a contagem de produtos
}

// opcao5, tem que testar

// Função para salvar os produtos no arquivo original
void salvarProdutos(const char *nomeArquivo, Produto *produtos, int n)
{
    FILE *f = fopen(nomeArquivo, "w");
    if (!f)
    {
        printf("Erro ao abrir o arquivo de produtos para escrita.\n");
        return;
    }

    fprintf(f, "%d\n", n);
    for (int i = 0; i < n; i++)
    {
        fprintf(f, "%d\n%s\n%.2f\n%d\n",
                produtos[i].codigo,
                produtos[i].nome,
                produtos[i].preco,
                produtos[i].estoque);
    }

    fclose(f);
    printf("Arquivo de produtos atualizado com sucesso.\n");
}
char* numVirg(float num){
 float numero = num;
 char* buffer;

 buffer = (char*)malloc(50 * sizeof(char)); // Aloca memória para a string

    // Converte o float para string com ponto
    snprintf(buffer, sizeof(buffer), "%.2f", numero);

    // Substitui o ponto por vírgula
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == '.') {
            buffer[i] = ',';
        }
    }

    return buffer; // Retorna o número convertido de volta para float
}

// Função para gerar nome do arquivo de vendas com a data atual
void gerarNomeArquivoVendas(char *nomeArquivo)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(nomeArquivo, "vendas%02d%02d%04d.txt",
            tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

// Função para buscar nome do produto pelo codigo
const char *obterNomeProduto(int codigo, Produto *produtos, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (produtos[i].codigo == codigo)
            return produtos[i].nome;
    }
    return "Desconhecido";
}

// Função para salvar as vendas em um novo arquivo com a data do dia
void salvarVendas(Venda *vendas, int totalVendas, Produto *produtos, int nProdutos)
{
    setlocale(LC_ALL, "pt_BR");
    char nomeArquivo[100];
    gerarNomeArquivoVendas(nomeArquivo);

    FILE *f = fopen(nomeArquivo, "w");
    if (!f)
    {
        printf("Erro ao criar o arquivo de vendas.\n");
        return;
    }

    for (int i = 0; i < totalVendas; i++)
    {
        fprintf(f, "%s\n", vendas[i].data);
        fprintf(f, "%02d:%02d:%02d\n",
                vendas[i].hora.hora,
                vendas[i].hora.minuto,
                vendas[i].hora.segundo);
        fprintf(f, "%s\n", vendas[i].cpf);
        

        ItemVenda *item = vendas[i].itens;
        while (item != NULL)
        {
            const char *nome = obterNomeProduto(item->codigoProduto, produtos, nProdutos);
            fprintf(f, "%d %s %d %s\n",
                    item->codigoProduto,
                    nome,
                    item->quantidade,
                    numVirg(item->precoVenda));
            item = item->prox;
        }

        fprintf(f, "%s\n", numVirg(vendas[i].total));
        fprintf(f, "\n");
    }

    fclose(f);
    printf("Arquivo de vendas '%s' salvo com sucesso.\n", nomeArquivo);
}

// int main()
// {
//     unsigned int n;
//     Produto *produtos = Ler_arquivo(&n);
//     if (produtos == NULL)
//     {
//         printf("Erro ao ler o arquivo.\n");
//         return 1; // Retorna um codigo de erro
//     }

//     // Aqui você pode adicionar mais lógica para manipular os produtos lidos
//     // Por exemplo, listar, alterar, remover produtos, etc.
//     for (int i = 0; i < 5; i++)
//     {
//         printf("%s\n", produtos[i].nome);
//         printf("%d\n", produtos[i].codigo);
//         printf("%d\n", produtos[i].estoque);
//         printf("%.2f\n", produtos[i].preco);
//         printf("%s\n", produtos[i].usadoEmVenda ? "true" : "false");
//         printf("---------------------------------\n");
//     }
//     printf("\n");

//     mergesort(0, n, produtos); // Ordena os produtos por nome
//     printf("Produtos ordenados:\n");
//     for (int i = 0; i < 5; i++)
//     {
//         printf("%s\n", produtos[i].nome);
//         printf("%d\n", produtos[i].codigo);
//         printf("%d\n", produtos[i].estoque);
//         printf("%.2f\n", produtos[i].preco);
//         printf("%s\n", produtos[i].usadoEmVenda ? "true" : "false");
//         printf("---------------------------------\n");
//     }
//     printf("\n");

//     // Libera a memória alocada para os produtos
//     free(produtos);
//     return 0; // Retorna 0 para indicar sucesso
// }
