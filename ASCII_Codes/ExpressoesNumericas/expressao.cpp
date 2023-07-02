#include <cmath>
#include <stack>
#include <memory>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

class ExpressoesNumericas {
  private:
    bool isOperador(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
    }

    int ordemOperador(char op) {
        switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
        }
    }

    void realizaOperacao(std::stack<double> &numeros,
                         std::stack<char> &operadores) {
        if (numeros.size() < 2 || operadores.size() < 1) {
            throw std::runtime_error("ERR SYNTAX");
        }

        double num2 = numeros.top();
        numeros.pop();
        double num1 = numeros.top();
        numeros.pop();
        char op = operadores.top();
        operadores.pop();
        double result = aplicaOperacao(num1, num2, op);
        numeros.push(result);
    }

    double aplicaOperacao(double num1, double num2, char op) {
        switch (op) {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
            if (num2 == 0) {
                throw std::runtime_error("ERR DIVBYZERO");
            }
            return num1 / num2;
        case '^':
            return pow(num1, num2);
        default:
            throw std::runtime_error("ERR SYNTAX");
        }
    }

  public:
    double avaliaExpressao(std::string &expressao) {
        expressao.erase(std::remove(expressao.begin(), expressao.end(), ' '),
                        expressao.end());
        if (expressao.empty()) {
            throw std::runtime_error("ERR SYNTAX");
        }

        double result = 0.0;
        std::stack<double> numeros;
        std::stack<char> operadores;

        for (size_t i = 0; i < expressao.length(); i++) {
            char c = expressao[i];
            if (std::isdigit(c) || c == '.') {
                std::string numero_string = "";
                while (i < expressao.length() &&
                       (std::isdigit(expressao[i]) || expressao[i] == '.')) {
                    numero_string += expressao[i];
                    i++;
                }
                i--;

                try {
                    size_t pos;
                    double num = std::stod(numero_string, &pos);
                    if (pos != numero_string.length()) {
                        throw std::invalid_argument("ERR SYNTAX");
                    }

                    numeros.push(num);
                } catch (const std::invalid_argument &) {
                    throw std::invalid_argument("ERR SYNTAX");
                } catch (const std::out_of_range &) {
                    throw std::out_of_range("ERR SYNTAX");
                }

            } else if (c == '(') {
                operadores.push(c);
            } else if (c == ')') {
                while (!operadores.empty() && operadores.top() != '(') {
                    realizaOperacao(numeros, operadores);
                }

                if (operadores.empty() || operadores.top() != '(') {
                    throw std::runtime_error("ERR SYNTAX");
                }

                operadores.pop();
            } else if (isOperador(c)) {
                while (!operadores.empty() && operadores.top() != '(' &&
                       ordemOperador(c) <= ordemOperador(operadores.top())) {
                    realizaOperacao(numeros, operadores);
                }

                operadores.push(c);
            } else {
                throw std::runtime_error("ERR SYNTAX");
            }
        }
        while (!operadores.empty()) {
            if (operadores.top() == '(' || operadores.top() == ')') {
                throw std::runtime_error("ERR SYNTAX");
            }

            realizaOperacao(numeros, operadores);
        }

        if (numeros.size() != 1) {
            throw std::runtime_error("ERR SYNTAX");
        }
        if (!numeros.empty()) {
            result = numeros.top();
        }
        return result;
    }
};

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Nome do arquivo de expressoes nao fornecido!!!" << '\n';
        std::exit(1);
    }

    std::string expressao;
    std::ifstream expressoesArq(argv[1]);
    auto exp{std::make_shared<ExpressoesNumericas>()};

    if (!expressoesArq.is_open()) {
        std::cerr << "Erro ao abrir o arquivo!!!" << '\n';
        std::exit(1);
    }

    while (std::getline(expressoesArq, expressao)) {
        try {
            std::cout << exp->avaliaExpressao(expressao) << '\n';
        } catch (const std::exception &e) {
            std::cerr << e.what() << '\n';
        }
    }

    return 0;
}
