//
//  eval.cpp
//  CS32_HW2
//
//  Created by Philip Huang on 1/31/22.
//

#include "Map.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

int precedence(char ch);
bool isOperand(char ch);
bool isOperator(char ch);
bool isParenthesis(char ch);
bool isInfixToPostfix(string infix, string& postfix);
bool isEvalPostfix(string postfix,const Map& values,int& result);
int evaluate(string infix, const Map& values, string& postfix, int& result);

int precedence(char ch){ //checks operator precedence
    switch(ch){
        case ('*'):
        case ('/'):
            return 2;
        case ('+'):
        case ('-'):
            return 1;
        default:
            return 0;
    }
}

//Here is Carrano's pseudocode for the infix to postfix conversion step:
//
//    Initialize postfix to empty
//    Initialize the operator stack to empty
//    For each character ch in the infix string
//        Switch (ch)
//          case operand:
//            append ch to end of postfix
//            break
//          case '(':
//            push ch onto the operator stack
//            break
//          case ')':
//              // pop stack until matching '('
//            While stack top is not '('
//              append the stack top to postfix
//              pop the stack
//            pop the stack  // remove the '('
//            break
//          case operator:
//            While the stack is not empty and the stack top is not '('
//                    and precedence of ch <= precedence of stack top
//                append the stack top to postfix
//                    pop the stack
//                push ch onto the stack
//                break
//    While the stack is not empty
//        append the stack top to postfix
//            pop the stack


bool isInfixToPostfix(string infix, string& postfix){
    
    postfix = "";
    stack<char> operatorStack;
    

    string cleanInfix = "";
    for(int i = 0; i < infix.size(); i++){
        if (infix[i] == ' ') continue; //ignore spaces
        if (isalpha(infix[i])){
            if (islower(infix[i])){
                cleanInfix += infix[i];
            }
            else{ //is capital letter
                continue;
            }
        }
        else{ //not a letter
            if (isOperator(infix[i]) or isParenthesis(infix[i])){
                cleanInfix += infix[i];
            }
            else{ //is invalid character
                continue;
            }
        }
    }
    //Now that cleanInfix has removed spaces, we can implement the algorithm
    
    switch(cleanInfix[0]){//make sure we don't start off with operators or close parenthesis
        case '+':
        case '-':
        case '*':
        case '/':
        case ')':
            return false;
        default:
            break;
    }
    
    switch (cleanInfix[cleanInfix.size()-1]){//make sure we don't end up with operators or open parenthesis
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
            return false;
        default:
            break;
    }
    
    for (int i = 0; i < cleanInfix.size(); i++){ //iterate through the cleanInfix
        char ch = cleanInfix[i];
        switch(ch){
            case ('a'):
            case ('b'):
            case ('c'):
            case ('d'):
            case ('e'):
            case ('f'):
            case ('g'):
            case ('h'):
            case ('i'):
            case ('j'):
            case ('k'):
            case ('l'):
            case ('m'):
            case ('n'):
            case ('o'):
            case ('p'):
            case ('q'):
            case ('r'):
            case ('s'):
            case ('t'):
            case ('u'):
            case ('v'):
            case ('w'):
            case ('x'):
            case ('y'):
            case ('z'):
                if (i+1 < cleanInfix.size()){//if the current item is a character, we want to check the next item is valid
                    switch(cleanInfix[i+1]){//if next item is another character or open parenthesis, not valid infix
                        case ('a'):
                        case ('b'):
                        case ('c'):
                        case ('d'):
                        case ('e'):
                        case ('f'):
                        case ('g'):
                        case ('h'):
                        case ('i'):
                        case ('j'):
                        case ('k'):
                        case ('l'):
                        case ('m'):
                        case ('n'):
                        case ('o'):
                        case ('p'):
                        case ('q'):
                        case ('r'):
                        case ('s'):
                        case ('t'):
                        case ('u'):
                        case ('v'):
                        case ('w'):
                        case ('x'):
                        case ('y'):
                        case ('z'):
                        case '(':
                            return false;
                        default:
                            break;
                    }
                }
                postfix+=ch;
                break;
            case '(':
                if (i+1 < cleanInfix.size()){ //if ch is ( it cant be ) or the operators
                    switch(cleanInfix[i+1]){
                        case ')':
                        case '+':
                        case '-':
                        case '*':
                        case '/':
                            return false;
                        default:
                            break;
                    }
                }
                operatorStack.push(ch);
                break;
            case ')':
                if (i+1<cleanInfix.size()){ //if ch is ), can't be followed by letter or open parenthesis
                    switch(cleanInfix[i+1]){
                        case ('a'):
                        case ('b'):
                        case ('c'):
                        case ('d'):
                        case ('e'):
                        case ('f'):
                        case ('g'):
                        case ('h'):
                        case ('i'):
                        case ('j'):
                        case ('k'):
                        case ('l'):
                        case ('m'):
                        case ('n'):
                        case ('o'):
                        case ('p'):
                        case ('q'):
                        case ('r'):
                        case ('s'):
                        case ('t'):
                        case ('u'):
                        case ('v'):
                        case ('w'):
                        case ('x'):
                        case ('y'):
                        case ('z'):
                        case '(':
                            return false;
                        default:
                            break;
                            
                    }
                }
                while(!operatorStack.empty() and operatorStack.top() != '('){ //what if operator stack is empty, need to check validity before we pop
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                if (operatorStack.empty()){ //if we keep popping and never find ( and stack is empty
                    return false;
                }
                operatorStack.pop(); //gets rid of (
                break;
            case '+':
            case '-':
            case '*':
            case '/':
                if (i+1<cleanInfix.size()){ //got to make sure the next character isn't and close parenthesis or operator
                    switch(cleanInfix[i+1]){
                        case ('+'):
                        case ('-'):
                        case ('*'):
                        case ('/'):
                        case ')':
                            return false;
                        default:
                            break;
                    }
                }
                while (!operatorStack.empty() and operatorStack.top() != '(' and precedence(ch) <= precedence(operatorStack.top())){
                    postfix+=operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.push(ch);
                break;
        }
    }
    while(!operatorStack.empty()){
        if(operatorStack.top()=='('){ //parenthesis was mismatched
            return false;
        }
        postfix+=operatorStack.top();
        operatorStack.pop();
    }
    
    return true;
}

bool isOperand(char ch){
    switch(ch){
        case ('a'):
        case ('b'):
        case ('c'):
        case ('d'):
        case ('e'):
        case ('f'):
        case ('g'):
        case ('h'):
        case ('i'):
        case ('j'):
        case ('k'):
        case ('l'):
        case ('m'):
        case ('n'):
        case ('o'):
        case ('p'):
        case ('q'):
        case ('r'):
        case ('s'):
        case ('t'):
        case ('u'):
        case ('v'):
        case ('w'):
        case ('x'):
        case ('y'):
        case ('z'):
            return true;
    }
    return false;
}

bool isOperator(char ch){
    switch(ch){
        case ('+'):
        case ('-'):
        case ('*'):
        case ('/'):
            return true;
    }
    return false;
}
bool isParenthesis(char ch){
    switch(ch){
        case ('('):
        case (')'):
            return true;
    }
    return false;
}

//And here is his pseudocode for the evaluation of the postfix expression:
//
//    Initialize the operand stack to empty
//    For each character ch in the postfix string
//        if ch is an operand
//            push the value that ch represents onto the operand stack
//        else // ch is a binary operator
//            set operand2 to the top of the operand stack
//        pop the stack
//            set operand1 to the top of the operand stack
//        pop the stack
//        apply the operation that ch represents to operand1 and
//                operand2, and push the result onto the stack
//    When the loop is finished, the operand stack will contain one item,
//      the result of evaluating the expression

bool isEvalPostfix(string postfix,const Map& values,int& result){ //assumes postfix is valid
    stack<char> operandStack;
    for(int i=0; i<postfix.size(); i++){
        char ch = postfix[i];
        if(isOperand(ch)){
            int value;
            values.get(ch,value);
            operandStack.push(value);
        }
        else{ //ch is binary operator
            int operand2 = operandStack.top();
            operandStack.pop();
            int operand1 = operandStack.top();
            operandStack.pop();
            if (ch == '*'){
                int evaluate = operand1 * operand2;
                operandStack.push(evaluate);
                continue;
            }
            if (ch == '/'){
                if (operand2 == 0){
                    return false;
                }
                int evaluate = operand1 / operand2;
                operandStack.push(evaluate);
                continue;
            }
            if (ch == '+'){
                int evaluate = operand1 + operand2;
                operandStack.push(evaluate);
                continue;
            }
            if (ch == '-'){
                int evaluate = operand1 - operand2;
                operandStack.push(evaluate);
                continue;
            }
        }
    }
    result = operandStack.top(); // must make sure its valid infix
    return true;
}

int evaluate(string infix, const Map& values, string& postfix, int& result){
    bool isLowerCase = true; //to see if everything is lowerCase letters
    bool isInMap = true; //to see if everything is In the Map for letters
    if (infix == "") { //if infix is empty, set isLowerCase to false
        isLowerCase = false;
    }
    int letterCount = 0; //the number of letters in valid infix should be one more than the number of operators
    int operatorCount = 0; //number of operators in infix
    for (int i=0; i<infix.size();i++){
        if (infix[i] == ' ') continue; //empty space, we can skip it
        if (isalpha(infix[i])){ //if it is a letter
            if (islower(infix[i])){ //check if it is lowercase
                if (!values.contains(infix[i])){ //check if it is contained in Map
                    isInMap = false;
                }
                letterCount++;
                continue;
            }
            else{ //uppercase letter
                isLowerCase = false;
                break;
            }
        }
        else{ //not a letter
            if (isOperator(infix[i])){ //if it is an operator we increment count and continue
                operatorCount++;
                continue;
            }
            else if (isParenthesis(infix[i])){ //ignore the parenthesis
                continue;
            }
            else{ //if it does not contain valid symbols, set isLowerCase to false
                isLowerCase = false;
                break;
            }
        }
    }
    
    string postfixAttempt;// try to attempt an isInfixToPostfix, don't want to change postfix since it is passed by reference
    if (isLowerCase and (letterCount-1)==operatorCount and isInfixToPostfix(infix,postfixAttempt)){ //is valid infix?
        isInfixToPostfix(infix,postfix); //convert the infix to postfix.
    }
    else{ //not valid infix
        return 1;
    }
    if(!isInMap){ //if an element is not in map, but it is valid infix
        return 2;
    }
    if(!isEvalPostfix(postfix, values, result)){ //if valid infix, but at some point when evaluating postfix, we divide by 0
        return 3;
    }
    else{//otherwise, everything is good, valid infix and postfix can be evaluated
        isEvalPostfix(postfix,values,result); //result is pass by reference
        return 0;
    }
    
}
  // Evaluates an integer arithmetic expression
  //   If infix is a syntactically valid infix integer expression whose
  //   only operands are single lower case letters (whether or not they
  //   appear in the values map), then postfix is set to the postfix
  //   form of the expression; otherwise postfix may or may not be
  //   changed, result is unchanged, and the function returns 1.  If
  //   infix is syntactically valid but contains at least one lower
  //   case letter operand that does not appear in the values map, then
  //   result is unchanged and the function returns 2.  If infix is
  //   syntactically valid and all its lower case operand letters
  //   appear in the values map, then if evaluating the expression
  //   (using for each letter in the expression the value in the map
  //   that corresponds to it) attempts to divide by zero, then result
  //   is unchanged and the function returns 3; otherwise, result is
  //   set to the value of the expression and the function returns 0.

int main()
       {
           char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
           int  vals[] = {  3,  -9,   6,   2,   4,   1  };
           Map m;
           for (int k = 0; vars[k] != '#'; k++)
               m.insert(vars[k], vals[k]);
           string pf;
           int answer;
           assert(evaluate("a+ e", m, pf, answer) == 0 && pf == "ae+");
           assert(evaluate("a+ e", m, pf, answer) == 0  &&
                                   pf == "ae+"  &&  answer == -6);
           answer = 999;
           assert(evaluate("", m, pf, answer) == 1  &&  answer == 999);
           assert(evaluate("a+", m, pf, answer) == 1  &&  answer == 999);
           assert(evaluate("a i", m, pf, answer) == 1  &&  answer == 999);
           assert(evaluate("ai", m, pf, answer) == 1  &&  answer == 999);
           assert(evaluate("()", m, pf, answer) == 1  &&  answer == 999);
           assert(evaluate("()o", m, pf, answer) == 1  &&  answer == 999);
           assert(evaluate("y(o+u)", m, pf, answer) == 1  &&  answer == 999);
           assert(evaluate("y(*o)", m, pf, answer) == 1  &&  answer == 999);
           assert(evaluate("a+E", m, pf, answer) == 1  &&  answer == 999);
           assert(evaluate("(a+(i-o)", m, pf, answer) == 1  &&  answer == 999);
//             // unary operators not allowed:
           assert(evaluate("-a", m, pf, answer) == 1  &&  answer == 999);
           assert(evaluate("a*b", m, pf, answer) == 2  &&
                                   pf == "ab*"  &&  answer == 999);
           assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0  &&
                                   pf == "yoau-*+"  &&  answer == -1);
           answer = 999;
           assert(evaluate("o/(y-y)", m, pf, answer) == 3  &&
                                   pf == "oyy-/"  &&  answer == 999);
           assert(evaluate(" a  ", m, pf, answer) == 0  &&
                                   pf == "a"  &&  answer == 3);
           assert(evaluate("((a))", m, pf, answer) == 0  &&
                                   pf == "a"  &&  answer == 3);
    assert(evaluate("(",m,pf,answer) == 1);
    assert(evaluate(")",m,pf,answer) == 1);
    assert(evaluate("))",m,pf,answer) == 1);
    assert(evaluate("(()",m,pf,answer) == 1);
    assert(evaluate("*(-",m,pf,answer) == 1);
    assert(evaluate("roo",m,pf,answer) == 1);
    assert(evaluate("int*string",m,pf,answer) == 1);
    assert(evaluate("   e ",m,pf,answer)==0 && answer == -9);
//           cout << "Passed all tests" << endl;
    assert(evaluate("   E ",m,pf,answer)==1);
           cout << "Passed all tests" << endl;
}
