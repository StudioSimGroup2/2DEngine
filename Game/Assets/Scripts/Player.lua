self:SetName("luaMario")
self:GetTransform():SetPosition(vec2f.new(250, 250))
print("init")
self:MakeSprite()
self:GetSprite():SetPath("Assets/Textures/Mario.png")
print("created SpriteComp")

function OnStart()
    
end

function OnUpdate()
    pos = self:GetTransform():GetPosition()

    if (OnKeyDown(65) == true)
    then
        pos.x = pos.x - 1
        self:GetSprite():SetFlipX(true)
        self:GetTransform():SetPosition(pos)
    elseif (OnKeyDown(68) == true)
    then
        pos.x = pos.x + 1
        self:GetSprite():SetFlipX(false)
        self:GetTransform():SetPosition(pos)
    end
end



