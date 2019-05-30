#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>


using namespace std;

int main(){
    int linhas, colunas, nPalavras, i=0, n=4, m=3, max_char=14;
    FILE * arquivo;
    char info[n][n];
    char palavras[m][max_char];
	//Abre o arquivo no modo "leitura" (read)
    arquivo = fopen("epdoc.txt", "r");
    //Checa se o arquivo existe
    if(arquivo != NULL){
        //Coleta as informacoes do arquivo seguindo esse padrao
    	fscanf(arquivo, "%d %d %d\n", &linhas, &colunas, &nPalavras);//1a linha com inteiros
	}
	//Coleta o caca palavras e salva na matriz
	for(int j = 0; j < 3; j++){
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
	//le palavras
	int l = 0;
	char temp[max_char];
	while (fgets(temp, sizeof temp, arquivo) != NULL) {
		if(strcmp(temp, "\n")==0){continue;}
		else{
			strcpy(palavras[l],temp);
			l++;	
		}
	}
    //Imprime o string de characters e o 3o numero do arquivo
    for(int j = 0; j < 3; j++){
		for(int k = 0; k <n; k++){
    		cout << info[j][k];
		}
		cout << "\n";
	}
	//Imprime palavras
	for(int i = 0; i<3 ; i++){
		cout << palavras[i];
	}
	printf("\n%d", nPalavras);
    //Finaliza o programa
    return 0;
}
