package com.empty.open;

import android.content.Context;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
*这个是默认的GLSurfaceView 模板启动格式
*详细方法实现自己去百度
**/

public class GLES3JNIView extends GLSurfaceView implements GLSurfaceView.Renderer {

	public GLES3JNIView(Context context) {
		super(context);
		setEGLConfigChooser(8, 8, 8, 8, 16, 0);
		getHolder().setFormat(-3);
		setEGLContextClientVersion(3);//GL Version 2 x86的需要用2 一般手机都支持
		setRenderer(this);
	}

	public static native void init();

	public static native void resize(int width, int height);

	public static native void step();

	public static native void MotionEventClick(boolean down, float PosX, float PosY);

	public static native String getWindowRect();

	public static native void real(float width, float height);

	public void onDrawFrame(GL10 gl) {
		step();
	}

	public void onSurfaceChanged(GL10 gl, int width, int height) {
		resize(width, height);
	}

	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		init();
	}

	@Override
	protected void onDetachedFromWindow() {
		super.onDetachedFromWindow();
	}

}

