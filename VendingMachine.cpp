//Vending Machine
/*Esse código simula uma Vending Machine, o usuário interage de acordo com as instruções. Existem dois modos possíveis, o Usuário e o Administrador*/

//Bibliotecas
#include <iostream>
#include <conio.h>
#include <string>
#include <iomanip>
#include <ctype.h>


using namespace std;

//Definindo as cores de saida por atalhos
#define NC "\e[0m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define CYN "\e[0;36m"
#define REDB "\e[41m"

//Struct de produtos
typedef struct produto{

        string nome;
        float preco;
        int quant;        
};

//Cabecalho de funcoes
bool verificarNumero(string valor); //verifica se eh numero

void DesenhaVitrine(produto[]); //desenha no prompt

void ModoUsuario(produto[]); //Funcao do modo usuario

void ModoAdm(produto[]); //Funcao do modo adm

void DesenhaVitrineAdm(produto[]);

void CriaProdutos(produto[]);

int MenuAdm(); //Menu interno do modo adm
int Menu();


//Variavel global para o modo usuario
float totalPagar; //Valor total das compras realizadas

/*------------------------------------------------------------------------------
------------------------------------------------------------------------------*/

//Funcao principal
int main(){
    
    //Variaveis
    int retornoMenu;
    produto vetorProdutos[16];
    
    
    
    //Setar a saida de dados com 2 casas decimais
    cout << fixed << setprecision(2);
        
    //Cria o vetor para fins de teste
    CriaProdutos(vetorProdutos);
        
     do {
       //chamada da funcao principal
       retornoMenu = Menu();
       if (retornoMenu == 1){ 
          ModoUsuario(vetorProdutos);
       }
       if (retornoMenu == 2){
          ModoAdm(vetorProdutos);                
       }   
    } while (retornoMenu != 0);
    
    system("pause");
}

/*------------------------------------------------------------------------------
------------------------------------------------------------------------------*/

//Menu principal de opcoes - primeiro menu
int Menu(){
    
    int modo;
    
    system("cls");
    cout << CYN "Selecione o modo: " NC << endl;
    cout << "(0) - Sair"  << endl;
    cout << "(1) - Usuario" << endl;
    cout << "(2) - Administrador" << endl;
    
    cin >> modo;
    
    //Verifica se o valor eh valido
    if (modo < 0 || modo > 2){
       //erro
       cout << RED "ERRO - Favor inserir uma opcao valida" NC << endl;
	   return 0;        
    }
    else {
       return modo;     
    }
}

/*------------------------------------------------------------------------------
------------------------------------------------------------------------------*/

void ModoUsuario(produto produtos[]){
     
    //Variaveis locais 
    int produtoDesejado;
    int quantidadeDesejada;
    float valorPagamento;
    char repetir;
    float somaValor;
	float *transferencia;
        
    //Exibir a lista de produtos (deSenha a matriz)
    DesenhaVitrine(produtos);

/*---------------------------------------- ENTRADA DE DADOS -------------------------------------------*/     
    //Entrada do produto
    cout << endl << "Insira o produto desejado [numero ao lado do produto em colchetes]: " << endl;
    cin >> produtoDesejado;
    
    //Caso o usuario insira um  numero inexistente repetidas vezes
	while(produtoDesejado > 15 || produtoDesejado < 0 ){
		cout << RED "Favor inserir um numero valido: " NC << endl; 
	 	cin >> produtoDesejado;
	}
	 
	//Entrada da quantidade
    cout << "Insira a quantidade desejada (numero)" << endl;
    cin >> quantidadeDesejada;
 
/*---------------------------------- ALTERACOES INTERNAS NO ESTOQUE -----------------------------------*/    
    //Mexendo nA quantidade no estoque
    if(quantidadeDesejada <= produtos[produtoDesejado].quant){
       //Subtracao na quantidade de produtos restantes 
       produtos[produtoDesejado].quant -= quantidadeDesejada; 
       //Somatoria do valor dos produtos locais
       somaValor += quantidadeDesejada * produtos[produtoDesejado].preco;                     
    }else{
    	//Caso o valor desejado seja superior ao que o estoque possui
       cout << endl << RED "MENSAGEM DE ERRO (PRODUTO FORA DO ESTOQUE)" NC << endl;
       cout << "Favor digitar um valor menor que " << produtos[produtoDesejado].quant << endl;
     }
     
    //Confirmação da compra
    cout << endl << GRN "Valor dessa compra: " << somaValor << NC << endl;
     
    //Nova compra?
    cout << endl << "Deseja realizar uma nova compra? <S/N>" << endl;
    cin >> repetir;
     
    //Somando o valor gasto em uma variável global
    transferencia = &totalPagar;
    *transferencia += somaValor;
     
//--------------------------- PAGAMETO -------------------------------------//
     if (toupper(repetir) == 'S')  
     	//Caso o usuario queria realizar uma nova compra, usa-se a recursividade
        ModoUsuario(produtos);
     else{
          
        //Mostrar a lista de produtos comprados
        system("cls");
        cout << CYN "Carrinho de compras: " NC << endl;
        for (int i = 0; i < 15; i++)
        {
        	if(produtos[i].quant != 10)
        	{
        		cout << produtos[i].nome << " : " << 10 - produtos[i].quant << " itens" << endl;
			}
		}
        
        //Recebimento do pagamento
        cout << endl << GRN "Valor total das compras: " << totalPagar << NC << endl;
        cout << endl << "Insira o valor de pagamento: ";
        cin >> valorPagamento;
        
        //Calculo do troco
        
        //Caso o valor seja insuficiente
        if(valorPagamento < totalPagar)
        {
           do{
                   //Mensagem de erro
                   cout << endl << RED "MENSAGEM DE ERRO - VALOR INSUFICIENTE" NC << endl;
                   cout << endl << "Insira o valor de pagamento: ";
                   cin >> valorPagamento;
           }while(valorPagamento < totalPagar);    
        }
        
        //Caso o valor seja suficente
        cout << endl << GRN "TROCO: R$" << valorPagamento - totalPagar << NC << endl;
        system("pause");
        
        //Zerando para a proxima operacao
        somaValor = 0; 
     }
     
}

/*------------------------------------------------------------------------------
------------------------------------------------------------------------------*/

//Funcao para desenhar a vitrine com todos os produtos
void DesenhaVitrine(produto vitrine[]){

	//Variveis	
	int contador1 = 0; 
	int contador2 = 0;//Guarda o indice do produto
	
	system("cls"); //Limpa o promtp
	
/*------------------------------------- PARTE SUPERIOR ----------------------------------*/
	cout << CYN "+==================================================================+" << endl;
	cout << "| +--------------------------------------------------------------+ |" << endl;
	cout << "| |                                                              | |" << endl;
	cout << "| |                                                              | |" << endl;
	
/*-------------------------------- PARTE INTERIOR - PRODUTOS ----------------------------*/
	for(int i = 0; i < 4; i++){
		cout << "| | ";
		for(int c = 0; c < 4; c++){
			cout << NC;
			cout << setw(15) << vitrine[contador1].nome;
			contador1++; //produto
			cout << CYN;
		}
		cout << " | |" << endl;
		cout << "| | ";
		for(int c = 0; c < 4; c++){
			cout << GRN;
			cout << setw(6) << "R$ " << vitrine[contador2].preco << "     ";
			contador2++;
			cout << CYN;
		}
		cout << " | |" << endl;
		cout << "| | 							       	 | |" << endl;
		cout << "| | 							       	 | |" << endl;
		cout << "| | 							       	 | |" << endl;
	}
	
/*------------------------------------- PARTE INFERIOR ----------------------------------*/
	cout << "| +--------------------------------------------------------------+ |" << endl;	
	cout << "+==================================================================+" << endl;
	cout << "|===============+----------------------------------+===============|" << endl;
	cout << "|===============|               PUSH               |===============|" << endl;
	cout << "|===============+----------------------------------+===============|" << endl;
	cout << "+==================================================================+" NC << endl;
	cout << endl;
}    

/*------------------------------------------------------------------------------
------------------------------------------------------------------------------*/

//Modo ADM
void ModoAdm(produto produtos[]){
	
	//Variaveis locais
    float somaTotal = 0;
    int repoProduto;
    int quantRepo;
    float valorMax;
    int respMenu;
     
/*------------------------ SOMA DOS VALORES TOTAIS PEDIDOS ----------------------*/
     for(int i = 0; i < 16; i++){
             if(produtos[i].quant != 10){
                    somaTotal = (10 - produtos[i].quant) * produtos[i].preco;
             }
     }
     
/*-------------------------------- MENU DE OPCOES -------------------------------*/
     do{
     	respMenu = MenuAdm();
        switch (respMenu){
                   
                //Retornar
                case 0:
                     break;
                     
                //Inventario
                case 1:
                    DesenhaVitrineAdm(produtos);
                    system("pause");
                    break;
                    
                //Total de vendas
                case 2:
                    cout << endl << GRN "Fatura das vendas: " << totalPagar << NC << endl;
                    system("pause");
                    break;
                    
                //Repor estoque
                case 3:
                    //Perguntar infos de reposicao
                    DesenhaVitrineAdm(produtos);
                    cout << endl << "Qual produto quer repor? " << endl;
                    cin >> repoProduto;
                    cout << "Quantos itens serao repostos? " << endl;
                    cin >> quantRepo;
                        
                    //Repor
                    if(produtos[repoProduto].quant != 10 && quantRepo < produtos[repoProduto].quant){
                        produtos[repoProduto].quant += quantRepo;
                    }
                    else{
                        cout << endl << RED "ERRO - Quantidade de produtos superior ao estoque OU Produto selecionado ja tem capacidade maxima" NC<< endl;
                    	system("pause");
                    	break;
					}
                        
                    //Mostrando a nova lista atualizada
                    system("cls"); //Limpar o promt
                    cout << CYN "Nova lista de produtos: " NC << endl;
                    DesenhaVitrineAdm(produtos);
                        
                    system("pause");
                    break;
                
				//Prospectivo de vendas
                case 4: 
                    //Calcular valor maximo que pode ser arrecadado
                    for(int i = 0; i < 16; i++){
                            valorMax += produtos[i].quant * produtos[i].preco;
                    }
    
                    cout << GRN "Prospectivo de vendas brutas: " << valorMax  << NC << endl;
                    valorMax = 0; //Zerando para o valor poder ser atualizado a cada vez que a funcao eh evocada
                    system("pause");
                    break;
            }
     }while(respMenu != 0);
     
}
/*------------------------------------------------------------------------------
------------------------------------------------------------------------------*/

//Menu interno do modo adm
int MenuAdm(){
    int opcao;   
    
    //LImpa o prompt 
    system("cls");
    
    //Lista de opcoes
    cout << "0 - Retornar" << endl;
    cout << "1 - Listar inventario" << endl;
    cout << "2 - Valor total das vendas" << endl;
    cout << "3 - Repor estoque" << endl;
    cout << "4 - Prospectivo de vendas restantes" << endl;
    cin >> opcao;
    
    //Tratando erro de digitacao
    if(opcao < 0 || opcao > 4){
             cout << RED "ERRO - Favor inserir um valor valido" NC << endl;
             MenuAdm();
    }
    else
        return opcao;
}


/*------------------------------------------------------------------------------
------------------------------------------------------------------------------*/

//Lista os produtos e suas respectivas quantidades
void DesenhaVitrineAdm(produto vitrineAdm[]){
         
         //listar inventario
         for(int i = 0; i < 16; i++){
            cout << vitrineAdm[i].nome << "  | Estoque de ";
            cout << CYN << vitrineAdm[i].quant << NC << " itens|" << endl;
            }
         
}

/*------------------------------------------------------------------------------
------------------------------------------------------------------------------*/

//Atribuicao de valores e nomes de cada produto
void CriaProdutos(produto vetorProdutos[]){
	vetorProdutos[0].nome = "Coca-Cola[0]";     
    vetorProdutos[0].preco = 3.50;
    vetorProdutos[0].quant = 10;
	vetorProdutos[1].nome = "Pepsi[1]    ";     
    vetorProdutos[1].preco = 3.50;
    vetorProdutos[1].quant = 10;
	vetorProdutos[2].nome = "Fanta-Uva[2]";     
    vetorProdutos[2].preco = 4.00;
    vetorProdutos[2].quant = 10;
	vetorProdutos[3].nome = "Sprite[3]   ";     
    vetorProdutos[3].preco = 2.00;
    vetorProdutos[3].quant = 10;
    vetorProdutos[4].nome = "Doritos[4]  ";     
    vetorProdutos[4].preco = 7.00;
    vetorProdutos[4].quant = 10;
	vetorProdutos[5].nome = "Fandangos[5]";     
    vetorProdutos[5].preco = 7.50;
    vetorProdutos[5].quant = 10;
	vetorProdutos[6].nome = "Cheetos[6]  ";     
    vetorProdutos[6].preco = 4.30;
    vetorProdutos[6].quant = 10;
	vetorProdutos[7].nome = "Ruffles[7]  ";     
    vetorProdutos[7].preco = 5.00;
    vetorProdutos[7].quant = 10;
	vetorProdutos[8].nome = "Snickers[8] ";     
    vetorProdutos[8].preco = 5.00;
    vetorProdutos[8].quant = 10;
	vetorProdutos[9].nome = "Bis[9]      ";     
    vetorProdutos[9].preco = 4.20;
    vetorProdutos[9].quant = 10;
	vetorProdutos[10].nome = "Hersheys[10]";     
    vetorProdutos[10].preco = 7.00;
    vetorProdutos[10].quant = 10;
	vetorProdutos[11].nome = "M&M[11]     ";     
    vetorProdutos[11].preco = 6.20;
    vetorProdutos[11].quant = 10;
	vetorProdutos[12].nome = "Fini[12]    ";     
    vetorProdutos[12].preco = 4.00;
    vetorProdutos[12].quant = 10;
	vetorProdutos[13].nome = "Kit-Kat[13] ";     
    vetorProdutos[13].preco = 5.00;
    vetorProdutos[13].quant = 10;
	vetorProdutos[14].nome = "Agua-Gas[14]";     
    vetorProdutos[14].preco = 3.50;
    vetorProdutos[14].quant = 10;
    vetorProdutos[15].nome = "Agua[15]    ";     
    vetorProdutos[15].preco = 3.00;
    vetorProdutos[15].quant = 10;
}
