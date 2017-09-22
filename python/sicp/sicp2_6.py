def make_instance(cls):
    
    def get_value(name):
        if name in attributes:
            return attributes[name]
        else:
            value = cls['get'](name)
            return bind_method(value, instance)
            
    def set_value(name, value):
        attributes[name] = value
        
    attributes = {}
    instance = {'get': get_value, 'set': set_value}
    return instance
    
def bind_method(value, instance):
    if callable(value):
        def method(*args):
            return value(instance, *args)
        return method
    else:
        return value
        
def make_class(attributes, base_class=None):
    
    def get_value(name):
        if name in attributes:
            return attributes[name]
        elif base_class is not None:
            return base_class['get'](name)
            
    def set_value(name, value):
        attibutes[name] = value
        
    def new(*args):
        return init_instance(cls, *args)
    
    cls = {'get': get_value, 'set': set_value, 'new': new}
    return cls
    
def init_instance(cls, *args):
    instance = make_instance(cls)
    init = cls['get']('__init__')
    if init:
        init(instance, *args)
    return instance
    
def make_account_class():
    
    interest = 0.02
    
    def __init__(self, account_holder):
        self['set']('holder', account_holder)
        self['set']('balance', 0)
        
    def deposit(self, amount):
        new_balance = self['get']('balance') + amount
        self['set']('balance', new_balance)
        return self['get']('balance')
        
    def withdraw(self, amount):
        balance = self['get']('balance')
        if amount > balance:
            return 'Insufficient funds'
        self['set']('balance', balance - amount)
        return self['get']('balance')
    
    return make_class(locals())
    
Account = make_account_class()

def make_checkint_account_class():
    
    interest = 0.01
    withdraw_fee = 1
    
    def withdraw(self, amount):
        fee = self['get']('withdraw_fee')
        return Account['get']('withdraw')(self, amount + fee)
        
    return make_class(locals(), Account)
   
CheckintAccount = make_checkint_account_class()

kirk_account = Account['new']('Kirk')
print kirk_account['get']('holder')
print kirk_account['get']('interest')
print kirk_account['get']('deposit')(20)
print kirk_account['get']('withdraw')(5)
kirk_account['set']('interest', 0.04)
print Account['get']('interest')

jack_acct = CheckintAccount['new']('Spock')
print jack_acct['get']('interest')
print jack_acct['get']('deposit')(20)
print jack_acct['get']('withdraw')(5)