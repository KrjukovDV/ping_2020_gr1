#pragma once
#include <iostream>
#include"Queue.h"
using namespace std;
enum TypeLexem { op, value};
enum State { q0, q1};
class Lexem
{
    string s;
    TypeLexem type;
    int val;
public:
    Lexem() { s = ""; type = op; val = -1; }
    Lexem(string s, TypeLexem type, int val = -1)
    {
        this->s = s;
        this->type = type;
        this->val = val;
    }
    ~Lexem() {}
    TypeLexem getType() { return type; }
    int getVal() { return val; }
    string getStr() { return s; }

    friend ostream& operator<< (ostream& o, const Lexem& p)
    {
        o << "|" << p.s << ", " << p.type << "|";
        return o;
    }

};