#!/usr/bin/python3
import subprocess
import os
import timeit

googletest_root = "googletest/googletest"

include_dirs = [
	'{}/include'.format(googletest_root),
	'include',
	'/usr/include/OpenEXR',
]

library_dirs = [
	'{}/build'.format(googletest_root),
	'build',
]

cpp_flags = [
	'-Wall',
	'-g',
]

sources = [
	'format',
	'image',
	'array',
	'data_t',
]

tests = [
	'test/main.cpp',
	'test/image.test.cpp',
	'test/misc.cpp',
]

libs = [
	'-lformat',
	'-lgtest_main', 
	'-lgtest', 
	'-pthread',
	'-lpng',
	'-ljpeg',
	'-lIlmImf',
	'-lIex',
]

include_flags = ['-I{}'.format(x) for x in include_dirs]
library_flags = ['-L{}'.format(x) for x in library_dirs]

os.makedirs('build', 0o755, exist_ok = True)

def compile_format():
	for source in sources:
		subprocess.check_call(['g++', '-std=c++11'] + cpp_flags + include_flags + ['-c', '{}.cpp'.format(source), '-o', 'build/{}.o'.format(source)])

try:
	time = timeit.timeit(compile_format, number=1)
	objects = ['build/{}.o'.format(source) for source in sources]
	subprocess.check_call(['ar', 'rcs', 'build/libformat.a'] + objects)
	subprocess.check_call(['g++', '-std=c++11'] + tests + cpp_flags + include_flags + library_flags + libs + ['-o', 'build/test.bin'])
	print("Compilation time: ", time)
except subprocess.CalledProcessError as error:
	print('Compilation failed.')
	exit(1)

try:
	subprocess.check_call(['build/test.bin'])
except subprocess.CalledProcessError as error:
	print('Running test failed.')
	exit(1)
