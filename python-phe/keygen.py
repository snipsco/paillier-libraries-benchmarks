
import time
import phe.paillier as paillier

ITERATIONS = 100
KEY_SIZES = [1024, 2048, 3072, 4096]


def keygen(key_size):

    start = time.time()

    for _ in range(ITERATIONS):
        pubkey, prikey = paillier.generate_paillier_keypair(n_length=key_size)

    stop = time.time()

    diff = stop - start
    diff = diff / ITERATIONS
    print("keygen (%d): %fms" % (key_size, diff * 1000))


if __name__ == "__main__":
    for key_size in KEY_SIZES:
        keygen(key_size)
