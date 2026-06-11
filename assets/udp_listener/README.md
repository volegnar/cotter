#UDP Listener native extension
this extension is used by Cotter

#How to use:
```lua
local port = 8888
myextension.start(port)

local packets = myextension.udp_poll()

local status = myextension.get_status()
if status.state == "error" then
  gui.set_text(gui.get_node("listenhint"), status.error)
  myextension.stop()
end
```

! it will only catch packets whose receiver is your ip address or broadcast packets
