// Copyright 2023 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#include "core/runtime/bindings/jsi/resource/response_handler_in_js.h"

#include <memory>
#include <utility>
#include <vector>

#include "core/runtime/bindings/common/event/runtime_constants.h"
#include "core/runtime/bindings/common/resource/response_promise.h"
#include "core/runtime/bindings/jsi/js_app.h"

namespace lynx {
namespace piper {

ResponseHandlerInJS::ResponseHandlerInJS(
    Delegate& delegate,
    const std::shared_ptr<runtime::ResponsePromise<tasm::BundleResourceInfo>>&
        promise,
    std::weak_ptr<App> native_app)
    : runtime::ResponseHandlerProxy(promise),
      delegate_(delegate),
      native_app_(native_app) {}

Value ResponseHandlerInJS::get(Runtime* rt, const PropNameID& name) {
  if (rt == nullptr) {
    return piper::Value::undefined();
  }

  auto method_name = name.utf8(*rt);
  if (method_name == runtime::kWait) {
    return WaitingForResponse(*rt);
  }
  if (method_name == runtime::kThen) {
    return AddListenerForResponse(*rt);
  }

  return piper::Value::undefined();
}

Value ResponseHandlerInJS::WaitingForResponse(Runtime& rt) {
  return Function::createFromHostFunction(
      rt, PropNameID::forAscii(rt, runtime::kWait), 1,
      [this](Runtime& rt, const piper::Value& this_val,
             const piper::Value* args,
             size_t count) -> base::expected<Value, JSINativeException> {
        if (count < 1) {
          return base::unexpected(BUILD_JSI_NATIVE_EXCEPTION(
              "ResponseHandler.wait's args count must be 1."));
        }
        auto ptr = native_app_.lock();
        if (ptr && !ptr->IsDestroying()) {
          if (!args[0].isNumber()) {
            return base::unexpected(BUILD_JSI_NATIVE_EXCEPTION(
                "ResponseHandler.wait's first param must be number."));
          }

          long timeout = static_cast<long>(args[0].getNumber());
          auto result = promise_->Wait(timeout);
          piper::Value value = piper::Value::undefined();
          if (result.has_value()) {
            // convert result to PiperValue;
          } else {
            // timeout. convert result to PiperValue;
          }
          return value;
        }
        return piper::Value::undefined();
      });
}

Value ResponseHandlerInJS::AddListenerForResponse(Runtime& rt) {
  return Function::createFromHostFunction(
      rt, PropNameID::forAscii(rt, runtime::kThen), 1,
      [this](Runtime& rt, const piper::Value& this_val,
             const piper::Value* args,
             size_t count) -> base::expected<Value, JSINativeException> {
        if (count < 1) {
          return base::unexpected(BUILD_JSI_NATIVE_EXCEPTION(
              "ResponseHandler.then's args count must be 1."));
        }
        auto ptr = native_app_.lock();
        if (ptr && !ptr->IsDestroying()) {
          if (!args[0].isObject() || !args[0].getObject(rt).isFunction(rt)) {
            return base::unexpected(BUILD_JSI_NATIVE_EXCEPTION(
                "ResponseHandler.then's first param must be function."));
          }

          piper::Function func = args[0].getObject(rt).getFunction(rt);
          promise_->AddCallback(
              [this, func = std::move(func)](tasm::BundleResourceInfo) mutable {
                delegate_.RunOnJSThread([this]() {
                  auto ptr = native_app_.lock();
                  if (ptr && !ptr->IsDestroying()) {
                    auto rt = ptr->GetRuntime();
                    if (rt != nullptr) {
                      // TODO(nihao.royal): invoke piper function here;
                    }
                  }
                });
              });
        }
        return piper::Value::undefined();
      });
}

void ResponseHandlerInJS::set(Runtime* rt, const PropNameID& name,
                              const Value& value) {}

std::vector<PropNameID> ResponseHandlerInJS::getPropertyNames(Runtime& rt) {
  std::vector<PropNameID> vec;
  vec.push_back(piper::PropNameID::forUtf8(rt, runtime::kWait));
  vec.push_back(piper::PropNameID::forUtf8(rt, runtime::kThen));
  return vec;
}

}  // namespace piper
}  // namespace lynx
