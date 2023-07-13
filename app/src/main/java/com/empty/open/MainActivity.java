package com.empty.open;

import android.Manifest;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.provider.Settings;
import android.util.Log;
import android.view.WindowManager;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

/**
 * Create By.阿夜 该项目已在github开源 有兴趣的小伙伴欢迎给个 start
 * 2022.09.27
 * AIDE全解 带注释给小白学习用
 **/
public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("ImGui");
        //导入静态库
    }

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

        init();

        Functions.OutFiles(MainActivity.this, getFilesDir() + "/assets", "draw");
    }

    private void init() //初始化软件
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
