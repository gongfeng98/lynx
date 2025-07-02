// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.
package com.lynx.tasm.behavior.shadow;

import com.lynx.react.bridge.mapbuffer.ReadableCompactArrayBuffer;
import com.lynx.tasm.base.CalledByNative;
import com.lynx.tasm.behavior.LynxUIOwner;

public class TextLayout {
  final LynxUIOwner mUIOwner;
  public TextLayout(LynxUIOwner uiOwner) {
    mUIOwner = uiOwner;
  }

  @CalledByNative
  public float[] measureText(int sign, float width, int widthMode, float height, int heightMode) {
    return mUIOwner.measureText(sign, width, widthMode, height, heightMode);
  }
  @CalledByNative
  public void dispatchLayoutBefore(int sign, ReadableCompactArrayBuffer buffer) {
    mUIOwner.dispatchLayoutBefore(sign, buffer);
  }

  @CalledByNative
  public void align() {}
}
