// This code is adpated from
//https://medium.com/@a7ul/beginners-guide-to-writing-nodejs-addons-using-c-and-n-api-node-addon-api-9b3b718a9a7f
#include <napi.h>
#include "HuffmanTree.h"

class MyClass : public Napi::ObjectWrap<MyClass> {
 public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  MyClass(const Napi::CallbackInfo& info);
  HuffmanTree* GetInternalInstance();

 private:
  static Napi::FunctionReference constructor;
  Napi::Value Decompress(const Napi::CallbackInfo& info);
  Napi::Value Compress(const Napi::CallbackInfo& info);
  Napi::Value GetSizeCompressed(const Napi::CallbackInfo& info);
  Napi::Value GetSizeSource(const Napi::CallbackInfo& info);
  Napi::Value GetExt(const Napi::CallbackInfo& info);
  HuffmanTree *huffTree;
};
