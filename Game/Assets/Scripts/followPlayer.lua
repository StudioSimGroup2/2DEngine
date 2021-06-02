

function OnStart()
    -- sprite = self:MakeSprite()
    -- sprite:LoadSpriteSheet("Assets/Textures/spritesheet.png", 4)
		
end

function OnUpdate()
    pos = self:GetTransform():GetPosition()

    self:GetTransform():SetPosition(0,0)
end