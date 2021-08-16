#include <iostream>
#include <fstream>
#include <list>
#include <cstdio>
#include <cstring>
#include <regex>

using namespace std;

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
		if (strlen(lista[i].c_str()) > 7){
			positive = -1;
			for(auto ignore : ignorar){
				if (ignore != "\0" && lista[i] == ignore) positive++;
			}
			if(positive < 0)
				return lista[i];
		}
}

void LimparTela() {
	system("cls");
}

void Pause(int v) {
	char a;
	switch (v) {
	case 1: cout << endl << "Pressione uma tecla para remover da lista e continuar!" << endl; a = getchar(); break;
	case 2: cout << endl << "Pressione uma tecla para finalizar o programa!" << endl; a = getchar(); break;
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
	string leitura, entrada, saida, ignorar, ip;
	list <string> lista, ligados, ignore;
	entrada = "txt\\lista.txt"; saida = "txt\\resultado.txt"; ignorar ="txt\\ignore.txt";
	ifstream input_file;
	ofstream output_file;

	input_file.open(ignorar);
	if (input_file.is_open()) {
		while (!input_file.eof()) {
			getline(input_file, leitura);
			if (leitura != "\0") {
				ignore.push_back(leitura);
				qtd++;
			}
		}
		input_file.close();
	}

	LimparTela();
	do {
		n = 0; qtd = 0; removido = 0;

		input_file.open(entrada);
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
			cout << n << ". Testando o ip " << ip << endl;
			Pingar(ip, saida);
			if (ligado(saida)) {
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

		if (removido) {
			for (auto linha : ligados) lista.remove(linha);
			Remover(entrada);
			Remover(saida);
			output_file.open(entrada);
			for (auto linha : lista) output_file << linha << endl;
			output_file.close();
			ligados.clear();
		}
		lista.clear();
	} while (qtd != 0);
	LimparTela();
	Remover(entrada);
	cout << "Fim de lista!" << endl;
	Pause(2);
	return 0;
}
