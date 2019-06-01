#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>

//definindo constantes
#define MAX_CHAR 18
#define MAX_PAL 10
#define MAX_MAT 30

//Inicializando variaveis
int linhas, colunas, nPalavras;
char matriz[MAX_MAT][MAX_MAT], palavras[MAX_PAL][MAX_CHAR];
bool deuErro = false;

using namespace std;

void leDoc(){
	//Inicializando as variaveis
    char nomeArquivo[20];
    FILE* arquivo;
    cout << "Insira o nome do arquivo completo (com .txt) do caça palavras (note qe o arquivo deve estar com a formatacao adequada, indicado no arquivo READ.ME):\n";
    cin >> nomeArquivo;
	//Abre o arquivo no modo "leitura" (read)
    arquivo = fopen(nomeArquivo, "r");
    //Checa se o arquivo existe
    if(arquivo == NULL){
        cout << "Não foi possivel carregar o arquivo,  cheque se o nome e o arquivo estão corretos";
	}else{
		//Coleta as informacoes do arquivo seguindo esse padrao
    	fscanf(arquivo, "%d %d %d\n", &linhas, &colunas, &nPalavras);//1a linha com inteiros	
		//Coleta o caca palavras e salva na matriz
		for(int j = 0; j < linhas; j++){
			for(int k = 0; k < colunas; k++){
				char st;
				if(k==colunas-1){
					fscanf(arquivo, "%c\n", &st);
				}else{
					fscanf(arquivo, "%c", &st);	
				}
				matriz[j][k] = st;
			}
		}
		//le palavras
		int i = 0;
		char temp[MAX_CHAR];
		do { //le a linha de palavras e salva em temp
			fgets(temp, sizeof (temp), arquivo);
			strcpy(palavras[i],temp); // LEMBRE QE O PALAVRAS[i] é salvo com o "\n" no final!
			i++;
		}while (i < nPalavras);
		fclose(arquivo);
	}
}

void imprime(){
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
				   cout << matriz[j-1][k-1] << " ";
               }       
		}  
    } 
}

int main(){
	//Le o documento e salva toda sua informação
	leDoc();
	//Imprime a matriz (info) devidamente, com os numeros e com a formatação adequada
	imprime();   
    
	return 0;
}
