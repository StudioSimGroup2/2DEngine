

function OnStart()
    -- sprite = self:MakeSprite()
    -- sprite:LoadSpriteSheet("Assets/Textures/spritesheet.png", 4)
		
end

function OnUpdate()
   Pos = vec2f.new(GetObjectByname("Player"):GetTransform():GetPosition())
   Pos.y = 0 + Pos.y
   offset = 30

   Pos.x = Pos.x + offset
   self:GetTransform():SetPosition(Pos)
end