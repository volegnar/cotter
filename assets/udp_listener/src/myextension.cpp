#define LIB_NAME "MyExtension"
#define MODULE_NAME "myextension"

#include <dmsdk/sdk.h>

#include <thread>
#include <atomic>
#include <queue>
#include <mutex>
#include <string>
#include <cstring>

#if defined(_WIN32)
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

struct UdpPacket
{
	std::string msg;
	std::string ip;
	int port;
};

static std::thread g_thread;
static std::atomic<bool> g_running(false);

static int g_socket = -1;
static int g_port = 0;

static std::queue<UdpPacket> g_queue;
static std::mutex g_mutex;

static std::mutex g_status_mutex;
static std::string g_status_state = "idle";
static std::string g_status_error = "";

static void SetStatus(const std::string& state, const std::string& error = "")
{
	std::lock_guard<std::mutex> lock(g_status_mutex);
	g_status_state = state;
	g_status_error = error;
}

static void UdpThread()
{
	SetStatus("starting");

	#if defined(_WIN32)
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);
	#endif

	g_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (g_socket < 0)
	{
		SetStatus("error", "failed to create socket");
		return;
	}

	sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(g_port);
	addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(g_socket, (sockaddr*)&addr, sizeof(addr)) < 0)
	{
		SetStatus("error", "bind failed on port");
		return;
	}

	#if defined(_WIN32)
	DWORD timeout = 1000;
	setsockopt(g_socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
	#else
	struct timeval timeout;
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	setsockopt(g_socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
	#endif

	SetStatus("listening", "port " + std::to_string(g_port));

	char buffer[2048];

	while (g_running)
	{
		sockaddr_in sender;
		socklen_t sender_len = sizeof(sender);

		int len = recvfrom(
			g_socket,
			buffer,
			sizeof(buffer) - 1,
			0,
			(sockaddr*)&sender,
			&sender_len
		);

		if (!g_running)
		break;

		if (len > 0)
		{
			buffer[len] = '\0';

			char ip[64];
			inet_ntop(AF_INET, &sender.sin_addr, ip, sizeof(ip));

			UdpPacket packet;
			packet.msg = buffer;
			packet.ip = ip;
			packet.port = ntohs(sender.sin_port);

			{
				std::lock_guard<std::mutex> lock(g_mutex);
				g_queue.push(packet);
			}
		}
	}

	#if defined(_WIN32)
	closesocket(g_socket);
	WSACleanup();
	#else
	close(g_socket);
	#endif

	g_socket = -1;
	SetStatus("stopped");
}

static int StartUDP(lua_State* L)
{
	DM_LUA_STACK_CHECK(L, 0);

	if (g_running)
	{
		SetStatus("error", "already running");
		return 0;
	}

	g_port = luaL_checkinteger(L, 1);
	g_running = true;

	g_thread = std::thread(UdpThread);

	return 0;
}

static int StopUDP(lua_State* L)
{
	DM_LUA_STACK_CHECK(L, 0);

	if (!g_running)
	return 0;

	g_running = false;

	if (g_socket >= 0)
	{
		#if defined(_WIN32)
		closesocket(g_socket);
		#else
		close(g_socket);
		#endif
		g_socket = -1;
	}

	if (g_thread.joinable())
	g_thread.join();

	{
		std::lock_guard<std::mutex> lock(g_mutex);
		std::queue<UdpPacket> empty;
		std::swap(g_queue, empty);
	}

	SetStatus("stopped");

	return 0;
}

static int UdpPoll(lua_State* L)
{
	DM_LUA_STACK_CHECK(L, 1);

	lua_newtable(L);
	int index = 1;

	std::lock_guard<std::mutex> lock(g_mutex);

	while (!g_queue.empty())
	{
		const UdpPacket& p = g_queue.front();

		lua_newtable(L);

		lua_pushstring(L, "msg");
		lua_pushstring(L, p.msg.c_str());
		lua_settable(L, -3);

		lua_pushstring(L, "ip");
		lua_pushstring(L, p.ip.c_str());
		lua_settable(L, -3);

		lua_pushstring(L, "port");
		lua_pushinteger(L, p.port);
		lua_settable(L, -3);

		lua_rawseti(L, -2, index++);

		g_queue.pop();
	}

	return 1;
}

static int GetStatus(lua_State* L)
{
	DM_LUA_STACK_CHECK(L, 1);

	std::lock_guard<std::mutex> lock(g_status_mutex);

	lua_newtable(L);

	lua_pushstring(L, "state");
	lua_pushstring(L, g_status_state.c_str());
	lua_settable(L, -3);

	lua_pushstring(L, "error");
	lua_pushstring(L, g_status_error.c_str());
	lua_settable(L, -3);

	return 1;
}

static const luaL_reg Module_methods[] =
{
	{"start", StartUDP},
	{"stop", StopUDP},
	{"udp_poll", UdpPoll},
	{"get_status", GetStatus},
	{0, 0}
};

static void LuaInit(lua_State* L)
{
	int top = lua_gettop(L);

	luaL_register(L, MODULE_NAME, Module_methods);

	lua_pop(L, 1);

	assert(top == lua_gettop(L));
}

dmExtension::Result AppInitializeMyExtension(dmExtension::AppParams* params)
{
	SetStatus("idle");
	return dmExtension::RESULT_OK;
}

dmExtension::Result InitializeMyExtension(dmExtension::Params* params)
{
	LuaInit(params->m_L);
	return dmExtension::RESULT_OK;
}

dmExtension::Result AppFinalizeMyExtension(dmExtension::AppParams* params)
{
	return dmExtension::RESULT_OK;
}

dmExtension::Result FinalizeMyExtension(dmExtension::Params* params)
{
	g_running = false;

	if (g_socket >= 0)
	{
		#if defined(_WIN32)
		closesocket(g_socket);
		#else
		close(g_socket);
		#endif
		g_socket = -1;
	}

	if (g_thread.joinable())
	g_thread.join();

	SetStatus("stopped");

	return dmExtension::RESULT_OK;
}

DM_DECLARE_EXTENSION(
	MyExtension,
	LIB_NAME,
	AppInitializeMyExtension,
	AppFinalizeMyExtension,
	InitializeMyExtension,
	0,
	0,
	FinalizeMyExtension
)