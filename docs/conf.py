import os
import subprocess
import sys

sys.path.insert(0, os.path.abspath("fake/"))

project = "rollNW"
extensions = [
    'sphinx.ext.autodoc',
    'sphinx.ext.napoleon',
    'enum_tools.autoenum',
]

# Check if we're running on Read the Docs' servers
read_the_docs_build = os.environ.get('READTHEDOCS', None) == 'True'
html_theme = "sphinx_rtd_theme"
