#include "element.h"

Valuation::Valuation(char v, int i){
	valuation[v] = i;
}

void Valuation::val(char x, int y){
	valuation.insert(pair<char,int>(x,y));
}

template<>
		IntElement& IntElement::operator+=(const IntElement& i){
			this->var = this->var + i.var;
			return *this;
		}
		
		template<>
		IntElement& IntElement::operator-=(const IntElement& i){
			this->var = this->var - i.var;
			return *this;
		}
		
		template<>
		IntElement& IntElement::operator*=(const IntElement& i){
			this->var = this->var * i.var;
			return *this;
		}
