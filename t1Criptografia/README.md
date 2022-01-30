#### Grupo: 
* Gabriel Vinicius Canzi Candido  
    *  GRR20152825
* Stephanie Briere Americo        
    * GRR20165313
* Talita Halboth Cunha Fernandes  
    * GRR20165399

## Trabalho de Criptografia
Este trabalho é um programa que criptografa um arquivo, 
convertendo o que foi criptografado em um áudio tipo WAV.
Para fazer a criptografia, são usadas três cifras simétricas:
Playfair, Rail Fence e Vigenére Autokey, daí o nome desta versão, Play Fence Vigekey WAV
 (PLAFEVIW).

 Diferentemente do proposto, o dicionário utilizado serão todos os caracteres no intervalo
 [0,256).
 
 O funcionamento do algoritmo é o seguinte:
##### Cifra: 
 1. O cifrador lê o texto claro do arquivo `entrada`.
 2. O cifrador lê as três chaves necessárias para fazer a cifra.
 3. O cifrador cifra a entrada com as playfair.
 4. A saída da playfair é a entrada para este passo, que cifra utilizando a rail fence.
 5. A saída da rail fence é a entrada para este passo, que cifra utilizando o vigenere autokey.
 6. A saída do vigenere autokey é a entrada para este passo, que transforma a cifra em um arquivo de áudio tipo wav e o salva em `saida.wav`.


##### Decifra: 
 1. O decifrador lê as três chaves necessárias para fazer a decifra.
 2. O decifrador lê o arquivo de áudio e pega os dados criptografados
 3. O decifrador decifra os dados usando vigenere autokey
 4. A saída do vigenere é a entrada para esse passo, que decifra utilizando
 a rail fence
 5. A saída da rail fence é a entrada para esse passo, que decifra utilizando
 a playfair
 6. A saída  da playfair é o texto claro, que é impresso na saída padrão.

#### Rodando o cifrador: 
```
$ python encrypt.py
```
#### Rodando o decifrador: 
```
$ python decrypt.py
```
