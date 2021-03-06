#!/bin/bash

# centos7-* only
if test -f /root/.bash_profile; then
  # meson master until v0.56 comes out with fix for hdf5 <= 1.8 dependency
  pip3 uninstall meson -y
  cd /root
  git clone https://github.com/mesonbuild/meson.git
  echo "alias meson='python3 /root/meson/meson.py'" >> /root/.bash_profile
  
  shopt -s expand_aliases
  source /root/.bash_profile
  echo "Enabling gcc and clang compilers"
  gcc --version
  echo "Enable meson alias"
  meson --version
fi

case "$1" in 

  # Configure ncio using meson using out-of-source builds 
  configure)
   
    cd ${GITHUB_WORKSPACE}/..
    mkdir ncio-build
    cd ncio-build
    
    case "${GH_JOBNAME}" in
      # Sanitize with clang compilers
      *"asan"*)
        echo 'Configure for address sanitizer asan'
        CC=clang CXX=clang++ meson -Db_lundef=false -Db_sanitize=address --prefix=${GITHUB_WORKSPACE}/../ncio-install ${GITHUB_WORKSPACE}
      ;;
      *"ubsan"*)
        echo 'Configure for undefined behavior sanitizer ubsan'
        CC=clang CXX=clang++ meson -Db_lundef=false -Db_sanitize=undefined --prefix=${GITHUB_WORKSPACE}/../ncio-install ${GITHUB_WORKSPACE}
      ;;
      *"tsan"*)
        echo 'Configure for thread sanitizer tsan'
        CC=clang CXX=clang++ meson -Db_lundef=false -Db_sanitize=thread --prefix=${GITHUB_WORKSPACE}/../ncio-install ${GITHUB_WORKSPACE}
      ;;
      *"msan"*)
        echo 'Configure for unintialized memory sanitizer msan'
        CC=clang CXX=clang++ meson -Db_lundef=false -Db_sanitize=memory --prefix=${GITHUB_WORKSPACE}/../ncio-install ${GITHUB_WORKSPACE}
      ;;
      *"coverage"*)
        echo 'Configure for code coverage'
        # meson regression bug in > 0.55 using 0.54.2
        pip3 install meson==0.54.2
        meson -Dbuildtype=debug -Db_coverage=true --prefix=${GITHUB_WORKSPACE}/../ncio-install ${GITHUB_WORKSPACE}
      ;;
      # Test with clang compilers
      *"clang"*)
        echo 'Configure for clang compilers'
        CC=clang CXX=clang++ meson --prefix=${GITHUB_WORKSPACE}/../ncio-install ${GITHUB_WORKSPACE}
      ;;
      # Test with default compilers
      *)
        echo 'Configure for default system compilers'
        meson --prefix=${GITHUB_WORKSPACE}/../ncio-install ${GITHUB_WORKSPACE}
      ;;
    esac
   
    ;;

  # Build using ninja
  build)
    cd ${GITHUB_WORKSPACE}/../ncio-build
    ninja
    ;;

  # Run all tests
  test)
    cd ${GITHUB_WORKSPACE}/../ncio-build
    ninja test
    ;;

  # Install the library
  install)
    cd ${GITHUB_WORKSPACE}/../ncio-build
    ninja install
    ;;
  
  # Generate coverage reports
  coverage)
    cd ${GITHUB_WORKSPACE}/../ncio-build
    ninja coverage-xml
    du -hs meson-logs/coverage.xml
    cat meson-logs/coverage.xml
    ;;
    
  *)
    echo " Invalid step" "$1"
    exit -1
    ;;
esac
