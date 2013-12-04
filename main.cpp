#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>

#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

bool is_numircal(char c)
{
    return (c >='0' && c <='9') || (c == '.');
}


bool is_operator(string o)
{
    bool result = false;
    char opr = o[0];
    string operators = "%*/+-";
    for (string::size_type i = 0 ; i <operators.length() ; i++ )
    {
        result = ( result || (opr == operators[i]) ) ;
    }
    return result;
}


bool is_bracket(string o)
{
    return ((o[0] == '(') || (o[0] == ')'));
}

int opr_order(string o)void write_to_file(string data,const char* file_name)
{
    ofstream f;
    f.open(file_name, ios::app);
    f << data << "\n";
    f.flush();
    f.close();
}

{
    if (o == "+" || o == "-") return 0;
    if (o == "*" || o == "/" || o == "%") return 1;
    if (o == "^") return 2;

}

string normalize(string expr)
{
    string normalized_str;
    expr.erase(remove(expr.begin(), expr.end(), ' '), expr.end());

    for (string::size_type i = 0 ; i < expr.length(); i++)
    {
        char c = expr[i];
        char n = expr[i+1];

        normalized_str += c;
        if ( (is_numircal(n) && !is_numircal(c)) || !is_numircal(n))
        {
            normalized_str += " ";
        }
    }
    return normalized_str;
}

bool validate_brackets (string expr)
{
    stack <string> br_stack;
     istringstream iss(expr);

    do
    {
         string sub;
         iss >> sub;
         if (sub != "")
         {
             if(is_bracket(sub))
             {
                 if(sub == "(")
                 {
                     br_stack.push("(");
                 }
                 else
                 {
                     if(!br_stack.empty())
                     {
                         br_stack.pop();
                     }
                     else
                     {
                         return false;
                     }
                 }
             }
         }

    }while (iss);
    if(!br_stack.empty()) return false;
    return true;
}

bool validate_oprands_count (string expr)
{
    //note that this funcion is not 100% accurate. since it only counts .
    //but the oprands will be validated again in the solving function automaticly as it uses a stack.
    istringstream iss(expr);
    int operator_count = 0;
    int oprand_count  = 0;
   do
   {
        string sub;
        iss >> sub;
        if (sub != "")
        {
            if(is_operator(sub)) operator_count ++;
            else if (!is_bracket(sub)) oprand_count ++;
        }
    }while(iss);
    return (oprand_count > operator_count);
}

string validate (string expr)
{
    return expr;
    if (validate_brackets(expr) && validate_oprands_count(expr)) return expr;
    // note that adding one & will call the two functions in the condition
    else return "";

}

string get_rpn(string expr) // my implimentation of shunting-yard algorithm
{
    string rpn = "";
    stack<string> op_stack;
    istringstream iss(expr);

    do
    {
        string sub;
        iss >> sub;


        if (sub != "")
        {
            if (is_operator(sub))
            {
                if(!op_stack.empty())
                {
                    // the other empty check for when checking for 2 singl operators in the same preseds
                    //stack top is null
                    while((!op_stack.empty()) && (opr_order(sub) <= opr_order(op_stack.top())))
                    {
                        rpn += op_stack.top() + " ";
                        op_stack.pop();
                    };
                }
                op_stack.push(sub);
            }
            else if  (is_bracket(sub))
            {
                if (sub == ")")
                {
                    while(op_stack.top() !="(")
                    {
                        rpn += op_stack.top() +" ";
                        op_stack.pop();
                    };

                    op_stack.pop();
                }
                else
                {
                    op_stack.push(sub);
                }
            }
            else
            {
                rpn += sub + " ";
            }
        }
    }while(iss);

    while (!op_stack.empty())
    {
        rpn += op_stack.top() + " ";
        op_stack.pop();

    }

    return rpn;
}

template < class T> // to dump a stack with whtever data type it has
string get_stack_str(stack<T> s)
{
    stack<T> tmp ;
    ostringstream dump;


    while(!s.empty())
    {
        dump << s.top() << endl;
        tmp.push(s.top());
        s.pop();
    }

    while (!tmp.empty())

    {
        s.push(tmp.top());
        tmp.pop();
    }
    return dump.str();
}

void write_to_file(string data,const char* file_name)
{
    ofstream f;
    f.open(file_name, ios::app);
    f << data << "\n";
    f.flush();
    f.close();
}

template < class T>
void dump_stack(stack<T> s)
{
    write_to_file(get_stack_str(s),"stack_dump.txt");
}

double solve(string rpn)
{
    stack <double> data;
    istringstream iss(rpn);

    do {
        string token;
        iss >> token;

        if (token == "") continue; // for the empty token.

        // after validation only tokens that are expected are numbers and operators
        if(!is_operator(token))
        {
            double n;
            istringstream (token)>> n;
            data.push(n);
        }
        else
        {
            double op1 ,op2;
            if (!data.empty())
            {
                op2 = data.top();
                data.pop();
            }
            else goto invalid;

            if ( !data.empty())
            {

                op1 = data.top();
                data.pop();
            }else goto invalid;

            double result;

            if(token == "+") result = op1 + op2;
            else if (token == "-") result = op1 - op2;
            else if (token == "*") result = op1 * op2;
            else if (token == "/") result = op1 / op2;
            else if (token == "%") result = (int)op1 % (int)op2; // % cant works on ints

            data.push(result);
        }
        write_to_file("\n\n === Current Token : " + token + " ===\n","stack_dump.txt");
        dump_stack(data);

    }while(iss);

    return data.top();

    invalid :
    cout << "invalid parameters" << endl;
    return 0;

}

int main()
{
//    string expr = "( 10.0 + 2 ) + ( 3 + 45 )";
//    string expr = "5 + 10 - 1";
//    string expr = "5-1/3/5*(1.5)";
//    string expr = "(7.5*2)/3 + 3 * (5/2)";
//    string expr = "(())";

    string expr = "1+-2-";


    validate_brackets(normalize(expr));
    cout << "Normalized : "<< normalize(expr) << endl;
    cout << "Validated : " << validate(normalize(expr)) << endl;
    cout << "RPN : " << get_rpn(validate(normalize(expr))) << endl;
    cout << "result : " << solve(get_rpn(validate(normalize(expr)))) << endl;




    return 0;
}

