#include "elementarymatrix.h"
#include <functional>
#include <sstream>

using CSMFunction = function<ConcreteSquareMatrix(const ConcreteSquareMatrix&, const ConcreteSquareMatrix&)>;

class CompositeSquareMatrix{
	private:
		unique_ptr<SquareMatrix> oprnd1;
		unique_ptr<SquareMatrix> oprnd2;
		CSMFunction oprtor;
		char op_sym;
	
	public:
		CompositeSquareMatrix(SquareMatrix& op1, SquareMatrix& op2, const CSMFunction& opr, char ops);
		CompositeSquareMatrix(const CompositeSquareMatrix& m);
		CompositeSquareMatrix(CompositeSquareMatrix&& m);
		~CompositeSquareMatrix(){};
		CompositeSquareMatrix& operator=(const CompositeSquareMatrix& m);
		CompositeSquareMatrix& operator=(CompositeSquareMatrix&& m);
		unique_ptr<SquareMatrix> clone();
		void print(ostream& os);
		string toString();
		ConcreteSquareMatrix evaluate(const Valuation& v);
};
