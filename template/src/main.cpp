#include <real-engine/real-engine.hpp>

void newFrameCallback() {
	//nowCamera->moveBackward(0.01f);
}

float movementSpeed = 5.0f;
float mouseSensitivity = 0.05f;

void pressW() {
	printf("w\n");
	nowCamera->moveForward(getDeltaTime() * movementSpeed);
}

void pressA() {
	printf("a\n");
	nowCamera->moveLeft(getDeltaTime() * movementSpeed);
}

void pressS() {
	printf("s\n");
	nowCamera->moveBackward(getDeltaTime() * movementSpeed);
}

void pressD() {
	printf("d\n");
	nowCamera->moveRight(getDeltaTime() * movementSpeed);
}

void pressSpace() {
	printf("space\n");
	nowCamera->moveUp(getDeltaTime() * movementSpeed);
}

void pressShift() {
	printf("shift\n");
	nowCamera->moveDown(getDeltaTime() * movementSpeed);
}

void pressESC() {
	printf("esc\n");
	realEngineClose();
}

void moveMouse(float xOffset, float yOffset) {
	nowCamera->rotateYaw(xOffset * mouseSensitivity);
	if(nowCamera->pitch + yOffset * mouseSensitivity > 89.9f)
		nowCamera->pitch = 89.9f;
	else if(nowCamera->pitch + yOffset * mouseSensitivity < -89.9f)
		nowCamera->pitch = -89.9f;
	else
		nowCamera->rotatePitch(yOffset * mouseSensitivity);
}

int main() {
	realEngineInit(1280, 720, "test window");
	registKey(GLFW_KEY_W, GLFW_PRESS, &pressW);
	registKey(GLFW_KEY_A, GLFW_PRESS, &pressA);
	registKey(GLFW_KEY_S, GLFW_PRESS, &pressS);
	registKey(GLFW_KEY_D, GLFW_PRESS, &pressD);
	registKey(GLFW_KEY_SPACE, GLFW_PRESS, &pressSpace);
	registKey(GLFW_KEY_LEFT_SHIFT, GLFW_PRESS, &pressShift);
	registKey(GLFW_KEY_RIGHT_SHIFT, GLFW_PRESS, &pressShift);
	registKey(GLFW_KEY_ESCAPE, GLFW_PRESS, &pressESC);
	disableMouse();
	registMouseCallback(moveMouse);
	Camera camera = Camera();
	camera.setPosition(0.0f, 0.0f, 3.0f);
	camera.rotateYaw(-90.0f);
	nowCamera = &camera;
	Shader shader = Shader("vertexShader.glsl", "fragmentShader.glsl");
	nowShader = &shader;
	Model tempModel = Model("nanosuit", "nanosuit.obj");
	tempModel.setPosition(0.0f, 0.0f, 0.0f);
	tempModel.setScale(1.0f, 1.0f, 1.0f);
	model = &tempModel;
	realEngineLoop();
	return 0;
}