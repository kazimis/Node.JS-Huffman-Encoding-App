/*part of this code is adapted from
https://medium.com/@a7ul/beginners-guide-to-writing-nodejs-addons-using-c-and-n-api-node-addon-api-9b3b718a9a7f
*/
#include "MyClass.h"

Napi::FunctionReference MyClass::constructor;

Napi::Object MyClass::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "MyClass", {
    InstanceMethod("decompress", &MyClass::Decompress),
    InstanceMethod("compress", &MyClass::Compress),
    InstanceMethod("getSizeSource", &MyClass::GetSizeSource),
    InstanceMethod("getSizeCompressed", &MyClass::GetSizeCompressed),
    InstanceMethod("getExt", &MyClass::GetExt),
  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("MyClass", func);
  return exports;
}

MyClass::MyClass(const Napi::CallbackInfo& info) : Napi::ObjectWrap<MyClass>(info)  {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  this->huffTree = new HuffmanTree();
}

//GetSizeSource
Napi::Value MyClass::GetSizeSource(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  int size = this->huffTree->getSizeSource();
  return Napi::Number::New(env, size);
}

//getSizeCompressed
Napi::Value MyClass::GetSizeCompressed(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  int size = this->huffTree->getSizeCompressed();
  return Napi::Number::New(env, size);
}

//Compress
Napi::Value MyClass::Compress(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if (info.Length() != 2 || !info[0].IsString() || !info[1].IsString()){
    Napi::TypeError::New(env, "Two filename expected").ThrowAsJavaScriptException();
  }
  Napi::String srcFile = info[0].As<Napi::String>();
  Napi::String destFile = info[1].As<Napi::String>();
  bool isCompressed = this->huffTree->compress(srcFile, destFile);
  return Napi::Boolean::New(env, isCompressed);
}

//Decompress
Napi::Value MyClass::Decompress(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if (info.Length() != 2 || !info[0].IsString() || !info[1].IsString()){
    Napi::TypeError::New(env, "Two filename expected").ThrowAsJavaScriptException();
  }

  Napi::String srcFile = info[0].As<Napi::String>();
  Napi::String destFile = info[1].As<Napi::String>();
  bool isDecompressed = this->huffTree->decompress(srcFile, destFile);
  return Napi::Boolean::New(info.Env(), isDecompressed);
}

//getfile extension
Napi::Value MyClass::GetExt(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  string str = this->huffTree->getExt();
  return Napi::String::New(info.Env(), str);
}
HuffmanTree* MyClass::GetInternalInstance() {
  return this->huffTree;
}
