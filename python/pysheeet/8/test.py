class CtxManager(object):
    
    def __enter__(self):
        self._attr = "KerKer"
        return self._attr
        
    def __exit__(self, *e_info):
        del self._attr
        
with CtxManager() as c:
    print(c)