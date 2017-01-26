#! /usr/bin/env python
# encoding: utf-8
# Guy Sherman, 2015

import subprocess
import waftools
import sys

PROJ_VERSION			=	'0.0.1'
PROJ_MAJOR_VERSION 	=	'0'


VERSION = PROJ_VERSION
APPNAME = 'darkroom'

top = '.'
out = 'build'
libs = ['pthread', 'boost_system']
linkerflags = []
if sys.platform == 'darwin':
	linkerflags = ['-framework', 'GLUT', '-framework', 'OpenGL']


defines = ''


SUBFOLDERS = ['dep']

def options(opt):
	opt.recurse(SUBFOLDERS)

	opt.load('compiler_cxx')
	opt.load('cppcheck', tooldir=waftools.location)
#	opt.add_option("--shared", action="store_true", help="build shared library")
#	opt.add_option("--static", action="store_true", help="build static library")


def configure(conf):
	env = conf.env
	conf.recurse(SUBFOLDERS)
	conf.setenv('main', env)
	conf.load('compiler_cxx')
	conf.load('cppcheck')
	conf.env.CXXFLAGS = ['-Wall', '-g', '-std=c++11']
	conf.check_cfg(package='glfw3', uselib_store='GLFW', args=['--cflags', '--libs'])
	conf.check_cfg(package='glew', uselib_store='GLEW', args=['--cflags', '--libs'])
	if sys.platform == 'darwin':
		conf.env.LIBPATH_BOOST = ['/usr/local/lib']
		conf.env.INCLUDES_BOOST = ['/usr/local/include']
	else:
		conf.env.LIBPATH_BOOST = ['/usr/lib']
		conf.env.INCLUDES_BOOST = ['/usr/include']


def build(bld):
	bld.recurse(SUBFOLDERS)
	bld.env = bld.all_envs['main']
	bld.program(source = bld.path.ant_glob('src/**/*.cxx'),
				includes = ['./include'],
				cxxflags=['-pedantic-errors'],
				ldflags=linkerflags,
				lib = libs,
				target = 'darkroom',
				install_path = '${BINDIR}',
				use=['GLEW', 'GLFW', 'BOOST'],
				defines = defines,
				features="cxx cxxprogram")

	bld.program(source = bld.path.ant_glob('tests/**/*.cxx'),
				includes = ['./include', './src', './dep/wq/include'],
				cxxflags=['-w'],
				lib = ['pthread', 'boost_system'],
				target = 'tests/all',
				install_path = '${BINDIR}',
				defines = defines,
				use=['wq', 'gtest', 'gtest_main', 'BOOST'],
				cppcheck_skip=True,
				features="cxx cxxprogram")


def test(bld):
	subprocess.check_call("./run_tests.sh")


def verify(bld):
	subprocess.check_call("./grind_tests.sh")
