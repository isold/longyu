# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)


LOCAL_CFLAGS += -DOS_LINUX

LOCAL_LDLIBS :=  -L$(SYSROOT)/usr/lib -llog 

source_path := $(dir $(LOCAL_PATH))jni
sources := $(wildcard $(source_path)/*.cpp $(source_path)/base/task/*.cpp $(source_path)/base/*.cpp $(source_path)/base/pack/*.cpp $(source_path)/base/rsa/*.cpp)
sources := $(sources:$(LOCAL_PATH)/%=%)

LOCAL_MODULE    := SdkKernel
LOCAL_SRC_FILES := $(sources)



include $(BUILD_SHARED_LIBRARY)
