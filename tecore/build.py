import os
import shutil

if not os.path.exists("build"):
	os.mkdir("build")

os.chdir("build")
os.system("cmake .. -G \"Visual Studio 15 2017\" -A x64 -T host=x64")
os.chdir("..")
os.system("devenv /build debug ./build/tecore.sln")