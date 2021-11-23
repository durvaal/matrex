# Sobre

Projeto realizado para a atividade 1 da disciplina de Sistemas Operacionais do curso de BTI na UFRN. O foco dessa atividade foi trabalhar o conceito de processos através da multiplicação de matrizes.

# Integrantes

Paulo de Lima Xavier
Samuel de Araújo Costa

# Matrex Sequential

Calcula a multiplicação de matrizes de forma sequencial a partir de dois arquivos **m1.txt** e **m2.txt**. Ele é dividido em 4 partes:

### Criação das Matrizes - create_matrix.cpp

Recebe as dimensões (linha e coluna) de duas matrizes (4 argumentos), gerando as matrizes e preenchando-as com valores aleatórios. 
As matrizes são salvas em um arquivo .txt, que serão utilizos nos cálculos.

### Multiplicação Sequencial - sequential.cpp

Recebe os arquivos .txt que representam duas matrizes, que são passadas através da linha de comando. 
Realizam o cálculo de forma convencional. 
Salva a matriz resultante em um arquivo .txt, contendo a linha e coluna, o valor de cada posição e o tempo que passou para finalizar o cálculo.

### Multiplicação Paralela Thredas - threads.cpp

Recebe os arquivos .txt que representam duas matrizes e um inteiro P, que são passadas através da linha de comando. 
Realizam o cálculo através de uma nova thread que é criada para cada P elementos. 
Salva a matriz resultante em n1*m2/P arquivos .txt, contendo a linha e coluna, o valor de cada posição e o tempo que passou para finalizar o cálculo.

### Criação das Matrizes - create_matrix.cpp

Recebe os arquivos .txt que representam duas matrizes e um inteiro P, que são passadas através da linha de comando. 
Realizam o cálculo através processos diferentes, que são criados para cada P elementos. 
Salva a matriz resultante em n1*m2/P arquivos .txt, contendo a linha e coluna, o valor de cada posição e o tempo que passou para finalizar o cálculo.

## Como compilar o programa

```
make
```

## Como executar o programa

```
./matrex_exec
```

## Métodos suportados

### Sair do sistema

```
quit
```

### Gerar as matrizes

```
write [row1] [col1] [row2] [col2]
```
> `row1` e `col1` é a linha e coluna da primeira matriz e `row2` e `col2` é a linha e coluna da segunda matriz

> Exemplo de execução: `write 100 100 100 100`

### Cálculo das matrizes de forma sequencial

```
sequential [file1] [file2] 
```
> `file1` e `file2` são os os nomes dos arquivos com extensão, por exemplo, `m1.txt` e `m2.txt`

> Exemplo de execução: `sequential m1.txt m2.txt`

### Cálculo das matrizes usando paralelo threads

```
threads [file1] [file2] [p] 
```
> `file1` e `file2` são os os nomes dos arquivos com extensão, por exemplo, `m1.txt` e `m2.txt` e `p` um inteiro

> Exemplo de execução: `threads m1.txt m2.txt 5000`

### Cálculo das matrizes usando paralelo processo

```
process [file1] [file2] [p] 
```
> `file1` e `file2` são os os nomes dos arquivos com extensão, por exemplo, `m1.txt` e `m2.txt` e `p` um inteiro

> Exemplo de execução: `process m1.txt m2.txt 500`

:rocket: