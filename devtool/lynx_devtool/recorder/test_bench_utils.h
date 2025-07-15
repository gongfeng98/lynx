// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#ifndef DEVTOOL_LYNXDEVTOOL_RECORDER_TEST_BENCH_UTILS_H_
#define DEVTOOL_LYNXDEVTOOL_RECORDER_TEST_BENCH_UTILS_H_

#include <string>
#include <vector>

namespace lynx {
namespace devtool {

const std::string TEST_BENCH_URL_PREFIX = "sslocal://arkview?";

std::string TestBenchDecode(const std::string& encoded);

std::vector<uint8_t> TestBenchDecompress(const std::vector<uint8_t>& data);

}  // namespace devtool
}  // namespace lynx

#endif  // DEVTOOL_LYNXDEVTOOL_RECORDER_TEST_BENCH_UTILS_H_
