#include <string.h>

#include <primes.h>

int main(int argc, char *argv[]) {
    bool dump_d = argc > 1;
    (void)argv;

    Int86 n1; scan(&n1);
    Int86 n2; scan(&n2);

    Int86 two = {2, 0};
    if (le(&n1, &two) && lt(&two, &n2)) {
        puts("2");
    }

    if (le(&n1, &two)) {
        n1.low = 3;  // n1 = 3
    }

    n1.low += 1 - (n1.low & 1); // make n1 next odd
    assert((n1.low & 1) == 1);
    n2.low += 1 - (n2.low & 1); // make n2 next odd
    assert((n2.low & 1) == 1);

    while (lt(&n1, &n2)) {
        uint64_t d = i86_isqrt(&n1);
        d += d & 1;  // make it next even
        Int86 n = n1; add(&n, d); // n = n1 + d
        if (lt(&n2, &n)) {
            d = sub(&n2, &n1);
            n = n2;
        }
        assert((d & 1) == 0);
        uint64_t s = d >> 1;

        assert((n1.low & 1) != 0);
        bool *sieve = malloc(s);
        if (sieve == NULL) {
            exit(1);
        }
        if (dump_d) {
            fprintf(stderr, "d %" PRIu64 "\n", d);
        }
        i86_fill_sieve_seg(&n1, s, sieve);
        i86_print_sieve_seg(&n1, s, sieve);
        free(sieve);

        n1 = n;
    }
}
