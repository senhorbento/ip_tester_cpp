#include <iostream>
#include <fstream>
#include <list>
#include <cstdio>
#include <cstring>
#include <regex>

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
	case 1: cout << endl << "Pressione uma tecla para remover da lista e continuar!" << endl; getchar(); break;
	case 2: cout << endl << "Pressione uma tecla para finalizar o programa!" << endl; getchar(); break;
	case 3: cout << endl << "Finalizando o programa devido ao erro!" << endl; getchar(); break;
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

int main() {
	int qtd, n;
	bool removido;
	string leitura, ip;
	list <string> lista, ligados, ignore;
	ifstream input_file;
	ofstream output_file;

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
				cout << "Foi encontrado um erro no elemento de posição " << n << ", favor verificar a lista = )" << endl << endl;
				qtd = -1;
				break;
			}
			else {
				cout << n << ". Testando o ip " << ip << endl;
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
		Remover(_ENTRADA_);
		cout << "Fim de lista!" << endl;
		Pause(2);
	}
	return 0;
}
