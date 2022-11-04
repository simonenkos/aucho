#!/usr/bin/env python
from conans import ConanFile, CMake


class Aucho(ConanFile):
    name = "aucho"
    version = "1.0"
    license = ""
    url = ""
    description = "Auction House Server"
    settings = "os", "compiler", "build_type"
    generators = "cmake"

    options = {"shared": [True, False]}
    default_options = {
        "shared": False,
        "boost:without_test": True,
        "boost:without_locale": True,
        "boost:without_log": True,
        "boost:without_stacktrace": True
    }

    build_requires = [
        "boost/1.80.0"
    ]

    # def configure(self):
    #     cmake = CMake(self)
    #     cmake.configure()
