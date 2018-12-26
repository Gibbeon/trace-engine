import os, subprocess, shutil

if not os.path.exists("build/win64"):
	os.makedirs("build/win64")

INIT_ENV_BAT = "C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Auxiliary/Build/vcvars64.bat"
vars = subprocess.check_output([INIT_ENV_BAT, '&&', 'set'])
for var in vars.splitlines():
	var = var.decode('cp1252')
	k, _, v = map(str.strip, var.strip().partition('='))
	if k.startswith('?'):
		continue
	os.environ[k] = v

os.chdir("build/win64")
os.system("cmake ../../ -G \"Visual Studio 15 2017\" -A x64 -T host=x64")
os.chdir("../../")
os.system("devenv /build debug ./build/win64/tecore.sln")