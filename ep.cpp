#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>


using namespace std;

int main(){
	//Inicializando as variaveis
    int linhas, colunas, nPalavras, max_char=14;
    FILE * arquivo;
    char nomeArquivo[20] = "epdoc.txt";
    cout << "Insira o nome do arquivo completo (com .txt) caça palavras (note qe o arquivo deve estar com a formatação adequada):\n";
    cin >> nomeArquivo;
	//Abre o arquivo no modo "leitura" (read)
    arquivo = fopen(nomeArquivo, "r");
    //Checa se o arquivo existe
    if(arquivo == NULL){
        cout << "Não foi possivel carregar o arquivo,  cheque se o nome e o arquivo estão corretos";
        return 0;
	}else{
		//Coleta as informacoes do arquivo seguindo esse padrao
    	fscanf(arquivo, "%d %d %d\n", &linhas, &colunas, &nPalavras);//1a linha com inteiros	
	}
	char info[linhas][colunas];
    char palavras[nPalavras][max_char];
    
	//Coleta o caca palavras e salva na matriz
	for(int j = 0; j < linhas; j++){
		for(int k = 0; k < colunas; k++){
			char st;
			if(k==colunas-1){
				fscanf(arquivo, "%c\n", &st);
			}else{
				fscanf(arquivo, "%c", &st);	
			}
			info[j][k] = st;
		}
	}
	//le palavras
	int i = 0;
	char temp[max_char];
	do { //le a linha de palavras e salva em temp
		fgets(temp, sizeof (temp), arquivo);
		strcpy(palavras[i],temp); // LEMBRE QE O PALAVRAS[i] é salvo com o "\n" no final!
		i++;
	}while (i < nPalavras);
	//Imprime a matriz (info) devidamente, com os numeros e com a formatação adequada
	for(int j = 0; j < linhas + 2; j++) {
		cout << "\t\t\t\t";
        for(int k = 0; k < colunas + 2; k++) {
        	//Imprime numeros na 1a ou ultima linha
            if(j == 0 || j == linhas + 1){
				if(k == 0) {//se for o elemento 0,0 ou linha -1, 0
				    cout << "  ";
				} else if (k == colunas + 1) {//se for o elemento (0, coluna - 1) ou (linha - 1, coluna - 1)
				    cout << " " << endl;
				} else{
				    cout << k - 1 << " ";
				}
				} else if(k == 0) {//se for a 1a coluna
					cout << j - 1 << " ";
				} else if(k == colunas + 1) {//se for a ultima coluna
					cout << j - 1 << endl;
				} else { //se nao for nenhuma das anteriores, então imprimiremos a matriz
				   cout << info[j-1][k-1] << " ";
               }       
		}  
    }    
    
	
	
    /*Imprime o string de characters e o 3o numero do arquivo
    for(int j = 0; j < linhas; j++){
		for(int k = 0; k < colunas; k++){
    		cout << info[j][k] << " " << j << ", " << k << "\n";
		}
		cout << "\n";
	}
	//Imprime palavras
	for(int i = 0; i<nPalavras ; i++){
		cout << palavras[i];
	}
	printf("\n%d", nPalavras);
    //Finaliza o programa
    */
	return 0;
}
