subdir('CXX17')

# Python bindings
if get_option('NCIO_USE_Python')
  pybind11_dep = dependency('pybind11', fallback: ['pybind11', 'pybind11_dep'])
  if pybind11_dep.found()
    subdir('Python')
  endif
endif

