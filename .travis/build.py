import json
import os
import sys
import shutil
import zipfile
import tarfile
import urllib.request
from sys import stderr, stdout 
MakefileNames = ['Makefile', 'makefile', 'GNUMakefile']
default_root = "."

def download_file(url, path):
    try:
    	urllib.request.urlretrieve(url, path)
    except Exception as e:
    	print(e)
    	print("This file from {} can't be download".format(url))
    	sys.exit(1)
    	
def download_gnu(version="2017.09", path=None):
	baseurl = "https://github.com/foss-for-synopsys-dwc-arc-processors/toolchain/releases/download/"
	url = baseurl + "arc-" + version + "-release/arc_gnu_"  + version+ "_prebuilt_elf32_le_linux_install.tar.gz"
	if path is not None:
		path = os.path.join(path , "arc_gnu_" + version +"_prebuilt_elf32_le_linux_install.tar.gz")
	else:
		path = os.path.join(os.getcwd(), "arc_gnu_" + version +"_prebuilt_elf32_le_linux_install.tar.gz")
	download_file(url, path)
	gnu = "arc_gnu_" + version + "_prebuilt_elf32_le_linux_install.tar.gz"
	return gnu

def unzip(file, path):
	try:
		pack = zipfile.ZipFile(file, "r")
		pack.extractall(path)
		pack.close()
	except Exception:
		sys.exit(1)

def untar(file, path):
	try:
		pack = tarfile.open(file, "r:gz")
		files = pack.getnames()
		for file in files:
			pack.extract(file, path)
		pack.close()
	except Exception:
		sys.exit(1)

def extract_file(file, path):
	filename, filesuffix = os.path.splitext(file)
	if filesuffix == ".gz":
		untar(file, path)
	elif filesuffix == ".zip":
		unzip(file, path)
	else:
		print("This file {} can't be extracted".format(file))


def add_env_path(path):
	sys.path.append(path)

def add_gnu(version, path=None):
	os.chdir("/")
	os.chdir("tmp")
	gnu = download_gnu(version, path)
	extract_file(gnu, os.getcwd())
	gnu_bin_path = os.path.join(gnu.split(".")[0],"bin")
	add_env_path(os.path.join(os.getcwd(), gnu_bin_path))
	os.system("arc-elf32-gcc --version")

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

def get_tcf(bsp_root, board, bd_version, cur_core):
	result = dict()
	tcf_name = cur_core + ".tcf"
	board_path = "board/" + board + "/configs/" + bd_version + "/"
	tcf_path = os.path.join(bsp_root, board_path, tcf_name)
	result[tcf_name] = None
	if os.path.exists(tcf_path) and os.path.isfile(tcf_path):
		result[tcf_name] = tcf_path
	return result

def get_tcfs(bsp_root, board, bd_version, cur_core=None):
	result = []
	board_path = "board/" + board + "/configs/" + bd_version
	tcfs_path = os.path.join(bsp_root, board_path)
	if os.path.exists(tcfs_path):
		if cur_core is not None:
			cur_core_file = cur_core + ".tcf"
			if cur_core_file in os.listdir(tcfs_path):
				result.append(cur_core)
				return result
		for file in os.listdir(tcfs_path):
			filename, filesuffix = os.path.splitext(file)
			if not filesuffix == ".tcf":
				continue
			result.append(filename)
	return result

def get_board_version(bsp_root, board, bd_version=None):
	result = []
	board_path = "board/" + board + "/configs/"
	ver_path = os.path.join(bsp_root, board_path)
	if os.path.exists(ver_path):
		if bd_version is not None:
			if bd_version in os.listdir(board_path):
				result.append(bd_version)
				return result
		for file in os.listdir(ver_path):
			if os.path.isdir(os.path.join(ver_path, file)):
				result.append(file)
	return result

def get_boards(bsp_root, board=None):
	result = []
	board_path = os.path.join(bsp_root, "board")
	if os.path.exists(board_path):
		if board is not None:
			if board in os.listdir(board_path):
				result.append(board)
				return result
		for file in os.listdir(board_path):
			if os.path.isdir(os.path.join(board_path, file)):
				result.append(file)
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

def build_project_configs(app_path, config):
	make_configs = config
	bsp_root = default_root
	board_input = None
	bd_ver_input = None
	cur_core_input = None
	bd_vers = dict()
	cur_cors = dict()
	make_config = dict()
	results = []
	toolchain = "gnu"
	build_count = 0
	if "TOOLCHAIN" in make_configs:
		toolchain = make_configs["TOOLCHAIN"]
	if "BSP_ROOT" in make_configs:
		bsp_root = make_configs["BSP_ROOT"]
	if "BOARD" in make_configs:
		board_input = make_configs["BOARD"]
	boards = get_boards(bsp_root, board_input)
	if "BD_VER" in make_configs: 
		bd_ver_input = make_configs["BD_VER"]
	for board in boards:
		version = get_board_version(bsp_root, board, bd_version=bd_ver_input)
		bd_vers[board] = version
	if "CUR_CORE" in make_configs:
		cur_core_input = make_configs["CUR_CORE"]
	for (board, versions) in bd_vers.items():
		cur_cors[board] = dict()
		for version in versions:
			cors = get_tcfs(bsp_root, board, version, cur_core=cur_core_input)
			cur_cors[board][version] = cors
	for board in cur_cors:
		for bd_ver in cur_cors[board]:
			for cur_core in cur_cors[board][bd_ver]:
				make_config["BSP_ROOT"] = bsp_root
				make_config["BOARD"] = board
				make_config["BD_VER"] = bd_ver
				make_config["CUR_CORE"] = cur_core
				make_config["TOOLCHAIN"] = toolchain
				isMakefileProject, result = build_makefile_project(app_path, make_config)
				if isMakefileProject is False:
					print("Application {} doesn't have makefile".format(app_path))
				else:
					build_count += 1

					results.append(result)
	return results, build_count

if __name__ == '__main__':
	# result = {}

	cwd_path = os.getcwd() # /.travis
	bsp_path = os.path.dirname(cwd_path)
	add_gnu("2017.09")

	'''os.chdir("/")

	os.chdir("tmp")
	version = "2018.03"
	download_gnu(local="arc_gnu_2017.09_prebuilt_elf32_le_linux_install.tar.gz")
	extract_file("arc_gnu_2017.09_prebuilt_elf32_le_linux_install.tar.gz",os.getcwd())
	add_env_path(os.path.join(os.getcwd(),"arc_gnu_2017.09_prebuilt_elf32_le_linux_install/bin"))'''
	

	make_config = get_config(sys.argv[1])
	os.chdir(bsp_path)
	results, build_count = build_project_configs("example/hello/arcgnu",make_config)

	os.chdir(cwd_path)

	print("Compilation result")
	print("This project is compiled for {} times".format(build_count))
	print(results)
	for result in results:
		if result["status"]:
			sys.exit(1)
	sys.exit(0)

