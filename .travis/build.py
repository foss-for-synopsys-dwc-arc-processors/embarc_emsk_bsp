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
	return isMakeProject, result



if __name__ == '__main__':
	# result = {}
	cwd_path = os.getcwd() # /.travis
	bsp_path = os.path.dirname(cwd_path) # embarc_emsk_bsp

	make_configs = get_config(sys.argv[1])
	os.chdir(bsp_path)
	isMakefileProject, result = build_makefile_project("example/hello/arcgnu", make_configs)
	os.chdir(cwd_path)
	#os.chdir(cwd_path)
	print("Compilation result")
	print(result)
	if result["status"]:
		sys.exit(1)
	sys.exit(0)

