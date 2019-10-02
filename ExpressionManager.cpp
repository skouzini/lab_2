#include "ExpressionManager.h"

ExpressionManager::ExpressionManager() {
    balanced = false;
}
ExpressionManager::~ExpressionManager() {}

/*
* Checks whether an expression is balanced on its parentheses
*
* - The given expression will have a space between every number or operator
*
* @return true if expression is balanced
* @return false otherwise
*/

bool ExpressionManager::isBalanced(string expression) {
    stack<char> balanceStack;
    balanced = false;
    if (expression.at(0) == ']' || expression.at(0) ==  '}' || expression.at(0) ==  ')') {
    }
    else {
        for (int i = 0; i < expression.length(); i++) {
            
            if (expression.at(i) == '[' || expression.at(i) ==  '{' || expression.at(i) == '(') {
                balanceStack.push(expression.at(i));
            }
            
            if (expression.at(i) == ']') {
                if (balanceStack.top() == '[') {
                    balanceStack.pop();
                    balanced = true;
                }
                else {
                    while (balanceStack.size() > 0) {
                        balanceStack.pop();
                    }
                    balanced = false;
                    return balanced;
                }
            }
            else if (expression.at(i) == '}') {
                if (balanceStack.top() == '{') {
                    balanceStack.pop();
                    balanced = true;
                }
                else {
                    while (balanceStack.size() > 0) {
                        balanceStack.pop();
                    }
                    balanced = false;
                    return balanced;
                }
            }
            else if (expression.at(i) == ')') {
                if (balanceStack.top() == '(') {
                    balanceStack.pop();
                    balanced = true;
                }
                else {
                    while (balanceStack.size() > 0) {
                        balanceStack.pop();
                    }
                    balanced = false;
                    return balanced;
                }
            }
        }
        
        if (balanceStack.size() != 0) {
            while (balanceStack.size() > 0) {
                balanceStack.pop();
            }
            balanced = false;
        }
    }
    return balanced;

}

/**
* Converts a postfix expression into an infix expression
* and returns the infix expression.
*
* - The given postfix expression will have a space between every number or operator.
* - The returned infix expression must have a space between every number or operator.
* - Redundant parentheses are acceptable i.e. ( ( 3 * 4 ) + 5 ).
* - Check lab requirements for what will be considered invalid.
*
* return the string "invalid" if postfixExpression is not a valid postfix expression.
* otherwise, return the correct infix expression as a string.
*/
string ExpressionManager::postfixToInfix(string postfixExpression) {
    cout << "Postfix to Infix function working.\n";
    cout << postfixExpression << endl;
}

/*
* Evaluates a postfix expression returns the result as a string
*
* - The given postfix expression will have a space between every number or operator.
* - Check lab requirements for what will be considered invalid.
*
* return the string "invalid" if postfixExpression is not a valid postfix Expression
* otherwise, return the correct evaluation as a string
*/
string ExpressionManager::postfixEvaluate(string postfixExpression) {
    cout << "Postfix Evaluate function working.\n";
}

/*
* Converts an infix expression into a postfix expression
* and returns the postfix expression
*
* - The given infix expression will have a space between every number or operator.
* - The returned postfix expression must have a space between every number or operator.
* - Check lab requirements for what will be considered invalid.
*
* return the string "invalid" if infixExpression is not a valid infix expression.
* otherwise, return the correct postfix expression as a string.
*/
string ExpressionManager::infixToPostfix(string infixExpression) {
    cout << "Infix to Postfix function working\n";
}

int ExpressionManager::precedence(char test) {
    if (test == ')' || test == ']' || test == '}') {
        return 3;
    }
    else if (test == '*' || test == '/' || test == '%') {
        return 2;
    }
    else if (test == '+' || test == '-') {
        return 1;
    }
    else {
        return 0;
    }
}