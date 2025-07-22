// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#include "core/runtime/bindings/common/resource/response_promise_unittest.h"

#include <memory>

#include "core/runtime/bindings/common/resource/response_promise.h"
#include "third_party/googletest/googletest/include/gtest/gtest.h"

namespace lynx {
namespace runtime {
namespace test {
TEST_F(ResponsePromiseTest, TestResponsePromiseAddCallback) {
  ResponsePromise<int32_t> response_promise;
  response_promise.AddCallback([](int32_t value) { EXPECT_EQ(value, 42); });
  response_promise.SetValue(42);
}

TEST_F(ResponsePromiseTest, TestResponsePromiseWait) {
  ResponsePromise<int32_t> response_promise;
  response_promise.SetValue(42);
  auto result = response_promise.Wait(0);
  EXPECT_EQ(result.value(), 42);
}

TEST_F(ResponsePromiseTest, TestResponsePromiseAddCallbackAfterSetValue) {
  ResponsePromise<int32_t> response_promise;
  response_promise.SetValue(42);
  response_promise.AddCallback([](int32_t value) { EXPECT_EQ(value, 42); });
}

}  // namespace test
}  // namespace runtime
}  // namespace lynx
