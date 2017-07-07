#

from setuptools import setup, Extension

module1 = Extension(
  'cPool',
  define_macros = [
    ('_WIN32_WINNT', '0x0600'),
  ],
  sources = ['cPool.c', 'WinPool.c'],
  libraries = ['ws2_32'],
)

setup(
  name = 'cPool',
  version = '1.0',
  description = 'This is a demo package',
  ext_modules = [module1],

)

