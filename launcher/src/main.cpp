#include "AppWindow.h"

int main(void)
{
	AppWindow app;

	if (app.init()) {
		while (app.isRun()) {
			app.broadcast();
		}
	}
	return (0);
}