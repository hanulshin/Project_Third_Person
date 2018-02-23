speed = 5;
gravity = 10;
jump = 10;
aim = {x = 0, y = 0}

function start()

end

function move( x, y, j )
	m = {x = 0,y = 0}
	aim:calculate(x, y)
	m.x = x * speed;

	return m.y, m.x;
end

function aim:calculate(x, y)
	self.x = x;
	self.y = y;
	length = math.sqrt(math.pow(self.x, 2) + math.pow(self.y, 2))
	self.x = self.x / length
	self.y = self.y / length
end

function shoot( ... )
	-- body
end

function step( dt )

end

function lastStep( dt )

end
