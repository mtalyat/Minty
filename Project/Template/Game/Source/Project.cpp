#include <Minty.h>

using namespace Minty;

int main(int const argc, char const* const argv[])
{
	// create the context from the minty file
	Unique<Application> app = Application::open("game.minty");

	// run the application
	app->run();

	return 0;
}