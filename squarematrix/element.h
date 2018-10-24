#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <memory>
using namespace std;

class Valuation{
	public:
		map<char, int> valuation;
		Valuation(){}
		~Valuation(){}
		Valuation(char v, int i);
		void val(char x, int y);
};

class Element{
	public:
		virtual ~Element(){};
		virtual unique_ptr<Element> clone() = 0;
		virtual string toString() = 0;
		virtual int evaluate(const Valuation& v) = 0;
};

template<typename T>
class TElement: public Element{
	private:
		T var;
	public:
		TElement(){};
		TElement(T v);
		~TElement(){};
		T getVal();
		setVal(T v);
		unique_ptr<Element> clone();
		string toString();
		
		int evaluate(const Valuation& v);
		bool operator==(const TElement& i);
		TElement& operator+=(const TElement& i);
		TElement& operator-=(const TElement& i);
		TElement& operator *=(const TElement& i);
};

using IntElement = TElement<int>;
using VariableElement = TElement<char>;

template<typename T>
TElement<T>::TElement(T v){
	var = v;
}

template<typename T>
T TElement<T>::getVal(){
	return var;
}

template<typename T>
TElement<T>::setVal(T v){
	var = v;
}

template<typename T>
string TElement<T>::toString(){
	stringstream ss;
	string jono;
	ss << var;
	ss >> jono;
	return jono;
}

template<typename T>
int TElement<T>::evaluate(const Valuation& val){
	int luku;
	if(var == val.valuation.find(var)->first){
		luku = val.valuation.find(var)->second;
		return luku;
	} else{
		cout << "exception: variable not defined!";
	}
}

template<typename T>
bool TElement<T>::operator==(const TElement& i){
	bool onko;
	char muuttuja = i.var;
	if( muuttuja == var){
		onko = true;
	}else{
		onko = false;
	}
	return onko;
}

template<typename T>
unique_ptr<Element> TElement<T>::clone(){
	unique_ptr<Element> pointteri(new TElement<T>(var));
	return pointteri;
}
