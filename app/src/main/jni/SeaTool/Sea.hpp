
// by 阿夜 V2Tools
// 使用的所有功能面向开发者 并不提供全部例子 不建议小白使用

#ifndef Sea__H
#define Sea__H

#ifdef __cplusplus
#include <string>
#include <vector>

struct T3_Json
{
    int code; // 状态码

    time_t time;   // 返回网络时间
    int available; // 单码登录剩余时间 秒

    std::string id;        // 卡密ID
    std::string end_time;  // 到期时间
    std::string amount;    // 卡密类型 3天/7天/一年
    std::string token;     // 校验码
    std::string statecode; // 登录状态码
    std::string date;      // 登录的时间 纯数字
    std::string imei;      // 登录成功的卡密
    std::string change;    // 解绑次数
    std::string core;      // 核心数据 自动转为16进制 alldate保持10进制
    std::string msg;       // 登录失败或卡密解绑等其他提示

    std::string ver;
    std::string version;
    std::string uplog;
    std::string upurl;

    bool isLogin;        // 用于判断是否登录成功 登录成功返回true 其他均false
    bool isUpdate;       // 用于判断是否为最新版本
    std::string alldata; // 返回所有数据 用户自定义

    // 数据示例 {"code":345,"id":"5744620","end_time":"2024-03-27 12:03:35","amount":"1\u5e74","available":28900341,"token":"a33ca95230c3bdb7eb3fb996cf40b54d","statecode":"7c7e7fdbe96557bbf09cba61fee88918","time":1682611874,"date":"202304280011","imei":"abcd","change":"83","core":"e998bfe590a7e998bfe590a7"}
};

// 避免与其他Color命名重复
enum Colors
{
    COLOR_SILVERY,   // 银色
    COLOR_RED,       // 红色
    COLOR_GREEN,     // 绿色
    COLOR_YELLOW,    // 黄色
    COLOR_DARK_BLUE, // 暗夜蓝
    COLOR_PINK,      // 粉色
    COLOR_SKY_BLUE,  // 天空蓝
    COLOR_WHITE      // 白色
};

extern "C++"
{
#endif
    //-------------------T3网络验证封装区
    // T3登录 配置 全局数据加密->开启 加密算法->base64自定义编码集 请求值，返回值加密->开启 请求值编码->HEX 时间戳校验->开启 签名校验->双向签名 返回值格式->文本 返回带时间撮
    // 没有实现其他网络验证已经加密算法 如有需要自行调用网络请求去实现 大部分加密解密功能都有 不提供教程 不推荐小白自行尝试
    void mem_CheckVersion(); //打印当前静态库版本  在线检测更新
    int T3_LogIn(const char *url, const char *base64, const char *key, const char *kami, const char *imei, int code, T3_Json &t3_Json); // T3网络验证
    //int T3_LogIn2(const char *url, const char *base64, const char *key, const char *kami, const char *imei, int code, T3_Json &t3_Json); // T3网络验证
    int T3_Update(const char *url, int code, int version, T3_Json &t3_Json);                                                            // T3网络验证 获取更新 安全传输关闭
    int T3_Notice(const char *url, int code, T3_Json &t3_Json);                                                                         // T3网络验证 获取公告软件安全传输关闭

    //-------------------数据加密解密区
    char *toHEX(const char *string);                    // 转换HEX
    char *toMD5(char *pstr, unsigned long long len_B_); // 字符串转MD5
    std::string hexToString(const std::string &hexStr); // 16进制转字符串
    std::string stringToHex(const std::string &str);    // 字符串转16进制
    int hextoint(const char *hex);                      // 16进制转换为10进制

    //-------------------网络请求区
    int http_post(const char *hostname, const char *url, const char *cs, char **run); // 网络POST 主机地址 地址 传入数据 接受数据
    //int http_post2(const char *hostname, const char *url, const char *cs, char **run); // 更改部分写法 
    int http_get(const char *hostname, const char *url, char **run);                  // 同上 少了一个提交的数据 baidu.com url传入/即可

    //-------------------文本读写区
    char *Read(const char *FilePath);           // 读取文件内容
    void Write(char *FilePath, char *contents); // 文件路径 文件内容

    //-------------------进程读取 内存映射区
    int getPID(const char *packageName);                              // 获取游戏进程 理论通杀所有游戏 修复获取不到UE4游戏的BUG
    void *build_mmap(const char *filename, bool readonly, int msize); // 封装mmap函数库

    //-------------------终端颜色区
    void setColor(Colors color); // 设置控制台颜色

    //-------------------手机信息获取区
    bool Mem_isRoot(); // 设备Root判断 非自身运行环境判断

    //-------------------绘制CPU优化区
    int initKeepCUP(int FPS); // 推荐传入 30FPS 45FPS 60FPS 90FPS 120FPS 144FPS 165FPS
    void tickFuntion();       // 循环某位函数 动态调控CPU

    //-------------------内存管理区
    // 只提供syscall内存读取的方法 过CRC校验请自行绕道 暂且提供D/F类型的数据更改和读取

    int initPackage(std::string packageName,bool printLog);                   // 初始化内存广角
    bool mem_vm_readv(long address, void *buffer, size_t size);  // 公开接口 可以实现结构体的读取
    bool mem_vm_writev(long address, void *buffer, size_t size); // 公开接口 同上
    long Mem_lsp64(long addres);                                 // 指针跳转
    long Mem_lsp(long addres); //兼容lsp32 lsp64 上面的lsp64 也兼容32 只是方便这么写而已
    // 数据声明 原本是想要用aoto封装读写 但是考虑到小小白也不会 就舍弃了
    float Mem_getFloat(long addres);             // 获取地址的Float
    int Mem_getDword(long addres);               // 获取内存的Dworld
    void Mem_WriteFloat(long addres, float fix); // 写入指定内存的Float
    void Mem_WriteDword(long addres, int fix);   // 写入指定内存的Dworld

    //获取模块首地址
    long Mem_get_module_cb(const char *name, int index);
    long Mem_get_module_cb(const char *name, int index,bool isSplit,const char * txt); //具体就加了一个条件 因为有些内存字段在r-rw 有些在r-p
    long Mem_get_module_cd(const char *name, int index);

    //-------------------内存管理拓展
    long Mem_readPointer(long addr, long *arr, int sz);          // 读取数组链条 传入数组 
    long Mem_readPointer(long orgin,std::vector<long>& vec);//读取指针 升级版噢
    long Mem_readPointer(long addr, ...);//智能读取指针 
#ifdef __cplusplus
}
#endif

#endif
