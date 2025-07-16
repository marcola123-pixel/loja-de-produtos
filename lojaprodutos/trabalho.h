struct Produto {
    int codigo;
    char* nome;
    float preco;
    int estoque;
    bool usadoEmVenda = false;
};

struct Horario{
    int hora;
    int minuto;
    int segundo;
};

struct ItemVenda {
    int codigoProduto;
    float precoVenda;
    int quantidade;
    struct ItemVenda* prox;     
}; 

struct Venda {
    char data[11]; 
    Horario hora; 
    char cpf[20];
    ItemVenda* itens;
    float total;    
};


Produto* Ler_arquivo(unsigned int* n, char *nomeArquivo);

char* numVirg(float num);

void mergesort(unsigned int p, unsigned int r, Produto *arr);

void intercala(unsigned int p, unsigned int q, unsigned int r, Produto *arr);

void listarProdutos(Produto* produtos,unsigned int n);

void alterarProduto(Produto* produtos,unsigned int n);

int buscarProduto(Produto* produtos,unsigned int n, int codigo);

void obterDataHora(char* dataStr, Horario* horaStruct);

void adicionarItem(ItemVenda** lista, int codigo, float preco, int quantidade);

void removerProduto(Produto* produtos,unsigned int* n, Venda* vendas, int totalVendas);

void cadastrarVenda(Produto* produtos,unsigned int n, Venda* vendas, int* totalVendas);

void listarVendasPorData(Venda* vendas, int totalVendas, const char* dataDesejada);

void salvarProdutos(const char* nomeArquivo, Produto* produtos, int n);

void salvarVendas(Venda* vendas, int totalVendas, Produto* produtos, int nProdutos);

void gerarNomeArquivoVendas(char* nomeArquivo);

