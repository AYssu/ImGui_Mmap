#include <string>
#include <jni.h>
#include <errno.h>
#include <random>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
#include <thread>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <sys/uio.h>

#include <fcntl.h>
#include <android/log.h>
#include <pthread.h>
#include <dirent.h>
#include <list>
#include <libgen.h>

#include <sys/mman.h>
#include <sys/wait.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>

#include <codecvt>
#include <chrono>
#include <queue>

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_android.h"
#include "../imgui/imgui_impl_opengl3.h"
#include "../imgui/imgui_internal.h"

#include <EGL/egl.h>
#include <GLES3/gl3.h>

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include <sys/system_properties.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <android/log.h>

#define TAG "lOG日志" // 这个是自定义的LOG的标识
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__) // 定义LOGGED类型
#define maxplayerCount 100
#define maxvehicleCount 50
#define maxitemsCount 400

struct Vector2A
{
	float X;
	float Y;

	  Vector2A()
	{
		this->X = 0;
		this->Y = 0;
	}

	Vector2A(float x, float y)
	{
		this->X = x;
		this->Y = y;
	}
};

struct Vector3A
{
	float X;
	float Y;
	float Z;

	  Vector3A()
	{
		this->X = 0;
		this->Y = 0;
		this->Z = 0;
	}

	Vector3A(float x, float y, float z)
	{
		this->X = x;
		this->Y = y;
		this->Z = z;
	}

};

struct FMatrix
{
	float M[4][4];
};

struct Quat
{
	float X;
	float Y;
	float Z;
	float W;
};

struct FTransform
{
	Quat Rotation;
	Vector3A Translation;
//	float chunk;
	Vector3A Scale3D;
};

enum Mode {
	InitMode = 1,
	ESPMode = 2,
	HackMode = 3,
	StopMode = 4,
};

struct Request {
	int Mode;
	int ScreenWidth;
	int ScreenHeight;
};


struct ItemData {
    char ItemName[50];
    float x;
	float y;
	float w;
    float Distance;
};

struct VehicleData {
	char VehicleName[50];
	float x;
	float y;
	float w;
	float Distance;
};

struct PlayerData {
	char PlayerName[100]; 
	float x;
	float y;
	float w;
	float h;
	int TeamID;
	int State;
	int isBot;
	float Unhealthy;
	float Health;
	float Distance;
	Vector2A Radar;
	Vector2A Head;
	Vector2A Chest;
	Vector2A Pelvis;
	Vector2A Left_Shoulder;
	Vector2A Right_Shoulder;
	Vector2A Left_Elbow;
	Vector2A Right_Elbow;
	Vector2A Left_Wrist;
	Vector2A Right_Wrist;
	Vector2A Left_Thigh;
	Vector2A Right_Thigh;
	Vector2A Left_Knee;
	Vector2A Right_Knee;
	Vector2A Left_Ankle;
	Vector2A Right_Ankle;
	int handheld;
	int bullet;
};

struct Response {
	bool Success;
	int PlayerCount;
	int VehicleCount;
	int ItemsCount;
    int See;
    PlayerData Players[maxplayerCount];
	VehicleData Vehicles[maxvehicleCount];
	ItemData Items[maxitemsCount];
};
