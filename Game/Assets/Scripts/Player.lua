local health = 100
local speed = 2.0
local jumpHeight = -1.0
local gravity = -8.0
local grounded = true

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

    if (grounded and OnKeyDown(32) == true)
    then
        pos.y = pos.y + jumpHeight
    end
end