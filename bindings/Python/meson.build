# MESON file to build the ncio Python bindings library and public headers
#  Created on: May 11, 2020
#      Author: William F Godoy godoywf@ornl.gov  

ncio_py11_sources = ['py11ncio.cpp',
                     'ncio/py11/py11NCIO.cpp',
                     'ncio/py11/py11DataDescriptor.cpp',
                     ]

pymod = import('python')
py = pymod.find_installation()

py.extension_module('ncio', sources : ncio_py11_sources,
                    install : true,  
                    install_dir : py.get_install_dir(),
                    dependencies : [dependency('python3'), pybind11_dep, ncio_dep]
                    )

pypathdir = meson.project_build_root() / 'meson-out'
message('PYPATHDIR: ' + pypathdir )
