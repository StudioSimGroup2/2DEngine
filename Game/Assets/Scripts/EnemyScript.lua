local health = 10
local speed = 2.0
local gravity = -8.0
local spritePos = 0

function OnStart()
    ThrustAmount = vec2f.new(40,0)
		self:GetPhysics():AddThrust(ThrustAmount)
end

function OnUpdate()
    pos = self:GetTransform():GetPosition()

    if (CheckTrigger(self:GetName(), "Trigger1"))
	then
		ThrustAmount = vec2f.new(-40,0)
		self:GetPhysics():AddThrust(ThrustAmount)
	elseif (CheckTrigger(self:GetName(), "Trigger2"))
	then
		ThrustAmount = vec2f.new(40,0)
		self:GetPhysics():AddThrust(ThrustAmount)
    end
end