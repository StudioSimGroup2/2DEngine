local health = 100
local speed = 2.0
local jumpHeight = -1.0
local grounded = true
local spritePos = 0
local doubleJumpEnabled = true
local canDoubleJump = false
local jumCount = 0

local mass = 10
local gravity = 600
local friction = 10
local maxSpeed = 300

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
		self:GetSprite():SetFlipX(true);
    elseif (OnKeyDown(68) == true) -- D
    then
		Veloicty = vec2f.new(self:GetPhysics():GetVelocity())
		Veloicty.x = 200
		self:GetPhysics():SetVelocity(Veloicty)
		self:GetSprite():SetFlipX(false);
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


	--jump
	 if (self:GetPhysics():GetGrounded() and OnKeyDown(32) == true) -- SPACE
    then
        ThrustAmount = vec2f.new(self:GetPhysics():GetVelocity())
		ThrustAmount.y = ThrustAmount.y - 400
		self:GetPhysics():SetVelocity(ThrustAmount)
		canDoubleJump = true
    end

	--Double jump
	if (OnKeyDown(02) == true and canDoubleJump == true and self:GetPhysics():GetGrounded() == false)
    then
        ThrustAmount = vec2f.new(self:GetPhysics():GetVelocity())
		ThrustAmount.y = ThrustAmount.y - 400
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
	

	if (OnKeyDown(01) == true)
	then
        GetObjectByname("Sword"):Enable()
	end
		if (OnKeyUp(01) == true)
	then
        GetObjectByname("Sword"):Disable()
	end
	
end