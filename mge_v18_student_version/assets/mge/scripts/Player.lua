function vec2(px, py)
	return {x = px, y = py}
end

World = "root"

speed = 5
gravity = 10
jump = 10

facing = 1

weapons = {}
equiped = ""
cooldown = 0


aim = vec2(0, 0)

function vecMult(vec, mult)
	if(vec.x == nil) then
		vec.x = 0
	end
	if(vec.y == nil) then
		vec.y = 0
	end
	vec.x = vec.x * mult
	vec.y = vec.y * mult
	return vec
end

function newWeapon( pName, pDamage, pFireRate, pRange, pSpeed )
	w = { 
		name = pName, 
		damage = pDamage, 
		fireRate = pFireRate, 
		range = pRange, 
		speed = pSpeed 
	}

	if(w.speed <= 0) then
		w.speed = 1
	end
	return w
end

function start()
	weapons["pistol"] = newWeapon("pistol", 1, 1, 5, 5)
	equip("pistol")
end

function move( x, y, j )
	m = vec2(0, 0)
	aim:calculate(x, y)
	m.x = x * speed;

	return m.y, m.x;
end

function aim:calculate(x, y)
	if(x ~= 0)then
		facing = x;
	end
	self.x = x;
	self.y = y;
	if(self.x == 0 and self.y == 0) then
		self.x = facing
	end
	length = math.sqrt(math.pow(self.x, 2) + math.pow(self.y, 2))
	self = vecMult(self, 1 / length)
end

function shoot(pX, pY)
	if(cooldown > 0) then
		return
	end
	if(weapons[equiped] == nil) then
		print("Error: ["..equiped.."] doesn't exist!")
		return;
	end
	cooldown = weapons[equiped].fireRate;
	bulletDelta = vecMult(aim, weapons[equiped].speed)
	bsp = weapons[equiped].range / weapons[equiped].speed

	--print(pX..", "..pY)
	--print(bulletDelta.x..", "..bulletDelta.y)

	fire(weapons[equiped].name ,pX, pY, bulletDelta.x, bulletDelta.y, weapons[equiped].damage, weapons[equiped].speed, bsp)
end

function equip( weapon )
	if(weapons[weapon] == nil) then
		print("Error: ["..weapon.."] doesn't exist!")
	else
		equiped = weapon
	end
end

function step( dt )
	if(cooldown > 0) then
		cooldown = cooldown - dt;
	end
end

function lastStep( dt )

end
