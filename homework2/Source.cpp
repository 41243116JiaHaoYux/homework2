#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// 定義 Term 類別
class Term {
public:
    float coef; // 係數
    int exp;    // 指數

    Term(float c = 0, int e = 0) : coef(c), exp(e) {}
};

// 定義 Polynomial 類別
class Polynomial {
public:
    Polynomial(); // 預設建構子
    Polynomial Add(const Polynomial& poly) const;  
    Polynomial Mult(const Polynomial& poly) const;
    float Eval(float x) const;                     
    friend ostream& operator<<(ostream& out, const Polynomial& poly); // 輸出運算子
    friend istream& operator>>(istream& in, Polynomial& poly);        // 輸入運算子

private:
    vector<Term> termArray; // 儲存多項式中的非零
    void Simplify();        // 簡化
};

// 預設建構子
Polynomial::Polynomial() {}

// 多項式加法
Polynomial Polynomial::Add(const Polynomial& poly) const {
    Polynomial result;
    size_t i = 0, j = 0;

    while (i < termArray.size() && j < poly.termArray.size()) {
        if (termArray[i].exp == poly.termArray[j].exp) {
            float newCoef = termArray[i].coef + poly.termArray[j].coef;
            if (newCoef != 0)
                result.termArray.emplace_back(newCoef, termArray[i].exp);
            i++;
            j++;
        }
        else if (termArray[i].exp > poly.termArray[j].exp) {
            result.termArray.push_back(termArray[i]);
            i++;
        }
        else {
            result.termArray.push_back(poly.termArray[j]);
            j++;
        }
    }

    // 加入剩餘項
    while (i < termArray.size()) result.termArray.push_back(termArray[i++]);
    while (j < poly.termArray.size()) result.termArray.push_back(poly.termArray[j++]);

    return result;
}

// 多項式乘法
Polynomial Polynomial::Mult(const Polynomial& poly) const {
    Polynomial result;

    for (const auto& term1 : termArray) {
        for (const auto& term2 : poly.termArray) {
            result.termArray.emplace_back(term1.coef * term2.coef, term1.exp + term2.exp);
        }
    }

    result.Simplify();
    return result;
}

// 多項式求值
float Polynomial::Eval(float x) const {
    float result = 0;

    for (const auto& term : termArray) {
        result += term.coef * pow(x, term.exp);
    }

    return result;
}

// 化簡
void Polynomial::Simplify() {
    if (termArray.empty()) return;

    // 排序，按指數降序
    sort(termArray.begin(), termArray.end(), [](const Term& a, const Term& b) {
        return a.exp > b.exp;
        });

    // 合併同類項
    vector<Term> simplified;
    simplified.push_back(termArray[0]);

    for (size_t i = 1; i < termArray.size(); i++) {
        if (termArray[i].exp == simplified.back().exp) {
            simplified.back().coef += termArray[i].coef;
        }
        else {
            simplified.push_back(termArray[i]);
        }
    }

    // 去除係數為 0 的項
    termArray.clear();
    for (const auto& term : simplified) {
        if (term.coef != 0)
            termArray.push_back(term);
    }
}

// 輸出運算子重載
ostream& operator<<(ostream& out, const Polynomial& poly) {
    if (poly.termArray.empty()) {
        out << "0";
        return out;
    }

    for (size_t i = 0; i < poly.termArray.size(); i++) {
        const auto& term = poly.termArray[i];
        if (i > 0 && term.coef > 0) out << "+";
        out << term.coef;
        if (term.exp > 0) out << "x^" << term.exp;
    }

    return out;
}

// 輸入運算子重載
istream& operator>>(istream& in, Polynomial& poly) {
    int n; // 輸入的項數
    cout << "Enter number of terms: ";
    in >> n;
    poly.termArray.clear();

    for (int i = 0; i < n; i++) {
        float coef;
        int exp;
        cout << "Enter coefficient and exponent (separated by space): ";
        in >> coef >> exp;
        poly.termArray.emplace_back(coef, exp);
    }

    poly.Simplify();
    return in;
}

// 主函數測試
int main() {
    Polynomial p1, p2;
    cout << "Enter first polynomial:\n";
    cin >> p1;

    cout << "Enter second polynomial:\n";
    cin >> p2;

    cout << "P1: " << p1 << endl;
    cout << "P2: " << p2 << endl;

    Polynomial sum = p1.Add(p2);
    cout << "Sum: " << sum << endl;

    Polynomial product = p1.Mult(p2);
    cout << "Product: " << product << endl;

    float x;
    cout << "Enter value of x for evaluation: ";
    cin >> x;
    cout << "P1(" << x << ") = " << p1.Eval(x) << endl;
    cout << "P2(" << x << ") = " << p2.Eval(x) << endl;

    return 0;
}
