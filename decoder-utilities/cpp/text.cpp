#include "text.h"

#include <string>

#include "trim_funcs.h"

namespace Decoder {
	namespace Utilities {

		const char ascii_space = ' ';
		const wchar_t unicode_spaces[] =
			{ ascii_space // SPACE
			, '\u00a0'    // NO-BREAK SPACE           
			, '\u1680'    // OGHAM SPACE MARK         
			, '\u2000'    // EN QUAD                  
			, '\u2001'    // EM QUAD                  
			, '\u2002'    // EN SPACE                 
			, '\u2003'    // EM SPACE                 
			, '\u2004'    // THREE-PER-EM SPACE       
			, '\u2005'    // FOUR-PER-EM SPACE        
			, '\u2006'    // SIX-PER-EM SPACE         
			, '\u2007'    // FIGURE SPACE             
			, '\u2008'    // PUNCTUATION SPACE        
			, '\u2009'    // THIN SPACE               
			, '\u200a'    // HAIR SPACE               
			, '\u202f'    // NARROW NO-BREAK SPACE    
			, '\u205f'    // MEDIUM MATHEMATICAL SPACE
			, '\u3000'    // IDEOGRAPHIC SPACE        
		};


		std::tuple<const char*, size_t> trim_front(const char * str, size_t length, const char spcs[], size_t spcc)
		{
			while (length > 0 && isspace(*str))
			{
				++str;
				--length;
			}

			return std::make_tuple(str, length);
		}
		std::tuple<const char*, size_t> trim_back(const char * str, size_t length, const char spcs[], size_t spcc)
		{
			const char * back = str + length - 1;
			while (length > 0 && isspace(*back))
			{
				--back;
				--length;
			}

			return std::make_tuple(str, length);
		}

	}
}
