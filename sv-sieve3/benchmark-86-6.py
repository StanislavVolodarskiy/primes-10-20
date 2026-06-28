import sys

sys.path.append('tools')

import collections
import numpy as np

import benchmark_app


def main():
    step = 10_000_000_000

    scheme = collections.Counter()
    p1 = 6
    p2 = 20
    f = 1
    for n2 in map(round, np.geomspace(10 ** p1, 10 ** p2, 1 + f * (p2 - p1))):
        n1 = max(0, n2 - step)
        scheme.update({(n1, n2): 1})

    def command(n1, n2):
        return f'echo {n1} {n2} {step} | temp/sv-sieve3-86-6 > temp/sv-sieve3-86-6.txt'

    benchmark_app.main(
        scheme,
        command,
        init_command=lambda n1, n2: command(n2, n2)
    )


main()
