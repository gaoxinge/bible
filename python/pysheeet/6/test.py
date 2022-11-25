class closure(object):
    
    def __init__(self):
        self.val = 5566
        
    def __call__(self, var):
        self.val += var
        
        
c = closure()
c(9527)
print(c.val)


val = 5566
def closure():
    def wrapper(var):
        global val
        val += var
    return wrapper
    
c = closure()
c(9527)
print(val)