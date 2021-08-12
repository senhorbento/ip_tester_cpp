#include <iostream>
#include <fstream>
#include <list>
#include <cstdio>
#include <cstring>
#include <regex>

using namespace std;

bool ligado(string arq){
	bool aux;
	string leitura, inativo;
	list <string> resultado;
	ifstream input_file(arq);
	inativo="Host de destino inacess";

    while(getline(input_file, leitura)){
        resultado.push_back(leitura);
    };
	input_file.close();

	for(auto confere : resultado) if(strstr(confere.c_str(),inativo.c_str()) > 0) return aux=0;

	return aux=1;
}

string obterIP(string s){
		string lista[20];
		char ip[20];
		smatch m;
		regex e ("[_]([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5]){1,3}(\\.([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5]){1,3}){3}");
		int qtd, i;
		qtd=0;

		while(regex_search (s,m,e)){
			for(auto x:m){
				lista[qtd]=x;
				qtd++;
			} 
			s = m.suffix().str();
		}
		strcpy(ip, lista[0].c_str());
		for(i=0;i<strlen(ip);i++) ip[i]=ip[i+1];
	
		return ip;

}

int main(){
	int qtd;
	bool removido;
	string leitura,teste, abrir, entrada, saida,ip;
	list <string> lista, ligados;
	qtd=-1; entrada = "lista.txt"; saida = "resultado.txt";
	ifstream input_file(entrada);
	ofstream output_file;

	system("cls");
	while(qtd!=0){
		qtd=1; removido=0;
		while(getline(input_file, leitura)){
			lista.push_back(leitura);
		};
		input_file.close();

		for(auto linha : lista){
			ip=obterIP(linha);
			teste="ping -n 1 -i 150 " + ip + " > " + saida;
			system(teste.c_str());
			if(ligado(saida)){
				abrir="\"C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe\" " + ip;
				system(abrir.c_str());
				ligados.push_back(ip);
				removido=1;
			}
			qtd++;
		}

		if (removido){
			for(auto ip : ligados) lista.remove(ip);
			system("del lista.txt && del resultado.txt");
			output_file.open(entrada);
			for(auto ip : lista) output_file << ip << endl;
			output_file.close();
			ligados.clear();
		}
		system("pause");
		cout << "A lista foi pesquisada " << n << " vezes" << endl;
	}

	return 0;
}
