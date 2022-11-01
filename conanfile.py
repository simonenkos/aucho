#!/usr/bin/env python
from conans import ConanFile, CMake


class Aucho(ConanFile):
    name = "aucho"
    version = "1.0"
    license = ""
    url = ""
    description = "Auction House Server"
    settings = "os", "compiler", "build_type"
    options = {"shared": [True, False]}
    default_options = {"shared": False}
    generators = "cmake"

    build_requires = [
        "boost/1.80.0"
    ]

    # def configure(self):
    #     cmake = CMake(self)
    #     cmake.configure()
