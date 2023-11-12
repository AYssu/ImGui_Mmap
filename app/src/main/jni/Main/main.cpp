#include "struct.h"
#include "ImGui/font.h"
#include "SeaTool/Sea.hpp"

bool g_Initialized;
Response *response;
// 绘制结构体
ImGuiWindow *g_window = nullptr;
char temp[888];
//静态缓存char
struct 全局配置
{
    std::string 悬浮窗标题 = "阿夜";
    std::string 软件根目录库;
    ImFont *字体指针;
    JNIEnv *Jvm_env = NULL;
    ImGuiIO io;

} 配置;

struct T3后台
{
    const char *url = (char *)"http://w.t3yanzheng.com/E5633A3CA5023084";
    const char *unurl = (char *)"http://w.t3yanzheng.com/520AE8C6B453B9C0";
    const char *base64 = (char *)"bCY/Pxg0VMUsXahjNIoi4LDzfAKRZTQ7S3dkWvOqwl9Jycnm1p5Ft6uBHr+2EeG8";
    const char *key = (char *)"aa199d730b93da766143de1fe640bcb2";
    const char *version = (char *)"aa199d730b93da766143de1fe640bcb2";
    const char *tips = (char *)"aa199d730b93da766143de1fe640bcb2";

} 验证;

bool 登录成功 = false;

struct 绘制信息结构体
{
    bool 初始化;

    bool 方框;
    bool 射线;
    bool 昵称;
    bool 距离;
    bool 血量;
    bool 帧率;
    bool 阵营;
    bool 人数;
    bool 背景;
    bool 背敌;

} 绘制;

struct 颜色结构体
{
    ImColor 方框颜色 = ImColor(200, 255, 0, 255);
    ImColor 真人射线颜色 = ImColor(0, 255, 255, 255);
    ImColor 骨骼颜色 = ImColor(200, 255, 0, 255);
    ImColor 随机颜色[1000] = {};
    ImColor 浅色透明度 = {};
} 颜色;
struct 功能结构体
{
    bool 除草;
    bool 无后;
    bool 加速;
    bool 自瞄;
} 功能;

struct 数值结构体
{
    float 屏幕X = 0;
    float 屏幕Y = 0;

    int 主题选项 = 2;

    float 射线宽 = 1.8f;
    float 方框宽 = 1.8f;
    float 骨骼宽 = 1.8f;
} 数值;

struct 绘制
{

    float 人物X, 人物Y, 人物W, 距离, 血量;
    int 人机, 阵营;

    float 头X, 头Y;         // 头部
    float 胸部X, 胸部Y;     // 胸部
    float 臀部X, 臀部Y;     // 屁股
    float 左肩X, 左肩Y;     // 左肩
    float 右肩X, 右肩Y;     // 右肩
    float 左手肘X, 左手肘Y; // 左手肘
    float 右手肘X, 右手肘Y; // 右手肘
    float 左手腕X, 左手腕Y; // 左手腕
    float 右手腕X, 右手腕Y; // 右手腕
    float 左大腿X, 左大腿Y; // 左大腿
    float 右大腿X, 右大腿Y; // 右大腿
    float 左膝盖X, 左膝盖Y; // 左膝盖
    float 右膝盖X, 右膝盖Y; // 右膝盖
    float 左脚腕X, 左脚腕Y; // 左脚腕
    float 右脚腕X, 右脚腕Y; // 右脚腕
} 人物数据;

void 命令执行(char *shell, bool onlyDIR)
{
    char *cmd = (char *)malloc(4096);
    sprintf(cmd, "%s", shell);
    jclass jcls = 配置.Jvm_env->FindClass("com/empty/open/MainActivity");
    jobject jt = 配置.Jvm_env->AllocObject(jcls);
    jmethodID jfun = 配置.Jvm_env->GetMethodID(jcls, "call", "(Ljava/lang/String;)V");
    if (onlyDIR)
    {
        sprintf(cmd, "%s/%s", 配置.软件根目录库.c_str(), shell);
    }
    jstring data = 配置.Jvm_env->NewStringUTF(cmd);
    配置.Jvm_env->CallVoidMethod(jt, jfun, data);
    free(cmd);
}

extern "C" JNIEXPORT void JNICALL
Java_com_empty_open_GLES3JNIView_init(JNIEnv *env, jclass cls)
{

    if (g_Initialized)
        return;
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    配置.io = ImGui::GetIO();
    配置.Jvm_env = env;
    配置.io.IniFilename = nullptr;

    for (auto & i : 颜色.随机颜色)
    {
        i = ImColor(ImVec4((rand() % 205 + 50) / 255.f, rand() % 255 / 255.f, rand() % 225 / 225.f, 225 / 225.f));
    }
    // 随机队伍颜色

    response = (Response *)build_mmap("/sdcard/Empty", false, sizeof(Response));
    // 文件名 只读 结构体大小 只能使用指针结构体
    memset(response,0, sizeof(Response));
    //清空结构体
    if (true)
    {
        response->PlayerCount=1;
        sprintf(response->Players[0].PlayerName,"%s","阿夜1");
        response->Players[0].x = 300;
        response->Players[0].y = 400;
        response->Players[0].w= 100;
        response->Players[0].Distance = 78.2f;
        response->Players[0].TeamID = 2;
        response->Players[0].Health = 88;
        response->Players[0].isBot = 0;

    }
    //  设置ImGui风格
    ImGui::StyleColorsLight();

    ImGui_ImplAndroid_Init();
    ImGui_ImplOpenGL3_Init("#version 300 es");
    配置.字体指针 =  配置.io.Fonts->AddFontFromMemoryTTF((void *)FontFile, Fontsize, 30.0f, NULL, 配置.io.Fonts->GetGlyphRangesChineseFull());
    IM_ASSERT(配置.字体指针 != NULL);

    ImGui::GetStyle().ScaleAllSizes(3.0f);

    ImGuiStyle &style = ImGui::GetStyle();
    style.WindowRounding = 5.3f;
    style.FrameRounding = 2.3f;
    style.ScrollbarRounding = 1;
    style.ScrollbarSize = 1.0f;

    g_Initialized = true;
}

extern "C" JNIEXPORT void JNICALL
Java_com_empty_open_GLES3JNIView_resize(JNIEnv *env, jclass obj, jint width, jint height)
{
    数值.屏幕X = (float)width;
    数值.屏幕Y = (float)height;
    glViewport(30, 400, width, height);
    ImGui::GetIO().DisplaySize = ImVec2((float)width, (float)height);
}


void AddText(ImFont *font, float font_size, ImVec2 pos, ImColor col, char *text_begin)
{
    auto size = ImGui::CalcTextSize(text_begin);
    float x = size.x * (font_size / font->FontSize);
    float y = size.y * (font_size / font->FontSize);
    ImGui::GetForegroundDrawList()->AddText(font, font_size, ImVec2(pos.x -= ((int)x >> 1), pos.y -= ((int)y >> 1)), col, text_begin);
}

void ESP()
{
    int 真人 = 0, 人机 = 0;

    for (int i = 0; i < response->PlayerCount; i++)
    {
        人物数据.人物X = response->Players[i].x;
        人物数据.人物Y = response->Players[i].y;
        人物数据.人物W = response->Players[i].w;
        人物数据.血量 = response->Players[i].Health;
        人物数据.人机 = response->Players[i].isBot;
        人物数据.阵营 = 人物数据.人机 > 0 ? 0 : response->Players[i].TeamID;
        人物数据.距离 = response->Players[i].Distance;
        颜色.浅色透明度 = ImColor(ImVec4(颜色.随机颜色[人物数据.阵营].Value.x, 颜色.随机颜色[人物数据.阵营].Value.y, 颜色.随机颜色[人物数据.阵营].Value.z,0.8f));
        //获取随机颜色 换透明度

        if (人物数据.人物W>0)
        {

            if (绘制.背景)
            {
                ImGui::GetForegroundDrawList()->AddRectFilled({人物数据.人物X - 130, (人物数据.人物Y - 人物数据.人物W) - 66}, { 人物数据.人物X- 90, (人物数据.人物Y - 人物数据.人物W) - 27},颜色.浅色透明度,10,0);
                ImGui::GetForegroundDrawList()->AddRectFilled({人物数据.人物X - 130, (人物数据.人物Y - 人物数据.人物W) - 66}, {人物数据.人物X + 130, (人物数据.人物Y - 人物数据.人物W) - 27},颜色.浅色透明度,8,0);
            }
            if (绘制.血量)
            {
                ImGui::GetForegroundDrawList()->AddLine({人物数据.人物X - 90, ( 人物数据.人物Y- 人物数据.人物W) - 30},{(人物数据.人物X - 130) + (2.6 * 人物数据.血量),(人物数据.人物Y - 人物数据.人物W) - 30},ImColor(225, 255, 225), 3);
            }

            if (绘制.射线)
            {
                if (人物数据.人机==0)
                    ImGui::GetForegroundDrawList()->AddLine({数值.屏幕X / 2, 130}, {人物数据.人物X, 人物数据.人物Y - 人物数据.人物W},颜色.随机颜色[人物数据.阵营], 数值.射线宽);
                else
                    ImGui::GetForegroundDrawList()->AddLine({数值.屏幕X / 2, 130}, {人物数据.人物X, 人物数据.人物Y - 人物数据.人物W},ImColor(255,255,255), 数值.射线宽);

            }

            if (绘制.方框)
            {
                ImGui::GetForegroundDrawList()->AddRect({人物数据.人物X - (人物数据.人物W / 2), 人物数据.人物Y - 人物数据.人物W},{人物数据.人物X + (人物数据.人物W / 2), 人物数据.人物Y + 人物数据.人物W},颜色.随机颜色[人物数据.阵营],3, 0, 数值.方框宽);
            }
            if (绘制.昵称)
            {
                if (人物数据.人机==0)
                    AddText(配置.字体指针, 24,ImVec2(人物数据.人物X, (人物数据.人物Y - 人物数据.人物W) - 46.5),ImColor(255, 255, 255),response->Players[i].PlayerName);
                else
                    AddText(配置.字体指针, 24,ImVec2(人物数据.人物X, (人物数据.人物Y - 人物数据.人物W) - 46.5),ImColor(255, 255, 255),"鸡哥");

            }

            if (绘制.距离)
            {
                sprintf(temp,"[%.0fm]",人物数据.距离);
                AddText(配置.字体指针,25,ImVec2(人物数据.人物X, (人物数据.人物Y + 人物数据.人物W) + 15),ImColor(255,255,255),temp);

            }

            if (绘制.阵营)
            {
                sprintf(temp,"%d",response->Players[i].TeamID);
                AddText(配置.字体指针,23,ImVec2(人物数据.人物X - 110, (人物数据.人物Y-人物数据.人物W) - 46.5),ImColor(255,255,255),temp);
            }

            if (绘制.背敌)
            {

                sprintf(temp,"%.0m",人物数据.距离);
                if (人物数据.人物X + (人物数据.人物W / 2) < 0) // 左侧背敌
                {

                    ImGui::GetForegroundDrawList()->AddCircle({0,人物数据.人物Y}, 62, ImColor(255,255,255,255), 0,2);

                    if (人物数据.人机 == 0)
                    {
                        ImGui::GetForegroundDrawList()->AddCircleFilled({0,人物数据.人物Y}, 60, 颜色.浅色透明度, 90);
                    }
                    else
                    {
                        ImGui::GetForegroundDrawList()->AddCircleFilled({0,人物数据.人物Y}, 60, ImColor(255,255,255,100), 90);
                    }
                    AddText(配置.字体指针, 30, ImVec2(30, 人物数据.人物Y), ImColor(255, 255, 255), temp);
                }

                else if (人物数据.人物X - (人物数据.人物W / 2) > 数值.屏幕X) // 右侧背敌
                {

                    ImGui::GetForegroundDrawList()->AddCircle({数值.屏幕X,人物数据.人物Y}, 62, ImColor(255,255,255,255), 0,2);

                    if (人物数据.人机 == 0)
                    {
                        ImGui::GetForegroundDrawList()->AddCircleFilled({数值.屏幕X,人物数据.人物Y}, 60, 颜色.浅色透明度, 90);
                    }
                    else
                    {
                        ImGui::GetForegroundDrawList()->AddCircleFilled({数值.屏幕X,人物数据.人物Y}, 60, ImColor(255,255,255,100), 90);
                    }
                    AddText(配置.字体指针, 30, ImVec2(数值.屏幕X - 30, 人物数据.人物Y), ImColor(255, 255, 255), temp);
                }
                else if (人物数据.人物Y + 人物数据.人物W < 0)
                {

                    ImGui::GetForegroundDrawList()->AddCircle({人物数据.人物X,0}, 62, ImColor(255,255,255,255), 0,2);

                    if (人物数据.人机 == 0)
                    {
                        ImGui::GetForegroundDrawList()->AddCircleFilled({人物数据.人物X,0}, 60, 颜色.浅色透明度, 90);
                    }
                    else
                    {
                        ImGui::GetForegroundDrawList()->AddCircleFilled({人物数据.人物X,0}, 60, ImColor(255,255,255,100), 90);
                    }

                    AddText(配置.字体指针, 30, ImVec2(人物数据.人物X, 30), ImColor(255, 255, 255), temp);
                }
            }
        }
        else {
            if (绘制.背敌&&绘制.初始化) {

                ImGui::GetForegroundDrawList()->AddCircle({人物数据.人物X,数值.屏幕Y}, 62, ImColor(255,255,255,255), 0,2);

                if (人物数据.人机 == 0)
                {
                    ImGui::GetForegroundDrawList()->AddCircleFilled({人物数据.人物X,数值.屏幕Y}, 60, 颜色.浅色透明度, 90);
                }
                else
                {
                    ImGui::GetForegroundDrawList()->AddCircleFilled({人物数据.人物X,数值.屏幕Y}, 60, ImColor(255,255,255,100), 90);
                }
                sprintf(temp,"%.0m",人物数据.距离);
                AddText(配置.字体指针, 30, ImVec2(人物数据.人物X, 数值.屏幕Y - 30), ImColor(255, 255, 255), temp);
            }
        }
    }
    // 绘制帧率
    if (绘制.帧率)
    {
        AddText(配置.字体指针, 30, ImVec2(100, 110), ImColor(255, 0, 0, 120), "阿夜映射插件");
        sprintf(temp, "FPS：%.2f",  配置.io.Framerate);
        AddText(配置.字体指针, 30, ImVec2(100, 150), ImColor(0, 255, 0), temp);
    }
    // 绘制人数 队伍
    if (绘制.人数)
    {
        if (response->PlayerCount == 0)
        {
            AddText(配置.字体指针, 35, ImVec2(数值.屏幕X / 2, 数值.屏幕Y / 15), ImColor(0, 255, 0, 250), "安 全");
        }
        else
        {
            sprintf(temp, "真人:%d", 真人);

            AddText(配置.字体指针, 40, ImVec2(数值.屏幕X / 2 - 100, 85), ImColor(255, 0, 0, 255), temp);

            sprintf(temp, "人机:%d", 人机);
            AddText(配置.字体指针, 40, ImVec2(数值.屏幕X / 2 + 100, 85), ImColor(255, 255, 255), temp);
        }
    }

}
void BeginDraw()
{
    配置.io = ImGui::GetIO();
    // UI窗体背景色
    ImGuiStyle &style = ImGui::GetStyle();
    配置.io.ConfigWindowsMoveFromTitleBarOnly = false;
    配置.io.WantSaveIniSettings = true;
    配置.io.IniFilename = nullptr;
    style.FramePadding = ImVec2(16, 16);
    style.WindowRounding = 10.0f;
    style.FrameRounding = 5.0f;
    style.FrameBorderSize = 0.3f;
    // 滚动条圆角
    style.ScrollbarRounding = 5.0f;
    // 滚动条宽度
    style.ScrollbarSize = 38.0f;
    // 滑块圆角
    style.GrabRounding = 10.0f;
    // 滑块宽度
    style.GrabMinSize = 10.0f;
    // 窗体边框圆角
    style.WindowRounding = 10.0f;
    if (ImGui::Begin(配置.悬浮窗标题.c_str(), NULL, 0))
    {
        g_window = ImGui::GetCurrentWindow();
        ImGui::SetWindowPos({15, 250}, ImGuiCond_Once);
        ImGui::SetWindowSize({数值.屏幕X - 30, -1}, ImGuiCond_Once);
        if (ImGui::BeginTabBar("Tab", ImGuiTabBarFlags_NoCloseWithMiddleMouseButton | ImGuiTabBarFlags_NoTabListScrollingButtons))
        {
            // 菜单标题
            if (ImGui::BeginTabItem("\t绘制\t"))
            {
                if (ImGui::Checkbox("绘制初始化", &绘制.初始化))
                {
                    if (绘制.初始化)
                    {
                        命令执行("draw", true);
                    }
                    else
                    {
                        命令执行("kill -9 draw", false);
                    }
                }
                ImGui::SameLine(0,30);
                if(ImGui::Button("功能全开"))
                {
                    绘制.血量=绘制.阵营=绘制.人数=绘制.帧率=绘制.昵称=绘制.背景=绘制.距离=绘制.射线=绘制.方框=绘制.背敌 = true;
                }
                ImGui::Checkbox("方框", &绘制.方框);
                ImGui::SameLine();
                ImGui::Checkbox("射线", &绘制.射线);
                ImGui::SameLine();
                ImGui::Checkbox("距离", &绘制.距离);
                ImGui::SameLine();
                ImGui::Checkbox("阵营", &绘制.阵营);

                ImGui::Checkbox("昵称", &绘制.昵称);
                ImGui::SameLine();
                ImGui::Checkbox("血量", &绘制.血量);
                ImGui::SameLine();
                ImGui::Checkbox("人数", &绘制.人数);
                ImGui::SameLine();
                ImGui::Checkbox("帧率", &绘制.帧率);

                ImGui::Checkbox("背景", &绘制.背景);
                ImGui::SameLine();
                ImGui::Checkbox("背敌", &绘制.背敌);
                ImGui::ColorEdit4("方框颜色", (float *)&颜色.方框颜色);
                ImGui::ColorEdit4("射线颜色", (float *)&颜色.真人射线颜色);
                ImGui::ColorEdit4("骨骼颜色", (float *)&颜色.骨骼颜色);

                ImGui::SliderFloat("射线宽", &数值.射线宽, 1, 6);
                ImGui::SliderFloat("方框宽", &数值.方框宽, 1, 6);
                ImGui::SliderFloat("骨骼宽", &数值.骨骼宽, 1, 4);

                // 这个菜单页面结束
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("\t设置\t"))
            {

                if (ImGui::Combo("主题颜色", &数值.主题选项, "胖次蓝\0胖次紫\0胖次白\0"))
                {
                    switch (数值.主题选项)
                    {
                    case 0:
                        ImGui::StyleColorsDark();
                        break;
                    case 1:
                        ImGui::StyleColorsClassic();
                        break;
                    case 2:
                        ImGui::StyleColorsLight();
                        break;
                    }
                }

                ImGui::Text("注意：绘制默认以手机最大帧率运行！部分设备限制！");
                ImGui::Text("绘制耗时 %.3f ms (%.1f FPS)", 1000.0f /  配置.io.Framerate,  配置.io.Framerate);
                ImGui::Text("https://github.com/AYssu/ImGui_Mmap");
                ImGui::Text("开源项目为Android Studio 移植参考手机开源版本");

                ImGui::EndTabBar();
            }
        }
        ImGui::EndTabItem();
    }
}
void EndDraw()
{
    ImGuiWindow *window = ImGui::GetCurrentWindow();
    window->DrawList->PushClipRectFullScreen();
    ImGui::End();
}

extern "C" JNIEXPORT void JNICALL
Java_com_empty_open_GLES3JNIView_step(JNIEnv *env, jclass obj)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(数值.屏幕X, 数值.屏幕Y);
    ImGui::NewFrame();

    BeginDraw();

    if (g_Initialized&&绘制.初始化)
    {
        ESP();
    }

    EndDraw();

    ImGui::Render();
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

extern "C" JNIEXPORT void JNICALL
Java_com_empty_open_GLES3JNIView_MotionEventClick(JNIEnv *env, jclass obj, jboolean down, jfloat PosX, jfloat PosY)
{
    ImGuiIO &io = ImGui::GetIO();
    io.MouseDown[0] = down;
    io.MousePos = ImVec2(PosX, PosY);
}

extern "C" JNIEXPORT jstring JNICALL Java_com_empty_open_GLES3JNIView_getWindowRect(JNIEnv *env, jclass thiz)
{
    // TODO: 实现 getWindowSizePos()
    char result[256] = "0|0|0|0";
    if (g_window)
    {
        sprintf(result, "%d|%d|%d|%d", (int)g_window->Pos.x, (int)g_window->Pos.y, (int)g_window->Size.x, (int)g_window->Size.y);
    }
    return env->NewStringUTF(result);
}

extern "C" JNIEXPORT void JNICALL
Java_com_empty_open_GLES3JNIView_real(JNIEnv *env, jclass obj, jfloat w, jfloat h)
{
    数值.屏幕X = w;
    数值.屏幕Y = h;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_empty_open_MainActivity_LoadT3(JNIEnv *env, jobject thiz, jstring kami_s, jstring imei_s, jboolean isLogin)
{
    // TODO: implement LoadT3()
    char *kami = (char *)malloc(512);
    char *imei = (char *)malloc(512);
    std::string k_s = env->GetStringUTFChars(kami_s, JNI_FALSE);
    std::string i_s = env->GetStringUTFChars(imei_s, JNI_FALSE);
    sprintf(kami, "%s", k_s.c_str());
    sprintf(imei, "%s", i_s.c_str());
    int code = 200;

    T3_Json t3_Json{};
    if (isLogin)
    {
        T3_LogIn(验证.url, 验证.base64, 验证.key, kami, imei, code, t3_Json);
    }
    else
    {
        T3_LogIn(验证.unurl, 验证.base64, 验证.key, kami, imei, code, t3_Json);
    }
    char *tips = (char *)malloc(4096);
    if (!t3_Json.isLogin)
    {
        sprintf(tips, "%s", t3_Json.msg.c_str());
    }
    else
    {
        sprintf(tips, "登录成功!\n到期时间:%s \n", t3_Json.end_time.c_str());
    }
    free(kami);
    free(imei);
    return env->NewStringUTF(tips);
}


extern "C" JNIEXPORT void JNICALL
Java_com_empty_open_MainActivity_init(JNIEnv *env, jobject thiz, jstring dir)
{
    // TODO: implement init()
    if (Mem_isRoot())
    {
        配置.悬浮窗标题 = "ImGui Study 内存映射模板[Root]";
    }else
    {
        配置.悬浮窗标题 = "ImGui Study 内存映射模板[框架]";
    }
    配置.软件根目录库 = env->GetStringUTFChars(dir, JNI_FALSE);
    LOGD("加载软件根目录: %s", 配置.软件根目录库.c_str());
}