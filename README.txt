#Projeto de SD:
##Trabalho: Navegador 

#Realizado por:
-Daniel Valente nº35453
-Carolina Lopes nº 38338

#Manual de Utilização

	Correr a aplicação, normalemnte corre-se no Visual Studio para c++.
	Cuidado special na linkagem tem de se linkar urlmon.lib:
		-No visual Studio em cima do projeto carregar em proprieties
		-Na tab de Linker carregar no Input
		-No Input onde diz "Aditional Dependencies" carregar e adicionar "urlmon.lib" 

	Navegar pelo menu de acordo com as indicações e intenções do utilizador


#Descrição
	Para a realização deste projeto foi utilizado a linguagem c++ com auxilio de uma biblioteca chamada de urlmon cuja dll 
	vem incluida no projeto.

	O principal objetivo com este projeto é o de criar um programa eficiente no terminal através de manipulação de
 	threads e processos gerindo concorrencia no sistema que guarda o html de paginas web, com interface gráfica 
	opcional.

	A ideia geral por detrás do nosso projeto é ter um vetor de threads que correm uma função criada por nós 
	chamada de Tab, sempre que o utilizador cria uma nova tab uma thread é adicionada ao vetor de tabs ativas.
	Quando é criada a tab executa logo o seu modo de pesquisa, pois supomos que se o utilizador cria uma tab é 
	logo para pesquisa de dados. Após finalizar a pesquisa  thread passa para um estado de sleep até que o utilizador 
	a volte a requisitar.

	A função tab é uma função simples com um ciclo infinito while que se a thread estiver no estado de pesquisa 
	(estado 1) pesquisa e guarda o html do url inserido, se estiver em estado de espera (0) encontra se num 
	sleep indefinido até o programa acabar, onde é terminada ou até o utilizador necessitar dela outra vez passando
	para estado 1. Se o utilizador quiser fechar a tab esta passa para estado -1 que quebra o while infinito e termina
 	a função, terminando a thread e libertando todos  os seus recursos. 

