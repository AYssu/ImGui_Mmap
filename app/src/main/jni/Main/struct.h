

#ifndef EMPTY_MSTRUCT
#define EMPTY_MSTRUCT

#define maxplayerCount 100
#define maxitemsCount 400
#define PI 3.141592653589793238
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <string>
#include <pthread.h>
#include <sys/socket.h>
#include <malloc.h>
#include <math.h>
#include <thread>
#include <iostream>
#include <sys/stat.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include <locale>
#include <string>
#include <codecvt>
#include <sys/syscall.h>
#include <unistd.h>
#include <sys/uio.h>
#include <iostream>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <cstdio>
#include <malloc.h>
#include <cstdio>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/un.h>
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

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/log.h>
#include <string>
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

#define TAG "lOG日志"													   // 这个是自定义的LOG的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__) // 定义LOGGED类型

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
    float Z;
    float Y;

    Vector3A()
    {
        this->X = 0;
        this->Z = 0;
        this->Y = 0;
    }

    Vector3A(float x, float z, float y)
    {
        this->X = x;
        this->Y = y;
        this->Z = z;
    }
};

struct ItemData {
    char ItemName[50];
    float x;
    float y;
    float w;
    float Distance;
};
struct PlayerData
{
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

};

struct Response
{
    bool Success;
    int PlayerCount;
    int ItemsCount;
    PlayerData Players[maxplayerCount];
    ItemData Items[maxitemsCount];
};


#endif // EMPTY_MSTRUCT>