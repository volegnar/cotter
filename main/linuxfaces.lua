local M = {}

M.loopback = {
	color = vmath.vector4(0.60, 0.40, 0.20, 1), -- brown
	items = {
		"lo",
	}
}

M.wired = {
	color = vmath.vector4(1.0, 0.6, 0.0, 1), -- orange
	items = {
		"eth0", "eth1", "eth2",
		"enp0s3", "enp0s8", "enp3s0", "enp4s0",
		"eno1", "eno2",
		"ens3", "ens33", "ens160",
	}
}

M.wireless = {
	color = vmath.vector4(0.5, 1.0, 0.8, 1), -- mint
	items = {
		"wlan0", "wlan1",
		"wlp2s0", "wlp3s0", "wlp4s0",
		"wifi0",
	}
}

M.hotspot = {
	color = vmath.vector4(1.0, 0.8, 0.0, 1), -- gold
	items = {
		"ap0",
		"uap0",
	}
}

M.wifidirect = {
	color = vmath.vector4(1.0, 0.1, 0.7, 1), -- pink
	items = {
		"p2p0",
		"p2p-dev-wlan0",
	}
}

M.bluetooth = {
	color = vmath.vector4(0.0, 0.5, 1.0, 1), -- blue
	items = {
		"bnep0", "bnep1",
		"bt0",
	}
}

M.vpn = {
	color = vmath.vector4(0.6, 0.4, 1.0, 1), -- lavender
	items = {
		"tun0", "tun1", "tun2",
		"tap0", "tap1",
		"wg0", "wg1",
		"ppp0", "ppp1",
		"vpn0",
		"ipsec0",
	}
}

M.virtual = {
	color = vmath.vector4(0.7, 0.7, 0.7, 1), -- gray
	items = {
		"virbr0",
		"virbr1",
		"docker0",
		"br0",
		"br-lan",
		"veth0",
		"vboxnet0",
		"vmnet1",
		"vmnet8",
	}
}

M.container = {
	color = vmath.vector4(0.3, 0.9, 0.9, 1), -- cyan
	items = {
		"docker0",
		"cni0",
		"flannel.1",
		"kube-ipvs0",
		"virbr0",
	}
}

M.usb = {
	color = vmath.vector4(1.0, 0.3, 0.3, 1), -- watermelon
	items = {
		"usb0",
		"rndis0",
		"enx000000000000",
	}
}

return M