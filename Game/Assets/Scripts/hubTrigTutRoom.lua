function OnUpdate()
	if (CheckTrigger(self:GetName(), "Player"))
	then
	ChangeScene("Assets/Scenes/HubScene.lvl")
	end	
end