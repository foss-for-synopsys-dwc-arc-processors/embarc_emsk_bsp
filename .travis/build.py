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
	for k in result:
		paths.pop(k)

if __name__ == '__main__':
	result = {}
	cwd_path = os.getcwd() # /.travis
	bsp_path = os.path.dirname(cwd_path) # embarc_emsk_bsp
	bsp_application = bsp_path + "/example"
	get_makefile(bsp_application)
	print(make_path)
	embarc_makefile(make_path)
	print(make_path)

	for (k,v) in make_path.items():
		result[k] = 0
		print("application[%s]=" %k,v)
		pathin = v.replace("\\", "/")
		os.chdir(pathin)
		print("make configuration: ",sys.argv[1])
		print("start compile")
		os.system("make "+sys.argv[1]+" clean") 

		if os.system("make "+sys.argv[1]+" -k") != 0:

			result[k] = 1
		pathout = cwd_path 
		os.chdir(pathout)
	print("Compilation result")
	print(result)
	for (k,v) in result.items():
		if v == 1:
			print("build failed")
			sys.exit(1)
	sys.exit(0)
