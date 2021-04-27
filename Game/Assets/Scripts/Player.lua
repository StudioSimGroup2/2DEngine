this:SetName("createdInLua")
this:TransformComp():SetPos(250, 250)
sc = SpriteComp(this)
sc:SetTexture("Assets/Textures/Mario.png")

function OnStart()
    
end

function OnUpdate()

end

--this // pointer to gameobject
--this:SetName() // takes in string 
--this:GetName() // not yet tested
--this:TransformComp():SetPos([XPARAM][YPARAM]) // Set Position floats
--this:TransformComp():GetPos() // Get Position, returns as vec2f

