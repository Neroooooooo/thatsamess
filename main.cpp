#include "Application.h"

int main()
{
	Application::getInstance()->Run();
	Application::close();

	return 0;
}