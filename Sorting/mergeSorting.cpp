//#include <iostream>
////#define TAMVET 11   
////#define TAMGRUPO 3
//using namespace std;
//
//
//enum variaveisUteis { tv_, tg_, qntg_, inGAtt_, fiGAtt_ };
//
//int contarQntsGrupos(int tamVet, int tamGrupo){
//	int gpNCmpleto=0, totalGrupos;
//	if (tamVet % tamGrupo != 0) gpNCmpleto = 1;
//	totalGrupos = tamVet / tamGrupo + gpNCmpleto;
//	return totalGrupos;
//}
//
//int tamanhoGrupoAtual(int util[], int qualGrupo) {
//	if (qualGrupo == util[qntg_]) {
//		int gpCheios=(util[tv_]/util[tg_]), gpNaoCheio = util[tv_];
//		gpNaoCheio -= gpCheios * util[tg_];
//		return gpNaoCheio;
//	}
//	return util[tg_];
//}
//
//void showGroup(int vetPrincip[], int util[]) {
//	for (int i= util[inGAtt_]; i<= util[fiGAtt_]; i++){
//		cout<<vetPrincip[i]<<" ";
//	}
//}
//
//
//int vlrDaPosDoGrupo(int vetPrincip[], int tamGrupo, int pos, int grupo){
//	return vetPrincip[tamGrupo*grupo-tamGrupo+pos-1];
//}
//
//
//int miniOrdem(int vetPrincip[], int util[], int tgrupoAtual, int n) {
//	int *vet = new int[3]{10,20,30},
//		*ordGrupoMin = new int[3],
//		*utilizado = new int[3];
//	int aux = 0;
//
//	for (; n > tgrupoAtual-1; n--);
// 
//
//	for (int i = 0; i < 3; i++) {
//		ordGrupoMin[i] = -1;
//		utilizado[i] = 0;
//	}
//	
//	for (int i = util[inGAtt_], pos = 0; i <= util[fiGAtt_]; i++, pos++) {
//		for (int j = util[inGAtt_]; j <= util[fiGAtt_]; j++) {
//			if (vetPrincip[i] <= vetPrincip[j]) ordGrupoMin[pos]++;
//			//cout << ordGrupoMin[0] << " * " << ordGrupoMin[1] << " * " << ordGrupoMin[2]<<"\n";
//		}
//		int trazer = 3 - 1 - ordGrupoMin[pos] - aux;
//		for (; trazer > tgrupoAtual - 1; trazer--, aux++);
//		for (; utilizado[trazer] == 1; trazer--);
//		vet[trazer] = vetPrincip[i];
//		utilizado[trazer] = 1;
//	}
//
//	//cout << "\n-->";
//	//cin >> asd;
//
//	int resp = vet[n];
//
//	delete[] vet;
//	delete[] ordGrupoMin;
//	vet = nullptr;
//	ordGrupoMin = nullptr;
//
//	return resp;
//}
//
//
//int encontrarMax(int vetPrincip[], int inicio, int fim){
//	int max = vetPrincip[inicio]; //Recebe o valor da primeira posicao do grupo.
//	
//	for (int i=inicio+1; i<=fim; i++){
//		if (vetPrincip[i] > max) max = vetPrincip[i]; //Verifica se tem algum maior que o primeiro valor.
//	}
//
//	return max;
//}
//int encontrarMin(int vetPrincip[], int inicio, int fim){
//	int min = vetPrincip[inicio]; //Recebe o valor da primeira posicao do grupo.
//	
//	for (int i=inicio+1; i<=fim; i++){
//		if (vetPrincip[i] < min) min = vetPrincip[i]; ////Verifica se tem algum menor que o primeiro valor.
//	}
//
//	return min;
//}
//
//
//void limitesGrupoAtual(int util[], int tGrupoAtual, int qualGrupo) {
//	util[inGAtt_] = qualGrupo * util[tg_] - util[tg_];
//	util[fiGAtt_] = util[inGAtt_] - 1 + tGrupoAtual;
//}
//
//int separarGrupos(int vetPrincip[], int qualGrupo, int util[], int n) {
//	qualGrupo++;
//			
//	limitesGrupoAtual(util, tamanhoGrupoAtual(util, qualGrupo), qualGrupo);
//
//	return miniOrdem(vetPrincip, util, tamanhoGrupoAtual(util, qualGrupo), n);
//}
//
////int separarGrupos(int vetPrincip[], int qualGrupo, int tamVet, int tamGrupo,  int (*maxOuMin)(int [],int,int)){
////    qualGrupo++;
////
////    int inicioEFimGrupo[0] = qualGrupo * tamGrupo - tamGrupo;
////    int inicioEFimGrupo[1] = inicioEFimGrupo[0] - 1 + tamanhoGrupoAtual(tamVet, tamGrupo, qualGrupo); 
////
////    return maxOuMin(vetPrincip, inicioEFimGrupo[0], inicioEFimGrupo[1]);
////}
//
//
//int main(){
//	int t[2]{	11	,	3	};
//	int
//		*util = new int[5] {
//			t[0],	//......................................util[tv_]
//			t[1],	//......................................util[tg_]
//			contarQntsGrupos(t[0], t[1]),	//..............util[qntg_]
//			0,
//			0
//	    },
//		*_vetPrincipal = new int[util[tv_]]{ 10,9,8,7,6,5,4,3,2,1,10},						//Vetor principal, eh aqui que ficara os valores a ser ordenado.
//		*_vetSecundaria = new int[util[tv_]],												//Onde acontecera as trocas.
//		*_vetMax = new int[util[qntg_]], *_vetMin = new int[util[qntg_]],					//Armazenar o menor e maior de cada grupo.
//		*_concretizado = new int[util[qntg_]],												//Marcar grupos que tiver com os valores corretos.
//		_passos = 1;																		//Quantos passos necessarios para ordenar tudo.
//	
//
//
//
//
//
//	for (int i=util[qntg_] - 1; i >= 0; i--) {
//		_vetMax[i] = separarGrupos(_vetPrincipal, i+1, util, 2);
//		if (i != util[qntg_] - 1 && _vetMax[i] <= _vetMin[i + 1]) _concretizado[i] = 1;
//		else if (i == util[qntg_] - 1) _concretizado[i] = 55;
//		else _concretizado[i] = 0;
//		_vetMin[i] = separarGrupos(_vetPrincipal, i+1, util, 0);
//	}
//
//
//
//
//	cout << "################Passo " << _passos << "################\n";
//	for (int i=0; i<util[qntg_]; i++){
//		cout<<"--------------- Grupo "<<1+i<<" ---------------\nVetMax: "<<_vetMax[i];
//		cout<<"\t|\tVetMin: "<<_vetMin[i]<<"\nGrupo: ";
//		limitesGrupoAtual(util, tamanhoGrupoAtual(util, i+1), i+1);
//		showGroup(_vetPrincipal, util);
//		cout<<"\t|\tConcretizado:"<<_concretizado[i]<<"\n---------------------------------------\n";
//	}
//	cout << "\n\n";
//
//
//	_passos++;
//
//
//	delete[] _vetMax, _vetMin, _concretizado;
//	_vetMax, _vetMin, _concretizado = nullptr;
//}