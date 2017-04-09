LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)





LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
                   ../../Classes/BulletEnemy.cpp \
                   ../../Classes/Card.cpp \
		   ../../Classes/GameOver.cpp \
		   ../../Classes/Gems.cpp \
		   ../../Classes/HMap.cpp \
		   ../../Classes/HPauseLayer.cpp \
		   ../../Classes/LevelBulletEnemy.cpp \
		   ../../Classes/LevelGems.cpp \
		   ../../Classes/LevelNewBullet.cpp \
		   ../../Classes/LevelNewEnemy.cpp \
		   ../../Classes/LevelNewPlayer.cpp \
		   ../../Classes/LevelScene.cpp \
		   ../../Classes/LevelSelect.cpp \
		   ../../Classes/LevelUniqueSkill.cpp \
		   ../../Classes/LoadScene.cpp \
		   ../../Classes/LostGame.cpp \
		   ../../Classes/MainScene.cpp \
                   ../../Classes/MyGame.cpp \
		   ../../Classes/MyHanagerScene.cpp \
		   ../../Classes/NewBullet.cpp \
		   ../../Classes/NewEnemy.cpp \
		   ../../Classes/NewPlayer.cpp \
		   ../../Classes/PlayerScene.cpp \
		   ../../Classes/PopScene.cpp \
		   ../../Classes/RnakLayer.cpp \
		   ../../Classes/SetScene.cpp \
		   ../../Classes/SignLayer.cpp \
		   ../../Classes/UniqueSkill.cpp \
		   ../../Classes/Cocos2dx/Android/CCUMSocialController.cpp  \
		   ../../Classes/Cocos2dx/ShareButton/UMShareButton.cpp \
		   ../../Classes/Cocos2dx/Common/CCUMSocialSDK.cpp 


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,./prebuilt-mk)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
