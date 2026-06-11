#include <primes.h>

int main() {
    uint64_t n2;
    if (scanf("%" SCNu64, &n2) != 1) {
        return 1;
    }

    if (2 < n2) {
        puts("2");
    }

    const uint64_t n1 = 3;
    n2 += 1 - (n2 & 1);
    assert((n2 & 1) == 1);

    if (n1 < n2) {
        uint64_t s = (n2 - n1) >> 1;
        bool *sieve = malloc(s);
        if (sieve == NULL) {
            exit(1);
        }

        i64_fill_sieve(s, sieve);
        i64_print_sieve_seg(n1, s, sieve);
        
        free(sieve);
    }
}
