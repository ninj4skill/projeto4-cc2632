#include <stdio.h>
#include "clientes.h"


int main() {
  funcao Operacoes[] = {Adicionar,Deletar, Listar, Debitar, Depositar, Extrato , Salvar_clientes, Carregar_clientes/*, Transferencia*/};
  int pos = 0;
  Clientes cliente[total];
  Carregar_clientes(cliente, &pos);
  int opcao;

  do{
    printf("\t\tMENU\n");
    printf("1. Novo cliente\n");
    printf("2. Apagar cliente\n");
    printf("3. Listar clientes\n");
    printf("4. Débito\n");
    printf("5. Depósito\n");
    printf("6. Extrato\n");
    printf("7. Transferência entre contas\n");
    printf("0. Sair\n");
    printf("Insira a opcao desejada: ");
    scanf("%d", &opcao);
    if(opcao > 7){
      printf("Opção inválida\n");
    }
    else if (opcao > 0){
      Operacoes[opcao - 1](cliente, &pos);
    }
    else {
      printf("Saindo...\n");
      Salvar_clientes(cliente, &pos);
    }
  } while(opcao != 0);

  }