//
//  String.h
//  cxxreflect
//
//  Created by Nikita Ivanov on 3/14/20.
//  Copyright © 2020 Plak Corp. All rights reserved.
//

#ifndef String_h
#define String_h
#include <string>

#define CXSTRINGIFY(x) #x
namespace CX
{
    typedef std::string String;
}
typedef CX::String cxstring;

#endif /* String_h */
