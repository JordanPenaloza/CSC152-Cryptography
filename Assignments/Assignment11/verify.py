from sympy import isprime
import argparse

def main(): 
    parser = argparse.ArgumentParser(description="Verify a digital signature.")
    parser.add_argument("p", type=int)
    parser.add_argument("g", type=int)
    parser.add_argument("gd", type=int)
    parser.add_argument("x", type=int)
    parser.add_argument("r", type=int)
    parser.add_argument("s", type=int)
    args = parser.parse_args()
    if not isprime(args.p):
        raise ValueError("The value of p must be a prime number.")
    result = verify(args.p, args.g, args.gd, args.x, args.r, args.s)
    print(result)

def verify(p,g,gd,x,r,s):
    gx = pow(g,x,p)
    left = pow(gd, r, p) * pow(r,s,p) % p 
    if left == gx:
        return 1
    return 0
    
if __name__ == "__main__":
    main()