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
