#include "src/dictionaries/webrtc/rtc_error.h"

#include <nan.h>
#include <node-addon-api/napi.h>
#include <utility>
#include <v8.h>
#include <webrtc/api/rtc_error.h>

#include "src/functional/validation.h"
#include "src/node/error_factory.h"

namespace node_webrtc {

TO_JS_IMPL(webrtc::RTCError*, error) {
  return Converter<const webrtc::RTCError*, v8::Local<v8::Value>>::Convert(error);
}

TO_NAPI_IMPL(webrtc::RTCError*, pair) {
  return Converter<std::pair<Napi::Env, const webrtc::RTCError*>, Napi::Value>::Convert(pair);
}

TO_JS_IMPL(const webrtc::RTCError*, error) {
  Nan::EscapableHandleScope scope;
  if (!error) {
    return Validation<v8::Local<v8::Value>>::Invalid("No error? Please file a bug on https://github.com/js-platform/node-webrtc");
  }
  switch (error->type()) {
    case webrtc::RTCErrorType::NONE:
      return Validation<v8::Local<v8::Value>>::Invalid("No error? Please file a bug on https://github.com/js-platform/node-webrtc");
    case webrtc::RTCErrorType::UNSUPPORTED_PARAMETER:
    case webrtc::RTCErrorType::INVALID_PARAMETER:
      return Pure(scope.Escape(ErrorFactory::CreateInvalidAccessError(error->message())));
    case webrtc::RTCErrorType::INVALID_RANGE:
      return Pure(scope.Escape(ErrorFactory::CreateRangeError(error->message())));
    case webrtc::RTCErrorType::SYNTAX_ERROR:
      return Pure(scope.Escape(ErrorFactory::CreateSyntaxError(error->message())));
    case webrtc::RTCErrorType::INVALID_STATE:
      return Pure(scope.Escape(ErrorFactory::CreateInvalidStateError(error->message())));
    case webrtc::RTCErrorType::INVALID_MODIFICATION:
      return Pure(scope.Escape(ErrorFactory::CreateInvalidModificationError(error->message())));
    case webrtc::RTCErrorType::NETWORK_ERROR:
      return Pure(scope.Escape(ErrorFactory::CreateNetworkError(error->message())));
    // NOTE(mroberts): SetLocalDescription in the wrong state can throw this.
    case webrtc::RTCErrorType::INTERNAL_ERROR:
      return Pure(scope.Escape(ErrorFactory::CreateInvalidStateError(error->message())));
    case webrtc::RTCErrorType::UNSUPPORTED_OPERATION:
    case webrtc::RTCErrorType::RESOURCE_EXHAUSTED:
      return Pure(scope.Escape(ErrorFactory::CreateOperationError(error->message())));
  }
}

TO_NAPI_IMPL(const webrtc::RTCError*, pair) {
  auto env = pair.first;
  Napi::EscapableHandleScope scope(env);
  auto error = pair.second;
  if (!error) {
    return Validation<Napi::Value>::Invalid("No error? Please file a bug on https://github.com/js-platform/node-webrtc");
  }
  switch (error->type()) {
    case webrtc::RTCErrorType::NONE:
      return Validation<Napi::Value>::Invalid("No error? Please file a bug on https://github.com/js-platform/node-webrtc");
    case webrtc::RTCErrorType::UNSUPPORTED_PARAMETER:
    case webrtc::RTCErrorType::INVALID_PARAMETER:
      return Pure(scope.Escape(ErrorFactory::napi::CreateInvalidAccessError(env, error->message())));
    case webrtc::RTCErrorType::INVALID_RANGE:
      return Pure(scope.Escape(ErrorFactory::napi::CreateRangeError(env, error->message())));
    case webrtc::RTCErrorType::SYNTAX_ERROR:
      return Pure(scope.Escape(ErrorFactory::napi::CreateSyntaxError(env, error->message())));
    case webrtc::RTCErrorType::INVALID_STATE:
      return Pure(scope.Escape(ErrorFactory::napi::CreateInvalidStateError(env, error->message())));
    case webrtc::RTCErrorType::INVALID_MODIFICATION:
      return Pure(scope.Escape(ErrorFactory::napi::CreateInvalidModificationError(env, error->message())));
    case webrtc::RTCErrorType::NETWORK_ERROR:
      return Pure(scope.Escape(ErrorFactory::napi::CreateNetworkError(env, error->message())));
    // NOTE(mroberts): SetLocalDescription in the wrong state can throw this.
    case webrtc::RTCErrorType::INTERNAL_ERROR:
      return Pure(scope.Escape(ErrorFactory::napi::CreateInvalidStateError(env, error->message())));
    case webrtc::RTCErrorType::UNSUPPORTED_OPERATION:
    case webrtc::RTCErrorType::RESOURCE_EXHAUSTED:
      return Pure(scope.Escape(ErrorFactory::napi::CreateOperationError(env, error->message())));
  }
}

}  // namespace node_webrtc