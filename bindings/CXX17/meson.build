# MESON file to build the ncio-cxx17 bindings library and public headers
#  Created on: May 11, 2020
#      Author: William F Godoy godoywf@ornl.gov  

ncio_cxx17_sources = ['ncio/cxx17/cxx17NCIO.cpp',
                      'ncio/cxx17/cxx17DataDescriptor.cpp'
                     ]

ncio_cxx17_includes = ['ncio/cxx17']


# DEFINE CXX17 PUBLIC LIBRARY
ncio_cxx17_lib = library('ncio-cxx17', 
                         sources: ncio_cxx17_sources,
                         include_directories: include_directories(ncio_cxx17_includes),
                         dependencies : [ncio_dep],
                         install: true)

# public include current headers location for linking externally with tests
# and source for common headers
ncio_cxx17_dep = declare_dependency(link_with: [ncio_cxx17_lib],
                                    include_directories: ['.','../../source'])
                                    
#################################
## INSTALL PUBLIC CXX17 HEADERS #
#################################

# only public header that should be included in projects using ncio
install_headers('ncio.h')

ncio_cxx17_headers = ['ncio/cxx17/cxx17NCIO.h',
                      'ncio/cxx17/cxx17DataDescriptor.h'
                     ]
# ncio/cxx17 headers 
# install in -> include/ncio/cxx17/cxx17.h
install_headers(ncio_cxx17_headers, subdir:'ncio/cxx17')
