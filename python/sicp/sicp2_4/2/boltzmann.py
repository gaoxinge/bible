from connector import connector
from constraint import multiplier

def converter(p, v, n, t):
    u = connector()
    multiplier(p, v, u)
    multiplier(n, t, u)

p = connector('p')
v = connector('v')
n = connector('n')
t = connector('t')
converter(p, v, n, t)
p['set_val']('user', 25)
v['set_val']('user', 30)
n['set_val']('user', 35)
p['forget']('user')
v['forget']('user')
n['forget']('user')