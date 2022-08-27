# Processos e treads

## Compilacao

> make clean
>
> make
>
> make run

## Documentação

- Mais informações sobre o problema pode ser encontrado em [Documentação](https://github.com/danieldiv/processos-e-treads/blob/main/README-DOC.md)

# Menu

![Scrennshot](src/files/imgs/menuPrincipal.png)

- Ao executar o programa tera as seguintes opções

  - `0` - Finaliza o programa
  - `1` - Realizar a leitura do arquivo [D](https://github.com/danieldiv/processos-e-treads/blob/main/src/files/D.csv)
  - `2` - Realizar a leitura do arquivo [T](https://github.com/danieldiv/processos-e-treads/blob/main/src/files/T.csv)
  - `3` - Fazer as operacoes envolvendo os arquivod `D` e `T`

## Sistema multitarefa: Etapa I

- Na etapa I é realizada a leitura e tokenizacao do arquivo `D`. O arquivo sera [tokenizado](https://github.com/danieldiv/processos-e-treads/blob/main/src/util.hpp#L44) em 5 colunas que representa as chaves e as linhas representam os valores, as 4 primeiras colunas sera utilizado como chave dos itens e a ultima coluna sera utilizado como chave da classe.

## Sistema multitarefa: Etapa II

- Na etapa II é realizada a leitura, tokenizacao e processamento do arquivo `D`. O arquivo sera [tokenizado](https://github.com/danieldiv/processos-e-treads/blob/main/src/util.hpp#L82) linha a linhas utilizado as colunas como valores e linha como chave.

## Sistema multitarefa: Etapa III

- Para executar a etapa III é necessario liberar a opção `3`, que ficara bloqueada até fazer a leitura dos arquivos `D` e `T`. Nesta etapa é feita a operação para encontrar a classe da tarefa em T.
