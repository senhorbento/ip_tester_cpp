#include <iostream>
#include <fstream>
#include <list>
#include <cstdio>
#include <cstring>
#include <regex>

using namespace std;

bool ligado(string arq) {
	bool aux;
	string leitura, inativo;
	list <string> resultado;
	ifstream input_file(arq);
	inativo = "Host de destino inacess";

	while (getline(input_file, leitura)) {
		resultado.push_back(leitura);
	};
	input_file.close();

	for (auto confere : resultado)
		if (strstr(confere.c_str(), inativo.c_str()) > 0)
			return aux = 0;

	return aux = 1;
}

string obterIP(string s) {
	int qtd, i;
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
	for(i = 0; i < qtd; i++)
		if (strlen(lista[i].c_str()) > 7)
			if (lista[i] != "172.16.0.2" &&
				lista[i] != "172.16.8.2" &&
				lista[i] != "172.16.16.2" &&
				lista[i] != "172.16.24.2" &&
				lista[i] != "172.16.32.2" &&
				lista[i] != "172.16.40.2" &&
				lista[i] != "172.16.48.2" &&
				lista[i] != "172.16.56.2" &&
				lista[i] != "172.16.64.2" &&
				lista[i] != "172.16.72.2" &&
				lista[i] != "172.16.80.2" &&
				lista[i] != "172.16.88.2" &&
				lista[i] != "172.16.96.2" &&
				lista[i] != "172.16.104.2" &&
				lista[i] != "172.16.112.2" &&
				lista[i] != "172.16.120.2" &&
				lista[i] != "172.16.128.2" &&
				lista[i] != "172.16.136.2" &&
				lista[i] != "172.16.144.2" &&
				lista[i] != "172.16.152.2" &&
				lista[i] != "172.16.160.2") 
					return lista[i];

}

void LimparTela() {
	system("cls");
}

void Pause(int v){
	char a;
	switch (v) {
	case 1: cout << endl << "Pressione uma tecla para remover da lista e continuar!" << endl; a = getchar(); break;
	case 2: cout << endl << "Pressione uma tecla para finalizar o programa!" << endl; a = getchar(); break;
	}
}

int main() {
	int qtd, n;
	bool removido;
	string leitura, teste, abrir, entrada, saida, ip;
	list <string> lista, ligados;
	n = 0; entrada = "lista.txt"; saida = "resultado.txt";
	ifstream input_file(entrada);
	ofstream output_file;

	LimparTela();
	do {
		qtd = 0; removido = 0; n++;
		while (getline(input_file, leitura)) {
			lista.push_back(leitura);
			qtd++;
		};
		input_file.close();

		for (auto linha : lista) {
			ip = obterIP(linha);
			cout << "Testando o ip " << ip << endl;
			teste = "ping -n 1 -i 150 " + ip + " > " + saida;
			system(teste.c_str());
			if (ligado(saida)) {
				abrir = "start chrome " + ip;
				system(abrir.c_str());
				ligados.push_back(linha);
				removido = 1;
				qtd--;
				Pause(1);
				LimparTela();
				break;
			}
		}

		if (removido) {
			for (auto linha : ligados) lista.remove(linha);
			system("del lista.txt && del resultado.txt");
			output_file.open(entrada);
			for (auto linha : lista) output_file << linha << endl;
			output_file.close();
			ligados.clear();
		}
	} while (qtd > 0);
	LimparTela();
	cout << "Fim de lista!" << endl;
	Pause(2);

	return 0;
}
