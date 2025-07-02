// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.
package com.lynx.tasm.behavior.shadow.text;

public class AttributedTextBundle {
  final private CharSequence mSpan;
  final private TextAttributes mTextAttributes;

  public AttributedTextBundle(CharSequence span, TextAttributes textAttributes) {
    mSpan = span;
    mTextAttributes = textAttributes;
  }

  public CharSequence getSpan() {
    return mSpan;
  }

  public TextAttributes getTextAttributes() {
    return mTextAttributes;
  }
}
