owner = "";

spawnEngine = {
	types = {},
	shafts = 7, -- range in which boxes spawn
	spawnRate = 1.2, --enemies that spawn per second [0 to inf]
	spawnHeight = 30, --enemies spawn above the platform [0 to inf]
	enemyLimit = 5, --limit of enemies on spawned at the refreshRate seconds time [0 to inf]
	refreshRate = 0.3, --balance shrinks over time [0 to inf]
	flowControl = 0.9 --spawn rate decreses when overflowing [0 to 1]
}

enemyNumber = 0

function spawnEngine:spawnObject()
	local sum = self:typeSum()
	local t = math.random() * sum
	local index = 1
	for i = 1, #self.types do
		if(t > self.types[i][2]) then
			index = index + 1
			t = t - types[i][2]
		else 
			break 
		end
	end
	local shaft = math.floor(math.random() * spawnEngine.shafts)
	return self.types[index][1], shaft;
end

function spawnEngine:typeSum()
	local s = 0
	for i = 1, #self.types do
		s = s + self.types[i][2]
	end
	return s
end

enemiesBalance = 0
time = 0

function start( pOwner)
	print(pOwner)
	owner = pOwner
	addColor("green", 0, 1, 0, 1)
	addSpawnType("crate", 1, "cube_flat", "green")
end

counter = 0
spawnMass = 0
function step( dt )
	time = time + dt
	if(enemiesBalance > 0) then
		enemiesBalance = enemiesBalance - (refreshRate * dt)
	end
	counter = counter + dt
	if(counter > 1) then
		counter = counter - 1
		spawnMass = math.random() * spawnEngine.spawnRate + spawnMass;
		while(spawnMass > 1)do
			spawnMass = spawnMass - 1
			createEnemy()
		end
	end
end

function addSpawnType( type, frquency, mesh, texture )
	spawnEngine.types[#spawnEngine.types + 1] = {"crate", frquency}
	blueprint(type, mesh, texture)
end

function createEnemy()
	local toSpawn = {spawnEngine:spawnObject()}
	enemyNumber = enemyNumber + 1;
	print(enemyNumber)
	currentEnemy = "enemy("..enemyNumber..")"
	clone("_"..toSpawn[1], currentEnemy)
	addToWorld(currentEnemy)
	local elevator = { getPos("elevator") }
	local enemyPos = { 0, 0 }
	enemyPos[1] = toSpawn[2] - (spawnEngine.shafts - 1) * 0.5;
	enemyPos[2] = elevator[2] + spawnEngine.spawnHeight
	setPos(currentEnemy, enemyPos[1], enemyPos[2], 0)
	addLua(currentEnemy, "enemy", currentEnemy, toSpawn[1])
end