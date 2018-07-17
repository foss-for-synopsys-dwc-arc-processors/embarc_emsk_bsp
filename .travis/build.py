import json
import os
import sys

folder = ".travis"
make_path = dict()
makefile = 'makefile'
MakefileNames = ['Makefile', 'makefile', 'GNUMakefile']

def get_makefile(path):
	for root, dirs, files in os.walk(path):
		dirs[:] = [d for d in dirs  if not d.startswith('.')]
		for f in files:
			if f in MakefileNames:
				key = os.path.basename(root)+'_'+os.path.basename(os.path.dirname(root))
				make_path[key] = root

def is_embarc_makefile(paths):
	result = []
	for (k,v) in paths.items():
		for name in MakefileNames:
			if name in os.listdir(v):
				with open(os.path.join(v,name)) as f:
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
	for k in result:
		paths.pop(k)

def get_config(config): # from input to get the config dict{"TOOLCHAIN":,"BOARD":,"BD_VER":,"CUR_CORE":}
	make_configs = dict()
	for make_config in config.split(" "):
		[config_name,value] = make_config.split("=")
		make_configs[config_name] = value
	return make_configs

def is_tcf(bd_name,bd_version,bd_core):
	path = os.path.join(os.getcwd(),"board",bd_name,"configs",bd_version)
	if os.path.exists(path):
		tcf = bd_core + ".tcf"
		if tcf in os.listdir(path):
			return True
		else:
			return False
def get_tcf(bd_name,bd_version,bd_core):
	result = dict()
	path = os.path.join(os.getcwd(),"board",bd_name,"configs",bd_version)
	if os.path.exists(path):
		tcf = bd_core + ".tcf"
		if tcf in os.listdir(path):
			result["name"] = tcf
			result["path"] = os.path.join(path,tcf)
			return result
		else:
			return False

def get_tcfs(path):
	result = []
	for path in os.listdir(path):
		suffix = os.path.splitext(path)[1]
		if suffix == ".tcf":
			result.append(path)
	return result

def make_file(config):
	result = dict()
	make_configs = get_config(config)
	print(make_configs)
	root = make_configs["BSP_ROOT"]
	toolchain = make_configs["TOOLCHAIN"]
	board = make_configs["BOARD"]
	bd_ver = make_configs["BD_VER"]
	cur_core = make_configs["CUR_CORE"]

	print(os.getcwd())
	if is_tcf(board,bd_ver,cur_core):
		tcf = get_tcf(board,bd_ver,cur_core)

		os.popen("tcftool " + tcf["path"] + " -q -x C_defines,arc_core_config.h -x gcc.arg")
		print(os.listdir(os.getcwd()))
		tcf_dir = os.path.dirname(tcf["path"])

		arc_core_config = os.path.join(os.getcwd(),"arc_core_config.h")
		gcc = os.path.join(os.getcwd(),"gcc.arg")
		linker = os.path.join(tcf_dir,"ld","linker_gnu.ld")

		get_makefile(os.getcwd())
		for (k,v) in make_path.items():
			print("makepath...............",v)
			os.popen("mv " + arc_core_config + " " + gcc +" " + v)
			os.popen("cp "+ linker + " " +v)
			os.chdir(v)

			os.popen("mv linker_gnu.ld arc_core.ld")
			os.system("make " + config + " clean")
			key = bd_ver + "_" + cur_core+"_" +k
			if os.system("make "+config+" -k") != 0:
				result[key] = 1
			else:
				result[key] = 0
	return result




if __name__ == '__main__':
	# result = {}
	cwd_path = os.getcwd() # /.travis
	bsp_path = os.path.dirname(cwd_path) # embarc_emsk_bsp
	print("input",sys.argv[1])

	os.chdir(bsp_path)
	result = make_file(sys.argv[1])
	os.chdir(cwd_path)
	print("Compilation result")
	print(result)
	for (k,v) in result.items():
		if "arcgnu" in k:
			if v == 1 :
				print("build failed")
				sys.exit(1)
	sys.exit(0)

