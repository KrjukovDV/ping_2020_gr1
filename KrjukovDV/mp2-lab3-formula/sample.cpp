#include "Formula.h"

int main()
{
    ICollection<Lexem*>* q = new Queue<Lexem*>;
    Formula l("2*30/5 / (3*2)-3");
    q = l.analysis();
    while (!q->isEmpty())
    {
        cout << (*(q->pop()));
    }
    Queue<int>* s = new Queue<int>;
    int errors = l.checkBrackets(s);
    while (!s->isEmpty())
    {
        cout << endl << s->pop();
        cout << ' ' << s->pop();
    }
    cout<< endl << "Errors:" << errors << endl;
    q = l.FormulaConverter();
    while (!q->isEmpty())
    {
        cout << ' ' << (q->pop())->getStr();
    }
   
    cout <<endl << l.FormulaCalculator();
    return 0;
}