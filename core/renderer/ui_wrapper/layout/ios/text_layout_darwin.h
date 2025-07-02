// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#ifndef CORE_RENDERER_UI_WRAPPER_LAYOUT_IOS_TEXT_LAYOUT_DARWIN_H_
#define CORE_RENDERER_UI_WRAPPER_LAYOUT_IOS_TEXT_LAYOUT_DARWIN_H_

#import <Foundation/Foundation.h>

#include "core/public/text_layout_impl.h"

namespace lynx {
namespace tasm {

class TextLayoutDarwin : public TextLayoutImpl {
 public:
  explicit TextLayoutDarwin() {}

  ~TextLayoutDarwin() override = default;

  LayoutResult Measure(Element* element, float width, int width_mode,
                       float height, int height_mode) override;

  void Align(Element* element) override;

  void DispatchLayoutBefore(Element* element) override;
};

}  // namespace tasm
}  // namespace lynx

#endif  // CORE_RENDERER_UI_WRAPPER_LAYOUT_IOS_TEXT_LAYOUT_DARWIN_H_
