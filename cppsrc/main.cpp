#include <napi.h>
#include "Samples/MyClass.h"
Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  // functionexample::Init(env, exports);
  return MyClass::Init(env, exports);
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, InitAll)
