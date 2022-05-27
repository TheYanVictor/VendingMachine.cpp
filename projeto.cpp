#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

//Máquina de vendas

void ModoUsuario(); //função do modo usuário

void ModoAdministrador(); //função do modo administrador

int Menu();

//Matriz global (por enquanto)
float matrizProdutosGlobal[2][16]; /* primeira linha contem valor
                               segunda linha contem quantidade
                               cada colna e um produto */
//Vetor global de nomes
string vetorNomesProdutosGlobal[16];

//Variaveis globais
float somaValor = 0;

int main(){
    
    int retornoMenu;
    
    //Duas casas depois da virgula
    cout << fixed << setprecision(2);
    
    do {
       //chamada da funcao principal
       retornoMenu = Menu();
       if (retornoMenu == 1){ 
          ModoUsuario();
       }
       /*if (retornoMenu == 2){
          ModoAdministrador();                
       }*/     
    } while (retornoMenu != 0);
}

int Menu(){
    
    int modo;
    
    cout << "Selecione o modo: " << endl;
    cout << "(0) - Sair" << endl;
    cout << "(1) - Usuario" << endl;
    cout << "(2) - Administrador" << endl;
    
    cin >> modo;
    
    //Inicializacao de valores
     for(int i = 0; i < 2; i++) // linha
         for(int j = 0; j < 16; j++){ // coluna
             if(i == 0)
               matrizProdutosGlobal[i][j] = 5.5; 
             else
               matrizProdutosGlobal[i][j] = 10;
         }
    
    //Verifica se o valor e valido
    if (modo < 0 || modo > 2){
       //erro
       cout << "Mensagem de erro" << endl;        
    }
    else {
       return modo;     
    }
}

void ModoUsuario(){
     //Variaveis locais
     int i, j, produtoDesejado, quantidadeDesejada;
     char repetir = 'S';
     float valorPagamento; 
        
     //Exibir a lista de produtos
     for(i = 0; i < 16; i++){
           vetorNomesProdutosGlobal[i] = "Produto";
           cout << vetorNomesProdutosGlobal[i] << " " << i << endl;
     }
     
     //Entrada das opcoes do usuario
     cout << endl << "Insira o produto desejado (numero do produto)" << endl;
     cin >> produtoDesejado; 
     cout << "Insira a quantidade desejada (numero)" << endl;
     cin >> quantidadeDesejada;
     
     //Subtracao das quantidades existentes
     if(quantidadeDesejada > matrizProdutosGlobal[1][produtoDesejado]){
            cout << endl << "Nao temos essa quantidade, favor inserir um numero menor que " << matrizProdutosGlobal[1][produtoDesejado] << endl;
     }
     else{
         matrizProdutosGlobal[1][produtoDesejado] = matrizProdutosGlobal[1][produtoDesejado] - quantidadeDesejada;
         //Somatoria do valor 
         somaValor += quantidadeDesejada * matrizProdutosGlobal[0][produtoDesejado];
     }
      
     //TESTE DO VALOR
     cout << endl << "Soma: " << somaValor << endl;
     cout << "Quantidade de produtos restantes: " <<  matrizProdutosGlobal[1][produtoDesejado]<< endl;
     
     //Recursividade - Repetir o processo caso o cliente deseje fazer outra compra na máquina
     cout << endl << "Deseja repetir a operacao? <S/N>" << endl;
     cin >> repetir;
     if (toupper(repetir) == 'S')
        ModoUsuario();
     else{
        //Recebimento do pagamento
        cout << endl << "Insira o valor do pagamento: ";
        cin >> valorPagamento;
        
        //Calculo do troco
        cout << "Troco: R$" << valorPagamento - somaValor << endl;
     }
}

