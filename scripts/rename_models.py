import os

path = '/home/jimmy/projects/vania_files/vania_blender/urho_exporter/MAN/Models'
files =  os.listdir(path)

for f in files:
	if f == 'Cube.mdl':
		os.rename(path+'/'+f,path+'/'+'MAN.mdl')
	else:
		os.rename(path+'/'+f,path+'/MAN_'+f)
