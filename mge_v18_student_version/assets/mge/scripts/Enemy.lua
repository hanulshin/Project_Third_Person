owner = "";
ai = "";
hiveSpace = 0
skipMargin = 5

enemyTypes = {}

function addEnemy( pName, pGravity, pDamage, pAi )
	enemyTypes[pName] = { 
	name = pName,
	gravity = pGravity,
	damage = pDamage,
	aifunc = pAi
	}
end

function settupAI( pAi )
	ai = pAi
end

function start( pOwner )
	owner = pOwner
	print(getPos(pOwner))
	addEnemy("crate", 5, 1, fallAndDie)
end

function step( dt )
	move(owner, 0, -enemyTypes[ai].gravity * dt, 0)
	if(enemyTypes[ai] ~= nil)then
		enemyTypes[ai].aifunc()
	else
		print("No enemy ["..ai.."] exists")
	end
end

function fallAndDie()
	pPos = { getPos(owner) }
	ePos = { getPos("elevator") }
	if pPos[2] < ePos[2] then
		kill(owner)
	end
end