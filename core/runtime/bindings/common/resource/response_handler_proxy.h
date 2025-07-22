// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#ifndef CORE_RUNTIME_BINDINGS_COMMON_RESOURCE_RESPONSE_HANDLER_PROXY_H_
#define CORE_RUNTIME_BINDINGS_COMMON_RESOURCE_RESPONSE_HANDLER_PROXY_H_

#include <future>
#include <memory>
#include <optional>

#include "core/resource/lazy_bundle/bundle_resource_info.h"
#include "core/runtime/bindings/common/resource/response_promise.h"

namespace lynx {
namespace runtime {

class ResponseHandlerProxy {
 public:
  class Delegate {
   public:
    Delegate() = default;
    virtual ~Delegate() = default;
    virtual void RunOnJSThread(base::closure closure) = 0;
  };

  ResponseHandlerProxy(
      const std::shared_ptr<runtime::ResponsePromise<tasm::BundleResourceInfo>>&
          promise)
      : promise_(promise) {}

  virtual ~ResponseHandlerProxy() = default;

 protected:
  std::shared_ptr<runtime::ResponsePromise<tasm::BundleResourceInfo>> promise_;
};

}  // namespace runtime
}  // namespace lynx

#endif  // CORE_RUNTIME_BINDINGS_COMMON_RESOURCE_RESPONSE_HANDLER_PROXY_H_
