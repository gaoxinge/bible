class LetterIter(object):
    
    def __init__(self, start='a', end='e'):
        self.next_letter = start
        self.end = end
        
    def next(self):
        if self.next_letter == self.end:
            raise StopIteration
        letter = self.next_letter
        self.next_letter = chr(ord(letter) + 1)
        return letter
        
letter_iter = LetterIter()
try:
    while True:
        print next(letter_iter)
except StopIteration:
    pass
    
class Positives(object):
        
    def __init__(self):
        self.next_positive = 1;
        
    def next(self):
        result = self.next_positive
        self.next_positive += 1
        return result
        
p = Positives()
print next(p)
print next(p)
print next(p)