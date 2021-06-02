local health = 100
local speed = 2.0
local jumpHeight = -1.0
local gravity = -8.0
local grounded = true
local spritePos = 0
local jumping = false
local doubleJump = false
local jumpCount = 0

function OnStart()
    -- sprite = self:MakeSprite()
    -- sprite:LoadSpriteSheet("Assets/Textures/spritesheet.png", 4)
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





    if (self:GetPhysics():GetGrounded() and OnKeyDown(32) == true) -- SPACE
    then
		jumping = true
        ThrustAmount = vec2f.new(self:GetPhysics():GetVelocity())
		ThrustAmount.y = ThrustAmount.y - 200
		self:GetPhysics():SetVelocity(ThrustAmount)
    end

	if(jumpCount == true) then
		self:GetPhysics():SetFriction(5)
	end

	
	if (OnKeyDown(69) == true) -- E
	then
	self:GetPhysics():SetGravity(100)
	end
	
	if (OnKeyDown(82) == true) -- R
	then
	ChangeScene("Assets/Scenes/1234.lvl")
	end
end