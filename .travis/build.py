import json
import os
import sys
import shutil

folder = ".travis"
make_path = dict()
makefile = 'makefile'
MakefileNames = ['Makefile', 'makefile', 'GNUMakefile']

def get_makefile(app_path):
	for makefile in MakefileNames:
		makefile_path = os.path.join(app_path, makefile)
		if os.path.exists(makefile_path) and os.path.isfile(makefile_path):
			return makefile_path
	return None

	# for root, dirs, files in os.walk(path):
	# 	dirs[:] = [d for d in dirs  if not d.startswith('.')]
	# 	for f in files:
	# 		if f in MakefileNames:
	# 			key = os.path.basename(root)+'_'+os.path.basename(os.path.dirname(root))
				#make_path[key] = root

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

def get_tcf(bsp_root, bd_name, bd_version, bd_core):
	result = dict()
	tcf_name = bd_core + ".tcf"
	board_path = "board/" + bd_name + "/configs/" + bd_version + "/"
	tcf_path = os.path.join(bsp_root, board_path, tcf_name)
	result[tcf_name] = None
	if os.path.exists(tcf_path) and os.path.isfile(tcf_path):
		result[tcf_name] = tcf_path
	return result

def get_tcfs(path):
	result = []
	for path in os.listdir(path):
		suffix = os.path.splitext(path)[1]
		if suffix == ".tcf":
			result.append(path)
	return result

def prepare_generated_files(app_path, tcf_path, toolchain):
	extract_tcf = "tcftool " + tcf_path + " -q -x C_defines," + app_path + "/arc_core_config.h"
	ld_path = ""
	dst_ld_path = os.path.join(app_path, "arc_core.ld")
	if toolchain == "gnu":
		extract_tcf += " -x gcc.arg," + app_path + "/gcc.arg"
		ld_path = os.path.join(os.path.dirname(tcf_path), "ld", "linker_gnu.ld")
	else:
		extract_tcf += " -x ccac.arg," + app_path + "/ccac.arg"
		ld_path = os.path.join(os.path.dirname(tcf_path), "ld", "linker_mw.ld")
	# Generate ccac/gcc.arg and core_config.h from tcf file using tcftool
	print(extract_tcf)
	os.system(extract_tcf)
	# Copy linker file to application path
	print("Copy {} to {}".format(ld_path, dst_ld_path))
	shutil.copy(ld_path, dst_ld_path)

def build_makefile_project(app_path, config):
	result = dict()
	isMakeProject = False

	make_configs = config #get_config(config)
	print(make_configs)
	bsp_root = make_configs["BSP_ROOT"]
	toolchain = make_configs["TOOLCHAIN"]
	board = make_configs["BOARD"]
	bd_ver = make_configs["BD_VER"]
	cur_core = make_configs["CUR_CORE"]

	print(os.getcwd())

	conf_key = board + "_" + bd_ver + "_" + cur_core

	tcf_name = cur_core + ".tcf"
	tcf_found = get_tcf(bsp_root, board, bd_ver, cur_core)
	print("tcf_path",tcf_found)
	tcf_path = tcf_found[tcf_name]
	if tcf_path != None:
		makefile_found = get_makefile(app_path)
		print("makefile_found",makefile_found)
		if makefile_found != None:
			isMakeProject = True
			print("Prepare the generated files for application {}".format(app_path))
			prepare_generated_files(app_path, tcf_path, toolchain)
			# Record current folder
			cur_dir = os.getcwd()
			# Change to application makefile folder
			os.chdir(app_path)
			# Build application, clean it first
			print("Build Application {} with Configuration {}".format(app_path, config))
			sys.stdout.flush()

			os.system("make " + " clean")
			result["status"] = os.system("make ")
			result["app"] = app_path
			result["conf"] = conf_key
			result["toolchain"] = toolchain
			os.chdir(cur_dir)
	else:
		isMakeProject = False
	# if is_tcf(bsp_root, board,bd_ver,cur_core):
	# 	tcf = get_tcf(bsp_root, board,bd_ver,cur_core)

	# 	os.popen("tcftool " + tcf["path"] + " -q -x C_defines,arc_core_config.h -x gcc.arg")
	# 	print(os.listdir(os.getcwd()))
	# 	tcf_dir = os.path.dirname(tcf["path"])

	# 	arc_core_config = os.path.join(os.getcwd(),"arc_core_config.h")
	# 	gcc = os.path.join(os.getcwd(),"gcc.arg")
	# 	linker = os.path.join(tcf_dir,"ld","linker_gnu.ld")

	# 	get_makefile(os.getcwd())
	# 	for (k,v) in make_path.items():
	# 		print("makepath...............",v)
	# 		os.popen("mv " + arc_core_config + " " + gcc +" " + v)
	# 		os.popen("cp "+ linker + " " +v)
	# 		os.chdir(v)

	# 		os.popen("mv linker_gnu.ld arc_core.ld")
	# 		os.system("make " + config + " clean")
	# 		key = bd_ver + "_" + cur_core+"_" +k
	# 		if os.system("make "+config+" -k") != 0:
	# 			result[key] = 1
	# 		else:
	# 			result[key] = 0
	return isMakeProject, result




if __name__ == '__main__':
	# result = {}
	cwd_path = os.getcwd() # /.travis
	bsp_path = os.path.dirname(cwd_path) # embarc_emsk_bsp
	#print("input",sys.argv[1])


	#os.chdir(bsp_path)
	# make_configs = dict()
	make_configs = get_config(sys.argv[1])
	os.chdir(bsp_path)
	#result = make_file(sys.argv[1])
	'''make_configs["BSP_ROOT"] = "."
	make_configs["TOOLCHAIN"] = "gnu"
	make_configs["BOARD"] = "emsk"
	make_configs["BD_VER"] = "11"
	make_configs["CUR_CORE"] = "arcem6"'''
	isMakefileProject, result = build_makefile_project("example/hello/arcgnu", make_configs)
	os.chdir(cwd_path)
	#os.chdir(cwd_path)
	print("Compilation result")
	print(result)
	if result["status"]:
		sys.exit(1)
	# for (k,v) in result.items():
	# 	if "arcgnu" in k:
	# 		if v == 1 :
	# 			print("build failed")
	# 			sys.exit(1)
	sys.exit(0)

