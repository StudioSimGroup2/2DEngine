function OnUpdate()
    pos = self:GetTransform():GetPosition()

    if (OnKeyDown(87) == true)
    then
        pos.y = pos.y - 1
        self:GetTransform():SetPosition(pos)
    elseif (OnKeyDown(83) == true)
    then
        pos.y = pos.y + 1
        self:GetTransform():SetPosition(pos)
    end
end