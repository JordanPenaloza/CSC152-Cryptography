import random
import math
import secrets
from sympy import isprime
import argparse

def main(): 
    parser = argparse.ArgumentParser(description="Generate a digital signature.")
    parser.add_argument("p", type=int)
    parser.add_argument("g", type=int)
    parser.add_argument("gd", type=int)
    parser.add_argument("d", type=int)
    parser.add_argument("x", type=int)
    args = parser.parse_args()
    if not isprime(args.p):
        raise ValueError("The value of p must be a prime number.")
    sign(args.p, args.g, args.gd, args.d, args.x)


def sign(p,g,gd,d,x):
    num_bits = p.bit_length()
    e = 0
    while e <= 0 or e >= p-1 or math.gcd(e, p-1) != 1: #ensures e is within range 0 to p
        e = secrets.randbits(num_bits)
    r = pow(g, e, p) #g^e mod p
    s = (x - d * r) * pow(e, -1, p-1) % (p-1)
    return r, s

if __name__ == "__main__":
    main()