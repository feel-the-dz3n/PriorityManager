//
//  Stats.h
//  cxxreflect
//
//  Created by Nikita Ivanov on 3/14/20.
//  Copyright © 2020 Plak Corp. All rights reserved.
//

#ifndef Stats_h
#define Stats_h
#include "utils/debugbreak.h"

namespace CX
{
    namespace Stats
    {
        template<typename Base>
        class Tracker
        {
        private:
            static int sCreated, sActive;
            static bool sBreakOnCreation;
            static bool sBreakOnDestruction;
            
            static void InvokeBreakpoint()
            {
                debug_break();
            }
            static void OnCreate()
            {
                sCreated++; sActive++;
                if(sBreakOnCreation)
                    InvokeBreakpoint();
            }
            static void OnDestruct()
            {
                sActive--;
                if(sBreakOnDestruction)
                    InvokeBreakpoint();
            }
        public:
            Tracker() { OnCreate(); };
            Tracker(const Tracker&) { OnCreate(); };
            
            static int CXNumCreated() { return sCreated; }
            static int CXNumActive() { return sActive; }
            static int CXMemoryUsage() { return sActive * sizeof(Base); }
            
            static void CXBreakOnCreate() { sBreakOnCreation = true; }
            static void CXBreakOnDestruction() { sBreakOnDestruction = true; }
            
        protected:
            ~Tracker() { OnDestruct(); }
        };
        template <typename Base> int Tracker<Base>::sCreated (0);
        template <typename Base> int Tracker<Base>::sActive (0);
        
        template <typename Base> bool Tracker<Base>::sBreakOnCreation (false);
        template <typename Base> bool Tracker<Base>::sBreakOnDestruction (false);
    }
}

#endif /* Stats_h */
