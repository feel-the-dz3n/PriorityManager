//
//  Methods.h
//  cxxreflect
//
//  Created by Nikita Ivanov on 3/15/20.
//  Copyright © 2020 Plak Corp. All rights reserved.
//

#ifndef Methods_h
#define Methods_h
#include "String.h"

namespace CX
{
    namespace Reflection
    {
        template<class Base, typename ReturnType>
        struct BoundMethod
        {
        public:
            typedef ReturnType(__cdecl *MethodFunc_t)(Base* pThis, ...);
            BoundMethod(void* addr) : Invoke((MethodFunc_t) addr) {}
            const MethodFunc_t Invoke;
        };
        class ClassMethod
        {
        public:
            ClassMethod(const CX::String& name, void* fcn) : Name(name), mFunction(fcn) {}
            
            template<class Base, typename ReturnType>
            BoundMethod<Base, ReturnType> As()
            {
                return BoundMethod<Base, ReturnType>(mFunction);
            }
            
            CX::String Name;
        private:
            void* mFunction;
        };
        
    }
}

#define cxmethods(T) void SetupMethodList() { using Type = T; mCXMethods = {
#define cxmethods_end }; }
#define method(name) CX::Reflection::ClassMethod(CXSTRINGIFY(name), *(void**) &&Type::name)

#endif /* Methods_h */
