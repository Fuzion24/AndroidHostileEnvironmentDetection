LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_LDLIBS := -llog

LOCAL_MODULE    := emudetect
LOCAL_SRC_FILES := emudetect.c

include $(BUILD_SHARED_LIBRARY)
