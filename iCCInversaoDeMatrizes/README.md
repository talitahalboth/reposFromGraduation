# [ICC] Inversão de Matrizes

O objetivo deste trabalho é implementar um programa computacional que, dada uma matriz quadrada A de dimensão n, encontre a matriz inversa de A (inv(A)), tal que A * inv(A) = I, onde I é a matriz identidade. Para tal, o programa utiliza o Método da Eliminação de Gauss com Pivotamento Parcial, Fatoração LU e Refinamento.

## Compilando

Há uma makefile no projeto que compila o código, gerando o executável invmat.
```
cd sba16-thfc16
make
```

Para gerar a documentação, use make doc.
```
cd sba16-thfc16
make doc
```

### Rodando o programa

```
./invmat [-e arquivo_entrada] [-o arquivo_saida] [-r N] [-i k]
```

* -e arquivo_entrada: parâmetro opcional no qual arquivo_entrada é o caminho completo para o arquivo contendo a matriz a ser invertida. Em caso de ausência do parâmetro, a entrada será lida de stdin.
* -o arquivo_saida: parâmetro opcional no qual arquivo_saida é o caminho completo para o arquivo que vai conter a matriz inversa. Em caso de ausência do parâmetro, a saída será impressa em stdout.
* -r N: parâmetro opcional no qual N é a dimensão da matriz de entrada a ser gerada aleatoriamente
* -i k: Número de iterações de refinamento a serem executadas (>0)

## Estrutura do projeto

* Arquivos .c estão em sba16-thcf16/src
* Arquivos .h estão em sba16-thcf16/include
* Arquivos de teste básicos estão em sba16-thcf16/temp
* A documantação gerada pode ser encontrada em sba16-thcf16/doc
