[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![ci](https://github.com/jd28/rollnw-py/actions/workflows/ci.yml/badge.svg)](https://github.com/jd28/rollnw-py/actions?query=workflow%3Aci)
[![Documentation Status](https://readthedocs.org/projects/rollnw-py/badge/?version=latest)](https://rollnw-py.readthedocs.io/en/latest/?badge=latest)
[![PyPI version](https://badge.fury.io/py/rollnw.svg)](https://badge.fury.io/py/rollnw)

# rollnw.py

This repository has bindings for the [rollnw](https://github.com/jd28/rollnw/) library. Currently, splitting it off from the main repository for easier development.

**This library is a work-in-progress.  There will be serious refactoring and until there is a real release, it should be assumed the library is a work-in-progress.**

## Building

The only thing that is required is that you a c++20 compiler and python>=3.10 installed.

    pip install -r requirements.txt
    git clone git@github.com:jd28/rollnw-py.git --recursive
    nox -s dev
