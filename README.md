# ip_tester_cpp
Testador de ips que identifica, dado uma lista de ips, quais dispositivos estão ligados no momento.

Este projeto foi um aprimoramento de um trabalho feito na faculdade, o mesmo pode ser encontrado [aqui](https://github.com/mtdecarvalho/TrabalhoLFT)  
Também existe um fork que foi um aprimoramento do mesmo trabalho da faculdade, o mesmo pode ser encontrado [aqui](https://github.com/senhorbento/ip_tester)
#
## Como utilizar:

Ao iniciar o programa pela primeira vez, ele reconhecerá que é o primeiro início, ao pressionar uma tecla o mesmo ira abrir a pasta onde estará localizados 2 arquivos lista.txt e ignore.txt

### Arquivo lista.txt

- Dentro do arquivo deve ser inserida a lista de endereços ips a serem testados;  
- O programa verifica apenas 1 ip por linha;  
- O ip pode estar em qualquer posição da linha, o programa o encontrara.  

### Arquivo ignore.txt

- Dentro do arquivo deve ser inserido os endereços ips a serem ignorados durante os testes;  
- O programa verifica apenas 1 endereço ip por linha;  
- O ip pode estar em qualquer posição da linha, o programa o encontrara.   

**Observação: Caso não vá utilizar uma lista de ips ignorados, remova as linhas que estão dentro do arquivo.** 

Após inserir as informações, basta iniciar o programa novamente e o mesmo irá começar a realizar os testes a fim de detectar quais os dispositivos estão ligados, essa verificação é feita através da ferramenta de ping do próprio windows. Ao detectar um endereço ativo ele será aberto em uma janela do chrome e pausará o programa, para continuar a verificação basta pressionar uma tecla no programa, **o programa automaticamente remove endereços da lista após encontrá-lo ativo**.
