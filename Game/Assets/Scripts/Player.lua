
function OnStart()
    print("doing something")
    self:GetSprite():SetPath("Assets/Textures/Stone.png")
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



