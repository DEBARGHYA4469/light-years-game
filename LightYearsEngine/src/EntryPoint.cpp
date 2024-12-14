#include "EntryPoint.h"
#include "framework/Application.h"

int main() {
	ly::Application* app = getApplication();
	app->run();
	delete app;
}