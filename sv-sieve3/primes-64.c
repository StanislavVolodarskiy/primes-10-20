#include <primes.h>

int main() {
    uint64_t n1;
    uint64_t n2;
    scanf("%" SCNu64 " %" SCNu64, &n1, &n2);

    if (n1 <= 2 && 2 < n2) {
        puts("2");
    }

    if (n1 < 3) {
        n1 = 3;
    }

    n1 += 1 - (n1 & 1);
    assert((n1 & 1) == 1);
    n2 += 1 - (n2 & 1);
    assert((n2 & 1) == 1);

    if (n1 < n2) {
        uint64_t s = (n2 - n1) >> 1;
        bool *sieve = malloc(s);
        if (sieve == NULL) {
            exit(1);
        }

        i64_fill_sieve(n1, s, sieve);
        i64_print_sieve(n1, s, sieve);
        
        free(sieve);
    }
}
