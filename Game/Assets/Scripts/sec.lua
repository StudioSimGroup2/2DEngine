local health = 1000

function OnUpdate()
    health = health - 1

    if (health == 0)
    then
        print("sec died")
    end
end