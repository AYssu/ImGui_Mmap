package com.empty.open;

import android.annotation.SuppressLint;
import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.graphics.PixelFormat;
import android.os.Build;
import android.os.Handler;
import android.os.IBinder;
import android.util.Log;
import android.view.Gravity;
import android.view.MotionEvent;
import android.view.View;
import android.view.WindowManager;


public class MyService extends Service {

    public WindowManager windowManager;
    public int type;

    GLES3JNIView display;
    private WindowManager.LayoutParams vParams;


    @Override
    public IBinder onBind(Intent intent) {
        /*  Return the communication channel to the service. */
        throw new UnsupportedOperationException("Not yet implemented");
    }

    @SuppressLint({"WrongConstant", "RtlHardcoded", "ClickableViewAccessibility"})
    @Override
    public void onCreate() {

        windowManager = (WindowManager) getSystemService(WINDOW_SERVICE);
        //获取系统窗口
        WindowManager.LayoutParams params = new WindowManager.LayoutParams();

        vParams = Functions.getAttributes(false);
        vParams.x = vParams.y = 0;
        display = new GLES3JNIView(this);
        //引入GLSurfaceView
        WindowManager win = (WindowManager) getSystemService(Context.WINDOW_SERVICE);
        assert win != null;
        final View vTouch = new View(this);
        vTouch.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                int action = event.getAction();
                switch (action) {
                    case MotionEvent.ACTION_MOVE:
                    case MotionEvent.ACTION_DOWN:
                    case MotionEvent.ACTION_UP:
                        GLES3JNIView.MotionEventClick(action != MotionEvent.ACTION_UP, event.getRawX(), event.getRawY());
                        String date = String.valueOf(action != MotionEvent.ACTION_UP);
                        Log.d("Alice-", date + "X" + event.getRawX() + "Y" + event.getRawY());
                        break;
                    default:
                        break;
                }
                return false;
            }
        });
        final Handler handler = new Handler();
        handler.postDelayed(new Runnable() {
            @Override
            public void run() {
                try {
                    String rect[] = GLES3JNIView.getWindowRect().split("\\|");
                    vParams.x = Integer.parseInt(rect[0]);
                    vParams.y = Integer.parseInt(rect[1]);
                    vParams.width = Integer.parseInt(rect[2]);
                    vParams.height = Integer.parseInt(rect[3]);
                    windowManager.updateViewLayout(vTouch, vParams);
                } catch (Exception e) {
                }
                handler.postDelayed(this, 20);
            }
        }, 20);
        ////////*
        params.systemUiVisibility = View.SYSTEM_UI_FLAG_HIDE_NAVIGATION |
                View.SYSTEM_UI_FLAG_FULLSCREEN |
                View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION |
                View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY |
                View.SYSTEM_UI_FLAG_LAYOUT_STABLE |
                View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN;
        params.type = Build.VERSION_CODES.O <= Build.VERSION.SDK_INT ? WindowManager.LayoutParams.TYPE_APPLICATION_OVERLAY : WindowManager.LayoutParams.TYPE_SYSTEM_ALERT;
        params.gravity = Gravity.TOP | Gravity.LEFT;
        params.format = PixelFormat.TRANSPARENT;
        params.width = WindowManager.LayoutParams.MATCH_PARENT;
        params.height = WindowManager.LayoutParams.MATCH_PARENT;
        params.flags =
                WindowManager.LayoutParams.FLAG_NOT_TOUCHABLE |
                        WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE |
                        WindowManager.LayoutParams.FLAG_NOT_TOUCH_MODAL |
                        WindowManager.LayoutParams.FLAG_SPLIT_TOUCH |
                        WindowManager.LayoutParams.FLAG_HARDWARE_ACCELERATED |//硬件加速
                        WindowManager.LayoutParams.FLAG_FULLSCREEN |//隐藏状态栏导航栏以全屏(貌似没什么用)
                        WindowManager.LayoutParams.FLAG_LAYOUT_NO_LIMITS |//忽略屏幕边界
                        WindowManager.LayoutParams.FLAG_LAYOUT_ATTACHED_IN_DECOR |//显示在状态栏上方(貌似高版本无效
                        WindowManager.LayoutParams.FLAG_LAYOUT_IN_SCREEN;//布局充满整个屏幕 忽略应用窗口限制

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) {
            params.layoutInDisplayCutoutMode = WindowManager.LayoutParams.LAYOUT_IN_DISPLAY_CUTOUT_MODE_SHORT_EDGES;
            //覆盖刘海
        }
        windowManager.addView(display, params);
        windowManager.addView(vTouch, vParams);
        super.onCreate();
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        super.onStartCommand(intent, flags, startId);
        return Service.START_STICKY;
    }
}
