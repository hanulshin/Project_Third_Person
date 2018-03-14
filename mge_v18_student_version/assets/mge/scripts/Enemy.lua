owner = "";
ai = "";

health = 1;

knockback = 0;
skipMargin = 5
enemyTypes = {}

function addEnemy( pName, pGravity, pDamage, pHealth, pAi, pHit )
	enemyTypes[pName] = { 
	name = pName,
	gravity = pGravity,
	damage = pDamage,
	health = pHealth,
	aifunc = pAi,
	hitPlayer = pHit
	}
end

function settupAI( pAi )
	ai = pAi
	--print("settup:"..enemyTypes[1]);
	health = enemyTypes[ai].health
end

function start( pOwner )
	owner = pOwner
	--print(getPos(pOwner))
	addEnemy("crate", 5, 1, 6, fallAndDie, die)
	--print("start:"..enemyTypes[1]);
end

function step( dt )

	move(owner, 0, -enemyTypes[ai].gravity * dt, 0)
	if(enemyTypes[ai] ~= nil)then
		enemyTypes[ai].aifunc()
	else
		print("No enemy ["..ai.."] exists")
	end

	local hit = { onBulletHit(owner) }
	if hit[1] then
		dealDamage(hit[2])
		knockback = hit[3];
	end
	if knockback > 0 then
		knockback = knockback - dt;
	end
	move(owner, 0, hit[3])
end

function onHitPlayer()
	enemyTypes[ai].hitPlayer()
end

function die()
	kill(owner)
end

function fallAndDie()
	local pPos = { getPos(owner) }
	--print(pPos[1]..", "..pPos[2]..", "..pPos[3])
	local ePos = { getPos("elevator") }
	if pPos[2] < ePos[2] then
		die()
	end
end

function dealDamage( d )
	health = health - d;
	if health <= 0 then
		kill(owner)
	end
end

function getDamage()
	return enemyTypes[ai].damage;
end