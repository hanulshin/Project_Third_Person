meshes = 0;
colors = 0;
textures = 0;

bNum = { [true] = 1, [false] = 0}

function start( pOwner )
	addMesh("cube", "cube_flat")
	addMesh("player", "Player_7")
	print(meshes.." meshes loaded!")

	addColor("green", 0, 1, 0, 1)
	addColor("red"	, 1, 0, 0, 1)
	addColor("brown", 0.5, 0.25, 0, 1)
	addColor("white", 1, 1, 1, 1)
	addColor("sky", 0, 0.5, 1, 1)
	addColor("orange", 1, 0.5, 0, 1)
	print(colors.." colors loaded!")

	addPng("stone", "runicfloor")
	addPng("platform", "Elevator_PipeBarrierSG1_Diffuse (1)")
	addPng("shaft", "Shaft_phong2SG_Diffuse 1")
	addPng("gears", "Gears_phong4SG_Diffuse 1")
	print(textures.." textures loaded!")

	print("...")
	print("...")
	print("...")

	print("All files loaded! ")
end

function step( dt )
	
end

function addPng( name, file)
	textures = textures + bNum[loadTexture(name, file, "png")];
end

function addJpg( name, file )
	textures = textures + bNum[loadTexture(name, file, "jpg")];
end

function addMesh( name, file )
	meshes = meshes + bNum[loadMesh(name, file, "obj")];
end

function addColor( name, r, g, b, a )
	colors = colors + bNum[loadColor(name, r, g, b, a)]
end