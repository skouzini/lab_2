#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <ctype.h>
#include "ExpressionManagerInterface.h"

using namespace std;


class ExpressionManager : public ExpressionManagerInterface
{
    private:
        bool balanced;
        string input;
        int first;
        string firstStr;
        int last;
        string lastStr;
        string infixString;
        string outStr;
        int stackNum;
        
    	int precedence(string test);
    	
    	bool isNum(const string test);
    	
    	int stoi (const string num);
    	
    	int opEval (const string op, int primary, int secondary);
    	
    	bool isValid(const string test);
    	
    	bool isOp(const string test);
        
    public:
    	ExpressionManager();
    	~ExpressionManager();
    
    	bool isBalanced(string expression);
    
    	string postfixToInfix(string postfixExpression);
    
    	string postfixEvaluate(string postfixExpression);
    
    	string infixToPostfix(string infixExpression);
    	
};