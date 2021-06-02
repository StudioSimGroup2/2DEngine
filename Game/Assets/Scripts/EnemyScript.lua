local health = 10
local speed = 2.0
local gravity = -8.0
local spritePos = 0


function OnStart()
		EnemVelocity = vec2f.new(self:GetPhysics():GetVelocity())
		EnemVelocity.x = 200
		self:GetPhysics():SetVelocity(EnemVelocity)
end

function OnUpdate()
    pos = self:GetTransform():GetPosition()

    if (CheckTrigger(self:GetName(), "Trigger1"))
	then
		EnemVelocity.x = -200
		self:GetPhysics():SetVelocity(EnemVelocity)
	elseif (CheckTrigger(self:GetName(), "Trigger2"))
	then
		EnemVelocity.x = 200
		self:GetPhysics():SetVelocity(EnemVelocity)
    end
end