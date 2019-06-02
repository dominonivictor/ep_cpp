#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
#include <windows.h>

//definindo constantes
#define MAX_CHAR 18
#define MAX_PAL 10
#define MAX_MAT 30
#define AZUL 9
#define VERMELHO 12
#define VERDE 10
#define BRANCO 15
#define AMARELO 6
#define ROXO 13
#define CINZA 8
#define BEGE 14

typedef struct posicoes_do_selecionado{
	int x = 0;
	int y = 0;
	int tam = 1;
} Posi;

//ESSE STRUCT SERVIRA PARA GUARDAR AS POSIÇOES DAS PALAVRAS QUE JA FORAM ACERTADAS PARA POSTERIORMENTE MARCA-LAS COM COR DIFERENTE
//O ULTIMO INDICE sera um lugar temporario para, caso a palavra selecionada estiver na lista de palavras, ele irá salvar permanentemente as posições
// x, y no mesmo indice da palavra escolhida, para melhor organização
Posi pos[MAX_PAL][MAX_CHAR];

typedef struct variaveis_da_marca{
	int x = 1;
	int y = 1;
	int tam = 2;
	int dir = 6;
} marcaVars;

//teste
marcaVars vars;

//Inicializando variaveis globais
int comando, linhas, colunas, nPalavras, resultado = -1, acertadas = 0, t;
char matriz[MAX_MAT][MAX_MAT], palavras[MAX_PAL][MAX_CHAR], selecionado[MAX_CHAR];
bool terminou = false, leu = false, gameLoop = true;
char escolha;

using namespace std;

void debuga(){
	cout << "Insira o index da palavra acertada";
	cin >> t;
	for (int i = 0; i < pos[t][0].tam; i++){
		cout << "pos[0]["<<i<<"].x , pos[0]["<<i<<"].y= " << pos[t][i].x << ", " << pos[t][i].y; 
 }
}

void troca_cor(int cor){
	//Muda a cor do char impresso
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cor);
}

bool eh_igual(char pal[]){
	//Checa se a palavra (da matriz de palavras) é igual a char* selecionado
	for (int i = 0; i<vars.tam ; i++){
		if(pal[i]!=selecionado[i]){
			return false;
		}
	}
	return true;
}

int checa_palavras(){
	//Passa por todas as palavras restantes e checa se é igual a palavra selecionada, adiciona as variaveis da posição no primeiro elemento disponivel no 
	//array pos para serem marcados dps
	for(int i = 0; i < nPalavras; i++){
		if(eh_igual(palavras[i])){
			for(int p = 0; p < vars.tam; p++){
				pos[acertadas][p].x = pos[MAX_PAL-1][p].x;
				pos[acertadas][p].y = pos[MAX_PAL-1][p].y;
			}
			pos[acertadas][0].tam = pos[MAX_PAL][0].tam;
			acertadas++;
			return i;
		}
	}
	return -1;
}

void elimina_palavra(){
	if(leu){
		for (int i = resultado; i < nPalavras; ++i){
			memcpy(palavras[i], palavras[i + 1], MAX_CHAR+1);
		}
		nPalavras--;
	}
}

void junta_chars(){
	if(leu){
		int m, n;
		//Junta as letras selecionadas em um char para comparação
		if (vars.dir == 2){//esquerda para direita
			for(int i=0; i<vars.tam ;i++){
				m = vars.x+i;
				n = vars.y;
				selecionado[i] = matriz[m][n];
				pos[MAX_PAL-1][i].x = m;
				pos[MAX_PAL-1][i].y = n;	
			}
		}else if (vars.dir == 8){//direita para esquerda
			for(int i=0; i<vars.tam ;i++){
				m = vars.x-i;
				n = vars.y;
				selecionado[i] = matriz[m][n];
				pos[MAX_PAL-1][i].x = m;
				pos[MAX_PAL-1][i].y = n;	
			}
		}else if (vars.dir == 6){//cima para baixo
			for(int i=0; i<vars.tam ;i++){
				m = vars.x;
				n = vars.y+i;
				selecionado[i] = matriz[m][n];
				pos[MAX_PAL-1][i].x = m;
				pos[MAX_PAL-1][i].y = n;	
			}
		}else if (vars.dir == 4){//baixo para cima
			for(int i=0; i<vars.tam ;i++){
				m = vars.x;
				n = vars.y-i;
				selecionado[i] = matriz[m][n];
				pos[MAX_PAL-1][i].x = m;
				pos[MAX_PAL-1][i].y = n;	
			}
		}else if (vars.dir == 1){//diag baixo para cima, esquerda para direita
			for(int i=0; i<vars.tam ;i++){
				m = vars.x+i;
				n = vars.y-i;
				selecionado[i] = matriz[m][n];
				pos[MAX_PAL-1][i].x = m;
				pos[MAX_PAL-1][i].y = n;	
			}
		}else if (vars.dir == 7){//diag baixo para cima, direita para esquerda
			for(int i=0; i<vars.tam ;i++){
				m = vars.x-i;
				n = vars.y-i;
				selecionado[i] = matriz[m][n];
				pos[MAX_PAL-1][i].x = m;
				pos[MAX_PAL-1][i].y = n;	
			}
		}else if (vars.dir == 3){//diag cima para baixo, esquerda para direita
			for(int i=0; i<vars.tam ;i++){
				m = vars.x+i;
				n = vars.y+i;
				selecionado[i] = matriz[m][n];
				pos[MAX_PAL-1][i].x = m;
				pos[MAX_PAL-1][i].y = n;	
			}
		}else if (vars.dir == 9){//diag cima para baixo, direita para esquerda
			for(int i=0; i<vars.tam ;i++){
				m = vars.x-i;
				n = vars.y+i;
				selecionado[i] = matriz[m][n];
				pos[MAX_PAL-1][i].x = m;
				pos[MAX_PAL-1][i].y = n;	
			}
		}
		pos[MAX_PAL-1][0].tam=vars.tam;
		selecionado[vars.tam]='\0'; //finaliza o string
	}
}

void le_doc(){
	if(leu){
		cout << "Tem certeza que deseja carrega um novo arquivo (Isso irá apagar o progresso do caca palavras atual)?\nS/N:";
		cin >> escolha;
		if(char(tolower(escolha))=='s'){
			leu = false;
			le_doc();
		}else if(char(tolower(escolha))=='n'){
			return;
		}else{
			troca_cor(VERMELHO);
			cout << "Comando invalido, por favor digite \'s\' ou \'n\' da proxima vez!\n";
			troca_cor(BRANCO);
			return;
		}	
	}else{
		//Inicializando as variaveis do arquivo
	    char nomeArquivo[30];
	    FILE* arquivo;
	    troca_cor(AMARELO);
	    cout << "Insira o nome do arquivo completo (com .txt) do caça palavras (note qe o arquivo deve estar com a formatacao adequada):\n";
	    troca_cor(BRANCO);
		cin >> nomeArquivo;
		//Abre o arquivo no modo "leitura" (read)
	    arquivo = fopen(nomeArquivo, "r");
	    //Checa se o arquivo existe
	    if(arquivo == NULL){
	    	troca_cor(VERMELHO);
	        cout << "Não foi possivel carregar o arquivo,  cheque se o nome e o arquivo estão corretos\n";
			troca_cor(BRANCO);
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
			leu = true;
		}
	}
}

void imprime(){
	troca_cor(AZUL);
	if(leu){
		for(int j = 0; j < linhas + 2; j++) {
			cout << "\t\t\t\t\t\t";
	        for(int k = 0; k < colunas + 2; k++) {
	        	//Imprime numeros na 1a ou ultima linha
	            if(j == 0 || j == linhas + 1){
					if(k == 0) {//se for o elemento 0,0 ou linha -1, 0
					    cout << "  ";
					} else if (k == colunas + 1) {//se for o elemento (0, coluna - 1) ou (linha - 1, coluna - 1)
					    cout << " " << endl;
					} else{
						if(k>10){
							cout << k - 11 << " ";
						}else{
							cout << k - 1 << " ";	
						}
					}
				} else if(k == 0) {//se for a 1a coluna
					if(j>10){
						cout << j - 11 << " ";
					}else{
						cout << j - 1 << " ";	
					}
				} else if(k == colunas + 1) {//se for a ultima coluna
					if(j>10){
						cout << j - 11 << endl;
					}else{
						cout << j - 1 << endl;	
					}
				} else { //se nao for nenhuma das anteriores, então imprimiremos a matriz
					if(acertadas>0){//se houverem palavras acertadas
						for(int p = 0; p < acertadas; p++){//checa todas as palavras acertadas e suas posições, se x e y forem 
							for(int q = 0; q < pos[p][0].tam ; q++){
								if((j-1==pos[p][q].x) && (k-1==pos[p][q].y)){//imprime apenas se 
									troca_cor(VERDE);
									cout << matriz[j-1][k-1] << " ";
				   					troca_cor(AZUL);
				   					goto prox;
								}
							}
					   }
					   goto continuar;
				   }else{
				   		continuar:;
						troca_cor(BRANCO);
						cout << matriz[j-1][k-1] << " ";
						troca_cor(AZUL);
				   }
				   prox:;
               }       
			}  
			
	    }
	    //Imprimir palavras que faltam
	    cout<< "Palavras restantes:\n";
	    for(int p = 0; p < nPalavras; p++){
	    	cout << palavras[p];
		}
	}else{
		troca_cor(VERMELHO);
		cout << "Primeiro carregue seu caca palavras com o comando 1 (carrega).\n";
		troca_cor(BRANCO);
	}
	troca_cor(BRANCO);
}

void marca(){
	if(leu){
		cout << "Insira as coordenadas x, y da primeira letra, o tamanho da palavra e a direção seguindo o seguinte padrao: ";
		troca_cor(VERDE);
		cout << "\nX Y TAMANHO DIRECAO";
		troca_cor(AMARELO);
		cout << "\nDIAGONAIS:\
		\n1 - diag cima para baixo, direita para esquerda\
		\n7 - diag baixo para cima, direita para esquerda\
		\n9 - diag baixo para cima, esquerda para direita\
		\n3 - diag cima para baixo, esquerda para direita\
		\nORTOGONAIS:\
		\n6 - esquerda para direita\
		\n4 - direita para esquerda\
		\n2 - cima para baixo\
		\n8 - baixo para cima\n";
		troca_cor(BRANCO);
		imprime();
		cin >> vars.x >> vars.y >> vars.tam >> vars.dir;
		junta_chars();
		resultado = checa_palavras();
		if(resultado < 0){//char* "selecionado" não é igual a nenhuma das palavras
			troca_cor(ROXO);
			cout << "ERRROUUU, a palavra que você selecionou foi:\n" << selecionado << "\nTente de novo!\n";
			troca_cor(BRANCO);
		}else{
			troca_cor(VERDE);
			cout << "Boaa, uma a menos para a lista!\n";
			elimina_palavra();
			if(nPalavras == 0){
				cout << "Parabens voce achou todas as palavras!\n";
			}
			troca_cor(BRANCO);
		}
	}
}

int main(){
	while(gameLoop==true){
		cout << "Insira o comando desejado: 1 - carrega, 2 - marca, 3 - fecha, 4 - Teste do bool eh_igual\n";
		cin >> comando;
		switch(comando){
			case 1:{//carrega
				//Le o documento e salva toda sua informação
				le_doc();
				imprime();	
				break;
			}
			case 2:{//marca
				//Imprime a matriz devidamente, com os numeros e com a formatação adequada
				marca();
				imprime();
				break;
			}
			case 3:{//fecha
				// Sai do jogo atual
				if(leu){
					cout << "Todo seu progresso será perdido, tem certeza que quer continuar?\nS/N:";
					cin >> escolha;
					if(char(tolower(escolha))=='s'){
						cout << "Parabens todos os seus dados foram vendidos! Flw.\n" << endl;
						gameLoop = false;	
					}else if(char(tolower(escolha))=='n'){
					}else{
						cout << "Comando invalido, por favor digite \'s\' ou \'n\' da proxima vez!\n";
					}
				}else{
					cout<< "Que decepcao...";
					gameLoop = false;
					break;
				}
				break;
			}
			case 4:{
				debuga();
				break;
			}
			default:
				cout << "Comando invalido, por favor digite 1, 2 ou 3 da proxima vez!\n";
		}
	}
	return 0;
}
