
#include <Windows.h>
#include <string>
#include <random>
#include <iostream>

#define TEST_SCALE 1'000'000'000
#ifdef _DEBUG
#define TEST_SCALE 100000
#endif

//const char* s = "abcdefghijk";
char s[TEST_SCALE + 8] = { 0 };
char szOut[65536];

const char ccmap[200] = {
	'0','0','0','1','0','2','0','3','0','4','0','5','0','6','0','7','0','8','0','9',
	'1','0','1','1','1','2','1','3','1','4','1','5','1','6','1','7','1','8','1','9',
	'2','0','2','1','2','2','2','3','2','4','2','5','2','6','2','7','2','8','2','9',
	'3','0','3','1','3','2','3','3','3','4','3','5','3','6','3','7','3','8','3','9',
	'4','0','4','1','4','2','4','3','4','4','4','5','4','6','4','7','4','8','4','9',
	'5','0','5','1','5','2','5','3','5','4','5','5','5','6','5','7','5','8','5','9',
	'6','0','6','1','6','2','6','3','6','4','6','5','6','6','6','7','6','8','6','9',
	'7','0','7','1','7','2','7','3','7','4','7','5','7','6','7','7','7','8','7','9',
	'8','0','8','1','8','2','8','3','8','4','8','5','8','6','8','7','8','8','8','9',
	'9','0','9','1','9','2','9','3','9','4','9','5','9','6','9','7','9','8','9','9'
};

int main()
{
	std::mt19937_64 gen(GetTickCount());
	std::uniform_int_distribution<> rnd('a', 'z');

	//memset(s, 0, TEST_SCALE + 1);
	for (int i = 0; i<TEST_SCALE; i++)
	{
		s[i] = rnd(gen);
	}
	//*reinterpret_cast<unsigned long long*>(&s[TEST_SCALE]) = 0;

	LARGE_INTEGER tStart, tEnd;
	QueryPerformanceCounter(&tStart);

	char szTemp[20];
	szTemp[1] = ' ';
	int nIndex = 0;

	int c[128] = { 0 };
#if 0
	while (*s)
		c[*s++]++;
#elif 0
	int cc[0x7a7a] = { 0 };
	unsigned short *ss = reinterpret_cast<unsigned short*>(s);
	while (*ss != 0)
		cc[*ss++]++;
	for (char i = 'a'; i <= 'z'; i++)
	{
		for (char j = 'a'; j <= 'z'; j++)
		{
			auto x = cc[(i << 8) + j];
			c[i] += x;
			c[j] += x;
		}
		c[i] += cc[i];
	}
#elif 0
	unsigned long *ss = reinterpret_cast<decltype(ss)>(s);
	while (auto x = *ss++)
	{
		for (int i = 0; i < 4; ++i)
		{
			c[x & 0xff]++;
			x >>= 8;
		}
	}
#else
	int cc[0x7a7b] = { 0 };
	unsigned long long *ss = reinterpret_cast<decltype(ss)>(s);
	while (auto x = *ss++)
	{
		for (int i = 0; i < 4; ++i)
		{
			cc[x & 0xffff]++;
			x >>= 16;
		}
	}
	for (char i = 'a'; i <= 'z'; i++)
	{
		for (char j = 'a'; j <= 'z'; j++)
		{
			auto x = cc[(i << 8) + j];
			c[i] += x;
			c[j] += x;
		}
		c[i] += cc[i];
	}
#endif


#if 0
	for (char i = 'a'; i <= 'z'; i++)
	{
		//szTemp[0] = i;
		//_itoa_s(c[i], szTemp + 2, sizeof(szTemp) - 4, 10);
		//int nLen = strlen(szTemp);
		//szTemp[nLen++] = '\n';

		int nLen = _snprintf_s(szTemp, sizeof(szTemp), "%c %d\n", i, c[i]);
		memcpy(szOut + nIndex, szTemp, nLen);
		nIndex += nLen;
	}
	szOut[nIndex] = 0;

	printf(szOut);
#elif 0
	char *p = szOut + sizeof(szOut);
	*--p = 0;
	for (char i = 'z'; i >= 'a'; --i)
	{
		*--p = '\n';
		auto x = c[i];
		do
		{
			p -= 2;
			*reinterpret_cast<short*>(p) = *reinterpret_cast<const short*>(&ccmap[x % 100 * 2]);
			x /= 100;
		} while (x);
		if (*p == '0') ++p;

		*--p = ' ';
		*--p = i;
	}

	printf(p);
#else
	unsigned long long * p = reinterpret_cast<decltype(p)>(szOut);
	for (char i = 'a'; i <= 'z'; ++i)
	{
		auto x = c[i];
		unsigned long long y;
		size_t j = 8;
		while (x && j--)
		{
			y = (y << 8) | '0' | (x % 10);
			x /= 10;
		}
		while (j)
		{
			y = (y << 8) | ' ';
			--j;
		}
		*(p + 1) = y;
		j = 8;
		while (x && j--)
		{
			y = (y << 8) | '0' | (x % 10);
			x /= 10;
		}
		while (j > 1)
		{
			y = (y << 8) | ' ';
			--j;
		}
		y = (y << 8) | i;
		*p = y;
		p += 2;
	}
	*p = 0;
	printf(szOut);
#endif

	QueryPerformanceCounter(&tEnd);

	printf("Ticks costed: %ull\n", tEnd.QuadPart - tStart.QuadPart);
	
	LARGE_INTEGER tFeq;
	QueryPerformanceFrequency(&tFeq);
	printf("time spent: %g\n", (double)(tEnd.QuadPart - tStart.QuadPart) / (double)tFeq.QuadPart);

	return 0;
}

