# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
# import os
# import sys
# sys.path.insert(0, os.path.abspath('.'))

import os, subprocess, sys, re
if sys.version_info[0] >= 3:
  unicode = str

read_the_docs_build = 'True'#os.environ.get('READTHEDOCS', None) == 'True'
travis_build = os.environ.get('TRAVIS_CI', None) == 'True'

# Get a description of the current position. Use Popen for 2.6 compat
git_tag = subprocess.Popen(['git', 'describe', '--tags'], stdout=subprocess.PIPE).communicate()[0]

# Convert to unicode for python3
git_tag = unicode(git_tag)


# -- Project information -----------------------------------------------------

#project = 'Advanced Programming - Binary Search Tree'
#copyright = u'2020, Angela Carraro, Matteo Seclì'
#author = u'Angela Carraro, Matteo Seclì'
version = git_tag
release = git_tag


# -- General configuration ---------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
#extensions = [ "breathe" ]
extensions = [ ]

# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']


# Breathe Configuration
breathe_default_project = "Advanced Programming - Binary Search Tree"


# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = 'sphinx_rtd_theme'
master_doc = '_index'

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ['_static']




if read_the_docs_build:
  html_extra_path = ['_build/html']
  subprocess.call('cd .. && doxygen Doxyfile', shell=True)
