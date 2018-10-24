#include "elementarymatrix.h"

template<>
SymbolicSquareMatrix::ElementarySquareMatrix(const string& str_m){
			n = 0;
			char numero;
			vector<unique_ptr<Element>> numerot;
			unique_ptr<Element> uniikki;
			for (int i = 0; i < str_m.size(); i++){
				if(isdigit(str_m.at(i)) || isalpha(str_m.at(i))){
					numero = str_m.at(i);
					uniikki = unique_ptr<Element>(new VariableElement(numero));
					numerot.push_back(move(uniikki));
				}
				if(str_m.at(i) == ']'){
					elements.push_back(move(numerot));
					n++;
				}
			}
			n--;
		}
		
template<>
ConcreteSquareMatrix::ElementarySquareMatrix(const string& str_m){
	n = 0;
			int numero;
			IntElement elementti;
			vector<unique_ptr<IntElement>> numerot;
			unique_ptr<IntElement> uniikki;
			for (int i = 0; i < str_m.size(); i++){
				if(isdigit(str_m.at(i))){
					numero = str_m.at(i) - 48;
					elementti.setVal(numero);
					uniikki = unique_ptr<IntElement>(new IntElement(elementti));
					numerot.push_back(move(uniikki));
				}
				if(str_m.at(i) == ']'){
					elements.push_back(move(numerot));
					n++;
				}
			}
			n--;
}

template<>
ConcreteSquareMatrix SymbolicSquareMatrix::evaluate(const Valuation& v){
	string arvo = this->toString();
			int luku;
			stringstream ss;
			string jono;
			string toinen;
			char testi;
			for(int i = 0; i < arvo.size(); i++){
				if(isalpha(arvo.at(i))){
					luku = v.valuation.find(arvo.at(i))->second;
					ss << luku;
					ss >> toinen;
					jono += toinen;
				}else{
					jono.push_back(arvo.at(i));
				}
			}
			ConcreteSquareMatrix matriisi(jono);
			return matriisi;
}

template<>
SymbolicSquareMatrix::ElementarySquareMatrix(const SymbolicSquareMatrix& m){
			n = m.n;
			vector<unique_ptr<Element>> vektori;
			for (int i = 0; i < m.n; i++){
				for (int j = 0; j < m.n; j++){
					vektori.push_back(m.elements[i][j].get()->clone());
				}
				elements.push_back(move(vektori));
			}
		}
		
template<>
ConcreteSquareMatrix::ElementarySquareMatrix(const ConcreteSquareMatrix& m){
			n = m.n;
			vector<unique_ptr<IntElement>> vektori;
			unique_ptr<IntElement> pointteri;
			for (int i = 0; i < m.n; i++){
				for (int j = 0; j < m.n; j++){
					pointteri = unique_ptr<IntElement>(new IntElement(m.elements[i][j]->getVal()));
					vektori.push_back(move(pointteri));
				}
				elements.push_back(move(vektori));
			}
		}
		
template<>
ConcreteSquareMatrix ConcreteSquareMatrix::evaluate(const Valuation& v){
			ConcreteSquareMatrix matriisi(*this);
			return matriisi;
		}
		
template<>
ConcreteSquareMatrix& ConcreteSquareMatrix::operator+=(const ConcreteSquareMatrix& m){
			vector<vector<unique_ptr<IntElement>>> vektori = move(this->elements);
			this->elements.clear();
			vector<unique_ptr<IntElement>> vektori3;
			unique_ptr<IntElement> elementti;
			int luku1;
			int luku2;
			int luku3 = 0;
			for (int i = 0; i < m.n; i++){
				for (int j = 0; j < m.n; j++){
					luku1 = m.elements[i][j]->getVal();
					luku2 = vektori[i][j]->getVal();
					luku3 = luku1 + luku2;
					elementti = unique_ptr<IntElement>(new IntElement(luku3));
					vektori3.push_back(move(elementti));
					}
				this->elements.push_back(move(vektori3));
			}
			return *this;
		}
		
template<>
ConcreteSquareMatrix& ConcreteSquareMatrix::operator-=(const ConcreteSquareMatrix& m){
			vector<vector<unique_ptr<IntElement>>> vektori = move(this->elements);
			this->elements.clear();
			vector<unique_ptr<IntElement>> vektori2;
			unique_ptr<IntElement> pointteri;
			int luku1;
			int luku2;
			for (int i = 0; i < m.n; i++){
				for(int j = 0; j < m.n; j++){
					luku1 = m.elements[i][j]->getVal();
					luku2 = vektori[i][j]->getVal();
					luku2 = luku2 - luku1;
					pointteri = unique_ptr<IntElement>(new IntElement(luku2));
					vektori2.push_back(move(pointteri));
				}
				this->elements.push_back(move(vektori2));
			}
			return *this;
		}
		
template<>
ConcreteSquareMatrix& ConcreteSquareMatrix::operator*=(const ConcreteSquareMatrix& m){
			vector<vector<unique_ptr<IntElement>>> elementti = move(this->elements);
			this->elements.clear();
			vector<unique_ptr<IntElement>> vektori;
			unique_ptr<IntElement> pointteri;
			int luku1;
			int luku2;
			int luku3;
			for(int i = 0; i < this->n; i++){
				for(int j = 0; j < this->n; j++){
					pointteri = unique_ptr<IntElement>(new IntElement(0));
					vektori.push_back(move(pointteri));
				}
				this->elements.push_back(move(vektori));
			}
			for(int i = 0; i < m.n; i++){
				for(int j = 0; j < m.n; j++){
					for(int k = 0; k < m.n; k++){
						luku1 = this->elements[i][j]->getVal();
						luku2 = elementti[i][k]->getVal();
						luku3 = m.elements[k][j]->getVal();
						luku1 += luku2 * luku3;
						elementti[i][k]->setVal(luku1);
					}
				}
			}
			this->elements = move(elementti);
			return *this;
		}
	
template<>	
ConcreteSquareMatrix& ConcreteSquareMatrix::operator=(const ElementarySquareMatrix& m){
	this->elements.clear();
			vector<unique_ptr<IntElement>> vektori;
			unique_ptr<IntElement> pointteri;
			for(int i = 0; i < m.n; i++){
				for(int j = 0; j < m.n; j++){
					pointteri = unique_ptr<IntElement>(new IntElement(m.elements[i][j]->getVal()));
					vektori.push_back(move(pointteri));
				}
				this->elements.push_back(move(vektori));
			}
			this->n = m.n;
			return *this;
}

template<>	
SymbolicSquareMatrix& SymbolicSquareMatrix::operator=(const ElementarySquareMatrix& m){
	this->elements.clear();
			vector<unique_ptr<Element>> vektori;
			for(int i = 0; i < m.n; i++){
				for(int j = 0; j < m.n; j++){
					vektori.push_back(m.elements[i][j].get()->clone());
				}
				this->elements.push_back(move(vektori));
			}
			this->n = m.n;
			return *this;
}

template<>
SymbolicSquareMatrix SymbolicSquareMatrix::transpose(){
	SymbolicSquareMatrix matriisi;
			vector<unique_ptr<Element>> vektori;
			for (int i = 0; i < n; i++){
				for (int j = 0; j < n; j++){
					vektori.push_back(elements[j][i].get()->clone());
				}
				matriisi.elements.push_back(move(vektori));
			}
			matriisi.n = n;
			return matriisi;
}

template<>
ConcreteSquareMatrix ConcreteSquareMatrix::transpose(){
	ConcreteSquareMatrix matriisi;
			vector<unique_ptr<IntElement>> vektori;
			unique_ptr<IntElement> pointteri;
			for (int i = 0; i < n; i++){
				for (int j = 0; j < n; j++){
					pointteri = unique_ptr<IntElement>(new IntElement(elements[j][i]->getVal()));
					vektori.push_back(move(pointteri));
				}
				matriisi.elements.push_back(move(vektori));
			}
			matriisi.n = n;
			return matriisi;
}

template<>
bool SymbolicSquareMatrix::operator==(const SymbolicSquareMatrix& m){
	vector<unique_ptr<Element>> vektori1;
			vector<unique_ptr<Element>> vektori2;
			string luku1;
			string luku2;
			bool onko;
			for (int i = 0; i < m.n; i++){
				for (int j = 0; j < m.n; j++){
					vektori1.push_back(m.elements[i][j].get()->clone());
					vektori2.push_back(move(this->elements[i][j]));
				}
			}
			for(int j = 0; j < n; j++){
				luku1 = (vektori1[j].get())->toString();
				luku2 = (vektori2[j].get())->toString();
				if(luku1 == luku2){
					onko = true;
				} else{
					onko = false;
				}
			}
			return onko;
}

template<>
bool ConcreteSquareMatrix::operator==(const ConcreteSquareMatrix& m){
	bool onko;
			ConcreteSquareMatrix matriisi(m);
			string jono1 = matriisi.toString();
			string jono2 = this->toString();
			if(jono1 == jono2){
				onko = true;
			}else{
				onko = false;
			}
			return onko;
}
