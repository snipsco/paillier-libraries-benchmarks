
import time
from paillier.paillier import *

ITERATIONS = 10
KEY_SIZES = [1024, 2048]

PLAINTEXTS = {
    'small': 42,
    'large': 9601375721773960030826048348718350956180868954786249183055522621772391594913965263068361191091587324151101807311169301869981191762119859865346892157945421998951222949069729370836921713919282283633399891943869137940899827469813950721928452427835958620445001112962904065293585229146038515621140909326729
}

def addition(key_size, plaintext1, plaintext2):

    prikey, pubkey = generate_keypair(key_size)
    m1 = PLAINTEXTS[plaintext1]
    m2 = PLAINTEXTS[plaintext2]
    c1 = encrypt(pubkey, m1)
    c2 = encrypt(pubkey, m2)

    start = time.time()

    for _ in range(ITERATIONS):
        c = e_add(pubkey, c1, c2)

    stop = time.time()

    diff = stop - start
    diff = diff / ITERATIONS
    print("addition (%d, %s, %s): %fms" % (key_size, plaintext1, plaintext2, diff * 1000))


if __name__ == "__main__":
    for key_size in KEY_SIZES:
        addition(key_size, 'small', 'large')
