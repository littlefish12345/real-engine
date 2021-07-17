#include <real-engine/real-engine.hpp>

int main() {
	realEngineInit(800, 600, "test window");
	realEngineLoop();
	return 0;
}