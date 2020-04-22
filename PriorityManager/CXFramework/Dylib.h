#pragma once
#include <string>
#include <functional>
#include <exception>

#if defined(_WIN32)
#define CXDL_WINDOWS
#include <Windows.h>
#endif

#if defined(__unix__) || defined(__unix) || \
        (defined(__APPLE__) && defined(__MACH__))
#define CXDL_UNIX
#include <dlfcn.h>
#endif

namespace CX
{
	namespace Dylib
	{
#ifdef CXDL_WINDOWS
		typedef HMODULE Handle;

		// Windows library loader
		class Win32Library
		{
		public:
			Win32Library(const std::string& name) {
				mHandle = LoadLibraryA(name.c_str());
			}
			void UnloadLibrary() {
				FreeLibrary(mHandle);
			}
			void* GetSymbol(const std::string& symbol) const {
				return GetProcAddress(mHandle, symbol.c_str());
			}
		private:
			Handle mHandle;
		};
		using LibraryImpl = Win32Library;
#endif

#ifdef CXDL_UNIX
		typedef void* Handle;

		// Unix(-like) library loader
		class UnixLibrary
		{
		public:
			UnixLibrary(const std::string& name) {
				mHandle = dlopen(name.c_str(), RTLD_NOW);
			}
			void UnloadLibrary() {
				dlclose(mHandle);
			}
			void* GetSymbol(const std::string& symbol) const {
				return dlsym(mHandle, symbol.c_str());
			}
		private:
			Handle mHandle;
		};
		using LibraryImpl = UnixLibrary;
#endif

		class DeadLibraryException : public std::exception
		{
		public:
			DeadLibraryException(const std::string& libname)
			{
				mDescription = "DeadLibraryException: Library '" + libname + "' was accessed after being unloaded.";
			}
			const char* what() const {
				return mDescription.c_str();
			}
		private:
			std::string mDescription;
		};
		class InvalidSymbolException : public std::exception
		{
		public:
			InvalidSymbolException(const std::string& symname, const std::string& libname)
			{
				mDescription = "InvalidSymbolException: Symbol '" + symname + "' in library '" + libname + "' does not exist.";
			}
			const char* what() const {
				return mDescription.c_str();
			}
		private:
			std::string mDescription;
		};

		enum class LibraryBehavior
		{
			UnloadManually,
			UnloadOnDestruct
		};

		class Library : public LibraryImpl
		{
		public:
			Library() = delete;
			Library(const std::string& name, const LibraryBehavior behavior = LibraryBehavior::UnloadManually)
				: LibraryImpl(name), mLibraryName(name), mBehavior(behavior), mValid(true) {}
			~Library() {
				if (mBehavior == LibraryBehavior::UnloadOnDestruct)
					UnloadLibrary();
			}

			void Unload() { UnloadLibrary(); mValid = false; }

			template<typename ReturnType>
			using Function = ReturnType(*)(...);

			// Calling arbitrary functions
			template<typename ReturnType>
			Function<ReturnType> GetFunction(const std::string& symname) {
				if (!mValid)
					throw DeadLibraryException(mLibraryName);

				auto fcn = (Function<ReturnType>) GetSymbol(symname);
				if (!fcn)
					throw InvalidSymbolException(symname, mLibraryName);
				return fcn;
			}

			// Getting globals
			template<typename GlobalType>
			GlobalType& GetGlobal(const std::string& symname) {
				if (!mValid)
					throw DeadLibraryException(mLibraryName);

				const auto pSym = (GlobalType*)GetSymbol(symname);
				if (!pSym)
					throw InvalidSymbolException(symname, mLibraryName);
				return *pSym;
			}

			// Getting globals (const overload)
			template<typename GlobalType>
			const GlobalType& GetGlobal(const std::string& symname) const {
				if (!mValid)
					throw DeadLibraryException(mLibraryName);

				const auto pSym = (GlobalType*)GetSymbol(symname);
				if (!pSym)
					throw InvalidSymbolException(symname, mLibraryName);
				return *pSym;
			}
		private:
			std::string mLibraryName;
			LibraryBehavior mBehavior;
			bool mValid;
		};
	}
}

#undef CXDL_WINDOWS
#undef CXDL_UNIX