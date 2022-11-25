from math import atan2, sin, cos, pi
from fractions import gcd

class Number(object):
    
    def __add__(self, other):
        return self.add(other)
       
    def __mul__(self, other):
        return self.mul(other)
        
class Complex(Number):
    
    def add(self, other):
        return ComplexRI(self.real + other.real, self.imag + other.imag)
        
    def mul(self, other):
        magnitude = self.magnitude * other.magnitude
        return ComplexMA(magnitude, self.angle + other.angle)
        
class ComplexRI(Complex):
    
    def __init__(self, real, imag):
        self.real = real
        self.imag = imag
        
    @property
    def magnitude(self):
        return (self.real ** 2 + self.image ** 2) ** 0.5
        
    @property
    def angle(self):
        return atan2(self.imag, self.real)
        
    def __repr__(self):
        return 'ComplexRI({0:g}, {1:g})'.format(self.real, self.imag)
        
class ComplexMA(Complex):

    def __init__(self, magnitude, angle):
        self.magnitude = magnitude
        self.angle = angle

    @property
    def real(self):
        return self.magnitude * cos(self.angle)
        
    @property
    def imag(self):
        return self.magnitude * sin(self.angle)
    
    def __repr__(self):
        return 'ComplexMA({0:g}, {1:g} * pi)'.format(self.magnitude, self.angle/pi)
        
class Rational(Number):

    def __init__(self, numer, denom):
        g = gcd(numer, denom)
        self.numer = numer // g
        self.denom = denom // g
        
    def add(self, other):
        nx, dx = self.numer, self.denom
        ny, dy = other.numer, other.denom
        return Rational(nx * dy + ny * dx, dx * dy)
        
    def mul(self, other):
        numer = self.numer * other.numer
        denom = self.denom * other.denom
        return Rational(numer, denom)
    
    def __repr__(self):
        return 'Rational({0}, {1})'.format(self.numer, self.denom)
        