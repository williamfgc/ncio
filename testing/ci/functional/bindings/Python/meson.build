# MESON functional tests executables
#  Created on: May 19, 2020
#      Author: William F Godoy godoywf@ornl.gov


# Find Python
pymod = import('python')
py = pymod.find_installation()

message( 'pypathdir: ' + pypathdir )

tests = ['NCIO']

foreach test : tests
  test_file = files('functionalTest_py11' + test + '.py')
  test(test, py, args : test_file, env : ['PYTHONPATH=' + pypathdir],
       timeout: 10, suite: ['ci', 'functionaltest', 'py11'], is_parallel: false )
endforeach
