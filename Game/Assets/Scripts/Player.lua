local health = 100
local speed = 2.0
local jumpHeight = -1.0
local gravity = -8.0
local grounded = true
local spritePos = 0

function OnStart()
    -- sprite = self:MakeSprite()
    -- sprite:LoadSpriteSheet("Assets/Textures/spritesheet.png", 4)
end

function OnUpdate()
    pos = self:GetTransform():GetPosition()

    if (OnKeyDown(65) == true) -- A
    then
		ThrustAmount = vec2f.new(-40,0)
		self:GetPhysics():AddThrust(ThrustAmount)
    elseif (OnKeyDown(68) == true) -- D
    then
		ThrustAmount = vec2f.new(40,0)
		self:GetPhysics():AddThrust(ThrustAmount)
    end

    if (self:GetPhysics():GetGrounded() and OnKeyDown(32) == true) -- SPACE
    then
        ThrustAmount = vec2f.new(0,-4000)
		self:GetPhysics():AddThrust(ThrustAmount)
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