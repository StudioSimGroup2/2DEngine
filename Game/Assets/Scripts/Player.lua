local health = 30

function OnStart()
end

function OnUpdate()
    health = health - 1
    if (health == 0)
    then
        print("player died")
    end
end