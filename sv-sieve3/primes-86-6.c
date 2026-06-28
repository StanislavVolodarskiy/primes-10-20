#include <string.h>

#include <primes.h>

typedef struct {
    uint32_t capacity;
    uint32_t size;
    uint8_t *data;
} Incs;

void push(Incs *incs, uint8_t value) {
    if (incs->size == incs->capacity) {
        uint32_t capacity = 1 + 2 * incs->capacity;
        uint8_t *data = realloc(incs->data, capacity);
        if (data == NULL) {
            exit(1);
        }
        incs->capacity = capacity;
        incs->data = data;
    }
    incs->data[incs->size++] = value;
}

void small_primes(uint64_t n, Incs *incs) {
    assert((n & 1) == 1);
    uint64_t prev_i = 0;
    if (n > 3) {
        uint64_t s = (n - 3) >> 1;

        uint8_t *sieve = malloc((s + 7) / 8);
        if (sieve == NULL) {
            exit(1);
        }

        i64_fill_bit_sieve(s, sieve);

        for (uint64_t i = 1; i < s; ++i) {
            if (sieve[i >> 3] & (1 << (i & 7))) {
                uint64_t d = i - prev_i;
                assert(d <= 255);
                push(incs, (uint8_t)d);
                prev_i = i;
            }
        }

        free(sieve);
    }
    while (3 + (prev_i << 1) <= n) {
        push(incs, 255);
        prev_i += 255;
    }
}

int main(int argc, char *argv[]) {
    bool dump_d = argc > 1;
    (void)argv;

    Int86 n1; scan(&n1);
    Int86 n2; scan(&n2);
    uint64_t max_d;
    if (scanf("%" SCNu64, &max_d) != 1) {
        exit(1);
    }
    Int86 max_d_ = {0}; add(&max_d_, max_d);

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

    Incs incs = {0};
    uint64_t n2_sqrt = i86_isqrt(&n2) + 1;
    n2_sqrt += 1 - (n2_sqrt & 1); // make n2_sqrt next odd
    small_primes(n2_sqrt, &incs);

    while (lt(&n1, &n2)) {
        uint64_t d;
        if (le(&max_d_, &n1)) {
            d = max_d;
        } else {
            d = (n1.high << LOW_BITS) + n1.low + 1;  // d = n1
        }

        d += d & 1;  // make it next even
        Int86 n = n1; add(&n, d); // n = n1 + d
        if (lt(&n2, &n)) {
            d = sub(&n2, &n1);
            n = n2;
        }
        assert((d & 1) == 0);
        uint64_t s = d >> 1;

        assert((n1.low & 1) != 0);
        uint8_t *sieve = malloc((s + 7) >> 3);
        if (sieve == NULL) {
            exit(1);
        }
        if (dump_d) {
            fprintf(stderr, "d %" PRIu64 "\n", d);
        }
        i86_fill_bit_sieve_seg_p(incs.data, &n1, s, sieve);
        i86_print_bit_sieve_seg(&n1, s, sieve);

        free(sieve);

        n1 = n;
    }

    free(incs.data);
}
