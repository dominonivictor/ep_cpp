#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>


using namespace std;

int main(){
    
    int linhas, colunas, nPalavras, i=0, n=4;
    FILE * arquivo;
    char info[n][n];
    
	//Abre o arquivo no modo "leitura" (read)
    arquivo = fopen("epdoc.txt", "r");
    //Checa se o arquivo existe
    if(arquivo != NULL){
        //Coleta as informações do arquivo seguindo esse padrao
    	fscanf(arquivo, "%d %d %d\n", &linhas, &colunas, &nPalavras);//1a linha com inteiros
	}
	for(int j = 0; j < n; j++){
		for(int k = 0; k <n; k++){
			char st;
			if(k==n-1){
				fscanf(arquivo, "%c\n", &st);
			}else{
				fscanf(arquivo, "%c", &st);	
			}
			info[j][k] = st;
		}
	}
    //Imprime o string de characters e o 3o numero do arquivo
    for(int j = 0; j < n; j++){
		for(int k = 0; k <n; k++){
    		cout << info[j][k];
		}
		cout << "\n";
	}
	
	printf("\n%d", nPalavras);
    //Finaliza o programa
    return 0;
}
