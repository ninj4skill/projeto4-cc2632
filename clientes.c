#include <stdio.h>
#include <string.h>
#include "clientes.h"

erro Adicionar(Clientes cliente[], int *pos){
  if(*pos >= total){
    printf("Limite de clientes atingido\n");
    return MAXCLIENTES;
  }
  printf("Nome: ");
  clearBuffer();
  fgets(cliente[*pos].nome, sizeof(cliente[*pos].nome), stdin);
  cliente[*pos].nome[strcspn(cliente[*pos].nome, "\n")] = '\0';

  printf("CPF: ");
  scanf("%ld", &cliente[*pos].cpf);

  clearBuffer();
  printf("Tipo da Conta: ");
  fgets(cliente[*pos].conta, 50, stdin);
  cliente[*pos].conta[strcspn(cliente[*pos].conta, "\n")] = '\0';

  printf("Valor Inicial: ");
  scanf("%ld", &cliente[*pos].valor_inicial);

  printf("Senha do Usuário: ");
  clearBuffer();
  fgets(cliente[*pos].senha_usuario, 50, stdin);
cliente[*pos].senha_usuario[strcspn(cliente[*pos].senha_usuario, "\n")] = '\0';

  clearBuffer();

  *pos = *pos + 1;
  return SUCESSO;
}

erro Deletar(Clientes cliente[], int *pos){
  if(*pos == 0){
    printf("Sem clientes para deletar\n");
    return SEMCLIENTES;
  }
  long cpfdeletar;
  printf("CPF do cliente a ser deletado: ");
  scanf("%ld", &cpfdeletar);
  int encontrado = 0;
  for (int i = 0; i < *pos; i++) {
    if (cliente[i].cpf == cpfdeletar) {
      strcpy(cliente[i].nome, cliente[i + 1].nome);
      strcpy(cliente[i].conta, cliente[i + 1].conta);
      strcpy(cliente[i].senha_usuario, cliente[i + 1].senha_usuario);
      cliente[i].valor_inicial = cliente[i + 1].valor_inicial;
      cliente[i].cpf = cliente[i + 1].cpf;

      encontrado = 1;
    }
  }
  if (encontrado == 0){
    printf("Cliente não encontrado!\n");
    return NAOENCONTRADO;
  }
  *pos = *pos - 1;
  return SUCESSO;
}

erro Listar(Clientes cliente[], int *pos){
  if(*pos == 0){
  printf("Sem clientes para listar\n");
  return SEMCLIENTES;
}
  for (int i = 0; i < *pos; i++){
      printf("Nome: %s\t", cliente[i].nome);
      printf("CPF: %ld\t", cliente[i].cpf);
      printf("Tipo da Conta: %s\t", cliente[i].conta);
      printf("Saldo: %ld\t", cliente[i].valor_inicial);
      printf("Senha: %s\n", cliente[i].senha_usuario);
    }
    return SUCESSO;
}


erro Salvar_clientes(Clientes cliente[], int *pos){
  FILE *f = fopen("clientes.bin", "wb");
  if (f == NULL){
    return ABRIR;
  }
  int salvar = fwrite(cliente, total, sizeof(Clientes), f);
  salvar = fwrite(pos,1,sizeof(int),f);
  fclose(f);
  return SUCESSO;
}

erro Carregar_clientes(Clientes cliente[], int *pos){
  FILE *f = fopen("clientes.bin", "rb");
  if (f == NULL){
    return ABRIR;
  }
  int carregar = fread(cliente, total, sizeof(Clientes), f);
  carregar = fread(pos,1,sizeof(int),f);
  fclose(f);
  return SUCESSO;
}

void clearBuffer(){
      int c;
      while ((c = getchar()) != '\n' && c != EOF);
}
