import sys

sys.path.append('tools')

import collections
import numpy as np

import benchmark_app


def main():
    step = 10_000_000_000

    scheme = collections.Counter()
    for n2 in map(round, np.geomspace(1e6, 1e18, 13)):
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
