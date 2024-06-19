#include "GameEngine.h"

int main() {
	GameEngine g("assets.txt", "config.txt");
	g.run();

	return 0;
}