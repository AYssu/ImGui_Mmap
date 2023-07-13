LOCAL_PATH := $(call my-dir)

# 加载静态库 包含mmap内存映射函数封装 T3网络验证封装
include $(CLEAR_VARS)
LOCAL_MODULE := Sea
LOCAL_SRC_FILES := Static/libSea.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := ImGui
# 模块编译
LOCAL_STATIC_LIBRARIES := Sea
# 加载静态库
LOCAL_ARM_MODE := arm

# 一些编译参数
LOCAL_CFLAGS := -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w
LOCAL_CFLAGS += -fno-rtti -fno-exceptions -fpermissive
LOCAL_CPP_FEATURES += exceptions
LOCAL_CPPFLAGS := -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w -Werror -s -std=c++17
LOCAL_CPPFLAGS += -Wno-error=c++11-narrowing -fms-extensions -fno-rtti -fno-exceptions -fpermissive
LOCAL_LDFLAGS += -Wl,--gc-sections,--strip-all, -llog

LOCAL_C_INCLUDES += $(LOCAL_PATH)/ImGuu
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Main
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Static
LOCAL_C_INCLUDES += $(LOCAL_C_INCLUDES:$(LOCAL_PATH)/%:=%)


FILE_LIST += $(wildcard $(LOCAL_PATH)/Main/*.c*)
FILE_LIST += $(wildcard $(LOCAL_PATH)/ImGui/*.c*)
FILE_LIST += $(wildcard $(LOCAL_PATH)/Static/*.c*)
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_LDFLAGS += -llog -lEGL -lGLESv3 -landroid

include $(BUILD_SHARED_LIBRARY)
