// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME builddIce65dict
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "ROOT/RConfig.hxx"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Header files passed as explicit arguments
#include "inc/CE65Event.h"
#include "inc/Cluster.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static TClass *ce65_frame_Dictionary();
   static void ce65_frame_TClassManip(TClass*);
   static void *new_ce65_frame(void *p = nullptr);
   static void *newArray_ce65_frame(Long_t size, void *p);
   static void delete_ce65_frame(void *p);
   static void deleteArray_ce65_frame(void *p);
   static void destruct_ce65_frame(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::ce65_frame*)
   {
      ::ce65_frame *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::ce65_frame));
      static ::ROOT::TGenericClassInfo 
         instance("ce65_frame", "CE65Event.h", 8,
                  typeid(::ce65_frame), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &ce65_frame_Dictionary, isa_proxy, 4,
                  sizeof(::ce65_frame) );
      instance.SetNew(&new_ce65_frame);
      instance.SetNewArray(&newArray_ce65_frame);
      instance.SetDelete(&delete_ce65_frame);
      instance.SetDeleteArray(&deleteArray_ce65_frame);
      instance.SetDestructor(&destruct_ce65_frame);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::ce65_frame*)
   {
      return GenerateInitInstanceLocal(static_cast<::ce65_frame*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::ce65_frame*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *ce65_frame_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::ce65_frame*>(nullptr))->GetClass();
      ce65_frame_TClassManip(theClass);
   return theClass;
   }

   static void ce65_frame_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *ce65_event_Dictionary();
   static void ce65_event_TClassManip(TClass*);
   static void *new_ce65_event(void *p = nullptr);
   static void *newArray_ce65_event(Long_t size, void *p);
   static void delete_ce65_event(void *p);
   static void deleteArray_ce65_event(void *p);
   static void destruct_ce65_event(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::ce65_event*)
   {
      ::ce65_event *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::ce65_event));
      static ::ROOT::TGenericClassInfo 
         instance("ce65_event", "CE65Event.h", 24,
                  typeid(::ce65_event), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &ce65_event_Dictionary, isa_proxy, 4,
                  sizeof(::ce65_event) );
      instance.SetNew(&new_ce65_event);
      instance.SetNewArray(&newArray_ce65_event);
      instance.SetDelete(&delete_ce65_event);
      instance.SetDeleteArray(&deleteArray_ce65_event);
      instance.SetDestructor(&destruct_ce65_event);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::ce65_event*)
   {
      return GenerateInitInstanceLocal(static_cast<::ce65_event*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::ce65_event*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *ce65_event_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::ce65_event*>(nullptr))->GetClass();
      ce65_event_TClassManip(theClass);
   return theClass;
   }

   static void ce65_event_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_ce65_frame(void *p) {
      return  p ? new(p) ::ce65_frame : new ::ce65_frame;
   }
   static void *newArray_ce65_frame(Long_t nElements, void *p) {
      return p ? new(p) ::ce65_frame[nElements] : new ::ce65_frame[nElements];
   }
   // Wrapper around operator delete
   static void delete_ce65_frame(void *p) {
      delete (static_cast<::ce65_frame*>(p));
   }
   static void deleteArray_ce65_frame(void *p) {
      delete [] (static_cast<::ce65_frame*>(p));
   }
   static void destruct_ce65_frame(void *p) {
      typedef ::ce65_frame current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::ce65_frame

namespace ROOT {
   // Wrappers around operator new
   static void *new_ce65_event(void *p) {
      return  p ? new(p) ::ce65_event : new ::ce65_event;
   }
   static void *newArray_ce65_event(Long_t nElements, void *p) {
      return p ? new(p) ::ce65_event[nElements] : new ::ce65_event[nElements];
   }
   // Wrapper around operator delete
   static void delete_ce65_event(void *p) {
      delete (static_cast<::ce65_event*>(p));
   }
   static void deleteArray_ce65_event(void *p) {
      delete [] (static_cast<::ce65_event*>(p));
   }
   static void destruct_ce65_event(void *p) {
      typedef ::ce65_event current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::ce65_event

namespace ROOT {
   static TClass *vectorlEce65_framegR_Dictionary();
   static void vectorlEce65_framegR_TClassManip(TClass*);
   static void *new_vectorlEce65_framegR(void *p = nullptr);
   static void *newArray_vectorlEce65_framegR(Long_t size, void *p);
   static void delete_vectorlEce65_framegR(void *p);
   static void deleteArray_vectorlEce65_framegR(void *p);
   static void destruct_vectorlEce65_framegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<ce65_frame>*)
   {
      vector<ce65_frame> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<ce65_frame>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<ce65_frame>", -2, "vector", 389,
                  typeid(vector<ce65_frame>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEce65_framegR_Dictionary, isa_proxy, 4,
                  sizeof(vector<ce65_frame>) );
      instance.SetNew(&new_vectorlEce65_framegR);
      instance.SetNewArray(&newArray_vectorlEce65_framegR);
      instance.SetDelete(&delete_vectorlEce65_framegR);
      instance.SetDeleteArray(&deleteArray_vectorlEce65_framegR);
      instance.SetDestructor(&destruct_vectorlEce65_framegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<ce65_frame> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<ce65_frame>","std::vector<ce65_frame, std::allocator<ce65_frame> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<ce65_frame>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEce65_framegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<ce65_frame>*>(nullptr))->GetClass();
      vectorlEce65_framegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEce65_framegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEce65_framegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<ce65_frame> : new vector<ce65_frame>;
   }
   static void *newArray_vectorlEce65_framegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<ce65_frame>[nElements] : new vector<ce65_frame>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEce65_framegR(void *p) {
      delete (static_cast<vector<ce65_frame>*>(p));
   }
   static void deleteArray_vectorlEce65_framegR(void *p) {
      delete [] (static_cast<vector<ce65_frame>*>(p));
   }
   static void destruct_vectorlEce65_framegR(void *p) {
      typedef vector<ce65_frame> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<ce65_frame>

namespace ROOT {
   static TClass *vectorlEce65_eventgR_Dictionary();
   static void vectorlEce65_eventgR_TClassManip(TClass*);
   static void *new_vectorlEce65_eventgR(void *p = nullptr);
   static void *newArray_vectorlEce65_eventgR(Long_t size, void *p);
   static void delete_vectorlEce65_eventgR(void *p);
   static void deleteArray_vectorlEce65_eventgR(void *p);
   static void destruct_vectorlEce65_eventgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<ce65_event>*)
   {
      vector<ce65_event> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<ce65_event>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<ce65_event>", -2, "vector", 389,
                  typeid(vector<ce65_event>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEce65_eventgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<ce65_event>) );
      instance.SetNew(&new_vectorlEce65_eventgR);
      instance.SetNewArray(&newArray_vectorlEce65_eventgR);
      instance.SetDelete(&delete_vectorlEce65_eventgR);
      instance.SetDeleteArray(&deleteArray_vectorlEce65_eventgR);
      instance.SetDestructor(&destruct_vectorlEce65_eventgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<ce65_event> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<ce65_event>","std::vector<ce65_event, std::allocator<ce65_event> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<ce65_event>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEce65_eventgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<ce65_event>*>(nullptr))->GetClass();
      vectorlEce65_eventgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEce65_eventgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEce65_eventgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<ce65_event> : new vector<ce65_event>;
   }
   static void *newArray_vectorlEce65_eventgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<ce65_event>[nElements] : new vector<ce65_event>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEce65_eventgR(void *p) {
      delete (static_cast<vector<ce65_event>*>(p));
   }
   static void deleteArray_vectorlEce65_eventgR(void *p) {
      delete [] (static_cast<vector<ce65_event>*>(p));
   }
   static void destruct_vectorlEce65_eventgR(void *p) {
      typedef vector<ce65_event> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<ce65_event>

namespace {
  void TriggerDictionaryInitialization_ce65dict_Impl() {
    static const char* headers[] = {
"inc/CE65Event.h",
"inc/Cluster.h",
nullptr
    };
    static const char* includePaths[] = {
"inc",
"/home/quark_hu/package/root/install/include/",
"/home/hinata/kyorin/analysis/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "ce65dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
struct __attribute__((annotate("$clingAutoload$inc/CE65Event.h")))  ce65_frame;
namespace std{template <typename _Tp> class __attribute__((annotate("$clingAutoload$bits/allocator.h")))  __attribute__((annotate("$clingAutoload$string")))  allocator;
}
struct __attribute__((annotate("$clingAutoload$inc/CE65Event.h")))  ce65_event;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "ce65dict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "inc/CE65Event.h"
#include "inc/Cluster.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"ce65_event", payloadCode, "@",
"ce65_frame", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("ce65dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_ce65dict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_ce65dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_ce65dict() {
  TriggerDictionaryInitialization_ce65dict_Impl();
}
