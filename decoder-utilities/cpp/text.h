#pragma once

#include <tuple>
#include <type_traits>
#include "trim_funcs.h"

namespace Decoder {
	namespace Utilities {

#pragma pack (push, 1)
		template<class F, class T, size_t size, class SF = is_space_func<T>,
			class = std::enable_if_t<
				std::is_same<T, char>::value ||
				std::is_same<T, wchar_t>::value
			>
		>
		class PaddedFixStr
		{
			T raw_buffer[size];
		};
#pragma pack (pop)
	}
}
