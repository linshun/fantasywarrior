LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2djs_shared

LOCAL_MODULE_FILENAME := libcocos2djs

LOCAL_SRC_FILES := hellojavascript/main.cpp \
                    ../../Classes/AppDelegate.cpp \
                    ../../Classes/custom/BillboardParticleSystem.cpp \
                    ../../Classes/custom/DrawNode3D.cpp \
                    ../../Classes/custom/EffectSprite3D.cpp \
                    ../../Classes/custom/JumpBy3D.cpp \
                    ../../Classes/custom/JumpTo3D.cpp \
                    ../../Classes/custom/Water.cpp \
                    ../../Classes/custom/EffectSprite.cpp \
                    ../../Classes/custom/ShadowSprite.cpp \
                    ../../Classes/custom/CCSequence3D.cpp \
                    ../../Classes/custom/GreyShader.cpp \
                    ../../Classes/custom/jsb_cocos2dx_custom_auto.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos_jsb_static

LOCAL_EXPORT_CFLAGS := -DCOCOS2D_DEBUG=2 -DCOCOS2D_JAVASCRIPT

include $(BUILD_SHARED_LIBRARY)


$(call import-module,bindings)
