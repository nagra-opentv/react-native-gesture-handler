/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <cxxreact/CxxModule.h>
#include "ReactSkia/LegacyNativeModules/NativeEventEmitter.h"
#include "ReactSkia/utils/RnsUtils.h"

#undef RNS_GESTURE_TESTING_TO_BE_REMOVED // This code is kept for testing will be removed once we implement actual module
#ifdef RNS_GESTURE_TESTING_TO_BE_REMOVED
#include "ReactSkia/core_modules/RSkInputEventManager.h"
#endif

using namespace std;

namespace facebook {
namespace xplat {

class RNGestureHandlerModule : public NativeEventEmitterModule {
 public:
  RNGestureHandlerModule();
  std::map<std::string, folly::dynamic> getConstants() override;
  std::vector<Method> getMethods() override;
  std::string getName() override;

  enum class RNGestureHandlerState {
    RNGestureHandlerStateUndetermined = 0,
    RNGestureHandlerStateFailed,
    RNGestureHandlerStateBegan,
    RNGestureHandlerStateCancelled,
    RNGestureHandlerStateActive,
    RNGestureHandlerStateEnd,
  };

  enum class RNGestureHandlerDirection {
    RNGestureHandlerDirectionRight = 1,
    RNGestureHandlerDirectionLeft = 2,
    RNGestureHandlerDirectionUp = 4,
    RNGestureHandlerDirectionDown = 8,
  };

 private:
  void startObserving() override;
  void stopObserving() override;

#ifdef RNS_GESTURE_TESTING_TO_BE_REMOVED
  int callbackId_ = 0;
  void sendGestureHandlerEvent(react::RSkKeyInput keyInput);
  void sendGestureHandlerStateChangeEvent(react::RSkKeyInput keyInput);
#else
  void sendGestureHandlerEvent();
  void sendGestureHandlerStateChangeEvent();
#endif
};

} // namespace xplat
} // namespace facebook
