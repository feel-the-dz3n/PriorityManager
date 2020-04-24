#pragma once
#include <string>
#include <typeinfo>
#include <type_traits>
#include <vector>
#include <stdexcept>

#define STRINGIFY(x) #x
#define __TPaste(a, b) a ## b
#define _TPaste(a, b) __TPaste(a, b)
#define _GenCXPName(name, line) _TPaste(_CXPropActivator_, line)
#define cxprop(name) name; private: CX::Reflection::Property<decltype(name)> _GenCXPName(name, __LINE__) = CX::Reflection::Property<decltype(name)>(*this, &name, STRINGIFY(name)); public:

namespace CX
{
	namespace Reflection
	{
		class Reflected;

		struct IPropValue
		{
			virtual ~IPropValue() {};

			virtual std::string Name() = 0;
			virtual std::string Type() = 0;
			virtual void* Data() = 0;
			virtual size_t Size() = 0;
		};
		class PVAccessor
		{
		public:
			PVAccessor(IPropValue* pValue) : mpIValue(pValue) {}

			operator bool() { return mpIValue != nullptr; }

			std::string name() {
				if (mpIValue) return mpIValue->Name();
				else throw std::runtime_error("Trying to access name() of a null PVAccessor");
			}
			std::string type() {
				if (mpIValue) return mpIValue->Type();
				else throw std::runtime_error("Trying to access type() of a null PVAccessor");
			}
			void* data() {
				if (mpIValue) return mpIValue->Data();
				else throw std::runtime_error("Trying to access data() of a null PVAccessor");
			}
			size_t size() {
				if (mpIValue) return mpIValue->Size();
				else throw std::runtime_error("Trying to access size() of a null PVAccessor");
			}

			template<typename T>
			T& operator=(const T& val) {
				static T defval;
				if (is<T>())
					return as<T>() = val;
			}

			template<typename T>
			bool is() {
				return type() == typeid(T).name();
			}

			template<typename T>
			T& as() {
				return *(T*)data();
			}
		private:
			IPropValue* mpIValue;
		};

		class Reflected
		{
		public:
			Reflected() {}
			Reflected(const Reflected&) {}

			PVAccessor operator[](const std::string& name)
			{
				for (auto& pProp : mProps)
					if (pProp->Name() == name)
						return PVAccessor(pProp);

				return PVAccessor(nullptr);
			}

			std::vector<PVAccessor> properties()
			{
				std::vector<PVAccessor> result;
				for (auto& pProp : mProps)
					result.push_back(PVAccessor(pProp));

				return result;
			}
		private:
			void OnPropConstruct(IPropValue* pProp)
			{
				mProps.push_back(pProp);
			}
			std::vector<IPropValue*> mProps;

			template<typename T>
			friend class Property;
		};

		template<typename T>
		class Property : public IPropValue
		{
		public:
			Property(Reflected& owner, T* pData, const std::string& name)
			{
				mpData = pData;
				mName = name;
				owner.OnPropConstruct(this);
			}

			std::string Name()
			{
				return mName;
			}
			std::string Type()
			{
				return typeid(*mpData).name();
			}
			void* Data()
			{
				return mpData;
			}
			size_t Size()
			{
				return sizeof(T);
			}
		private:
			T* mpData;
			std::string mName;
		};
	}
}