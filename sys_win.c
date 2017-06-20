#include <Windows.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

typedef uint8_t uint8;
typedef int32_t int32;
typedef uint32_t uint32;

#define MAX_NUM_ARGVS 50

int32 argc = 1;
uint8 *largv[MAX_NUM_ARGVS + 1];

boolean IsPrintable(uint8 character);
boolean ArgumentsHasRoom();
boolean IsADigit(uint8 character);
int32 COM_CheckParm(uint8 *parm);
int32 Q_strcmp();
int32 Q_atoi(uint8 *str);

int32 CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int32 nCmdShow)
{
	largv[0] = "";

	while (*lpCmdLine && ArgumentsHasRoom())
	{
		while (*lpCmdLine && !IsPrintable(*lpCmdLine))
		{
			lpCmdLine++;
		}

		if (*lpCmdLine)
		{
			largv[argc] = lpCmdLine;
			argc++;
		}

		while (*lpCmdLine && IsPrintable(*lpCmdLine))
		{
			lpCmdLine++;
		}

		if (*lpCmdLine)
		{
			*lpCmdLine = 0;
			lpCmdLine++;
		}
	}
	
	int32 test = COM_CheckParm("-setalpha");
	int32 value = Q_atoi(largv[test + 1]);
	return 0;
}

boolean ArgumentsHasRoom()
{
	return (argc < (MAX_NUM_ARGVS + 1));
}

boolean IsPrintable(uint8 character)
{
	return ((character >= 33) && (character <= 126));
}

int32 COM_CheckParm(uint8 *parm)
{
	for (int32 i = 1; i < argc; i++)
	{
		if (!Q_strcmp(parm, largv[i]))
		{
			return i;
		}
	}
	return 0;
}

int32 Q_strcmp(uint8 *s1, uint8 *s2)
{
	while (*s1 == *s2)
	{
		if (!*s1)
		{
			return 0;
		}
		++s1;
		++s2;
	}
	
	return (*s1 < *s2) ? -1 : 1;
}

int32 Q_atoi(uint8 *str)
{
	int32 sign = 1;
	int32 val = 0;
	uint8 character;

	if (*str == '-')
	{
		sign = -1;
		str++;
	}

	// hexadecimal
	if (*str == '0' && (
		str[1] == 'x' || str[1] == 'X')
		)
	{
		str += 2;
		while (true)
		{
			character = *str;
			str++;
			if (IsADigit(character))
			{
				val = val * 16 + (character - '0');
			}
			else if (character >= 'a' && character <= 'f')
			{
				val = val * 16 + (character - 'a' + 10);
			}
			else if (character >= 'A' && character <= 'F')
			{
				val = val * 16 + (character - 'a' + 10);
			}
			else
			{
				return val * sign;
			}
		}
	}

	// decimal
	while (true)
	{
		character = *str;
		str++;
		if (!IsADigit(character))
		{
			return sign * val;
		}
		val = val * 10 + (character - '0');
	}
}

boolean IsADigit(uint8 character)
{
	return (character >= '0' && character <= '9');
}