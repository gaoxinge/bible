from connector import connector
from constraint import adder, multiplier, constant

def converter(c, f):
    """Connect c to f with constraints to convert from Celsius to Fahrenheit."""
    u, v, w, x, y = [connector() for _ in range(5)]
    multiplier(c, w, u)
    multiplier(v, x, u)
    adder(v, y, f)
    constant(w, 9)
    constant(x, 5)
    constant(y, 32)

celsius = connector('Celsius')
fahrenheit = connector('Fahreheit')
converter(celsius, fahrenheit)
celsius['set_val']('user', 25)
fahrenheit['set_val']('user', 212)
celsius['forget']('user')
fahrenheit['set_val']('user', 212)