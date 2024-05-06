#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <stdarg.h>

void printColor(int color, const char *format, ...) {
    va_list args;
    va_start(args, format);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    vprintf(format, args);
    SetConsoleTextAttribute(hConsole, 15);
    va_end(args);
}

void sieve_of_atkin(unsigned long long int limit) {
    if (limit < 5) {
        return;
    }

    printColor(10, "2 ");
    printColor(10, "3 ");

    bool *sieve = (bool*)malloc(sizeof(bool) * limit);
    if (sieve == NULL) {
        printf("Erro ao alocar memoria.\n");
        return;
    }

    for (unsigned long long int i = 0; i < limit; i++) {
        sieve[i] = false;
    }

    for (unsigned long long int x = 1; x * x < limit; x++) {
        for (unsigned long long int y = 1; y * y < limit; y++) {
            unsigned long long int n = (4 * x * x) + (y * y);
            if (n <= limit && (n % 12 == 1 || n % 12 == 5)) {
                sieve[n] ^= true;
            }

            n = (3 * x * x) + (y * y);
            if (n <= limit && n % 12 == 7) {
                sieve[n] ^= true;
            }

            n = (3 * x * x) - (y * y);
            if (x > y && n <= limit && n % 12 == 11) {
                sieve[n] ^= true;
            }
        }
    }

    for (unsigned long long int r = 5; r * r < limit; r++) {
        if (sieve[r]) {
            for (unsigned long long int i = r * r; i < limit; i += r * r) {
                sieve[i] = false;
            }
        }
    }

    int prime_count = 0;
    for (unsigned long long int a = 5; a < limit; a++) {
        if (sieve[a]) {
            printColor(10, "%llu ", a);
            prime_count++;
        } else {
            printColor(8, "%llu ", a); 
        }
    }

    int total_numbers = limit - 1;
    float percentage = ((float)prime_count / total_numbers) * 100;
    printf("\n\nTotal de numeros primos encontrados: %d\n", prime_count);
    printf("Total de numeros ate o limite: %d\n", total_numbers);
    printf("Porcentagem de numeros primos: %.2f%%\n", percentage);

    free(sieve);
}

int main() {
    unsigned long long int limit = 10000;
    sieve_of_atkin(limit);
    return 0;
}
