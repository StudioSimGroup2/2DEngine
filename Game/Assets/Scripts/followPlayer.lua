

function OnStart()
    -- sprite = self:MakeSprite()
    -- sprite:LoadSpriteSheet("Assets/Textures/spritesheet.png", 4)
		
end

function OnUpdate()
   Pos = vec2f.new(GetObjectByname("Player"):GetTransform():GetPosition())
   Vel = vec2f.new(GetObjectByname("Player"):GetPhysics():GetVelocity())
   Pos.y = -0.5 + Pos.y
   if(Vel.x > 0)
   then
           offset = 20
           	self:GetSprite():SetFlipX(false);
   elseif(Vel.x < 0)
   then
           offset = -50
           	self:GetSprite():SetFlipX(true);
   end
   Pos.x = Pos.x + offset
   self:GetTransform():SetPosition(Pos)
end