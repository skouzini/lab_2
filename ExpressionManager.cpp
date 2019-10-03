#include "ExpressionManager.h"

ExpressionManager::ExpressionManager() {
    balanced = false;
    input = "";
    first = -1;
    firstStr = "";
    last = -1;
    lastStr = "";
    infixString = "";
    outStr = "";
    stackNum = -1;
}
ExpressionManager::~ExpressionManager() {}

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

string ExpressionManager::postfixToInfix(string postfixExpression) {
    stack<string> toInfixStack;
    stringstream expression(postfixExpression);
    int counter = 0;
    
    while (!expression.eof()) {
        expression >> input;
        
        if (counter == 0 && !isNum(input)) {
            return "Error";
        }
        
        if (!isValid(input)) {
            return "Error";
        }
        
        if (isNum(input)) {
            toInfixStack.push(input);
        }
        else if (toInfixStack.size() >= 2) {
            lastStr = toInfixStack.top();
            toInfixStack.pop();
            firstStr = toInfixStack.top();
            toInfixStack.pop();
            
            infixString = "( " + firstStr + ' ' + input + ' ' + lastStr + " )";
            toInfixStack.push(infixString);
        }
        else {
            return "Error";
        }
        
        counter++;
    }
    
    infixString = toInfixStack.top();
    toInfixStack.pop();
    return infixString;
}

string ExpressionManager::postfixEvaluate(string postfixExpression) {
    stack<int> postfixEvalStack;
    stringstream expression(postfixExpression);
    int eval;
    int counter = 0;
    
    while (!expression.eof()) {
        expression >> input;
        
        if (counter == 0 && !isNum(input)) {
            return "Error";
        }
        
        if (!isValid(input)) {
            return "Error";
        }
        
        if (isNum(input)) {
           stackNum = stoi(input);
           postfixEvalStack.push(stackNum);
        }
        else if (postfixEvalStack.size() >=2) {
            last = postfixEvalStack.top();
            postfixEvalStack.pop();
            first = postfixEvalStack.top();
            postfixEvalStack.pop();
            
            postfixEvalStack.push(opEval(input, first, last));
        }
        else {
            return "Error";
        }
        
        counter++;
    }
    return to_string(postfixEvalStack.top());
}

string ExpressionManager::infixToPostfix(string infixExpression) {

    stack <string> opStack;
    stringstream expression(infixExpression);
    bool isFound = false;
    int counter = 0;

    while (!expression.eof()) {
        expression >> input;
        
        if (counter == 0 && !isNum(input)) {
            return "Error";
        }
        
        if (!isValid(input)) {
            return "Error";
        }
        
        if (isNum(input)) {
            outStr += input + " ";
        }
        else if (opStack.size() == 0 || 
            precedence(input) == 0 || 
            (precedence(input) > precedence(opStack.top()) && precedence(input) != 3)) {
                opStack.push(input);
        }
        else if ((precedence(input) <= precedence(opStack.top())) && precedence(input) != 3) {
            while (opStack.size() != 0 && (precedence(input) <= precedence(opStack.top()))) {
                if (opStack.size() != 0) {
                    outStr += opStack.top() + " ";
                    opStack.pop();
                }
                else {
                   break; 
                }
            }
            
            opStack.push(input);
        }
        else if (precedence(input) == 3) {
            while (precedence(opStack.top()) != 0) {
                outStr += opStack.top() + " ";
                opStack.pop();
            }
            
            if ((opStack.top() == "(" && input == ")") || 
                (opStack.top() == "[" && input == "]") || 
                (opStack.top() == "{" && input == "}")) {
                    opStack.pop();
            }
            else {
                return "Error";
            }
        }
        
        counter++;
    }
    while (opStack.size() != 0) {
        outStr += opStack.top() + " ";
        opStack.pop();
    }
    
    return outStr;
}

bool ExpressionManager::isValid(const string test) {
    bool validated = false;
    
    if (isNum(test)) {
        validated = true;
    }
    else if (isOp(test)) {
        validated = true;
    }
    
    return validated;
}

bool ExpressionManager::isOp(const string test) {
    bool opYes = false;
    
    if (test == "(" || 
        test == ")" || 
        test == "[" || 
        test == "]" || 
        test == "{" || 
        test == "}" || 
        test == "*" || 
        test == "/" || 
        test == "%" || 
        test == "-" || 
        test == "+") {
            opYes = true;
    }
        
    return opYes;
}

int ExpressionManager::precedence(string test) {
    if (test == ")" || test == "]" || test == "}") {
        cout << test << ": precedence 3\n"; ///////////
        return 3;
    }
    else if (test == "*" || test == "/" || test == "%") {
        cout << test << ": precedence 2\n"; ///////////
        return 2;
    }
    else if (test == "+" || test == "-") {
        cout << test << ": precedence 1\n"; ///////////
        return 1;
    }
    else  if (test == "(" || test == "[" || test == "{") {
        cout << test << ": precedence 0\n"; ///////////
        return 0;
    }
    else {
        cout << test << ": precedence -1\n"; ///////////
        return -1;
    }
}

bool ExpressionManager::isNum(const string test) {
    bool numYes = false;
    cout << "testing isNum: " << test << endl; /////////
    
    for (int i = 0; i < test.size(); i++) {
        if (isdigit(test.at(i))) {
            numYes = true;
        }
        else {
            numYes = false;
            return numYes;
        }
    }
    
    return numYes;
}

int ExpressionManager::stoi(const string num) {
    int out = -1;
    stringstream convert(num);
    
    convert >> out;

    return out;
}

int ExpressionManager::opEval(const string op, int primary, int secondary) {
    if (op == "+") {
        return primary + secondary;
    }
    else if (op == "-") {
        return primary - secondary;
    }
    else if (op == "*") {
        return primary * secondary;
    }
    else if (op == "/") {
        return primary / secondary;
    }
    else if (op == "%") {
        return primary % secondary;
    }
}