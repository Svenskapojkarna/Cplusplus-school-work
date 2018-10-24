#include <vector>
#include "element.h"
using namespace std;

template<typename T>
class ElementarySquareMatrix;
class Valuation;
class SquareMatrix {
	public:
		virtual ~SquareMatrix(){}
		virtual unique_ptr<SquareMatrix> clone() = 0;
		virtual void print(ostream& os) = 0;
		virtual string toString() = 0;
		virtual ElementarySquareMatrix<IntElement> evaluate(const Valuation& v) = 0;
};
