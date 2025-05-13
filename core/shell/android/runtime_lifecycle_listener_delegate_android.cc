// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#include "lynx/core/shell/android/runtime_lifecycle_listener_delegate_android.h"

#include "base/include/log/logging.h"
#include "lynx/core/build/gen/RuntimeLifecycleListenerDelegate_jni.h"

namespace lynx {
namespace shell {

RuntimeLifecycleListenerDelegateAndroid::
    RuntimeLifecycleListenerDelegateAndroid(JNIEnv* env, jobject delegate)
    : RuntimeLifecycleListenerDelegate(
          RuntimeLifecycleListenerDelegate::DelegateType::PART),
      impl_(env, delegate) {}

void RuntimeLifecycleListenerDelegateAndroid::OnRuntimeAttach(
    Napi::Env current_napi_env) {
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_RuntimeLifecycleListenerDelegate_onRuntimeAttach(
      env, impl_.Get(),
      reinterpret_cast<jlong>(static_cast<napi_env>(current_napi_env)));
}

void RuntimeLifecycleListenerDelegateAndroid::OnRuntimeDetach() {
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_RuntimeLifecycleListenerDelegate_onRuntimeDetach(env, impl_.Get());
}

void RuntimeLifecycleListenerDelegateAndroid::RegisterJNI(JNIEnv* env) {
  RegisterNativesImpl(env);
}

}  // namespace shell
}  // namespace lynx
