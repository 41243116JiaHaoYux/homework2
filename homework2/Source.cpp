#include <iostream>

using namespace std;
/*問題：
實現 Polynomial 類別
根據圖1與圖2分別定義的抽象資料型別（ADT）與私有資料成員，實作 Polynomial 類別。

撰寫 C++ 函數
撰寫用於輸入與輸出的 C++ 函數來處理圖2表示的多項式資料。這些函數需要重載 << 和 >> 運算子。
*/
//p(x)=(a0*x^e0)+(a1*x^e1)+....+(an*x^en)
class Polynomial
{
public:
	Polynomial();
	Polynomial Add(Polynomial poly);
	Polynomial Mult(Polynomial poly);
	float Eval(float f);
private:
	Term* termArray;//array off nonzero terms
	int capacity;	//size of termArray
	int term;		//number of nonzero terms
};

class Term
{
	friend Polynomial;
private:
	float coef;	//係數
	int exp;	//指數
};


Polynomial::Polynomial()
{
}
