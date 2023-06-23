/*
 * Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "ReactSkia/utils/RnsLog.h"
#include <cxxreact/JsArgumentHelpers.h>

#include "RNGestureHandlerModule.h"

using namespace folly;

namespace facebook {
namespace xplat {

RNGestureHandlerModule::RNGestureHandlerModule() : NativeEventEmitterModule(nullptr) {
#ifdef RNS_GESTURE_TESTING_TO_BE_REMOVED
  RNS_LOG_TODO("This code needs to be removed when we implement actual native module");
  startObserving();
  addListener("onGestureHandlerEvent");
  addListener("onGestureHandlerStateChange");
#endif
}

auto RNGestureHandlerModule::getConstants() -> std::map<std::string, folly::dynamic> {
  return {
    {"State",
      folly::dynamic::object("UNDETERMINED", static_cast<int>(RNGestureHandlerState::RNGestureHandlerStateUndetermined))
        ("BEGAN", static_cast<int>(RNGestureHandlerState::RNGestureHandlerStateBegan))
        ("ACTIVE", static_cast<int>(RNGestureHandlerState::RNGestureHandlerStateActive))
        ("CANCELLED", static_cast<int>(RNGestureHandlerState::RNGestureHandlerStateCancelled))
        ("FAILED", static_cast<int>(RNGestureHandlerState::RNGestureHandlerStateFailed))
        ("END", static_cast<int>(RNGestureHandlerState::RNGestureHandlerStateEnd))
    },
    {"Direction",
      folly::dynamic::object("RIGHT", static_cast<int>(RNGestureHandlerDirection::RNGestureHandlerDirectionRight))
        ("LEFT", static_cast<int>(RNGestureHandlerDirection::RNGestureHandlerDirectionLeft))
        ("UP", static_cast<int>(RNGestureHandlerDirection::RNGestureHandlerDirectionUp))
        ("DOWN", static_cast<int>(RNGestureHandlerDirection::RNGestureHandlerDirectionDown))
    }
  };
}

std::string RNGestureHandlerModule::getName() {
  return "RNGestureHandlerModule";
}

auto RNGestureHandlerModule::getMethods() -> std::vector<Method> {
  std::vector<Method> emitterMethodsVector  = NativeEventEmitterModule::getMethods();
  std::vector<Method> supportedMethodsVector = {
    Method(
      "install",
      [] (dynamic args) -> bool {
        RNS_LOG_NOT_IMPL;
        return true;
      }),
    Method(
      "createGestureHandler",
      [] (dynamic args) {
        RNS_LOG_NOT_IMPL;
        RNS_LOG_INFO("createGestureHandler : handlerName : " << args[0].getString() << ", handlerTag : " << args[1].getDouble() << ", Configs : " << args[2]);
        return;
      }),
    Method(
      "attachGestureHandler",
      [] (dynamic args) {
        RNS_LOG_NOT_IMPL;
        RNS_LOG_INFO("attachGestureHandler : handlerTag : " << args[1].getDouble() << ", viewTag : " << args[1].getDouble());
        return;
      }),
    Method(
      "dropGestureHandler",
      [] (dynamic args) {
        RNS_LOG_NOT_IMPL;
        return;
      }),
    Method(
      "handleSetJSResponder",
      [] (dynamic args) {
        RNS_LOG_NOT_IMPL;
        return;
      }),
    Method(
      "handleClearJSResponder",
      [] () {
        RNS_LOG_NOT_IMPL;
        return;
      }),
  };
  supportedMethodsVector.insert(supportedMethodsVector.end(), emitterMethodsVector.begin(), emitterMethodsVector.end());
  return supportedMethodsVector;
}

#ifdef RNS_GESTURE_TESTING_TO_BE_REMOVED
void RNGestureHandlerModule::sendGestureHandlerEvent(react::RSkKeyInput keyInput) {
  folly::dynamic eventPlayload = folly::dynamic::object();

  int viewTag = 1;
  int handlerTag = 1;

  RNS_LOG_TODO("sendGestureHandlerEvent is a stubbed implementatiion..");

  eventPlayload["target"] = viewTag;
  eventPlayload["handlerTag"] = handlerTag;
  eventPlayload["state"] = static_cast<int>(RNGestureHandlerState::RNGestureHandlerStateBegan);

  sendEventWithName("onGestureHandlerEvent", folly::dynamic(eventPlayload));
}
#else
void RNGestureHandlerModule::sendGestureHandlerEvent() {
  folly::dynamic eventPlayload = folly::dynamic::object();
  eventPlayload["target"] = 1;
  eventPlayload["handlerTag"] = 1;
  eventPlayload["state"] = static_cast<int>(RNGestureHandlerState::RNGestureHandlerStateEnd);
  sendEventWithName("onGestureHandlerEvent", folly::dynamic(eventPlayload));
}
#endif

#ifdef RNS_GESTURE_TESTING_TO_BE_REMOVED
void RNGestureHandlerModule::sendGestureHandlerStateChangeEvent(react::RSkKeyInput keyInput) {
  folly::dynamic eventPlayload = folly::dynamic::object();

  int viewTag = 1;
  int handlerTag = 1;

  RNS_LOG_TODO("sendGestureHandlerStateChangeEvent is a stubbed implementatiion..");

  eventPlayload["target"] = viewTag;
  eventPlayload["handlerTag"] = handlerTag;
  eventPlayload["state"] = (keyInput.action_ == RNS_KEY_Press) ?
                            static_cast<int>(RNGestureHandlerState::RNGestureHandlerStateBegan) :
                            static_cast<int>(RNGestureHandlerState::RNGestureHandlerStateEnd);
  eventPlayload["oldState"] = (keyInput.action_ == RNS_KEY_Press) ?
                          static_cast<int>(RNGestureHandlerState::RNGestureHandlerStateEnd) :
                          static_cast<int>(RNGestureHandlerState::RNGestureHandlerStateBegan);

  sendEventWithName("onGestureHandlerStateChange", folly::dynamic(eventPlayload));
}
#else
void RNGestureHandlerModule::sendGestureHandlerStateChangeEvent() {
  folly::dynamic eventPlayload = folly::dynamic::object();
  eventPlayload["target"] = 1;
  eventPlayload["handlerTag"] = 1;
  eventPlayload["state"] = static_cast<int>(RNGestureHandlerState::RNGestureHandlerStateEnd);
  eventPlayload["oldState"] = static_cast<int>(RNGestureHandlerState::RNGestureHandlerStateBegan);
  sendEventWithName("onGestureHandlerStateChange", folly::dynamic(eventPlayload));
}
#endif

void RNGestureHandlerModule::startObserving() {
  RNS_LOG_NOT_IMPL;
#ifdef RNS_GESTURE_TESTING_TO_BE_REMOVED
  auto inputEventManager = react::RSkInputEventManager::getInputKeyEventManager();
  if (!inputEventManager) {
    RNS_LOG_ERROR("Unable to get RSkInputEventManager instance ");
    return;
  }
  callbackId_ = inputEventManager->addKeyEventCallback(
    [&](react::RSkKeyInput keyInput) {
      if(keyInput.key_ != RNS_KEY_Select)
        return;
      sendGestureHandlerEvent(keyInput);
      sendGestureHandlerStateChangeEvent(keyInput);
    });
#endif
}

void RNGestureHandlerModule::stopObserving() {
  RNS_LOG_NOT_IMPL;
#ifdef RNS_GESTURE_TESTING_TO_BE_REMOVED
  if(callbackId_ > 0) {
    auto inputEventManager = react::RSkInputEventManager::getInputKeyEventManager();
    if ( !inputEventManager ) {
      RNS_LOG_ERROR("Unable to get RSkInputEventManager instance ");
      return;
    }
    inputEventManager->removeKeyEventCallback(callbackId_);
    callbackId_ = 0;// resetting the callback
  } else {
    RNS_LOG_ERROR("callbackId is invalid callbackId_ :: " << callbackId_);
  }
#endif
}

#ifdef __cplusplus
extern "C" {
#endif
RNS_EXPORT_MODULE_WITHOUT_SUFFIX(RNGestureHandlerModule)
#ifdef __cplusplus
}
#endif

} // namespace xplat
} // namespace facebook

