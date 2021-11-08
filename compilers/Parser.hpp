#pragma once

#include "FlexScanner.hpp"
#include "Token.hpp"
#include "vector"
#include<algorithm>
#include<stack>
#define COUNT 10

const char * categoriesArray[] = {
        "<PAR_IZQUIERDO>",
        "<PAR_DERECHO>",
        "<OP_RESTA>",
        "<OP_SUMA>",
        "<OP_MULL>",
        "<NUMERO>",
        "<END>",
        "<ERROR>"
};

namespace utec {
namespace compilers {

// Grammar:
// S -> AB
// A -> aA | a
// B -> bB | b

class Node{
public:
    bool terminal = false;
    std::string value;
    std::vector<Node*> children;
    Node* parent;
    Node(Node* parent, bool terminal, std::string value) {
        this->parent = parent;
        this->value = value;
        this->terminal = terminal;
    }
};

void printBT(const std::string& prefix, const Node* node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        if (node->value == "")
            std::cout << "─┐" << std::endl;
        else
            std::cout << node->value << std::endl;

        // enter the next tree level - left and right branch
        for (int i = 0; i < node->children.size(); i++){
            if (i==node->children.size()-1)
                printBT( prefix + (isLeft ? "│   " : "    "), node->children[i], false);
            else
            printBT( prefix + (isLeft ? "│   " : "    "), node->children[i], true);

        }
    }
}

void printBT(const Node* node)
{
    printBT("", node, false);
}

bool error = false;

class Parser {

    bool accept(Categoria c){
        if (scanner.query_token()._atributo == c){
            scanner.get_token();
            return true;
        }
        return false;
    }

    bool expect(Categoria c){
        if (accept(c)){
            return true;
        }
        std::cout << "Expected symbol \"" << categoriesArray[c - Categoria::parIzquierdo] << "\" instead of: \"" <<  scanner.query_token()._lexema  <<"\"\n";
        error = true;
        return false;
    }

    void exp(Node* &root) {
        term(root);
        while (scanner.query_token()._atributo == Categoria::opResta || scanner.query_token()._atributo == Categoria::opSuma) {
            std::string op = scanner.query_token()._lexema;
            auto* last = root->children[root->children.size() - 1];
            auto* clone = new Node(last, true, last->value);
            last->terminal = false;
            last->value = "";
            //(root)->children.insert(root->children.begin(), child);
            scanner.get_token();
            //auto* parent = new Node(nullptr, false, "");
            clone->children = last->children;
            last->children.clear();
            last->children.push_back(clone);
            auto* child = new Node(root, true, op);
            last->children.push_back(child);
            (root)->parent = last;
            //root = last;
            //printBT(root);
            term(last);
        }
    }

    void term(Node* &root) {
        factor(root);
        while (scanner.query_token()._atributo == Categoria::opMull) {
            auto* last = root->children[root->children.size() - 1];
            auto* clone = new Node(last, true, last->value);
            last->terminal = false;
            last->value = "";
            //(root)->children.insert(root->children.begin(), child);
            scanner.get_token();
            //auto* parent = new Node(nullptr, false, "");
            clone->children = last->children;
            last->children.clear();
            last->children.push_back(clone);
            auto* child = new Node(root, true, "*");
            last->children.push_back(child);
            (root)->parent = last;
            //root = last;
            //printBT(root);
            factor(last);
        }
    }

    void factor(Node* &root) {
        std::string last_token = scanner.query_token()._lexema;
        if (accept(Categoria::parIzquierdo)){
            auto* parent = new Node(nullptr, false, "");
            //(root)->children.insert(root->children.begin(), child);

            exp(root);
            //root = parent;
            expect(Categoria::parDerecho);
            auto* grandParent = new Node(nullptr, false, "");
            parent->children.push_back(root);
            grandParent->children.push_back(parent);
            root->parent = grandParent;
            root = root->parent;

        } else if (accept(Categoria::numero)){
            auto* child = new Node(root, true, last_token);
            (root)->children.push_back(child);
        } else if (accept(Categoria::END)){
            ;
        }
        else {
            std::cout << "Unexpected Symbol: \"" << scanner.query_token()._lexema << "\"\n";
            error = true;
        }
    }

public:
    int result = 0;
    int solve(Node* root){
        if (root->children.size() <= 1) {
            if (root->value != "") {
                root->value.erase(remove_if(root->value.begin(), root->value.end(), isspace), root->value.end());
                return stoi(root->value);
            } else
                return solve(root->children[0]);
        } else {
            int a = solve(root->children[0]);
            int b = solve(root->children[root->children.size() - 1]);
            int result;
            std::string sign;
            for (int j = 0; j < root->children.size()-1; j++){
                if (root->children[j]->value == "*"){
                    sign = "*";
                    break;
                }
                else if (root->children[j]->value == "-") {
                    sign = "-";
                    break;
                }
                else if (root->children[j]->value == "+") {
                    sign = "+";
                    break;
                }
            }
            if (sign == "*") {
                result = a * b;
            } else if (sign == "-") {
                result = a - b;
            } else if (sign == "+") {
                result = a + b;
            }
            return result;
        }
    }
    bool parse() {
        auto* root = new Node(nullptr, false, "");
        error = false;
        auto* head = &root;
        exp(root);

        if (scanner.query_token()._atributo == Categoria::ERROR) {
            std::cout << "Unexpected Symbol: \"" << scanner.query_token()._lexema << "\" \n";
            error = true;
        }
        if (!error) printBT(root);
        std::cout << "Respuesta: " << solve(root);
        return !error;
    }


public:
    Parser(std::istream& arg_yyin, std::ostream& arg_yyout) : scanner(arg_yyin, arg_yyout) {}
 private:
  FlexScanner scanner;
};

}  // namespace compilers
}  // namespace utec