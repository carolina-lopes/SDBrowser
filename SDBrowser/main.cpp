#include <thread>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <mutex> 
#include <fstream>
using namespace std;

#include <urlmon.h>

std::vector <int> state;// estado de cada thread criada ---> 1-running, 0-waiting , -1 - terminate
char webAddress[256]; // site a visitar
std::vector<std::thread> vecOfThreads; // vetor onde se armazena as threads
char szFileName[80];// nome do ficheiro onde guardar o html
HRESULT hr;

std::ifstream::pos_type filesize(const char* filename)// funcao que retorna tamanho de um ficheiro 
{
	std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
	return in.tellg();
}

bool fileExists(const std::string& filename) //funcao que retorna se um ficehiro existe ou nao
{
	struct stat buf;
	if (stat(filename.c_str(), &buf) != -1)
	{
		return true;
	}
	return false;
}

void tab(int id) {
	int tab_id = id;

	while (1)
	{
		while (state[id] == 1) {

			 hr = URLDownloadToFile(NULL, webAddress, szFileName, 0, NULL);// pesquisa o URL e guarda no ficheiro com o nome atribuido pelo utilizador
			state[id] = 0; // apos guardar o html coloca o estado da thread a 0 -----> esperando trabalho
			
		}

		while (state[id] == 0) {
			Sleep(100); // enquanto espera por trabalho a thread dorme para minimizar os gastos de memoria RAM
		}

		if (state[id] == -1) {
			break; // sai do ciclo while de modo a terminar a execucao da thread e dá se a libertacao dos seus recursos
		}
	}
}

int main() {

	int menu=0;
	int time_count = 0;
	int erase_id = 0;
	int search = 0;
	int search_id;
	int tab_id=0;
	int close = -1;


	do {

		cout << "----------------------------------------------- \n";
		cout << "|BEM VINDO AO SD_BROWSER ESCOLHA UMA OPCAO    | \n";
		cout << "----------------------------------------------- \n";
		cout << "|   1- Pesquisa                               | \n";
		cout << "|   2-Apagar Tab                              | \n";
		cout << "|   3-Listar Tabs                             | \n";
		cout << "|   4-Sair                                    | \n";
		cout << "----------------------------------------------- \n";

		cin >> menu;

		if (menu == 1) {

			cout << "Threads Disponiveis: \n";
			for (int i=0; i<vecOfThreads.size(); i++)
			{
				if (state[i]==0) // apenas as threads em wait se encontram disponiveis para realizar uma nova pesquisa
					cout << i << endl;
			
			}
			cout << "1- Criar nova tab \n";
			cout << "2- Usar tab existente \n";

			cin >> search;

			if (search == 1) {
				
				cout << "Insira o endereco do site a visitar: \n";	// exemplo: http://www.google.com
				cin >> webAddress;
				cout << "Insira o nome do ficheiro onde ira guardar o html \n";
				cin >> szFileName;
			
				if (fileExists(szFileName)) { // se exixtir apaga se o conteudo do ficheiro por seguranca 
					remove(szFileName);
				}

				state.push_back(1); // ao criar a thread coloca se logo o estado a 1 porque quando se cria uma thread supoe-se que seja para uso imediato
				vecOfThreads.push_back(std::thread(tab, tab_id));
				vecOfThreads[tab_id].detach(); // ao dar detach a thread começa a correr em background e quando terminar a sua execução os seus recursos são libertados e a thread terminada 
				
				while (state[tab_id] == 1) {	//espera que o html seja carregado com tempo limite para não sobrecarregar o utilizador 
					Sleep(100);
					time_count = time_count + 1;
					if (time_count == 10)
					{
						state[tab_id] = 0;  // forçar a mudança de estado da tab para waiting 
						break;
					}
						
				}

				if (hr == -2146697203) //codigo de erro quando o site náo e valido (descoberto atraves de debug)
					cout << "Erro URL desconhecido" << endl;

				else {
					cout << "Informacoes do ficheiro guardado" << endl;
					cout << "ID= " << tab_id << "\t URL=" << webAddress;
					cout << "\t Nome de arquivo salvo= " << szFileName << "\t Tamanho=";

					cout << filesize(szFileName) << endl;
				}
				
				

				tab_id = tab_id + 1;

				
			}

			if (search == 2) {  //processo semenhante ao do caso acima sem a criacao da nova tab
				do {
					cout << "Insira o id da tab a executar: \n";
					cin >> search_id;
				} while ((search_id > size(state)-1) and (state[search_id]==0));
				

				cout << "Insira o endereco do site a visitar: \n";
				cin >> webAddress;
				cout << "Insira o nome do ficheiro onde ira guardar o html \n";
				cin >> szFileName;
				if (fileExists(szFileName)) {
					remove(szFileName);
				}
				state[search_id] = 1; // mudar estado para 1---> running de modo a entrar no while de execucao da pesquisa
				
	
				while (state[search_id] == 1) {
					Sleep(100);
					time_count = time_count + 1;
					if (time_count == 10) {
						state[search_id] = 0;
						break;
					}
						
				}

				if (hr == -2146697203)
					cout << "Erro URL desconhecido" << endl;

				else {
					cout << "Informacoes do ficheiro guardado" << endl;
					cout << "ID= " << tab_id << "\t URL=" << webAddress;
					cout << "\t Nome de arquivo salvo= " << szFileName << "\t Tamanho=";

					cout << filesize(szFileName) << endl;
				}

					
				
			}
		}

		if (menu == 2) {
			int tot_run = 0;
			cout << "Lista de tabs a correr \n";
			for (int i = 0; i < vecOfThreads.size(); i++)
			{
				if (state[i] != -1)
				{
					cout << i << endl;
					tot_run = tot_run + 1;
				}
				
			}
			if (tot_run > 0) {
				do {
					cout << "Selecione a tab a fechar \n";
					cin >> close;

					if (close > tot_run-1) {
						cout << "Por favor insira uma tab valida" << endl;
					}
					else
						state[close] = -1; // muda-se o estado da thread para -1 de modo a que esta saia do ciclo infinito onde se encontra, termine a sua execucao e liberte os seus recursos

				} while (close > tot_run-1);

			}
			else
				cout << "Nao exite tabs para fechar" << endl;
		}
			

		if (menu == 3) {
			cout << "---------------------------------------- \n";
			cout << "|       Lista de tabs                  | \n";
			cout << "---------------------------------------- \n";

			for (int i = 0; i < vecOfThreads.size(); i++) {
				if (state[i] != -1) {
					cout << "| \t ID=" << i;
					if (state[i] == 1) {
						cout << "\t estado= Processando URL\n";
					}
					
					if (state[i] == 0) {
						cout << "\t estado= Esperando URL | \n";
					}
				}
				 
			}

			cout << "---------------------------------------- \n";
		}


	} while (menu != 4);

	for (int i = 0; i < vecOfThreads.size(); i++) {
		state[i] = -1;
	}
		
	for (std::thread & th : vecOfThreads)
	{
		if (th.joinable())
			th.join();
	}
	

	return 0;
}

