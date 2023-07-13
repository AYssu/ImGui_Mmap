package com.empty.open;

import android.Manifest;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.provider.Settings;
import android.view.WindowManager;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

/**
 * 该项目已在github开源 有兴趣的小伙伴欢迎给个 start
 * 2022.09.27
 * AIDE全解 带注释给小白学习用
 *
 * @author 阿夜*/
public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("ImGui");
        //导入静态库
    }

    /**
     * @param kami 传入T3卡密信息
     * @param imei 传入T3 imei
     * @param isLogin 判断是否为登录/解绑
     * @return 返回登录信息的结果
     */
    public native String LoadT3(String kami, String imei, boolean isLogin);

    /**
     * @return 返回软件公告
     */
    public native String getTips();

    /**
     * @return 返回更新版本的校验 如果是最新则不处理
     */
    public native String checkVersion();

    private static final String[] NEEDED_PERMISSIONS = new String[]{
            //定义权限数值
            Manifest.permission.WRITE_SETTINGS,
            //写入设置
            Manifest.permission.WRITE_EXTERNAL_STORAGE,
            //写入外部存储
            Manifest.permission.READ_EXTERNAL_STORAGE,
            //读取文件
            Manifest.permission.READ_PHONE_STATE
            //读取手机信息
    };
    private String 悬浮窗权限 = Settings.ACTION_MANAGE_OVERLAY_PERMISSION;
    //悬浮窗权限

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        getWindow().addFlags(WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS);
        //沉浸式状态栏

        //getWindow().setFlags(WindowManager.LayoutParams.FLAG_SECURE, WindowManager.LayoutParams.FLAG_SECURE);//禁止软件首页截屏

        getWindow().setBackgroundDrawable(null);
        //设置背景透明

        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        //隐藏状态栏

        获取权限();

        Functions.OutFiles(MainActivity.this, getFilesDir() + "/assets", "draw");
    }

    /**
     * 获取软件必要权限 悬浮窗 读取权限 以及写入二进制 给予Root权限
     */
    private void 获取权限() //初始化软件
    {
        if (Settings.canDrawOverlays(getApplicationContext())) {
            //判断悬浮窗权限

            if (Functions.isRoot()) {
                //判断设备环境
                Toast.makeText(MainActivity.this, "Root", Toast.LENGTH_SHORT).show();
                Functions.shell("su -c chmod -R 7777 " + getFilesDir() + "/assets");

            } else {

                Toast.makeText(MainActivity.this, "框架", Toast.LENGTH_SHORT).show();
                Functions.shell("chmod -R 7777 " + getFilesDir() + "/assets");

            }
            startService(new Intent(MainActivity.this, MyService.class));
        } else {

            Intent intent = new Intent(悬浮窗权限);
            intent.setData(Uri.parse("package:" + getPackageName()));
            startActivity(intent);
            //跳转悬获取悬浮窗
            Toast.makeText(MainActivity.this, "权限获取后请重新启动！", Toast.LENGTH_SHORT).show();

        }
        ActivityCompat.requestPermissions(MainActivity.this, NEEDED_PERMISSIONS, 23);
        //获取权限

    }

    /**
     * native 使用反射 调用二进制
     * @param name 传入shell 命令 这是一个反射的接口
     */
    public void call(String name) {
        //jni反射调用，传递二进制路径
        if (Functions.isRoot()) {
            Functions.shell("su -c " + name);
        } else {
            Functions.shell(name);
        }
    }

    /**
     * 对弹窗方法进行封装 并没什么用 单纯方便
     */
    public void showToast(String msg) {
        Toast.makeText(this, msg, Toast.LENGTH_SHORT).show();
    }

}
