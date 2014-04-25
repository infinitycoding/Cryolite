print("** Message from LUA: Script testscript.lua loaded **")
v1 = vector:new(1,2,3)
v1:add(vector:new(1,1,1))
v1:scale(2)
v1:print()
v2 = vector:new(vector:new(1,2,3))
v2:print()

print("** Message from LUA: Script ended **")
