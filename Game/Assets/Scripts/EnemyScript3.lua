local health = 10
local speed = 2.0
local gravity = -8.0
local spritePos = 0
local direction = 1


function OnStart()
		EnemVelocity = vec2f.new(self:GetPhysics():GetVelocity())
		EnemVelocity.x = 200
		self:GetPhysics():SetVelocity(EnemVelocity)
end

function OnUpdate()
    pos = self:GetTransform():GetPosition()
	EnemVelocity.x = 80*direction
	self:GetPhysics():SetVelocity(EnemVelocity)



    if (CheckTrigger(self:GetName(), "Trigger5"))
	then
		direction =-1
	elseif (CheckTrigger(self:GetName(), "Trigger6"))
	then
		direction = 1
    end
end