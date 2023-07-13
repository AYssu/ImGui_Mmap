
// by 阿夜

#ifndef Sea__H
#define Sea__H

#ifdef __cplusplus

struct T3_Json
{
    int code; // 状态码

    int time;      // 返回网络时间
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

enum Color
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
    // 定义函数
    int Timecheck(int year, int mon, int day, int hour, int min, int sec); // 距离目标日期时间 返回时间差秒
    int getPID(const char *packageName);                                   // 获取游戏进程 理论通杀所有游戏
    void *build_mmap(const char *filename, bool readonly, int msize);      // 封装mmap函数库
    void setColor(Color color);                                            // 设置控制台颜色

    void CleanBash(); // 初始化静态库

    char *http_get(const char *url);                        // http get 封装
    char *http_post(const char *url, const char *params);   // http post 封装
    char *http_put(const char *url, const char *params);    // http put 封装
    char *http_delete(const char *url, const char *params); // http delete

    char *toHEX(const char *string);                    // 转换HEX
    char *toMD5(char *pstr, unsigned long long len_B_); // 字符串转MD5
    std::string hexToString(const std::string &hexStr); // 16进制转字符串
    std::string stringToHex(const std::string &str);    // 字符串转16进制
    int hextoint(const char *hex);
    char *Read(const char *FilePath);           // 读取文件内容
    void Write(char *FilePath, char *contents); // 文件路径 文件内容

    // T3登录 配置 全局数据加密->开启 加密算法->base64自定义编码集 请求值，返回值加密->开启 请求值编码->HEX 时间戳校验->开启 签名校验->双向签名 返回值格式->文本
    void T3_LOAD(const char *url, const char *base64, const char *key, const char *kami, const char *imei, int code, struct T3_Json &t3_Json); // T3网络验证
    void T3_GX(const char *url, int code, int version, struct T3_Json &t3_Json);                                                               // T3网络验证 获取更新 安全传输关闭
    void T3_GG(const char *url, int code, struct T3_Json &t3_Json);                                                                            // T3网络验证 获取公告 安全传输关闭

    void SetMemPID(pid_t ipid); //使用内存函数之前先设置pid方法即可 这个方法一定要之前设置
    long Mem_get_module_cd(const char *name, int index); // 获取内存CD头
    long Mem_get_module_cb(const char *name, int index); // 获取内存CB头

    long Mem_readPointer(long addr, long *arr, int sz); // 读取数组链条
    long Mem_lsp64(long addres);                        // 指针跳转
    float Mem_ReadFloat(long addres);                   // 获取地址的Float
    int Mem_ReadInt(long addres);                       // 获取内存的Dworld
    void Mem_WriteFloat(long addres, float fix);        // 写入指定内存的Float
    void Mem_WriteInt(long addres, int fix);            // 写入指定内存的Dworld
#ifdef __cplusplus
}
#endif

#endif
