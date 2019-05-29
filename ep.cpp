#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>


using namespace std;

int main(){
    
    int linhas, colunas, nPalavras, i=0;
    char info[10];
    FILE * arquivo;
    
    //Abre um arquivo no modo "escrever" (write)
    arquivo = fopen("epdoc.txt", "w");
    //Checa se o arquivo existe mesmo (talvez seja redundate visto qe o fopen cria o arquivo caso nao exista)
    if(arquivo != NULL){
        //Adiciona o texto abaixo no arquivo
        fputs("3 2 1 \nabc", arquivo);
        fclose(arquivo);
    }
    //Abre o arquivo novamente, porém no modo "leitura" (read)
    arquivo = fopen("epdoc.txt", "r");
    //Checa se o arquivo existe
    if(arquivo != NULL){
        //Coleta as informações do arquivo seguindo esse padrao
    	fscanf(arquivo, "%d %d %d\n%s", &linhas, &colunas, &nPalavras, info);
    	fclose(arquivo);	
	}
    //Imprime o string de characters e o 3o numero do arquivo
	printf(info);
	printf("\n%d", nPalavras);
    //Finaliza o programa
    return 0;
}
