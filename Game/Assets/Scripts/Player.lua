local health = 100
local speed = 2.0
local jumpHeight = -1.0
local gravity = -8.0
local grounded = true
local spritePos = 0

function OnStart()
    sprite = self:MakeSprite()
    sprite:LoadSpriteSheet("Assets/Textures/spritesheet.png", 4)
end

function OnUpdate()
    pos = self:GetTransform():GetPosition()

    if (OnKeyDown(65) == true)
    then
        pos.x = pos.x - 1
        --self:GetSprite():SetFlipX(true)
        self:GetTransform():SetPosition(pos)
    elseif (OnKeyDown(68) == true)
    then
        pos.x = pos.x + 1
        --self:GetSprite():SetFlipX(false)
        self:GetTransform():SetPosition(pos)
    end

    if (grounded and OnKeyDown(32) == true)
    then
        self:GetSprite():ChangeSprite(spritePos, 0)
        spritePos = spritePos + 1
    end

    if (spritePos == 4)
    then
        spritePos = 0
    end
end