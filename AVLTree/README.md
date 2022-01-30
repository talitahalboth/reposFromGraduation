# Trabalho de Alg III
Operações em uma AVL
### Inserção:
* Desce na árvore conforme o padrão de uma BST 
    * (chave maior, vai pra direita, chave menor, vai pra esquerda)
* Aloca um novo nodo pra chave inserida quando encontra a posição
* Atualiza a altura da árvore
* Balanceia a árvore através de rotações à esquerda e à direita


### Remoção
* Desce na árvore conforme o padrão de uma BST
    * (chave maior, vai pra direita, chave menor, vai pra esquerda)
* Se o nodo a ser removido tem 1 filho ou não tem filhos
   *  nodo recebe o filho que tem (ou nulo, se não tem filho)
* Se o nodo tem dois filhos
    * chave do nodo recebe chave do antecessor
    * remove nodo antecessor


### Busca 
* Desce na árvore conforme o padrão de uma BST, porém de forma iterativa
    * (chave maior, vai pra direita, chave menor, vai pra esquerda)
* Vai imprimindo cada nodo seguido com uma vírgula antes (menos no nodo inicial)


## Grupo:
* Stephanie Briere Americo
    * GRR20165313 
* Talita Halboth Cunha Fernandes
    * GRR20165399
