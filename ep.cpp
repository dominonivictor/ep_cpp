#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>


using namespace std;

int main(){
    
    int linhas, colunas, nPalavras, i=0, n=6;
    FILE * arquivo;
    char info1[n], info2[n], info3[n];
    
	//Abre o arquivo no modo "leitura" (read)
    arquivo = fopen("epdoc.txt", "r");
    //Checa se o arquivo existe
    if(arquivo != NULL){
        //Coleta as informações do arquivo seguindo esse padrao
    	fscanf(arquivo, "%d %d %d\n", &linhas, &colunas, &nPalavras);//1a linha com inteiros
    	fscanf(arquivo, "%s\n%s\n%s", info1, info2, info3);//2a, 3a e 4a linha com strings
    	fclose(arquivo);	
	}
    //Imprime o string de characters e o 3o numero do arquivo
	cout << info1 << "\n" << info2 << "\n" << info3;
	printf("\n%d", nPalavras);
    //Finaliza o programa
    return 0;
}
