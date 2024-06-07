#include <iostream>
#include <string_view>

using namespace std::string_view_literals;

void print_matriz_quadrada_mtfoda(const int M) {
    for (int i = 1; i <= M; ++i) {
        for (int j = 1; j <= M; ++j) {
            auto blank = ((j < M) ? "  "sv : ""sv); // qtde de espaços em branco
            
            // determina qual número printar
            int num{};
            if      (i < j)  { num = (1 - i) + j;         }
            else if (i == j) { num = 1; /* (i - j) + 1 */ }
            else             { num = (1 - j) + i;         }

            std::cout << num << blank;
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

// https://resources.beecrowd.com/repository/UOJ_1478.html
int main () {
    int M{};
 
    do {
        std::cin >> M;
        print_matriz_quadrada_mtfoda(M);
    } while (M > 0);
}