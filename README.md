## 开源ImGui 框架学习 (继续咯)
    - 搁这么久也更新一下 优化了一下登录以及绘制传输效率的问题
    - 移除传统读取文本的方式读取数据 修改为内存映射 效率优于Socket 
    - 优化登录 减少在java层的验证 全部封装至C++
    - 作者随缘更新 任何问题请自己百度解决
当前静态库支持arm64-v8a 无特殊需求 谁用32位谁就用反正我不用
Create by 阿夜  开源 Android ImGui 学习插件
测试卡密 XCYB046E52D1818360988D74A202D3A8