#include <iostream>
#include <fstream>
#include <list>
#include <cstdio>
#include <cstring>

using namespace std;

bool ligado(string arq){
	bool aux;
	string leitura, ip;
	list <string> resultado;
	ifstream input_file(arq);
	ip="Host de destino inacess";

    while(getline(input_file, leitura)){
        resultado.push_back(leitura);
    };
	input_file.close();

	for(auto confere : resultado){
		if(strstr(confere.c_str(),ip.c_str()) > 0) return aux=0;
	}

	return aux=1;
}

int main(){
	bool removido;
	string leitura,teste, abrir, entrada, saida;
	list <string> lista, ligados;
	removido=0;entrada = "lista.txt";saida = "resultado.txt";
	ifstream input_file(entrada);
	ofstream output_file;

	while(getline(input_file, leitura)){
        lista.push_back(leitura);
    };
	input_file.close();

	for(auto ip : lista){
		teste="ping -n 1 -i 150 " + ip + " > " + saida;
		cout << "Pingando para " << ip;
        system(teste.c_str());
		if(ligado(saida)){
			cout << " - Ligado!" << endl;
			abrir="\"C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe\" " + ip;
			system(abrir.c_str());
			ligados.push_back(ip);
			removido=1;
		}
		else cout << " - Desligado!" << endl;
    }

	if (removido){
		for(auto ip : ligados)
		lista.remove(ip);
		ligados.clear();
		system("del /f lista.txt");
		output_file.open(entrada);
		for(auto ip : lista)
				output_file << ip << endl;
		output_file.close();
	}

	return 0;
}
