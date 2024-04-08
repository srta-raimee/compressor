#include <iostream>
#include <map>
#include <queue>



struct node{
  char caracter;
  int frequencia;
  node *esquerda, *direita;
};

 
std::map<char,int> frequencia(std::string texto){
  
  std::map<char,int> frequencias;
  for(int i = 0; i < texto.size(); i++){
   
    if(frequencias.find(texto[i]) == frequencias.end()){
      frequencias[texto[i]] = 1;
    }
      
    else{
      frequencias[texto[i]] += 1;
    }
  };
  return frequencias;
};


node* criarArvore(std::map<char,int> frequencias){

  std::priority_queue<node*, std::vector<node*>, std::greater<node*>> filaPrioridade;

  for(const auto& [c, f] : frequencias) {

    node* novoNode = new node;
    novoNode->caracter = c;
    novoNode->frequencia = f;
    novoNode->esquerda = nullptr;
    novoNode->direita = nullptr;
    filaPrioridade.push(novoNode);
    
    std::cout << novoNode->caracter << " " << novoNode->frequencia << std::endl;
  }

  while(filaPrioridade.size() > 1){
    node* node1 = filaPrioridade.top();
    filaPrioridade.pop();

    node* node2 = filaPrioridade.top();
    filaPrioridade.pop();

    node* novoNode = new node;
    novoNode->frequencia = node1->frequencia + node2->frequencia;
    novoNode->esquerda = node1;
    novoNode->direita = node2;
    filaPrioridade.push(novoNode);
  }
  return filaPrioridade.top();
};

void codificar(node* node, std::string codigoAtual, std::map<char, std::string>& codigos){
  if(node->esquerda == nullptr && node->direita == nullptr){
    codigos[node->caracter] = codigoAtual;
  }
  else{
    codificar(node->esquerda, codigoAtual + "0", codigos);
    codificar(node->direita, codigoAtual + "1", codigos);
  }
}

std::map<char, std::string> gerarCodigo(node* arvore){
  std::map<char, std::string> codigos;

  codificar(arvore, "", codigos);

  return codigos;
}

std::string comprimirTexto(std::string texto, std::map<char, std::string> codigos){
  std::string textoCodificado;
  for(char c : texto){
    textoCodificado += codigos[c];
  }
  return textoCodificado;
}

std::string descomprimirTexto(std::string textoCodificado, node* arvore){
  std::string textoOriginal;
  node* atual = arvore;
  for(char b : textoCodificado){
    if(b == '0'){
      atual = atual->esquerda;
    }
    else{
      atual = atual->direita;
    }
    if(atual->esquerda == nullptr && atual->direita == nullptr){
      textoOriginal += atual->caracter;
      atual = arvore;
    }
  }
  return textoOriginal;
}

int main(){
  std::string texto = "I love jesus so much!";
  std::map<char,int> freq = frequencia(texto);
  node* arvore = criarArvore(freq);
  std::map<char, std::string> codigos = gerarCodigo(arvore);

  std::cout << "Texto original: " << texto <<	std::endl;
  
  std::string textoCodificado = comprimirTexto(texto, codigos);
  
  std::cout << "Texto codificado: " << textoCodificado << std::endl;

  std::string textoDescodificado = descomprimirTexto(textoCodificado, arvore);

  std::cout << "Texto descodificado: " << textoDescodificado << std::endl;
  
  return 0;
}