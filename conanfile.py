from conan import ConanFile
from conan.tools.files import copy
import os

class Aura(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "PremakeDeps"

    def requirements(self):
        self.requires("eastl/3.21.12")
        self.requires("spdlog/1.12.0")
