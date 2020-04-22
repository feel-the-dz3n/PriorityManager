//
//  Object.h
//  cxxreflect
//
//  Created by Nikita Ivanov on 3/14/20.
//  Copyright © 2020 Plak Corp. All rights reserved.
//

#ifndef Object_h
#define Object_h
#include "Stats.h"
#include "String.h"
#include "Methods.h"
#include <vector>
#include <type_traits>

namespace CX
{
    namespace Chimera
    {
        class Object
        {
        public:
            using Type = String;
            
            virtual ~Object() {}
            virtual Type GetType() const = 0;
            virtual String ToString() const = 0;
            virtual bool Equals(const Object&) const = 0;
            
            template<class DerivedObject>
            DerivedObject* Convert() { return dynamic_cast<DerivedObject*>(this); }
        };
        
        namespace Internal
        {
            template<class T>
            class ObjectImpl : public Object
            {
                Type GetType() const { return typeid(T).name(); }
                String ToString() const { return GetType(); }
                bool Equals(const Object& obj) const { return this->GetType() == obj.GetType(); }
            };
        }
    }
}


// Macros to create CX-capable classes

#define cxclass(RealType) \
class RealType : public CX::Chimera::Internal::ObjectImpl<RealType>, public CX::Stats::Tracker<RealType>

#define cxclass_templated(RealType, ...) \
class CXGen_ObjectImpl_##RealType : public CX::Chimera::Object { \
public: \
CX::Chimera::Object::Type GetType() const { return CXSTRINGIFY(RealType); } \
CX::String ToString() const { return CXSTRINGIFY(RealType); } \
bool Equals(const CX::Chimera::Object& obj) const { return this->GetType() == obj.GetType(); } \
}; \
__VA_ARGS__ class RealType : public CXGen_ObjectImpl_##RealType

#define extends(...) , __VA_ARGS__
#define implements extends

#define as(class) .Convert<class>()

typedef CX::Chimera::Object& cxobject;

#endif /* Object_h */
