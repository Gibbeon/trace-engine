import os
import shutil

if not os.path.exists("build/win64"):
	os.makedirs("build/win64")

os.chdir("build/win64")
os.system("cmake ../../ -G \"Visual Studio 15 2017\" -A x64 -T host=x64")
os.chdir("../../")
os.system("devenv /build debug ./build/win64/tecore.sln")