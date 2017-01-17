#include <Windows.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NUM_ARGVS 50

int argc = 1;
char *largv[MAX_NUM_ARGVS];

boolean IsPrintable(char character);
boolean ArgumentsHasRoom(int numberOfArguments);
int COM_CheckParm(char *parm);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	largv[0] = "";

	while (*lpCmdLine && ArgumentsHasRoom(argc))
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

	largv[argc] = "";
	return 0;
}

boolean ArgumentsHasRoom(int numberOfArguments)
{
	return (numberOfArguments < MAX_NUM_ARGVS);
}

boolean IsPrintable(char character)
{
	return ((character >= 33) && (character <= 126));
}

int COM_CheckParm(char *parm)
{
	for (int i = 1; i < argc; i++)
	{
		if (!strcmp(parm, largv[i]))
		{
			return i;
		}
	}
	return 0;
}