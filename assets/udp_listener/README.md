# UDP Listener native extension
this native extension is used by Cotter and it is ONLY for udp packets

# How to use:
```lua
local port = 8888
myextension.start(port)

-- in update function:
local packets = myextension.udp_poll()

for i = 1, #packets do
	local p = packets[i]
	local msg = tostring(p.msg):gsub("[\r\n]+", "")
	local ip = tostring(p.ip):gsub("[\r\n]+", "")
	local line = msg .. " | " .. ip
	table.insert(self.listens, line)
end

local status = myextension.get_status()
if status.state == "error" then
  gui.set_text(gui.get_node("listenhint"), status.error)
  myextension.stop()
end
```

! it will only catch packets whose receiver is your ip address or broadcast packets
