class Stream(object):
    """A lazily computed linked list."""
    
    class empty(object):
        def __repr__(self):
            return 'Stream.empty'
    
    empty = empty()
        
    def __init__(self, first, compute_rest=lambda: empty):
        assert callable(compute_rest), 'compute_rest must be callable.'
        self.first = first
        self._compute_rest = compute_rest
    
    @property
    def rest(self):
        """Return the rest of the stream, computing it if necessary."""
        if self._compute_rest is not None:
            self._rest = self._compute_rest()
            self._compute_rest = None
        return self._rest
        
    def __repr__(self):
        return 'Stream({0}, <...>)'.format(repr(self.first))
        
s = Stream(1, lambda: Stream(2+3, lambda: Stream(9)))
print s.first
print s.rest.first
print s.rest
print s.rest.rest

def integer_stream(first):
    return Stream(first, lambda: integer_stream(first+1))
    
positives = integer_stream(1)
print positives.first
print positives.rest.first
print positives.rest
print positives.rest.rest

def map_stream(fn, s):
    if s is Stream.empty:
        return s
    return Stream(fn(s.first), lambda: map_stream(fn, s.rest))
    
def filter_stream(fn, s):
    if s is Stream.empty:
        return s
    if fn(s.first):
        return Stream(s.first, lambda: filter_stream(fn, s.rest))
    else:
        return filter_stream(fn, s.rest)
        
def first_k_as_list(s, k):
    first_k = []
    while s is not Stream.empty and k > 0:
        first_k.append(s.first)
        s, k = s.rest, k-1
    return first_k
    
s = integer_stream(3)
m = map_stream(lambda x: x*x, s)
print first_k_as_list(m, 5)

def primes(pos_stream):
    def not_divible(x):
        return x % pos_stream.first != 0
    return Stream(pos_stream.first, lambda: primes(filter_stream(not_divible, pos_stream.rest)))
    
prime_numbers = primes(integer_stream(2))
print first_k_as_list(prime_numbers, 7)