import os
import subprocess
import sys

import colorama
from colorama import Fore
from colorama import Back
from colorama import Style

def conan(config):
    return (
        'conan', 'install', '.', 
        '--build', 'missing', 
        '--output-folder=./conan_dependencies', 
        '--deployer=full_deploy', 
        f'--settings=build_type={config}',
        '--settings=compiler.cppstd=23',
    )

def premake(script, action):
    exe = ""
    if sys.platform.startswith('linux'):
        exe = './tools/bin/premake/linux/premake5'
    else:
        exe = './tools/bin/premake/windows/premake5'
    return (exe, f'--file={script}', action)

if __name__ == '__main__':
    colorama.init()

    subprocess.call(conan("Debug"))
    subprocess.call(conan("Release"))

    print(f"{Style.BRIGHT}{Back.GREEN}Generating Visual Studio 2022 solution.{Style.RESET_ALL}")
    subprocess.call(premake("premake5.lua", "vs2022"))
    subprocess.call(premake("premake5.lua", "export-compile-commands"))