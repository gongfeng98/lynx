// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#include "core/renderer/ui_wrapper/layout/ios/text_layout_darwin.h"

namespace lynx {
namespace tasm {

LayoutResult TextLayoutDarwin::Measure(Element* element, float width, int width_mode, float height,
                                       int height_mode) {
  return LayoutResult{0, 0, 0};
}

void TextLayoutDarwin::Align(Element* element) {}

void TextLayoutDarwin::DispatchLayoutBefore(Element* element) {}

}  // namespace tasm
}  // namespace lynx
