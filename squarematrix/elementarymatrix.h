#include "squarematrix.h"

template<typename T>
class ElementarySquareMatrix: public SquareMatrix{
	private:
		unsigned int n;
		vector<vector<unique_ptr<T>>> elements;
	public:
		ElementarySquareMatrix(){};
		ElementarySquareMatrix(const string& str_m);
		ElementarySquareMatrix(const ElementarySquareMatrix& m);
		ElementarySquareMatrix(ElementarySquareMatrix&& m);
		~ElementarySquareMatrix(){};
		ElementarySquareMatrix& operator=(const ElementarySquareMatrix& m);
		ElementarySquareMatrix& operator=(ElementarySquareMatrix&& m);
		unique_ptr<SquareMatrix> clone();
		ElementarySquareMatrix transpose();
		bool operator==(const ElementarySquareMatrix& m);
		void print(ostream& os);
		string toString();
		
		ElementarySquareMatrix<IntElement> evaluate(const Valuation& v);
		ElementarySquareMatrix<IntElement>& operator+=(const ElementarySquareMatrix<IntElement>& m);
		ElementarySquareMatrix<IntElement>& operator-=(const ElementarySquareMatrix<IntElement>& m);
		ElementarySquareMatrix<IntElement>& operator*=(const ElementarySquareMatrix<IntElement>& m);
};

using SymbolicSquareMatrix = ElementarySquareMatrix<Element>;
using ConcreteSquareMatrix = ElementarySquareMatrix<IntElement>;
		
template<typename T>
ElementarySquareMatrix<T>::ElementarySquareMatrix(ElementarySquareMatrix&& m){
	elements = move(m.elements);
			n = m.n;
}

template<typename T>
ElementarySquareMatrix<T>& ElementarySquareMatrix<T>::operator=(ElementarySquareMatrix&& m){
	this->elements = move(m.elements);
			this->n = m.n;
			return *this;
}

template<typename T>
unique_ptr<SquareMatrix> ElementarySquareMatrix<T>::clone(){
	unique_ptr<SquareMatrix> pointteri(new ElementarySquareMatrix<T>(*this));
	return pointteri;
}

template<typename T>
void ElementarySquareMatrix<T>::print(ostream& os){
	os << toString() << endl;
}

template<typename T>
string ElementarySquareMatrix<T>::toString(){
	string luku;
			string jono = "[";
			for (int i = 0; i < n; i++){
				jono += "[";
				for(int j = 0; j < n; j++){
					luku = elements[i][j]->toString();
					jono += luku;
					jono += ",";
				}
				jono.pop_back();
				jono += "]";
			}
			jono = jono + "]";
			return jono;
}


