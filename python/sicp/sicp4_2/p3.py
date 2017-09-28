class LetterIter:
    
    def __init__(self, start='a', end='e'):
        self.next_letter = start
        self.end = end
        
    def __next__(self):
        if self.next_letter == self.end:
            raise StopIteration
        letter = self.next_letter
        self.next_letter = chr(ord(letter) + 1)
        return letter
        
letter_iter = LetterIter()
try:
    while True:
        print(next(letter_iter))
except StopIteration:
    pass
    
class Positives:
        
    def __init__(self):
        self.next_positive = 1;
        
    def __next__(self):
        result = self.next_positive
        self.next_positive += 1
        return result
        
p = Positives()
print(next(p))
print(next(p))
print(next(p))