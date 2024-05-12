#define total 1000

typedef struct{
  char nome[50];
  long cpf;
  char conta[50];
  long valor_inicial;
  char senha_usuario[50];
} Clientes;
typedef enum{SUCESSO, MAXCLIENTES, SEMCLIENTES, TIPOINVALIDO, NAOENCONTRADO, ABRIR, FECHAR, ESCREVER, LER}erro;
typedef erro (*funcao)(Clientes[], int*);

erro Adicionar(Clientes cliente[], int *pos);
erro Deletar(Clientes cliente[], int *pos);
erro Listar(Clientes cliente[], int *pos);
erro Debitar(Clientes cliente[], int *pos);
erro Depositar(Clientes cliente[], int *pos);
erro Extrato(Clientes cliente[], int *pos);
erro Transferencia(Clientes cliente[], int *pos);
erro Salvar_clientes(Clientes cliente[], int *pos);
erro Carregar_clientes(Clientes cliente[], int *pos);
void clearBuffer();