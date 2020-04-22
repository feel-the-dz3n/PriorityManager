//
//  Query.h
//  cxxreflect
//
//  Created by Nikita Ivanov on 3/16/20.
//  Copyright © 2020 Plak Corp. All rights reserved.
//

#ifndef Query_h
#define Query_h
#include "Object.h"
#include <vector>
#include <functional>

namespace CX
{
    namespace Queries
    {
        template<typename T>
        const std::vector<T> QueryCollection(const std::vector<T>& collection, const std::function<bool(const T&)> compare)
        {
            std::vector<T> result;
            for(auto& elem : collection)
            {
                if(compare(elem))
                    result.push_back(elem);
            }
            return result;
        }
    }
}

#define cxquery(elemName, container, condition) CX::Queries::QueryCollection<decltype(container)::value_type>(container, [](const decltype(container)::value_type& elemName) { return (condition); })

#define from(name, container) CX::Queries::QueryCollection<decltype(container)::value_type>(container, [](const decltype(container)::value_type& name) { return
#define where(condition) (condition); })

#endif /* Query_h */
