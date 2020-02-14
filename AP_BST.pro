###########################
#  GENERAL CONFIGURATION  #
###########################

TEMPLATE = app             # Makefile for an application
CONFIG -= qt               # Non-Qt project
CONFIG += cmdline          # Command-line application; SHOULD (but it doesn't)
                           # imply CONFIG += console on Windows and
                           # CONFIG -= app_bundle on MacOS
CONFIG += console          # Console application (Windows)
CONFIG -= app_bundle       # Console application (MacOS); do not make ".app"
CONFIG += c++14 strict_c++ # Enables C++14 standard with no compiler extensions
CONFIG -= no-pkg-config    # Enables pkg-config (disabled by default on MacOS)
CONFIG += warn_on          # Enables -Wall and -W (old jargon for -Wextra)


###########################
#      PROJECT FILES      #
###########################

SOURCES += \
    main.cpp

HEADERS += \
    BST.hpp \
    Iterator.hpp \
    Node.hpp

DISTFILES += \
    Doxyfile \
    LICENSE \
    README.md


###########################
#     COMPILER FLAGS      #
###########################

# Standard flags
# =====
# C++11 is NECESSARY; if your compiler doesn't support it, this will throw an
# error. Since we are in 2018 and C++11 is already more than old, update your
# compiler.
# This flag should automatically be activated by CONFIG += c++14, but if for
# some reason it's not you can activate it here.
# =====
#QMAKE_CXXFLAGS += -std=c++14

# DEBUG flags
# ====
# The DEBUG flag is used in qmake's DEBUG configuration, otherwise it's not.
# ====
QMAKE_CXXFLAGS_WARN_ON *= -Wextra -Wpedantic
QMAKE_CXXFLAGS_DEBUG *= -D__DEBUG_AP_BST
QMAKE_CXXFLAGS_RELEASE -= -D__DEBUG_AP_BST

# Optimization flags
# ====
# Optimize for processor's capabilities and vectorize loops.
# In Clang, add "-Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize" to
# perform a vectorization analysis during developement.
# For RELEASE, use -O3 flag both for compilation and linking.
# WARNING: according to Armadillo's doc, GCC with "-march=native" and "-fopenmp"
# could cause speed regressions on recent processors; use with caution.
# ====
QMAKE_CXXFLAGS += -march=native -funroll-loops
QMAKE_CXXFLAGS_RELEASE -= -O0
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE *= -O3
QMAKE_LFLAGS_RELEASE -= -O0
QMAKE_LFLAGS_RELEASE -= -O1
QMAKE_LFLAGS_RELEASE -= -O2
QMAKE_LFLAGS_RELEASE *= -O3

# Program-specific flags
# =====
# E.g. activate YOURMACRO.
#DEFINES += "DYOURMACRO=true"

# OpenMP flags (optional, can be turned off with 'qmake USEOMP=false')
# =====
# We need to make a distinction between (GNU) GCC and Intel's ICC, because
# OpenMP is activated by slightly different flags.
# It seems that also Clang (from version 3.7 on) supports OpenMP, but it must be
# explicitely enabled with -fopenmp=libomp. However, on MacOS this is disabled
# by Apple; in this case you must install libomp by yourself (e.g. with
# Homebrew), change the include and linkin paths if necessary (the ones below
# are Homebrew's default) and then we inject the omp.h header file.
# =====
USEOMP=false    # Delete/Comment this line to automatically activate OpenMP; so
                # far it's useless for this project
!defined(USEOMP, var) USEOMP = true
if ($$USEOMP) {
    *-gcc*|*-g++* {
        QMAKE_CXXFLAGS += -fopenmp
        QMAKE_LFLAGS   += -fopenmp
    }
    *-icc* {
        QMAKE_CXXFLAGS += -qopenmp
        QMAKE_LFLAGS   += -qopenmp
    }
    *-clang* {
        macx {
            QMAKE_CXXFLAGS += -Xpreprocessor -fopenmp -I/usr/local/include/
            QMAKE_LFLAGS   += -L/usr/local/lib -lomp
        } else {
            QMAKE_CXXFLAGS += -fopenmp=libomp
            QMAKE_LFLAGS += -fopenmp=libomp
        }
    }
}


###########################
#       PKG-CONFIG        #
###########################

# Your compile kit must be properly configured. For example, on MacOS + Homebrew
# set your kit with:
#     DYLD_LIBRARY_PATH=/usr/local/include:${DYLD_LIBRARY_PATH}
#     PATH=/usr/local/bin/:${PATH}
#     PKG_CONFIG=/usr/local/lib/pkg-config:${PKG_CONFIG}

#CONFIG += link_pkgconfig   # Generate proper linking flags for libraries added
#                           # via pkg-config
#PKGCONFIG += customlib     # Add 'customlib' via pkgconfig


###########################
#     POST-PROCESSING     #
###########################

# Strip the binary if we are in release mode
#CONFIG(release, debug|release) {
#    QMAKE_POST_LINK += $(STRIP) $(TARGET)
#}


###########################
#         DOXYGEN         #
###########################

# Create a target named 'doc' in the Makefile via the qmake target 'dox'
!defined(DOC_USE_MATHJAX, var) DOC_USE_MATHJAX = YES
dox.target = doc
dox.commands = DOXYGEN_INPUT=$${PWD} DOXYGEN_USE_MATHJAX=$${DOC_USE_MATHJAX} doxygen $${PWD}/Doxyfile#; \
    #test -d doxydoc/html/images || mkdir doxydoc/html/images; \
    #cp documentation/images/* doxydoc/html/images
dox.depends =

# Add the 'dox' qmake target
QMAKE_EXTRA_UNIX_TARGETS += dox
