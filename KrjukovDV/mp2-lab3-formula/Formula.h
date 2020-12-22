#pragma once
#include "Queue.h"
#include "Stack.h"
#include "Lexem.h"

class Formula 
{
    string str;

    bool number(const char c) { return c >= '0' && c <= '9'; }
    bool operation(const char c) { return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'; }
public:
    Formula() { str = ""; }
    Formula(string s) { str = s; }
    int checkBrackets(Queue<int>* queue = new Queue<int>)
    {
        Stack<int>* stack = new Stack<int>;
        int errors = 0;
        int iBrackets = 0;
        char c;
        for (int i = 0; i < str.length(); i++)
        {
            c = str[i];
            if (c == '(')
                stack->push(i + 1);
            else
                if (c == ')')
                {
                    if (stack->isEmpty())
                    {
                        queue->push(0);
                        queue->push(i + 1);
                        errors++;
                    }
                    else
                    {
                        queue->push(stack->pop());
                        queue->push(i + 1);
                    }
                }
        }
        while (!stack->isEmpty())
        {
            queue->push(stack->pop());
            queue->push(0);
            errors++;
        }
        return errors;
    }
    ~Formula() {};
    ICollection<Lexem*>* analysis()
    {
        if (checkBrackets())
            throw "wrong brackets";
        string st;
        char c;
        ICollection<Lexem*>* q = new Queue<Lexem*>;
        State state = q0;
        str += ' ';
        for (int i = 0; i < str.length(); i++)
        {
            c = str[i];
            if (state == q0)
            {
                st = c;
                if (number(c))
                {
                    state = q1;
                }
                if (operation(c))
                {
                    q->push(new Lexem(st, op));
                }
            }
            else
                if (state == q1)
                {
                    if (number(c))
                    {
                        st += c;
                        state = q1;
                    }
                    if (operation(c) || c == ' ')
                    {
                        int ival = atoi(st.c_str());
                        q->push(new Lexem(st, value, ival));
                        state = q0;
                        if (operation(c))
                        {
                            st = c;
                            q->push(new Lexem(st, op));
                        }

                    }
                }
        }

        return q;
    }
    int priority(Lexem* l)
    {
        if (l->getStr() == "(")
            return 0;
        if( l->getStr() == ")")
            return 1;
        if (l->getStr() == "-" || l->getStr() == "+")
            return 2;
        if (l->getStr() == "/" || l->getStr() == "*")
            return 3;



    }
    ICollection<Lexem*>* FormulaConverter()
    {
        ICollection<Lexem*>* q(analysis());
        ICollection<Lexem*>* PostfixForm = new Queue<Lexem*>;
        Stack<Lexem*>* stack = new Stack<Lexem*>;
        Lexem* work;
        Lexem* tmp;
        while (!q->isEmpty())
        {
            work = q->pop();
            if (work->getType() == value)
                PostfixForm->push(work);
            else
                if (stack->isEmpty() || priority(work) == 0)
                    stack->push(work);
                else
                {
                    if (priority(work) == 1)
                    {
                        while (priority(tmp = stack->pop()) != 0)
                            PostfixForm->push(tmp);
                    }
                    else
                    {
                        while (!(stack->isEmpty()))
                        {
                            tmp = stack->pop();
                            if(priority(tmp) >= priority(work))
                                PostfixForm->push(tmp);
                            else
                            {
                                stack->push(tmp);
                                break;
                            }  
                        }
                        
                        stack->push(work);
                    }
                }
        }
        while(!stack->isEmpty())
            PostfixForm->push(stack->pop());
        return PostfixForm;
    }
    double action(double a, double b, string c)
    {
        if (c == "+")
            return(a + b);
        if (c == "*")
            return(a * b);
        if (c == "-")
            return(a - b);
        if (c == "/")
            return(a / b);
    }
    double FormulaCalculator()
    {
        ICollection<Lexem*>* q(FormulaConverter());
        Stack<double>* stack = new Stack<double>;
        double a;
        Lexem* work;
        while (!q->isEmpty())
        {
            work = q->pop();
            if (work->getType() == value)
                stack->push(work->getVal());
            else
            {
                a = stack->pop();
                stack->push(action(stack->pop(), a, work->getStr()));
            }
            
        }
        return stack->pop();
    }
   
    
};
