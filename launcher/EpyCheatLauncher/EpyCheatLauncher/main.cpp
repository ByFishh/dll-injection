#include "required.h"

int main(void)
{
	std::unique_ptr<Window> win;

	win = std::make_unique<Window>(1589, 868);
	win->coreLoop();
	return (0);
}