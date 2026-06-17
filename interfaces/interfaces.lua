local M = {}

M.mobile = {
	color = vmath.vector4(1.0, 0.22, 0.22, 1), -- watermelon
	items = {
		"pdp1", "pdp2", "pdp_ip0", "pdp_ip1", "vnet0", "vnet1",
		"rmnet_ipa0", "rmnet_ipa1", "wwan0", "wwan1", "ccmni0", 
		"ccmni1", "ccmni2", "ccmni3", "ccmni4", "ccmni5", "rmnet0", 
		"rmnet1", "rmnet2", "rmnet3", "rmnet4", "rmnet5", "rmnet6", 
		"rmnet7", "rmnet_data0", "rmnet_data1", "rmnet_data2", "rmnet_data3", 
		"rmnet_data4", "rmnet_data5", "rmnet_data6", "rmnet_data7", 
		"rmnet_data8", "rmnet_data9", "rmnet_data10", "rmnet_data11", 
		"rmnet_data12", "rmnet_data13", "rmnet_data14", "rmnet_data15",
	}
}

M.hotspot = {
	color = vmath.vector4(1.0, 0.8, 0.0, 1), -- gold
	items = {
		"swlan0", "wlan1", "ap0",
	}
}

M.wifidirect = {
	color = vmath.vector4(1.0, 0.0, 1.0, 1), -- magenta
	items = {
		"p2p0", "p2p1", "p2p-p2p0", "p2p-p2p1", "p2p-wlan0-0", "p2p-wlan0-1", 
		"p2p-dev-wlan0", "p2p-dev-wlan1", "wigig0", "wifi-aware0", 
	}
}

M.vpn = {
	color = vmath.vector4(0.6, 0.4, 1.0, 1), -- lavender
	items = {
		"tun0", "tun1", "tun2", "tunl0", "wg0", "wg1", 
		"xfrm0", "ppp0", "ppp1", "gre0", "gretap0", 
		"ipsec0", "vti0", "vti1", "sit0", 
	}
}

M.bluetooth = {
	color = vmath.vector4(0.0, 0.5, 1.0, 1), -- blue
	items = {
		"bt-pan", "bnep0", "bnep1",
	}
}

M.loopback = {
	color = vmath.vector4(0.60, 0.40, 0.20, 1), -- brown
	items = {
		"lo",
	}
}

M.wireless = {
	color = vmath.vector4(0.6, 1.0, 0.2, 1), -- lime
	items = {
		"wlan0",
	}
}

M.physical = {
	color = vmath.vector4(1.0, 0.6, 0.0, 1), -- orange
	items = {
		"eth0", "eth1", "rndis0", "usb0", "en0", "en1",
	}
}

M.wificalling = {
	color = vmath.vector4(0.0, 1.0, 1.0, 1), -- cyan
	items = {
		"epdg0", "epdg1", "epdg2", "epdg3", "epdg4", "epdg5", 
		"epd6", "epdg7", 
	}
}

M.unknown = {
	color = vmath.vector4(0.96, 0.86, 0.70, 1), -- beige
	items = {}
}

return M
