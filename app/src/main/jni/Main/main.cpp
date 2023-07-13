#include "struct.h"
#include "ImGui/font.h"
#include "Static/Sea.h"


bool g_Initialized;
Response *response;
//绘制结构体
ImGuiWindow* g_window = nullptr;

struct 全局配置{
	ImFont *字体指针;
	JNIEnv * Jvm_env = NULL;

}配置;

bool 登录成功 = false;
struct 绘制信息结构体{
    bool 初始化;

    bool 方框;
    bool 射线;
    bool 昵称;
    bool 距离;
    bool 血量;
    bool 雷达;
    bool 观战;
    bool 骨骼;
    bool 帧率;
    bool 阵营;
    bool 人数;

    bool 自瞄圈;
    bool 雷达圈;
}绘制;

struct 颜色结构体{
    ImColor 方框颜色 = ImColor(200,255,0,255);
    ImColor 真人射线颜色 = ImColor(0,255,255,255);
    ImColor 骨骼颜色 = ImColor(200,255,0,255);
	ImColor 随机颜色[1000] = {};
}颜色;
struct 功能结构体{
    bool 除草;
    bool 无后;
    bool 加速;
    bool 自瞄;
}功能;

struct 数值结构体
{
    float 屏幕X = 0;
    float 屏幕Y = 0;

    int 主题选项 = 2;

    float 射线宽 = 1.8f;
    float 方框宽 = 1.8f;
    float 骨骼宽 = 1.8f;
}数值;

struct 绘制{

    float 人物X, 人物Y, 人物W, 距离, 血量;
    int 人机, 阵营;

    float 头X, 头Y;//头部
    float 胸部X, 胸部Y;//胸部
    float 臀部X, 臀部Y;//屁股
    float 左肩X, 左肩Y;//左肩
    float 右肩X, 右肩Y;//右肩
    float 左手肘X, 左手肘Y;//左手肘
    float 右手肘X, 右手肘Y;//右手肘
    float 左手腕X, 左手腕Y;//左手腕
    float 右手腕X, 右手腕Y;//右手腕
    float 左大腿X, 左大腿Y;//左大腿
    float 右大腿X, 右大腿Y;//右大腿
    float 左膝盖X, 左膝盖Y;//左膝盖
    float 右膝盖X, 右膝盖Y;//右膝盖
    float 左脚腕X, 左脚腕Y;//左脚腕
    float 右脚腕X, 右脚腕Y;//右脚腕
}人物数据;


extern "C"
JNIEXPORT void JNICALL
Java_com_empty_open_GLES3JNIView_init(JNIEnv* env, jclass cls){

    if(g_Initialized) return ;
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    io.IniFilename = nullptr;

    for (int i = 0; i < 1000; ++i) {
        颜色.随机颜色[i] = ImColor(ImVec4((rand()%205+50)/255.f,rand()%255/255.f,rand()%225/225.f,225/225.f));
    }
    //随机队伍颜色

    response = (Response *)build_mmap("/sdcard/Empty", false,sizeof(Response));
    //文件名 只读 结构体大小 只能使用指针结构体
    // 设置ImGui风格
    ImGui::StyleColorsLight();

    ImGui_ImplAndroid_Init();
    ImGui_ImplOpenGL3_Init("#version 300 es");
    配置.字体指针 = io.Fonts->AddFontFromMemoryTTF((void *)FontFile, Fontsize, 30.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
    IM_ASSERT(配置.字体指针 != NULL);

    ImGui::GetStyle().ScaleAllSizes(3.0f);

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 5.3f;
    style.FrameRounding = 2.3f;
    style.ScrollbarRounding = 1;
    style.ScrollbarSize = 1.0f;

    g_Initialized=true;


}

extern "C"
JNIEXPORT void JNICALL
Java_com_empty_open_GLES3JNIView_resize(JNIEnv* env,jclass obj, jint width, jint height) {
    数值.屏幕X = (int) width;
    数值.屏幕Y = (int) height;
    glViewport(30, 400, width, height);
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigWindowsMoveFromTitleBarOnly = true;
    io.IniFilename = nullptr;
    ImGui::GetIO().DisplaySize = ImVec2((float)width, (float)height);
}


void DrawText(float X, float Y,int sizem,char *data) {
    auto size = ImGui::CalcTextSize(data);
    float x = size.x*(sizem/39.0f);
    float y = size.y*(sizem/39.0f);
    ImGui::GetBackgroundDrawList()->AddText(配置.字体指针,sizem, ImVec2(X -= (float)((int)x >> 1), Y -= (float)( (int)y >> 1)), ImColor(225, 255, 255), data);
}



void ESP()
{
    ImGui::GetForegroundDrawList()->AddText(配置.字体指针,50,ImVec2(270, 170),ImColor(225,0,0),"ImGui 开源学习插件 ");

    int zr=0,rj=0;
    for (int i =0; i < response->PlayerCount; ++i)
    {


    }
}
void BeginDraw() {

    ImGuiIO &io = ImGui::GetIO();
    //UI窗体背景色
    ImGuiStyle &style = ImGui::GetStyle();
    io.ConfigWindowsMoveFromTitleBarOnly = false;
    io.WantSaveIniSettings = true;
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
    //窗体边框圆角
    style.WindowRounding = 10.0f;
    if (ImGui::Begin("\tImGui Study\t", NULL, 0)) {
        g_window = ImGui::GetCurrentWindow();
        ImGui::SetWindowPos({15, 250}, ImGuiCond_Once);
        ImGui::SetWindowSize({数值.屏幕X-30,-1},ImGuiCond_Once);
        if (ImGui::BeginTabBar("Tab", ImGuiTabBarFlags_NoCloseWithMiddleMouseButton | ImGuiTabBarFlags_NoTabListScrollingButtons)) {
            //菜单标题
            if (ImGui::BeginTabItem("\t绘制\t")) {
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
                ImGui::Checkbox("骨骼", &绘制.骨骼);

                ImGui::Checkbox("雷达", &绘制.雷达);
                ImGui::SameLine();
                ImGui::Checkbox("观战", &绘制.观战);
                ImGui::SameLine();
                ImGui::Checkbox("帧率", &绘制.帧率);

                ImGui::ColorEdit4("方框颜色", (float *) &颜色.方框颜色);
                ImGui::ColorEdit4("射线颜色", (float *) &颜色.真人射线颜色);
                ImGui::ColorEdit4("骨骼颜色", (float *) &颜色.骨骼颜色);


                ImGui::SliderFloat("射线宽", &数值.射线宽, 1, 6);
                ImGui::SliderFloat("方框宽", &数值.方框宽, 1, 6);
                ImGui::SliderFloat("骨骼宽", &数值.骨骼宽, 1, 4);

                //这个菜单页面结束
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("\t功能\t"))
            {
                ImGui::Checkbox("除草", &功能.除草);
                ImGui::SameLine();
                ImGui::Checkbox("无后", &功能.无后);
                ImGui::SameLine();
                ImGui::Checkbox("加速", &功能.加速);
                ImGui::SameLine();
                ImGui::Checkbox("自瞄", &功能.自瞄);

                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("\t设置\t")) {


                if (ImGui::Combo("主题颜色", &数值.主题选项, "胖次蓝\0胖次紫\0胖次白\0")) {
                    switch (数值.主题选项) {
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
                ImGui::Text("绘制耗时 %.3f ms (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

                ImGui::EndTabBar();

            }
        }
        ImGui::EndTabItem();
    }
}
void EndDraw()
{
    ImGuiWindow* window =  ImGui::GetCurrentWindow();
    window->DrawList->PushClipRectFullScreen();
    ImGui::End();
}


extern "C"
JNIEXPORT void JNICALL
Java_com_empty_open_GLES3JNIView_step(JNIEnv* env,jclass obj) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(数值.屏幕X,  数值.屏幕Y);
    ImGui::NewFrame();

    BeginDraw();

    if (g_Initialized) {
        ESP();
    }

    EndDraw();

    ImGui::Render();
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

extern "C"
JNIEXPORT void JNICALL
Java_com_empty_open_GLES3JNIView_MotionEventClick( JNIEnv* env, jclass obj,jboolean down,jfloat PosX,jfloat PosY){
    ImGuiIO & io = ImGui::GetIO();
    io.MouseDown[0] = down;
    io.MousePos = ImVec2(PosX,PosY);
}

extern "C"
JNIEXPORT jstring JNICALL Java_com_empty_open_GLES3JNIView_getWindowRect(JNIEnv *env,jclass thiz) {
    // TODO: 实现 getWindowSizePos()
    char result[256]="0|0|0|0";
    if(g_window){
        sprintf(result,"%d|%d|%d|%d",(int)g_window->Pos.x,(int)g_window->Pos.y,(int)g_window->Size.x,(int)g_window->Size.y);
    }
    return env->NewStringUTF(result);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_empty_open_GLES3JNIView_real(JNIEnv* env,jclass obj,jfloat w, jfloat h){
    数值.屏幕X = w;
    数值.屏幕Y = h;
}


