#include "reflection_register.h"
#include "reflection.h"
#include "runtime/core/meta/serializer/serializer.h"
#include "runtime/core/meta/json.h"
#include "_generated/reflection/all_reflection.h"
#include "_generated/serializer/all_serializer.ipp"

namespace SimpleEngine {
	namespace Reflection {
		void TypeMetaRegister::metaUnregister() { TypeMetaRegisterinterface::unregisterAll(); }
	}
}