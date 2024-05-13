PROJETO BANCO QUEM POUPA TEM

Introdução:
  Este projeto visa a simulação de um sistema de banco e foi desenvolvido em linguagem C por três alunos da FEI.

Desenvolvedores:

  Marcelo Boalento do Nascimento – R.A.: 24.123.078-9
  
  Morgana Rodrigues Zanetti – R.A.: 24.223.010-0
  
  Orlando Nagrockis Bertholdo – R.A.: 24.223.003-5


Funcionamento:
  Ao compilar (iniciar) o programa, um menu contendo 7 opções é fornecido aousuário, sendo as opções:

    (1) Encerrar o programa.
    
    (2) Cadastrar um novo cliente.
    
    (3) Apagasr cliente.
    
    (4) Listar clientes.
    
    (5) Débito.
    
    (6) Depósito.
    
    (7) Extrato.
    
    (8) Transferência entre 2 contas.
    

Como cada opção será executada:

  (1) Encerra o programa.
  
  (2) Cadastra um novo cliente no banco.
  
  (3) Pede o CPF do cliente que será removido do sistema.
  
  (4) Lista todos os clientes cadastrados.
  
  (5) Pede o CPF e a senha da conta do cliente para realizar um débito.
  
  (6) Pede o CPF do cliente e deposita um valor em sua conta.
  
  (7) Pede o CPF e a senha do cliente para que o extrato detodas as suas operações seja mostrado.
  
  (8) Solicita CPF e senha do cliente, conta de destino (conta para qual o dinheiro será transferido) e valor a ser transferido para efetuar uma transferência entre as contas.
  

Onde pode ser compilado:

  Este código pode ser compilado em qualquer compilador de linguagem C.


Arquivos:

 O repositório ‘extrato.txt’ é um arquivo texto que contém todas as operações realizadas pelo cliente, sendo elas: o tipo de operação, CPF, tipo da conta, valor que foi debitado, 
depositado ou transferido e o valor da tarifa.

  O repertório ‘transações.txt’ é um arquivo texto que grava todas as transações realizadas pelo cliente. Salvando no arquivo o nome do cliente, operação efetuada, CPF do usuário, 
tipo da conta, valor transferido, debitado e/ou transferido e tarifa (5% para contas do tipo ‘plus’ e 3% para contas ‘comum’).

  O arquivo ‘clientes.bin’ é um arquivo binário responsável por armazenar todos os dados dos clientes, sendo os seguintes dados gravados: nome, CPF, tipo da conta, valor inicial 
(saldo) e a senha cadastrada pelo cliente.


O código:

  O código é dividido em 3 partes: ‘main.c’, ‘clientes.c’ e ‘clientes.h’. Na main.c está contida o menu que será apresentado ao usuário. E, enquanto clientes.h define a struct 
(registro ou pacote de variáveis) do cliente e as funções, clientes.c implementa as funções definidas em clientes.h.


Observação:
  1. Com excessão da função listar clientes, que mostra todos os clientes cadastrados em forma de lista, as outras funções foram projetadas de modo em que sejam executadas
individualmente para cada cliente.
  3. O usuário só paga tarifa ao utilizar a função de débito.
