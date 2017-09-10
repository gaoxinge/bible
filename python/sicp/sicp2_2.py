from fractions import gcd

########
# pair #
########
def pair(x, y):
    def get(index):
        if index == 0:
            return x
        elif index == 1:
            return y
        return get
        
def select(p, i):
    return p(i)

###################################
# rational number: representation #
###################################
def rational(n, d):
    g = gcd(n, d)
    return pair(n//g, d//g)
    
def numer(x):
    return select(x, 0)
    
def denom(x):
    return select(x, 1)

##############################
# rational number: operation #
##############################
def add_rationals(x, y):
    nx, dx = numer(x), denom(x)
    ny, dy = numer(y), denom(y)
    return rational(nx * dy + ny * dx, dx * dy)
    
def mul_rationals(x, y):
    return rational(numer(x) * numer(y), denom(x) * denom(y))
    
def print_rational(x):
    print(numer(x), '/', denom(x))
    
def rationals_are_equal(x, y):
    return numer(x) * denom(y) == numer(y) * denom(x)