#include "compositematrix.h"

CompositeSquareMatrix::CompositeSquareMatrix(SquareMatrix& op1, SquareMatrix& op2, const CSMFunction& opr, char ops){
	oprnd1 = move(op1.clone());
	oprnd2 = move(op2.clone());
	oprtor = opr;
	op_sym = ops;
}

CompositeSquareMatrix::CompositeSquareMatrix(const CompositeSquareMatrix& m){
	oprnd1 = move(m.oprnd1->clone());
	oprnd2 = move(m.oprnd2->clone());
	oprtor = m.oprtor;
	op_sym = m.op_sym;
}

CompositeSquareMatrix::CompositeSquareMatrix(CompositeSquareMatrix&& m){
	oprnd1 = move(m.oprnd1);
	oprnd2 = move(m.oprnd2);
	oprtor = m.oprtor;
	op_sym = m.op_sym;
}

CompositeSquareMatrix& CompositeSquareMatrix::operator=(const CompositeSquareMatrix& m){
	this->oprnd1 = move(m.oprnd1->clone());
	this->oprnd2 = move(m.oprnd2->clone());
	this->oprtor = m.oprtor;
	this->op_sym = m.op_sym;
	return *this;
}

CompositeSquareMatrix& CompositeSquareMatrix::operator=(CompositeSquareMatrix&& m){
	this->oprnd1 = move(m.oprnd1);
	this->oprnd2 = move(m.oprnd2);
	this->oprtor = move(m.oprtor);
	this->op_sym = move(m.op_sym);
	return *this;
}

void CompositeSquareMatrix::print(ostream& os){
	os << "(" << oprnd1.get() << op_sym << oprnd2.get() << ")";
}

string CompositeSquareMatrix::toString(){
	stringstream ss;
	string ope;
	ss << op_sym;
	ss >> ope;
	string jono = "(" + oprnd1->toString() + " " + ope + " " + oprnd2->toString() + ")";
	return jono;
}

ConcreteSquareMatrix CompositeSquareMatrix::evaluate(const Valuation& v){
	ConcreteSquareMatrix matriisi1(oprtor(oprnd1->evaluate(v), oprnd2->evaluate(v)));
	return matriisi1;
}
