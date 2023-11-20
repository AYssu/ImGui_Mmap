package com.empty.open;

import android.Manifest;
import android.annotation.SuppressLint;
import android.app.ProgressDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.provider.Settings;
import android.util.Log;
import android.view.View;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

/**
 * 该项目已在github开源 有兴趣的小伙伴欢迎给个 start
 * 2022.09.27
 * 2023-11-12 进行二次开发完善 一直没时间
 * AIDE全解 带注释给小白学习用 学不会就算了
 *
 * @author 阿夜*/

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("ImGui");
        //导入静态库
    }

    public native void init(String dir);
    public native String LoadT3(String kami,String imei,boolean is_login);
    public Button 登录控件;
    public TextView 解绑控件;
    public EditText 卡密框;
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

        init(getFilesDir()+"/assets");
        //传入assets目录
        Tools.OutFiles(MainActivity.this, getFilesDir() + "/assets", "draw");

        设置点击监听();
    }

    /**
     * 获取点击事件 主要是验证卡密
     */
    private void 设置点击监听()
    {
        登录控件 = findViewById(R.id.activitymainButtonDL);
        解绑控件 = findViewById(R.id.activitymainTextViewJB);
        卡密框 = findViewById(R.id.activitymainEditTextKM);

        登录控件.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                final ProgressDialog progressDialog = new ProgressDialog(MainActivity.this, 5);
                progressDialog.setProgressStyle(ProgressDialog.STYLE_SPINNER);
                progressDialog.setMessage("Please wait...");
                progressDialog.setCancelable(false);
                progressDialog.show();

                @SuppressLint("HandlerLeak") final Handler loginHandler = new Handler() {
                    @Override
                    public void handleMessage(Message msg) {
                        if (msg.what == 0) {
                            progressDialog.dismiss();

                        } else if (msg.what == 1) {
                            progressDialog.dismiss();

                            AlertDialog.Builder builder = new AlertDialog.Builder(MainActivity.this);
                            builder.setTitle("登录成功");
                            builder.setMessage(msg.obj.toString());
                            builder.setCancelable(false);
                            builder.setPositiveButton("OK", new DialogInterface.OnClickListener() {
                                @Override
                                public void onClick(DialogInterface dialog, int which) {
                                    Tools.文件写入("/sdcard/卡密信息", 卡密框.getText().toString());
                                }
                            });
                            builder.show();
                        }

                    }
                };

                new Thread(() -> {
                    String result = LoadT3(卡密框.getText().toString(),android.provider.Settings.Secure.getString(MainActivity.this.getContentResolver(), android.provider.Settings.Secure.ANDROID_ID),true);
                    Log.d(Tools.TAG,result);
                    if (!result.contains("到期时间")) {
                        loginHandler.sendEmptyMessage(0);
                    } else {
                        Message msg = new Message();
                        msg.what = 1;
                        msg.obj = result;
                        loginHandler.sendMessage(msg);
                    }
                }).start();
            }
        });
        解绑控件.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                LoadT3(卡密框.getText().toString(),android.provider.Settings.Secure.getString(MainActivity.this.getContentResolver(), android.provider.Settings.Secure.ANDROID_ID),false);
            }
        });

        //其他什么加TG QQ群的自己copy copy吧
    }


    /**
     * 获取软件必要权限 悬浮窗 读取权限 以及写入二进制 给予Root权限
     */
    private void 获取权限() //初始化软件
    {
        if (Settings.canDrawOverlays(getApplicationContext())) {
            //判断悬浮窗权限

            if (Tools.isRoot()) {
                //判断设备环境
                Toast.makeText(MainActivity.this, "Root", Toast.LENGTH_SHORT).show();
                Tools.shell("su -c chmod -R 7777 " + getFilesDir() + "/assets");

            } else {

                Toast.makeText(MainActivity.this, "框架", Toast.LENGTH_SHORT).show();
                Tools.shell("chmod -R 7777 " + getFilesDir() + "/assets");

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
        if (Tools.isRoot()) {
            Tools.shell("su -c " + name);
        } else {
            Tools.shell(name);
        }
        Log.d(Tools.TAG,"cmd -> "+name +" isRoot -> "+Tools.isRoot());
    }

    /**
     * 对弹窗方法进行封装 并没什么用 单纯方便
     */
    public void showToast(String msg) {
        Toast.makeText(this, msg, Toast.LENGTH_SHORT).show();
    }

    @Override
    protected void onRestart() {
        super.onRestart();
        if (!Settings.canDrawOverlays(getApplicationContext()))
        {
            Toast.makeText(MainActivity.this,"授予悬浮窗权限失败!请手动打开悬浮窗 并重启软件",Toast.LENGTH_SHORT).show();
        }
    }
}
