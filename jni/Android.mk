LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_LDLIBS := -llog

LOCAL_MODULE    := emudetect
LOCAL_SRC_FILES := emudetect.c

APP_ABI := armeabi

include $(BUILD_SHARED_LIBRARY)
