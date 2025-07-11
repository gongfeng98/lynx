// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#ifndef CORE_INCLUDE_STARLIGHT_STANDALONE_STARLIGHT_H_
#define CORE_INCLUDE_STARLIGHT_STANDALONE_STARLIGHT_H_

#include <stdint.h>

#include "starlight_config.h"
#include "starlight_value.h"

#ifdef __cplusplus
extern "C" {
#endif

// a wrapper of LayoutObject.
struct StarlightNode;
typedef struct StarlightNode* SLNodeRef;
struct StarlightSize;
struct StarlightConfig;

/**
 *  1. When `widthMode` or `heightMode` is `SLNodeMeasureModeUndefined`:
 *  The corresponding `width` or `height` value is meaningless, as if setting
 * `width: max-content` or `height: max-content` in Web.
 *
 *  2. When `widthMode` or `heightMode` is `SLNodeMeasureModeExactly`:
 *  The `width` or `height` value specifies the exact size constraint (content
 * bounds) for the node.
 *
 *  3. When `widthMode` or `heightMode` is `SLNodeMeasureModeAtMost`:
 *  The `width` or `height` value specifies the maximum allowable size (content
 * bounds) for the node.
 *
 *  The `width`, `width_mode`, `height`, and `height_mode` parameters
 *  respectively define the width and height constraints (content bounds) of the
 *  node. This function is only required to return the content size of
 *  the node, excluding margins, borders, and padding.
 */
typedef StarlightSize (*StarlightMeasureFunc)(void* manager_node, float width,
                                              SLNodeMeasureMode width_mode,
                                              float height,
                                              SLNodeMeasureMode height_mode);

typedef float (*StarlightBaselineFunc)(void* manager_node, float width,
                                       float height);

typedef struct StarlightMeasureDelegate {
  // measure_func_ is used to measure the node.
  StarlightMeasureFunc measure_func_;
  // When baseline_func_ is set, it will be called to get the distance from the
  // top edge of the content box to the baseline of the node.
  StarlightBaselineFunc baseline_func_;
  // When the measure_func_ or baseline_func_ need to access the manager_node_,
  // set the manager_node_.
  void* manager_node_;
} StarlightMeasureDelegate;

SLNodeRef SLNodeNew();
// User need to manage the memory of config through calling `SLConfigFree` when
// not using.
SLNodeRef SLNodeNewWithConfig(StarlightConfig* config);

void SLNodeInsertChild(const SLNodeRef parent, const SLNodeRef child,
                       int32_t index);
// Recommended to use this function rather than SLNodeInsertChild.
void SLNodeInsertChildBefore(const SLNodeRef parent, const SLNodeRef child,
                             const SLNodeRef reference);
void SLNodeRemoveChild(const SLNodeRef parent, const SLNodeRef child);
void SLNodeRemoveAllChildren(const SLNodeRef parent);
// Nearly resets all of the node, including removing children, reseting layout
// results, reseting CSS styles, and so on.
void SLNodeReset(const SLNodeRef node);
SLNodeRef SLNodeGetChild(const SLNodeRef node, int32_t index);
int32_t SLNodeGetChildCount(const SLNodeRef node);
SLNodeRef SLNodeGetParent(const SLNodeRef node);

void SLNodeFree(const SLNodeRef node);
void SLNodeFreeRecursive(const SLNodeRef node);

bool SLNodeIsDirty(const SLNodeRef node);
void SLNodeMarkDirty(const SLNodeRef node);

// TODO(yuanzhiwen): currently unavailable
// bool SLNodeGetHasNewLayout(const SLNodeRef node);
// void SLNodeSetHasNewLayout(const SLNodeRef node, bool has_new_layout);

bool SLNodeIsRTL(const SLNodeRef node);

// owner_width, owner_height define the containing block for the root node, and
// the percentage for width, height, max-width, max-height, padding, margin will
// refer to this containing block. If width, height are not set, the root node's
// outer box (margin box) will be limited by the owner_width and owner_height.
void SLNodeCalculateLayout(const SLNodeRef node, float owner_width,
                           float owner_height, SLDirection owner_direction);

/**
 * @brief Set the measurement delegate of a node.
 *
 * @param delegate The measurement delegate object.
 *
 * This function sets the measurement delegate of a node. The measurement
 * delegate object should inject functions to measure the node:
 *   - StarlightMeasureFunc measure_func_ (optional): for measuring the node.
 *   - StarlightBaselineFunc baseline_func_ (optional): for calculating the
baseline of the node.
 *   - void* manager_node_ (optional): the manager node of the StarlightNode, it
 * usually holds the StarlightNode.
 *
 * Users need to manage the lifecycle of the measurement delegate object
 * themselves to ensure that it is released before the node is destroyed.
 */
void SLNodeSetMeasureDelegate(const SLNodeRef node,
                              StarlightMeasureDelegate* const delegate);
StarlightMeasureDelegate* SLNodeGetMeasureDelegate(const SLNodeRef node);
bool SLNodeHasMeasureFunc(const SLNodeRef node);

// Styles
void SLNodeStyleSetDirection(const SLNodeRef node, SLDirection type);
void SLNodeStyleSetFlexDirection(const SLNodeRef node, SLFlexDirection value);

// alignment
void SLNodeStyleSetJustifyContent(const SLNodeRef node, SLJustifyContent value);
void SLNodeStyleSetAlignContent(const SLNodeRef node, SLAlignContent value);
void SLNodeStyleSetAlignItems(const SLNodeRef node, SLFlexAlign value);
void SLNodeStyleSetAlignSelf(const SLNodeRef node, SLFlexAlign value);

// only supports `absoulte` and `relative`. Defaults to `relative`.
void SLNodeStyleSetPositionType(const SLNodeRef node, SLPositionType value);

// Defaults to `no-wrap`.
void SLNodeStyleSetFlexWrap(const SLNodeRef node, SLFlexWrap value);

// Defaults to `flex`.
void SLNodeStyleSetDisplay(const SLNodeRef node, SLDisplay value);

// Defaults to `border-box`. Different from Web (`content-box`).
void SLNodeStyleSetBoxSizing(const SLNodeRef node, SLBoxSizing value);

// Defaults to undefined.
void SLNodeStyleSetAspectRatio(const SLNodeRef node, float value);

// Defaults to 0.
void SLNodeStyleSetOrder(const SLNodeRef node, int32_t value);

// flex: 1 is equivalent to flex-grow: 1, flex-shrink: 1, flex-basis: 0 (differs
// from 0% in Web).
void SLNodeStyleSetFlex(const SLNodeRef node, float value);
// Defaults to 0.
void SLNodeStyleSetFlexGrow(const SLNodeRef node, float value);
// Defaults to 1.
void SLNodeStyleSetFlexShrink(const SLNodeRef node, float value);
// flex-basis: defaults to `auto`.
void SLNodeStyleSetFlexBasis(const SLNodeRef node, float value);
void SLNodeStyleSetFlexBasisPercent(const SLNodeRef node, float value);
void SLNodeStyleSetFlexBasisAuto(const SLNodeRef node);

// top, bottom, left, right: defaults to `auto`.
void SLNodeStyleSetPosition(const SLNodeRef node, SLEdge edge, float position);
void SLNodeStyleSetPositionPercent(const SLNodeRef node, SLEdge edge,
                                   float position);
void SLNodeStyleSetPositionAuto(const SLNodeRef node, SLEdge edge);

// margin
// Defaults to 0.
void SLNodeStyleSetMargin(const SLNodeRef node, SLEdge edge, float value);
void SLNodeStyleSetMarginPercent(const SLNodeRef node, SLEdge edge,
                                 float value);
void SLNodeStyleSetMarginAuto(const SLNodeRef node, SLEdge edge);

// padding
// Defaults to 0.
void SLNodeStyleSetPadding(const SLNodeRef node, SLEdge edge, float value);
void SLNodeStyleSetPaddingPercent(const SLNodeRef node, SLEdge edge,
                                  float value);

// border width
// Defaults to 0.
void SLNodeStyleSetBorder(const SLNodeRef node, SLEdge edge, float value);

// gap
// Defaults to 0.
void SLNodeStyleSetGap(const SLNodeRef node, SLGap gutter, float value);
void SLNodeStyleSetGapPercent(const SLNodeRef node, SLGap gutter, float value);

// width properties
// width: defaults to `auto`.
void SLNodeStyleSetWidth(const SLNodeRef node, float value);
void SLNodeStyleSetWidthPercent(const SLNodeRef node, float value);
void SLNodeStyleSetWidthAuto(const SLNodeRef node);
void SLNodeStyleSetWidthMaxContent(const SLNodeRef node);
void SLNodeStyleSetWidthFitContent(const SLNodeRef node);
// min-width: defaults to `0`.
void SLNodeStyleSetMinWidth(const SLNodeRef node, float value);
void SLNodeStyleSetMinWidthPercent(const SLNodeRef node, float value);
// max-width: defaults to no limit.
void SLNodeStyleSetMaxWidth(const SLNodeRef node, float value);
void SLNodeStyleSetMaxWidthPercent(const SLNodeRef node, float value);

// height properties
// height: defaults to `auto`.
void SLNodeStyleSetHeight(const SLNodeRef node, float value);
void SLNodeStyleSetHeightPercent(const SLNodeRef node, float value);
void SLNodeStyleSetHeightAuto(const SLNodeRef node);
void SLNodeStyleSetHeightMaxContent(const SLNodeRef node);
void SLNodeStyleSetHeightFitContent(const SLNodeRef node);
// min-height: defaults to `0`.
void SLNodeStyleSetMinHeight(const SLNodeRef node, float value);
void SLNodeStyleSetMinHeightPercent(const SLNodeRef node, float value);
// max-height: defaults to no limit.
void SLNodeStyleSetMaxHeight(const SLNodeRef node, float value);
void SLNodeStyleSetMaxHeightPercent(const SLNodeRef node, float value);

// get style
SLFlexDirection SLNodeStyleGetFlexDirection(const SLNodeRef node);
// When setting to SLJustifyContentStart/SLJustifyContentEnd, we will get
// SLJustifyContentFlexStart/SLJustifyContentFlexEnd.
SLJustifyContent SLNodeStyleGetJustifyContent(const SLNodeRef node);
SLAlignContent SLNodeStyleGetAlignContent(const SLNodeRef node);
SLFlexAlign SLNodeStyleGetAlignItems(const SLNodeRef node);
SLFlexAlign SLNodeStyleGetAlignSelf(const SLNodeRef node);
SLPositionType SLNodeStyleGetPositionType(const SLNodeRef node);
SLFlexWrap SLNodeStyleGetFlexWrap(const SLNodeRef node);
SLDisplay SLNodeStyleGetDisplay(const SLNodeRef node);
SLBoxSizing SLNodeStyleGetBoxSizing(const SLNodeRef node);
float SLNodeStyleGetAspectRatio(const SLNodeRef node);
int32_t SLNodeStyleGetOrder(const SLNodeRef node);
float SLNodeStyleGetFlexGrow(const SLNodeRef node);
float SLNodeStyleGetFlexShrink(const SLNodeRef node);
float SLNodeStyleGetBorder(const SLNodeRef node, SLEdge edge);
StarlightValue SLNodeStyleGetFlexBasis(const SLNodeRef node);
StarlightValue SLNodeStyleGetPosition(const SLNodeRef node, SLEdge edge);
StarlightValue SLNodeStyleGetMargin(const SLNodeRef node, SLEdge edge);
StarlightValue SLNodeStyleGetPadding(const SLNodeRef node, SLEdge edge);
StarlightValue SLNodeStyleGetGap(const SLNodeRef node, SLGap gutter);
StarlightValue SLNodeStyleGetWidth(const SLNodeRef node);
StarlightValue SLNodeStyleGetHeight(const SLNodeRef node);
StarlightValue SLNodeStyleGetMinWidth(const SLNodeRef node);
StarlightValue SLNodeStyleGetMaxWidth(const SLNodeRef node);
StarlightValue SLNodeStyleGetMinHeight(const SLNodeRef node);
StarlightValue SLNodeStyleGetMaxHeight(const SLNodeRef node);

// layout result
// the distance from the upper left corner of the current node's border box to
// the left edge of the parent node's border box.
float SLNodeLayoutGetLeft(const SLNodeRef node);
// the distance from the upper left corner of the current node's border box to
// the top edge of the parent node's border box.
float SLNodeLayoutGetTop(const SLNodeRef node);

// TODO(yuanzhiwen): offset_right, and offset_bottom
// float SLNodeLayoutGetRight(const SLNodeRef node);
// float SLNodeLayoutGetBottom(const SLNodeRef node);

// return the width and height of border box.
float SLNodeLayoutGetWidth(const SLNodeRef node);
float SLNodeLayoutGetHeight(const SLNodeRef node);
float SLNodeLayoutGetMargin(const SLNodeRef node, SLEdge edge);
float SLNodeLayoutGetPadding(const SLNodeRef node, SLEdge edge);
float SLNodeLayoutGetBorder(const SLNodeRef node, SLEdge edge);

#ifdef __cplusplus
}
#endif

#endif  // CORE_INCLUDE_STARLIGHT_STANDALONE_STARLIGHT_H_
