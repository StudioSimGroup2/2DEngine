

function OnStart()
   
end

function OnUpdate()
   Pos = vec2f.new(GetObjectByname("Player"):GetTransform():GetPosition())
   Pos.y = 0 - Pos.y
   self:GetTransform():SetPosition(Pos)
end