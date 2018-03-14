
boolNum = { [true] = 1, [false] = 0 }

function vec( px, py )
	return { x = px, y = py }
end

function aimVec( degrees )
	local rad = degrees / 180 * math.pi
	local v = { x = 0, y = 1 }
	local av = { x, y }
	av.x = v.x * math.cos(rad) - v.y * math.sin(rad)
	av.y = v.x * math.sin(rad) + v.y * math.cos(rad)
	return av;
end

health = 5
speed = 5
gravity = 10
jump = 10

facing = 1

bulletsFired = 0

weapons = {}
equiped = ""
cooldown = 0

owner = ""
bulletName = "bullet"

movement = vec(0, 0)

function vecScale(v, scalar)
	if(v.x == nil) then
		v.x = 0
	end
	if(v.y == nil) then
		v.y = 0
	end
	v.x = v.x * scalar
	v.y = v.y * scalar
	return v
end

function newWeapon( pName, pDamage, pKnockback, pFireRate, pRange, pSpeed, pAccuracy, pCluster )
	w = { 
		name = pName, 
		damage = pDamage, 
		Knockback = pKnockback,
		fireRate = pFireRate, 
		range = pRange, 
		speed = pSpeed,
		accuracy = pAccuracy,
		cluster = pCluster
	}

	if(w.speed <= 0) then
		w.speed = 1
	end
	return w
end

function start(pOwner)
	owner = pOwner
	-- Name, Damage, Knockback FireRate, Range, Speed, Accuracy, Cluster[2]
	weapons["pistol"] =  newWeapon("pistol" , 5, 0.50, 0.80, 30, 20, 95, 1 )
	weapons["flame"] =   newWeapon("flame"  , 1, 0.01, 0.06, 10, 10, 80, {1, 3} )
	weapons["shotgun"] = newWeapon("shotgun", 3, 0.75, 1.40, 25, 20, 60, {2, 4} )
	weapons["minigun"] = newWeapon("minigun", 2, 0.20, 0.12, 30, 20, 85, 1 )
	weapons["barrel"] =  newWeapon("barrel" , 4, 1.20, 1.20, 20, 30, 75, 2 )

	equip("minigun")

	blueprint(bulletName, "cube", "red")
	scale("_"..bulletName, 0.3, 0.3, 0.3)
end

function input( )

	movement.x = (boolNum[getKey("right")] - boolNum[getKey("left")]) * speed

	if getKey("z") then
		shoot(0, 1)
	end
end

function shoot(pX, pY)
	if(cooldown > 0) then
		return 
	end
	if(weapons[equiped] == nil) then
		print("Error: ["..equiped.."] doesn't exist!")
		return;
	end
	cooldown = weapons[equiped].fireRate

	local c = weapons[equiped].cluster
	local sh
	if(type(c) == "table") then
		sh = math.random(c[1], c[2])
	else
		sh = c
	end

	for i=1, sh do
		fireBullet()
	end
end

function equip( weapon )
	if(weapons[weapon] == nil) then
		print("Error: ["..weapon.."] doesn't exist!")
	else
		equiped = weapon
	end
end

function step( dt )
	input()
	if(cooldown > 0) then
		cooldown = cooldown - dt;
	end
	local m = vec(movement.x, movement.y)
	m = vecScale(m, dt)
	if m.x+dt < -2 or m.x+dt > 2 then m.x = m.x *-1 end
	move(owner, m.x, m.y, 0)

	local hit = { onEnemyHit(owner) }
	if hit[1] then
		local hitter = hit[2] --not sure if needed;
		print(hitter);
		health = health - hit[3]
		if health <= 0 then
			print("You Died")
		end
	end
end



function fireBullet()
	local bulletNumber = "bullet("..bulletsFired..")"
	bulletsFired = bulletsFired + 1
	clone("_bullet", bulletNumber)

	local aimCone = (100 - weapons[equiped].accuracy) / 2
	local trajectory = math.random(-aimCone, aimCone)
	local sp = weapons[equiped].speed
	local bulletDelta = vecScale(aimVec(trajectory), sp / 0.3)
	local bulletTime = weapons[equiped].range / sp

	addBullet(bulletNumber, bulletDelta.x, bulletDelta.y, weapons[equiped].damage, weapons[equiped].Knockback, bulletTime)
	pPos = { getPos(owner) }
	setPos(bulletNumber, pPos[1], pPos[2], pPos[3])
	addCBox(bulletNumber, 1, 1);
	addToWorld(bulletNumber)
end