#include <iostream>

using namespace std;
/*���D�G
��{ Polynomial ���O
�ھڹ�1�P��2���O�w�q����H��ƫ��O�]ADT�^�P�p����Ʀ����A��@ Polynomial ���O�C

���g C++ ���
���g�Ω��J�P��X�� C++ ��ƨӳB�z��2��ܪ��h������ơC�o�Ǩ�ƻݭn���� << �M >> �B��l�C
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
	float coef;	//�Y��
	int exp;	//����
};


Polynomial::Polynomial()
{
}
