#Projeto de SD:
##Trabalho: Navegador 

#Realizado por:
-Daniel Valente n�35453
-Carolina Lopes n� 38338

#Manual de Utiliza��o

	Correr a aplica��o, normalemnte corre-se no Visual Studio para c++.
	Cuidado special na linkagem tem de se linkar urlmon.lib:
		-No visual Studio em cima do projeto carregar em proprieties
		-Na tab de Linker carregar no Input
		-No Input onde diz "Aditional Dependencies" carregar e adicionar "urlmon.lib" 

	Navegar pelo menu de acordo com as indica��es e inten��es do utilizador


#Descri��o
	Para a realiza��o deste projeto foi utilizado a linguagem c++ com auxilio de uma biblioteca chamada de urlmon cuja dll 
	vem incluida no projeto.

	O principal objetivo com este projeto � o de criar um programa eficiente no terminal atrav�s de manipula��o de
 	threads e processos gerindo concorrencia no sistema que guarda o html de paginas web, com interface gr�fica 
	opcional.

	A ideia geral por detr�s do nosso projeto � ter um vetor de threads que correm uma fun��o criada por n�s 
	chamada de Tab, sempre que o utilizador cria uma nova tab uma thread � adicionada ao vetor de tabs ativas.
	Quando � criada a tab executa logo o seu modo de pesquisa, pois supomos que se o utilizador cria uma tab � 
	logo para pesquisa de dados. Ap�s finalizar a pesquisa  thread passa para um estado de sleep at� que o utilizador 
	a volte a requisitar.

	A fun��o tab � uma fun��o simples com um ciclo infinito while que se a thread estiver no estado de pesquisa 
	(estado 1) pesquisa e guarda o html do url inserido, se estiver em estado de espera (0) encontra se num 
	sleep indefinido at� o programa acabar, onde � terminada ou at� o utilizador necessitar dela outra vez passando
	para estado 1. Se o utilizador quiser fechar a tab esta passa para estado -1 que quebra o while infinito e termina
 	a fun��o, terminando a thread e libertando todos  os seus recursos. 

