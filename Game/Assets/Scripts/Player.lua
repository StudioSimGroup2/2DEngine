local health = 100
local speed = 2.0
local jumpHeight = -1.0
local grounded = true
local spritePos = 0
local doubleJump = true
local canDoubleJump = false

local mass = 10
local gravity = 600
local friction = 10
local maxSpeed = 200

function OnStart()
    -- sprite = self:MakeSprite()
    -- sprite:LoadSpriteSheet("Assets/Textures/spritesheet.png", 4)
	self:GetPhysics():SetFriction(friction)
	self:GetPhysics():SetGravity(gravity)
	self:GetPhysics():SetMass(mass)
	self:GetPhysics():SetMaxSpeed(maxSpeed)
end

function OnUpdate()
    pos = self:GetTransform():GetPosition()

    if (OnKeyDown(65) == true) -- A
    then
		Veloicty = vec2f.new(self:GetPhysics():GetVelocity())
		Veloicty.x = -200
		self:GetPhysics():SetVelocity(Veloicty)
    elseif (OnKeyDown(68) == true) -- D
    then
		Veloicty = vec2f.new(self:GetPhysics():GetVelocity())
		Veloicty.x = 200
		self:GetPhysics():SetVelocity(Veloicty)
    end

	    if (OnKeyUp(65) == true) -- A
    then
		Veloicty = vec2f.new(self:GetPhysics():GetVelocity())
		Veloicty.x = -50
		self:GetPhysics():SetVelocity(Veloicty)
    elseif (OnKeyUp(68) == true) -- D
    then
		Veloicty = vec2f.new(self:GetPhysics():GetVelocity())
		Veloicty.x = 50
		self:GetPhysics():SetVelocity(Veloicty)
    end




    if (self:GetPhysics():GetGrounded() and OnKeyDown(32) == true) -- SPACE
    then
        ThrustAmount = vec2f.new(self:GetPhysics():GetVelocity())
		ThrustAmount.y = ThrustAmount.y - 200
		self:GetPhysics():SetVelocity(ThrustAmount)
    end
	if(OnKeyUp(32) == true)
	then
		canDoubleJump = true
	end
	if (OnKeyDown(32) == true and doubleJump == true and canDoubleJump == true)
    then
        ThrustAmount = vec2f.new(self:GetPhysics():GetVelocity())
		ThrustAmount.y = ThrustAmount.y - 200
		self:GetPhysics():SetVelocity(ThrustAmount)
		canDoubleJump = false
	end


	if (OnKeyDown(69) == true) -- E
	then
		self:GetPhysics():SetGravity(10000)
		Veloicty = vec2f.new(self:GetPhysics():GetVelocity())
		Veloicty.x = 0
		self:GetPhysics():SetVelocity(Veloicty)
	end
	if (OnKeyUp(69) == true) -- E
	then
		self:GetPhysics():SetGravity(600)
	end
	
	
end