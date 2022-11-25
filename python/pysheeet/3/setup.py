from distutils.core import setup
from distutils.core import Extension

setup(name="spam", version="1.0", ext_modules=[Extension("spam", ["spam.cpp"])])
