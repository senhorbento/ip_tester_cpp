#include <iostream>
#include <fstream>
#include <list>
#include <cstdio>
#include <cstring>
#include <regex>
#include <sys/stat.h>

using namespace std;

#define _ENTRADA_ "txt\\lista.txt"
#define _SAIDA_ "txt\\resultado.txt"
#define _IGNORE_ "txt\\ignore.txt"

bool ligado(string arq) {
	bool aux;
	string leitura, inativo, inacess, EnInacess, EnInativo;
	list <string> resultado;
	ifstream input_file(arq);
	inacess = "Host de destino inacess";
	inativo = "Esgotado o tempo limite do pedido.";
	EnInacess = "Destination host unreachable.";
	EnInativo = "Request timed out.";

	while (getline(input_file, leitura)) {
		resultado.push_back(leitura);
	};
	input_file.close();

	for (auto confere : resultado)
		if (strstr(confere.c_str(), EnInativo.c_str()) > 0 || strstr(confere.c_str(), EnInacess.c_str()) > 0 ||
			strstr(confere.c_str(), inativo.c_str()) > 0 || strstr(confere.c_str(), inacess.c_str()) > 0)
			return aux = 0;

	return aux = 1;
}

string obterIP(string s, list <string> ignorar) {
	int qtd, i, positive;
	string lista[20];
	smatch m;
	regex e("([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5]){1,3}(\\.([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5]){1,3}){3}");
	qtd = 0;

	while (regex_search(s, m, e)) {
		for (auto x : m) {
			lista[qtd] = x;
			qtd++;
		}
		s = m.suffix().str();
	}
	for (i = 0; i < qtd; i++)
		if (strlen(lista[i].c_str()) > 6) {
			positive = -1;
			for (auto ignore : ignorar)
				if (lista[i] == ignore) positive++;

			if (positive < 0)
				return lista[i];
		}
	return "ERROR";
}

void LimparTela() {
	system("cls");
}

void Pause(int v) {
	switch (v) {
	case 1: cout << endl << "Ip Ativo!" << endl << "Pressione uma tecla para remover da lista e continuar!\n"; getchar(); break;
	case 2: cout << "Lista Finalizada!" << endl << "Pressione uma tecla para finalizar o programa!\n"; getchar(); break;
	case 3: cout << endl << "Finalizando o programa devido ao erro!" << endl; getchar(); break;
	case 4: cout << "Parece que voce esta executando o programa pela primeira vez.\n"
	             << "Acesse a pasta txt e siga as instrucoes dentro de cada arquivo =\)\n\n"
				 << "Pressione uma tecla para finalizar o programa e abrir a pasta!\n"; getchar(); break;
	case 5: cout << "Nao foi encontrado o arquivo ignore.txt\n"
				 << "Criando o arquivo ignore.txt...\n\n" << "Pressione uma tecla para continuar a execucao\n"; getchar(); break;
	}
}

void Remover(string v) {
	string arquivo;
	arquivo = "del " + v;
	system(arquivo.c_str());
}

void Pingar(string ip, string saida) {
	string ping;
	ping = "ping -n 1 -i 150 " + ip + " > " + saida;
	system(ping.c_str());
}

void Abrir(string ip) {
	string abrir;
	abrir = "start chrome " + ip;
	system(abrir.c_str());
}


int ExisteArquivo(const char* filename){
    struct stat buffer;
    int exist = stat(filename, &buffer);
    return exist;
}

void CriarArquivo(string txt){
	string texto;
	if(txt == _ENTRADA_){
		texto = "echo \/\/Remova essas linhas e coloque os enderecos a serem testados aqui =\) > " + txt;
		system(texto.c_str());
		texto = "echo \/\/Remove those lines and put the addresses to be tested here =\) >> " + txt;
		system(texto.c_str());
	}
	else if(txt == _IGNORE_){
		texto = "echo \/\/Remova essas linhas e coloque os enderecos a serem ignorados aqui =\( > " + txt;
		system(texto.c_str());
		texto = "echo \/\/Remove those lines and put the addresses to be ignored here =\( >> " + txt;
		system(texto.c_str());
	}

}

int main() {
	int qtd, n;
	bool removido;
	string leitura, ip;
	list <string> lista, ligados, ignore;
	ifstream input_file;
	ofstream output_file;

	if(ExisteArquivo(_ENTRADA_) == -1 && ExisteArquivo(_IGNORE_) == -1){
		system("mkdir txt");
		CriarArquivo(_ENTRADA_);
		CriarArquivo(_IGNORE_);
		LimparTela(); 
		Pause(4);
		system("explorer.exe /e, /n, txt");
		return EXIT_FAILURE;
	}

	if(!ExisteArquivo(_IGNORE_)){
		input_file.open(_IGNORE_);
		if (input_file.is_open()) {
			while (!input_file.eof()) {
				getline(input_file, leitura);
				if (leitura != "\0") {
					ignore.push_back(leitura);
				}
			}
			input_file.close();
		}
	}
	else {
		LimparTela();
		CriarArquivo(_IGNORE_);
		Pause(5);
	}

	LimparTela();
	do {
		n = 0; qtd = 0; removido = 0;

		input_file.open(_ENTRADA_);
		if (input_file.is_open()) {
			while (!input_file.eof()) {
				getline(input_file, leitura);
				if (leitura != "\0") {
					lista.push_back(leitura);
					qtd++;
				}
			}
			input_file.close();
		}

		for (auto linha : lista) {
			n++;
			ip = obterIP(linha, ignore);
			if (ip == "ERROR") {
				cout << "Nao foram encontrados ips na linha " << n << ", favor verificar a lista =)\n";
				qtd = -1;
				break;
			}
			else {
				cout << "Testando o ip " << ip << endl << n << "/" << qtd << endl;
				Pingar(ip, _SAIDA_);
				if (ligado(_SAIDA_)) {
					Abrir(ip);
					ligados.push_back(linha);
					removido = 1;
					qtd--;
					Pause(1);
					LimparTela();
					break;
				}
				LimparTela();
			}
		}

		if (removido) {
			for (auto linha : ligados) lista.remove(linha);
			Remover(_ENTRADA_);
			Remover(_SAIDA_);
			output_file.open(_ENTRADA_);
			for (auto linha : lista) output_file << linha << endl;
			output_file.close();
			ligados.clear();
		}
		lista.clear();
	} while (qtd > 0);

	if (qtd == -1)
		Pause(3);
	else {
		LimparTela();
		CriarArquivo(_ENTRADA_);
		Pause(2);
	}
	return 0;
}
