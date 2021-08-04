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
	ip="192.168.88.1";

    while(getline(input_file, leitura)){
        resultado.push_back(leitura);
    };

	for(auto confere : resultado){
		if(strstr(confere.c_str(),ip.c_str()) > 0) return aux=1;
	}

	return aux=0;
}

int main(){
	string leitura, teste, abrir, entrada = "lista.txt", saida = "resultado.txt";
	list <string> lista;
	ifstream input_file(entrada);
	ofstream output_file;

    while(getline(input_file, leitura)){
        lista.push_back(leitura);
    };
	for(auto ip : lista){
		teste="ping -n 1 -i 150 " + ip + " > " + saida;
		cout << teste << endl;
        system(teste.c_str());
		if(ligado(saida)==1){
			abrir="\"C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe\" " + ip;
			system(abrir.c_str());
			lista.remove();
		}
    }

	/*if (removido > 0){
		system("rm lista.txt");
		output_file.open(entrada);
		for(auto ip : lista)
				output_file << ip << endl;
		output_file.close();
	}*/

	return 0;
}