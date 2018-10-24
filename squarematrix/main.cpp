#define CATCH_CONFIG_RUNNER

#include "catch.hpp"
#include "compositematrix.h"
#include <stack>

using VariableElement = TElement<char>;
using IntElement = TElement<int>;

bool isSquareMatrix(const string&);

TEST_CASE("Muuttujatesti""[VariableElement]"){
	VariableElement elementti1('x');
	CHECK(elementti1.toString() == "x");
	
	char muuttuja = elementti1.getVal();
	CHECK(muuttuja == 'x');
	
	elementti1.setVal('y');
	CHECK(elementti1.toString() == "y");
	
	unique_ptr<Element> pointteri;
	pointteri = move(elementti1.clone());
	CHECK(pointteri.get()->toString() == "y");
	
	Valuation evaluointi('y', 10);
	CHECK(elementti1.evaluate(evaluointi) == 10);
	
	VariableElement elementti2('y');
	CHECK(elementti1.operator==(elementti2) == true);
}

TEST_CASE("Kokonaislukutesti""[IntElement]"){
	IntElement element(5);
	IntElement ele(10);
	IntElement elementti(5);
	int osoitin;
	
	IntElement elementti2(ele);
	CHECK(elementti2.getVal() == 10);
	
	CHECK(element.operator==(ele) == false);
	CHECK(element.operator==(elementti) == true);
	CHECK(element.getVal() == 5);
	CHECK(ele.getVal() == 10);
	IntElement plussa = element.operator+=(ele);
	CHECK(plussa.getVal() == 15);
	IntElement miinus = element.operator-=(ele);
	CHECK(miinus.getVal() == 5);
	IntElement kerto = element.operator*=(ele);
	CHECK(kerto.getVal() == 50);
	
	unique_ptr<Element> pointteri;
	IntElement elementti1(10);
	pointteri = move(elementti1.clone());
	CHECK((pointteri.get())->toString() == "10");
}

TEST_CASE("Symbolimatriisitesti""[SymbolicSquareMatrix]"){
	SymbolicSquareMatrix matriisi1("[[1,x,2][1,x,2][1,x,2]]");
	CHECK(matriisi1.toString() == "[[1,x,2][1,x,2][1,x,2]]");
	
	SymbolicSquareMatrix matriisi2(matriisi1);
	CHECK(matriisi2.toString() == "[[1,x,2][1,x,2][1,x,2]]");
	
	SymbolicSquareMatrix matriisi3;
	matriisi3.operator=(matriisi2);
	CHECK(matriisi3.toString() == "[[1,x,2][1,x,2][1,x,2]]");
	
	SymbolicSquareMatrix matriisi4(matriisi3.transpose());
	CHECK(matriisi4.toString() == "[[1,1,1][x,x,x][2,2,2]]");
	
	CHECK(matriisi2.operator==(matriisi3) == true);
	
	Valuation value('x', 3);
	ConcreteSquareMatrix matriisi5(matriisi4.evaluate(value));
	CHECK(matriisi5.toString() == "[[1,1,1][3,3,3][2,2,2]]");
	
	unique_ptr<SquareMatrix> pointteri = move(matriisi4.clone());
	CHECK(pointteri->toString() == "[[1,1,1][x,x,x][2,2,2]]");
}

TEST_CASE("Kokonaislukumatriisitesti""[ConcreteSquareMatrix]"){
	ConcreteSquareMatrix matriisi1("[[1,2,3][1,2,3][1,2,3]]");
	CHECK(matriisi1.toString() == "[[1,2,3][1,2,3][1,2,3]]");
	
	ConcreteSquareMatrix matriisi2(matriisi1);
	CHECK(matriisi2.toString() == "[[1,2,3][1,2,3][1,2,3]]");
	
	ConcreteSquareMatrix matriisi3("[[4,5,6][4,5,6][4,5,6]]");
	ConcreteSquareMatrix matriisi4(matriisi1.operator=(matriisi3));
	CHECK(matriisi4.toString() == "[[4,5,6][4,5,6][4,5,6]]");
	
	ConcreteSquareMatrix matriisi5(matriisi4.transpose());
	CHECK(matriisi5.toString() == "[[4,4,4][5,5,5][6,6,6]]");
	
	ConcreteSquareMatrix matriisi6("[[1,2,3][1,2,3][1,2,3]]");
	ConcreteSquareMatrix matriisi7(matriisi6);
	ConcreteSquareMatrix matriisi8(matriisi7.operator+=(matriisi6));
	CHECK(matriisi8.toString() == "[[2,4,6][2,4,6][2,4,6]]");
	
	ConcreteSquareMatrix matriisi9(matriisi8.operator-=(matriisi6));
	CHECK(matriisi9.toString() == "[[1,2,3][1,2,3][1,2,3]]");
	
	CHECK(matriisi9.operator==(matriisi6) == true);
	
	ConcreteSquareMatrix matriisi10(matriisi9.operator*=(matriisi6));
	CHECK(matriisi10.toString() == "[[6,12,18][6,12,18][6,12,18]]");
	
	Valuation v('x', 3);
	ConcreteSquareMatrix matriisi11(matriisi10.evaluate(v));
	CHECK(matriisi11.toString() == "[[6,12,18][6,12,18][6,12,18]]");
}

ConcreteSquareMatrix plussa(const ConcreteSquareMatrix& m1, const ConcreteSquareMatrix& m2){
	ConcreteSquareMatrix matriisi1(m1);
	ConcreteSquareMatrix matriisi2(matriisi1.operator+=(m2));
	return matriisi2;
}

ConcreteSquareMatrix miinus(const ConcreteSquareMatrix& m1, const ConcreteSquareMatrix& m2){
	ConcreteSquareMatrix matriisi1(m1);
	ConcreteSquareMatrix matriisi2(matriisi1.operator-=(m2));
	return matriisi2;
}

ConcreteSquareMatrix kerto(const ConcreteSquareMatrix& m1, const ConcreteSquareMatrix& m2){
	ConcreteSquareMatrix matriisi1(m1);
	ConcreteSquareMatrix matriisi2(matriisi1.operator*=(m2));
	return matriisi2;
}

TEST_CASE("Komposiittimatriisitesti""[CompositeSquareMatrix]"){
	CSMFunction funktio = plussa;
	ConcreteSquareMatrix matriisi1("[[1,2,3][1,2,3][1,2,3]]");
	ConcreteSquareMatrix matriisi2(matriisi1);
	CompositeSquareMatrix komposiitti1(matriisi1, matriisi2, funktio, '+');
	CHECK(komposiitti1.toString() == "([[1,2,3][1,2,3][1,2,3]] + [[1,2,3][1,2,3][1,2,3]])");
	
	Valuation v('x', 2);
	ConcreteSquareMatrix matriisi3(komposiitti1.evaluate(v));
	CHECK(matriisi3.toString() == "[[2,4,6][2,4,6][2,4,6]]");
	
	CompositeSquareMatrix komposiitti2(komposiitti1);
	CHECK(komposiitti2.toString() == "([[1,2,3][1,2,3][1,2,3]] + [[1,2,3][1,2,3][1,2,3]])");
	
	ConcreteSquareMatrix matriisi4("[[4,5,6][4,5,6][4,5,6]]");
	ConcreteSquareMatrix matriisi5(matriisi4);
	CompositeSquareMatrix komposiitti3(matriisi4, matriisi5, funktio, '+');
	CHECK(komposiitti3.toString() == "([[4,5,6][4,5,6][4,5,6]] + [[4,5,6][4,5,6][4,5,6]])");
	
	komposiitti2.operator=(komposiitti3);
	CHECK(komposiitti2.toString() == "([[4,5,6][4,5,6][4,5,6]] + [[4,5,6][4,5,6][4,5,6]])");
	
	SymbolicSquareMatrix symboli1("[[1,1,1][x,x,x][3,3,3]]");
	CompositeSquareMatrix komposiitti4(matriisi1, symboli1, funktio, '+');
	CHECK(komposiitti4.toString() == "([[1,2,3][1,2,3][1,2,3]] + [[1,1,1][x,x,x][3,3,3]])");
	
	ConcreteSquareMatrix matriisi6(komposiitti4.evaluate(v));
	CHECK(matriisi6.toString() == "[[2,3,4][3,4,5][4,5,6]]");
	
	SymbolicSquareMatrix symboli2(symboli1);
	CompositeSquareMatrix komposiitti5(symboli1, symboli2, funktio, '+');
	CHECK(komposiitti5.toString() == "([[1,1,1][x,x,x][3,3,3]] + [[1,1,1][x,x,x][3,3,3]])");
	
	ConcreteSquareMatrix matriisi7(komposiitti5.evaluate(v));
	CHECK(matriisi7.toString() == "[[2,2,2][4,4,4][6,6,6]]");
	
	funktio = miinus;
	
	CompositeSquareMatrix komposiitti6(matriisi4, matriisi1, funktio, '-');
	CHECK(komposiitti6.toString() == "([[4,5,6][4,5,6][4,5,6]] - [[1,2,3][1,2,3][1,2,3]])");
	
	ConcreteSquareMatrix matriisi8(komposiitti6.evaluate(v));
	CHECK(matriisi8.toString() == "[[3,3,3][3,3,3][3,3,3]]");
	
	SymbolicSquareMatrix symboli3("[[4,4,4][y,y,y][6,6,6]]");
	CompositeSquareMatrix komposiitti7(symboli3, matriisi1, funktio, '-');
	CHECK(komposiitti7.toString() == "([[4,4,4][y,y,y][6,6,6]] - [[1,2,3][1,2,3][1,2,3]])");
	
	v.val('y', 5);
	
	ConcreteSquareMatrix matriisi9(komposiitti7.evaluate(v));
	CHECK(matriisi9.toString() == "[[3,2,1][4,3,2][5,4,3]]");
	
	SymbolicSquareMatrix symboli4("[[1,1,1][x,x,x][3,3,3]]");
	CompositeSquareMatrix komposiitti8(symboli3, symboli4, funktio, '-');
	CHECK(komposiitti8.toString() == "([[4,4,4][y,y,y][6,6,6]] - [[1,1,1][x,x,x][3,3,3]])");
	
	ConcreteSquareMatrix matriisi10(komposiitti8.evaluate(v));
	CHECK(matriisi10.toString() == "[[3,3,3][3,3,3][3,3,3]]");
	
	funktio = kerto;
	
	CompositeSquareMatrix komposiitti9(matriisi1, matriisi2, funktio, '*');
	CHECK(komposiitti9.toString() == "([[1,2,3][1,2,3][1,2,3]] * [[1,2,3][1,2,3][1,2,3]])");
	
	ConcreteSquareMatrix matriisi11(komposiitti9.evaluate(v));
	CHECK(matriisi11.toString() == "[[6,12,18][6,12,18][6,12,18]]");
	
	CompositeSquareMatrix komposiitti10(matriisi1, symboli1, funktio, '*');
	CHECK(komposiitti10.toString() == "([[1,2,3][1,2,3][1,2,3]] * [[1,1,1][x,x,x][3,3,3]])");
	
	ConcreteSquareMatrix matriisi12(komposiitti10.evaluate(v));
	CHECK(matriisi12.toString() == "[[1,16,81][1,16,81][1,16,81]]");
	
	CompositeSquareMatrix komposiitti11(symboli1, symboli3, funktio, '*');
	CHECK(komposiitti11.toString() == "([[1,1,1][x,x,x][3,3,3]] * [[4,4,4][y,y,y][6,6,6]])");
	
	ConcreteSquareMatrix matriisi13(komposiitti11.evaluate(v));
	CHECK(matriisi13.toString() == "[[64,125,216][128,250,432][192,375,648]]");
} 

int main(){
	bool onko = false;
	string jono;
	int valinta = 0;
	int result = Catch::Session().run();
	string matriisi;
	bool matriisitesti = false;
	vector<string> vektori;
	stack<string, vector<string>> stakki (vektori);
	char muuttuja;
	Valuation valuaatio;
	int arvo;
	SymbolicSquareMatrix symbolimatriisi;
	ConcreteSquareMatrix oikeamatriisi;
	SymbolicSquareMatrix symbolimatriisi2;
	CSMFunction funktio1 = plussa;
	CSMFunction funktio2 = miinus;
	CSMFunction funktio3 = kerto;
	string kompo;
	
	
	do{
		cout << "Anna suoritettava operaatio!" << endl;
		cout << "Mahdolliset operaatiot ovat:" << endl;
		cout << "1. Kirjoita 'matriisi' antaaksesi uuden matriisin pinoon." << endl;
		cout << "2. Syota '+', '-' tai '*', jolloin annettu operaatio suorittaan kahdelle paallimmaiselle matriisille." << endl;
		cout << "3. Syota 'muuttuja' syottaaksesi muuttujan, jolla kykenet muuttamaan matriisien muuttujien arvoja." << endl;
		cout << "4. Syota '=' evaluoidaksesi paallimmaisen matriisin. Matriisi tulostetaan naytolle." << endl;
		cout << "5. Kirjoita 'quit' sulkeaksesi sovelluksen." << endl; 
		cin >> jono;
		
		if(jono == "matriisi"){
			valinta = 1;
		}
		
		if(jono == "+" || jono == "-" || jono == "*"){
			valinta = 2;
		}
		
		if(jono == "muuttuja"){
			valinta = 3;
		}
		
		if(jono == "="){
			valinta = 4;
		}
		
		if(jono == "quit"){
			valinta = 5;
		}
		
		if(valinta == 0){
			cout << "\nVirheellinen syote!" << endl;
		}
		
		switch(valinta){
			
			case 1:
				cout << "Syota matriisi: ";
				cin >> matriisi;
				matriisitesti = isSquareMatrix(matriisi);
				while(matriisitesti == false){
					cout << "Virheellinen matriisi! Anna matriisi uudelleen: ";
					cin >> matriisi;
					matriisitesti = isSquareMatrix(matriisi);
				}
				stakki.push(matriisi);
				break;
			case 2:
				kompo = kompo + stakki.top();
				symbolimatriisi.operator=(stakki.top());
				stakki.pop();
				kompo = kompo + jono;
				kompo = kompo + stakki.top();
				symbolimatriisi2.operator=(stakki.top());
				stakki.pop();
				if(jono == "+"){
					CompositeSquareMatrix komposiitti(symbolimatriisi, symbolimatriisi2, funktio1, '+');
					oikeamatriisi.operator=(komposiitti.evaluate(valuaatio));
					matriisi = oikeamatriisi.toString();
					stakki.push(matriisi);
				cout << kompo << endl;
				kompo.clear();
				}
				if(jono == "-"){
					CompositeSquareMatrix komposiitti(symbolimatriisi, symbolimatriisi2, funktio2, '-');
					oikeamatriisi.operator=(komposiitti.evaluate(valuaatio));
					matriisi = oikeamatriisi.toString();
					stakki.push(matriisi);
				cout << kompo << endl;
				kompo.clear();
				}
				if(jono == "*"){
					CompositeSquareMatrix komposiitti(symbolimatriisi, symbolimatriisi2, funktio3, '*');
					oikeamatriisi.operator=(komposiitti.evaluate(valuaatio));
					matriisi = oikeamatriisi.toString();
					stakki.push(matriisi);
				cout << kompo << endl;
				kompo.clear();
				}
				break;
			case 3:
				cout << "Anna muuttuja: ";
				cin >> muuttuja;
				cout << "Anna arvo: ";
				cin >> arvo;
				valuaatio.val(muuttuja, arvo);
				break;
			case 4:
				symbolimatriisi.operator=(stakki.top());
				oikeamatriisi.operator=(symbolimatriisi.evaluate(valuaatio));
				cout << oikeamatriisi.toString() << endl;
				break;
			case 5:
				onko = true;
				break;
		}
	}while (onko == false);
	
	return result;
	return 0;
}

bool isSquareMatrix(const string& jono){
    
    using namespace std;
    
    int koko = jono.length();
    int laskuri2 = 0;
    int laskuri3 = 0;
    int turha;
    bool onko;
    
   
    if (jono.at(0) != '['){
    		onko = false;
    		return onko;
	}
	
	if (jono.at(1) != '['){
		onko = false;
		return onko;
	}
	for (int j = 2; j < koko; j++){
		if (isdigit(jono.at(j)) || isalpha(jono.at(j))){
			laskuri2 = laskuri2 + 1;
		}
		if (jono.at(j) == ']'){
			laskuri3 = laskuri3 + 1;
			if(jono.at(j+1) != '['){
				break;
			}
		}
		else {
			turha++;
		}
	}
	
	laskuri2 = laskuri2 / laskuri3;

    if (laskuri2 == laskuri3){
    	onko = true;
	}
	else{
		onko = false;
	}
	return onko;
}
