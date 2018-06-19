from distutils.core import setup, Extension
module = Extension("libfib", sources=["fib.c"])
setup(name="libfib", version="1.0", ext_modules=[module])