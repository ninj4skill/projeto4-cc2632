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

erro Debitar(Clientes cliente[], int *pos){
  long cpfdebitar;
  char senhadebitar;
  long valordebitar;
  int encontrado = 0;
  printf("Digite o CPF do Cliente: ");
  scanf("%ld", &cpfdebitar);
  for (int i = 0; i < *pos; i++){
    if (cpfdebitar == cliente[i].cpf){
      printf("Digite a Senha do cliente: ");
      scanf("%s", &senhadebitar);
      if (strcmp(&senhadebitar, cliente[i].senha_usuario) == 0){
        printf("Digite o valor que deseja ser debitado: ");
        scanf("%ld", &valordebitar);
        if (strcmp(cliente[i].conta, "plus") == 0){
          int valortarifa = valordebitar * 0.03;
          cliente[i].valor_inicial -= valordebitar + valortarifa;
          FILE *f = fopen("transações.txt", "a");
          fprintf(f, "Cliente: %s\tOperação: Debito\tCPF: %ld\tTipo de conta: %s\tValor: -%ld\tTarifa: %d\n", cliente[i].nome, cliente[i].cpf, cliente[i].conta, valordebitar, valortarifa );
          fclose(f);
          Salvar_clientes(cliente, pos);
      }
        else{
          int valortarifa = valordebitar * 0.05;
          cliente[i].valor_inicial -= valordebitar + valortarifa;
          FILE *f = fopen("transações.txt", "a");
          fprintf(f,"Cliente: %s\tOperação: Debito\tCPF: %ld\tTipo de conta: %s\tValor: -%ld\tTarifa: %d\n", cliente[i].nome, cliente[i].cpf, cliente[i].conta, valordebitar, valortarifa);
          fclose(f);
          Salvar_clientes(cliente, pos);
        }
        encontrado = 1;;
      }
    }
   }
  return SUCESSO;
}

erro Depositar(Clientes cliente[], int *pos){
  long cpfdepositar;
  long valordeposito;
  int encontrado = 0;
  printf("Digite o cpf do Cliente: ");
  scanf("%ld", &cpfdepositar);
  for (int i = 0; i < *pos; i++){
    if (cpfdepositar == cliente[i].cpf){
      printf("Digite o valor que deseja depositar: ");
      scanf("%ld", &valordeposito);
      cliente[i].valor_inicial += valordeposito;
      FILE *f = fopen("transações.txt", "a");
      fprintf(f,"Cliente: %s\tOperação: Deposito\tCPF: %ld\tTipo de conta: %s\tValor: +%ld\tTarifa: 0\n", cliente[i].nome, cliente[i].cpf, cliente[i].conta, valordeposito);
      fclose(f);
      encontrado = 1;
      Salvar_clientes(cliente, pos);
    }
  }
  return SUCESSO;
}

erro Extrato(Clientes cliente[], int *pos){
  long cpfextrato;
  char senhaextrato[50];
  int encontradocpf = 0;
  int encontradosenha = 0;
  printf("Digite o CPF do Cliente: ");
  scanf("%ld", &cpfextrato);
  for(int i =0; i < *pos; i++){
    if (cpfextrato == cliente[i].cpf){
      encontradocpf = 1;
      printf("Digite a senha do cliente: ");
      clearBuffer();
      fgets(senhaextrato, sizeof(senhaextrato), stdin);
      senhaextrato[strcspn(senhaextrato, "\n")] = '\0';
      if (strcmp(senhaextrato, cliente[i].senha_usuario) == 0){
        encontradosenha = 1;
        FILE *f = fopen("extrato.txt", "w");
        FILE *f2 = fopen("transações.txt","r");
        char linha[100];
        while (fgets(linha, sizeof(linha), f2)){
          long cpf;
          char operacao[50];
          char tipo_conta[50];
          long valor;
          int tarifa;
          if (sscanf(linha, "Cliente: %*s Operação: %s CPF: %ld Tipo de conta: %s Valor: %ld Tarifa: %d", operacao, &cpf, tipo_conta, &valor, &tarifa)==5){
            if (cpf == cpfextrato){
              fprintf(f, "Operação: %s\tCPF: %ld\tTipo de conta: %s\tValor: %ld\tTarifa: %d\n", operacao, cpf, tipo_conta, valor, tarifa);
            } 
          }
        }
        fclose(f);
        fclose(f2);
      }
    }
  }

  return SUCESSO;
}

erro Transferencia(Clientes cliente[], int *pos){
  long cpforigem;
  char senhaorigem;
  long cpfdestino;
  long valortransferencia;
  printf("Digite o cpf de origem: ");
  scanf("%ld", &cpforigem);
  for(int i = 0; i < *pos; i++){
    if (cpforigem == cliente[i].cpf){
      printf("Digite a senha do cliente de origem: ");
      scanf("%s", &senhaorigem);
      if (strcmp(&senhaorigem, cliente[i].senha_usuario) == 0){
        printf("Digite o cpf de destino: ");
        scanf("%ld", &cpfdestino);
        for (int j = 0; j < *pos; j++){
          if (cpfdestino == cliente[j].cpf){
            printf("Digite o valor que deseja transferir: ");
            scanf("%ld", &valortransferencia);
            cliente[i].valor_inicial -= valortransferencia;
            cliente[j].valor_inicial += valortransferencia;
            FILE *f = fopen("transações.txt", "a");
            fprintf(f,"Cliente: %s\tOperação: Tranferência\tCPF: %ld\tTipo de conta: %s\tValor: -%ld\tTarifa: 0\n", cliente[i].nome, cliente[i].cpf, cliente[i].conta, valortransferencia);
            fprintf(f, "Cliente: %s\tOperação: Transferência\tCPF: %ld\tTipo de conta: %s\tValor: +%ld\tTarifa: 0\n", cliente[j].nome, cliente[j].cpf, cliente[j].conta, valortransferencia);
            fclose(f);
            Salvar_clientes(cliente, pos);
          }
        }
      }
    }
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
