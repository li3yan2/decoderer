#pragma once

#include <tuple>
#include <type_traits>

namespace Decoder {
	namespace Utilities {

		template<class T>
		struct check_space
		{
		};

		template<>
		struct check_space<char>
		{
			bool operator()(char c) { return isspace(c) != 0; }
		};

		template<>
		struct check_space<wchar_t>
		{
			bool operator()(char c) { return iswspace(c) != 0; }
		};

		template<class T, class F,
			class = std::enable_if_t<
				(std::is_same<T, char>::value ||
				std::is_same<T, wchar_t>::value) &&
			std::is_same<bool, decltype(F{}())> ::value
			>
		>
		struct trim_left
		{
			std::tuple<const T *, size_t> operator()(const T* str, size_t length, F f)
			{
				while (length > 0 && f(*str))
				{
					++str;
					--length;
				}

				return std::make_tuple(str, length);
			}
		};

		template<class T, class F,
			class = std::enable_if_t<
			(std::is_same<T, char>::value ||
				std::is_same<T, wchar_t>::value) &&
			std::is_same<bool, decltype(F{}())>::value
			>
		>
		struct trim_right
		{
			std::tuple<const T *, size_t> operator()(const T* str, size_t length, F f)
			{
				const T * back = str + length - 1;
				while (length > 0 && f(*back))
				{
					--back;
					--length;
				}

				return std::make_tuple(str, length);
			}
		};

	}
}
