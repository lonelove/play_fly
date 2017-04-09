/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import org.cocos2dx.lib.Cocos2dxActivity;

import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.widget.Toast;
import android.os.Bundle;

import com.umeng.social.CCUMSocialController;

public class AppActivity extends Cocos2dxActivity {
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		CCUMSocialController.initSocialSDK(this, "com.umeng.social");

	}


	protected void onResume() {
		super.onResume();
	}

	protected void onDestroy() {
		super.onDestroy();
	}
	public Cocos2dxGLSurfaceView onCreateView() {
		Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
		// UmengGame should create stencil buffer
		glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);

		return glSurfaceView;
	}
	private long mExitTime; 
	public boolean onKeyDown(int keyCode, KeyEvent event){   
        if (keyCode == KeyEvent.KEYCODE_BACK) {  
            if ((System.currentTimeMillis() - mExitTime) > 2000) {// Èç¹ûÁ½´Î°´¼üÊ±¼ä¼ä¸ô´óÓÚ2000ºÁÃë£¬Ôò²»ÍË³ö  
  
                Toast.makeText(this, "再按一次退出", Toast.LENGTH_SHORT).show();  
                mExitTime = System.currentTimeMillis();// ¸üÐÂmExitTime  
  
            } else {  
                System.exit(0);// ·ñÔòÍË³ö³ÌÐò  
  
            }  
            return true;  
        }  
        return super.onKeyDown(keyCode, event);  
    }  

	protected void onActivityResult(int requestCode, int resultCode, Intent data) {

		CCUMSocialController.onActivityResult(requestCode, resultCode, data);

		super.onActivityResult(requestCode, resultCode, data);
	}

	static {
		System.loadLibrary("cocos2dcpp");
	}

}
