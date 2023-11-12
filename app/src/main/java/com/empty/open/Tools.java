package com.empty.open;

import android.content.Context;
import android.graphics.PixelFormat;
import android.os.Build;
import android.util.Log;
import android.view.Gravity;
import android.view.WindowManager;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;


/**
 * @author 阿夜
 */
public class Tools {
   public static String TAG = "lOG日志";
    public static WindowManager.LayoutParams getAttributes(boolean isWindow) {
        WindowManager.LayoutParams params = new WindowManager.LayoutParams();
        params.type = WindowManager.LayoutParams.TYPE_APPLICATION_OVERLAY;
        params.flags = WindowManager.LayoutParams.FLAG_FULLSCREEN | WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS | WindowManager.LayoutParams.FLAG_TRANSLUCENT_NAVIGATION | WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE;

        if (isWindow) {
            params.flags |= WindowManager.LayoutParams.FLAG_NOT_TOUCH_MODAL | WindowManager.LayoutParams.FLAG_NOT_TOUCHABLE;
        }
        params.format = PixelFormat.RGBA_8888;
        // 设置图片格式，效果为背景透明
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) {
            params.layoutInDisplayCutoutMode = WindowManager.LayoutParams.LAYOUT_IN_DISPLAY_CUTOUT_MODE_SHORT_EDGES;
        }
        params.gravity = Gravity.LEFT | Gravity.TOP;
        // 调整悬浮窗显示的停靠位置为左侧置顶
        params.x = params.y = 0;
        params.width = params.height = isWindow ? WindowManager.LayoutParams.MATCH_PARENT : 0;
        return params;
    }

    public static boolean 文件写入(String 文件路径, String 文件内容) {
        try {
            FileWriter utf = new FileWriter(文件路径); //写入文件
            utf.write(文件内容);
            utf.close();
            return true;
        } catch (IOException e) {
            Log.d(TAG,"目标位置 -> " + 文件路径 + "内容 -> " + 文件内容 + "分析日志 ->" + e);
            return false;
        }
    }
    public static String 文件读取(String 文件路径)
    {
        String 返回文件 = "";
        try {
            File file = new File(文件路径);
            FileInputStream fis = new FileInputStream(file);
            InputStreamReader isr = new InputStreamReader(fis, "UTF-8");
            BufferedReader br = new BufferedReader(isr);

            String line;
            while ((line = br.readLine()) != null) {
                返回文件 = 返回文件  + line+"\n";
            }
            返回文件 = 返回文件.substring(0,返回文件.length()-1);
            br.close();
            return 返回文件;
        }catch (Exception e)
        {
            Log.d(TAG,"分析日志 ->" + e);
        }
        return "";
    }
    
    public static void shell(final String shell) {
        new Thread(new Runnable(){
                @Override
                public void run() {
                    try {
                        Process proc = Runtime.getRuntime().exec("sh");
                        DataOutputStream ous = new DataOutputStream(proc.getOutputStream());
                        ous.write(shell.getBytes());
                        ous.writeBytes("\n");
                        ous.flush();
                        ous.close();
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            }).start();
    }
    
    public static boolean OutFiles(Context context, String outPath, String fileName) {
        File file = new File(outPath);
        if (!file.exists()) {
            if (!file.mkdirs()) {
                Log.e("--Method--", "copyAssetsSingleFile: cannot create directory.");
                return false;
            }
        }
        try {
            InputStream inputStream = context.getAssets().open(fileName);
            File outFile = new File(file, fileName);
            FileOutputStream fileOutputStream = new FileOutputStream(outFile);
            // Transfer bytes from inputStream to fileOutputStream
            byte[] buffer = new byte[1024];
            int byteRead;
            while (-1 != (byteRead = inputStream.read(buffer))) {
                fileOutputStream.write(buffer, 0, byteRead);
            }
            inputStream.close();
            fileOutputStream.flush();
            fileOutputStream.close();
            return true;
        } catch (IOException e) {
            e.printStackTrace();
            return false;
        }
    }
    
    public static boolean isRoot(){
        String[] rootRelatedDirs = new String[]{"/su", "/su/bin/su", "/sbin/su", "/data/local/xbin/su", "/data/local/bin/su", "/data/local/su", "/system/xbin/su", "/system/bin/su", "/system/sd/xbin/su", "/system/bin/failsafe/su", "/system/bin/cufsdosck", "/system/xbin/cufsdosck", "/system/bin/cufsmgr", "/system/xbin/cufsmgr", "/system/bin/cufaevdd", "/system/xbin/cufaevdd", "/system/bin/conbb", "/system/xbin/conbb"};
        boolean hasRootDir = false;//初始为没有root权限
        String[] rootDirs;
        int dirCount = (rootDirs = rootRelatedDirs).length;

        for (int i = 0; i < dirCount; ++i) {    //for循环遍历数组
            String dir = rootDirs[i];
            if ((new File(dir)).exists()) {
                hasRootDir = true;
                break;
            }
        }
        return Build.TAGS != null && Build.TAGS.contains("test-keys") || hasRootDir;
    }
}
