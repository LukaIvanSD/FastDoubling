#include <stdio.h>
#include <gmp.h>
#include <time.h>

int main() {
    unsigned n;
    printf("Unesite n: ");
    scanf("%u", &n);

    clock_t start = clock();

    mpz_t a, b, c, d, temp;
    mpz_inits(a, b, c, d, temp, NULL);
    mpz_set_ui(a, 0);
    mpz_set_ui(b, 1);

    unsigned mask = 1;
    while (mask <= n) mask <<= 1;
    mask >>= 1;

    for (; mask > 0; mask >>= 1) {
        mpz_mul_ui(c, b, 2);
        mpz_sub(c, c, a);
        mpz_mul(c, c, a);

        mpz_mul(d, a, a);
        mpz_mul(temp, b, b);
        mpz_add(d, d, temp);

        if (n & mask) {
            mpz_set(a, d);
            mpz_add(b, c, d);
        } else {
            mpz_set(a, c);
            mpz_set(b, d);
        }
    }

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    gmp_printf("Fibonacci broj F(%u) je:\n%Zd\n", n, a);
    printf("Vreme izracunavanja: %.6f sekundi\n", time_spent);

    mpz_clears(a, b, c, d, temp, NULL);
    return 0;
}
