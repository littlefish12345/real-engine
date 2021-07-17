import subprocess
import shutil
import json
import sys
import os

__REAL_ENGINE_VERSION__ = 0.1

if len(sys.argv) != 2:
    print("Usage: python build_project.py <project_flooder_path>")
    exit(0)

project_path = sys.argv[1]
project_config_path = os.path.join(project_path, "config.json")
project_build_path = os.path.join(project_path, "build")

if not (os.path.exists(project_config_path) and os.path.isfile(project_config_path)):
    print("Usage: python build_project.py <path_to_project>")
    exit(0)

try:
    f = open(project_config_path)
    config = json.load(f)
except:
    f.close()
    print("Usage: python build_project.py <path_to_project>")
    exit(0)

f.close()

try:
    if config["engine_version"] > __REAL_ENGINE_VERSION__:
        print("Your real-engine version is too old.\nPlease update your engine in order to compile this project")
        exit(0)
    compiler = config["engine_version"]
except Exception as e:
    print(e)
    print("Usage: python build_project.py <path_to_project>")
    exit(0)

print('Cleaning build flooder...')
try:
    shutil.rmtree(project_build_path)
except:
    pass

try:
    os.makedirs(project_build_path)
except:
    pass

source_file_path_list = []
for src in config["source_files"]:
    source_file_path_list.append(os.path.join(project_path, "src", src))

ststic_lib_list = ['-lglad']

if sys.platform == 'win32':
    dy_lib_list = ["./lib/glfw3.dll"]
    extra_option = ""
else:
    dy_lib_list = ["./lib/libglfw.so.3"]
    extra_option = " -ldl -Wl,-rpath=."

final_command = config["compiler"] + " " + config["compiler_flags"] + " -I./include -L./lib " + " ".join(source_file_path_list) + " -o " + \
                os.path.join(project_path, "build", config["output_name"])  + " " + " ".join(ststic_lib_list) + " " + " ".join(dy_lib_list) + extra_option

print("Start to compile...")
p = subprocess.Popen(final_command,shell=True)
p.wait()
if p.returncode != 0:
    print('Build failure')
    exit(0)

if sys.platform == 'win32':
    shutil.copy("./lib/glfw3.dll", os.path.join(project_build_path, "glfw3.dll"))
else:
    shutil.copy("./lib/libglfw.so.3", os.path.join(project_build_path, "libglfw.so.3"))
    
print('Build finish')
