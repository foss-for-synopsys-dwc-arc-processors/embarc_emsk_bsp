import json
import os
import sys

folder = ".travis"
make_path = dict()
makefile = 'makefile'

def get_makefile(path): # to find the makefile in the embarc_applications
	path = os.path.abspath(path)
	for root, dirs, files in os.walk(path):
		dirs[:] = [d for d in dirs  if not d.startswith('.')]
		for f in files:
			if f == makefile or f == makefile.capitalize():
				key = os.path.basename(root)+'_'+os.path.basename(os.path.dirname(root))
				make_path[key] = root

def embarc_makefile(paths):
	result = []
	for (k,v) in paths.items():
		with open(os.path.join(v,"Makefile")) as f:
			embarc_root = False
			appl = False
			lines = f.read().splitlines()
			for line in lines:
				if "EMBARC_ROOT" in line:
					embarc_root = True
				if "APPL" in line:
					appl = True
			if not (embarc_root and appl):
				result.append(k)
			if "mwdt" in k:
			     result.append(k)
	for k in result:
		paths.pop(k)
def get_bd_ver(config):
	bd_config = config.split(" ")[2]
	if "11" in bd_config:
		bd_ver = "11"
	elif "22" in bd_config:
		bd_ver = "22"
	elif "23" in bd_config:
		bd_ver = "23"
	else:
		bd_ver = None
	return bd_ver

def get_tcf(path):
	result = []
	for path in os.listdir(path):
		suffix = os.path.splitext(path)[1]
		if suffix == ".tcf":
			result.append(path)
	return result

def make_file(config,bsp_config,makefile_paths):
	bd_ver = get_bd_ver(config) #11
	tcfs = get_tcf(os.path.join(bsp_config,bd_ver))
	print(tcfs)
	result = dict()
	for tcf in tcfs:
		for (k,v) in makefile_paths.items():
			if "mwdt" in k:
				continue
			os.chdir(os.path.join(bsp_config,bd_ver))
			command = "tcftool " + tcf + " -q -x C_defines,arc_core_config.h -x gcc.arg"
			print(command)
			print(os.getcwd())
			os.popen("ls")
			for file in os.listdir(os.getcwd()):
				print(file)
			os.popen(command)
			command = "mv arc_core_config.h gcc.arg " + v
			os.popen(command)
			print(command)
			os.popen("cp ld/linker_gnu.ld " + v)
			os.chdir(v)
			os.popen("mv linker_gnu.ld arc_core.ld")
			os.system("make " + config + " clean")
			key = tcf + "_" + k
			if os.system("make "+config+" -k") != 0:
				result[key] = 1
			else:
				result[key] = 0


	return result




if __name__ == '__main__':
	# result = {}
	cwd_path = os.getcwd() # /.travis
	bsp_path = os.path.dirname(cwd_path) # embarc_emsk_bsp
	bsp_application = os.path.join(bsp_path , "example")
	bsp_config = os.path.join(bsp_path , "board/emsk/configs")
	get_makefile(bsp_application)
	print(make_path)
	result = make_file(sys.argv[1],bsp_config,make_path)
	os.chdir(cwd_path)
	print("Compilation result")
	print(result)
	for (k,v) in result.items():
		if v == 1:
			print("build failed")
			sys.exit(1)
	sys.exit(0)

