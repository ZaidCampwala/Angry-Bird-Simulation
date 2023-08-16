#include "Scene1.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Body.h"
#include "Randomizer.h"
#include "Body.h"
#include "VMath.h"
#include "Timer.h"
Body* Flappy;
Body* Branch;

Scene1::Scene1(SDL_Window* sdlWindow_){
	window = sdlWindow_;
	
	Flappy = new Body(Vec3(2.0f, 5.0f, 0.0f),
		Vec3(30.0f * cos(27 * DEGREES_TO_RADIANS), 30.0f * sin(27 * DEGREES_TO_RADIANS), 0.0f),
		Vec3(0.0f, -9.80f, 0.0f),
		2.0f);


	Branch = new Body(Vec3(0.0f, 0.0f, 0.0f),
		Vec3(0.0f, 0.0f, 0.0f),
		Vec3(0.0f, 0.0f, 0.0f),
		2.0f);
		
}

Scene1::~Scene1(){
	delete Flappy;
	delete Branch;
}

bool Scene1::OnCreate() {
	int w, h;
	float xAxis = 30.0f;
	float yAxis = 15.0f;
	SDL_GetWindowSize(window,&w,&h);
	
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	


	IMG_Init(IMG_INIT_PNG);
	SDL_Surface* birdImage = IMG_Load("Bird.png");
	if (birdImage == nullptr) {
		std::cerr << "Image not found" << std::endl;
		return false;
	}

	IMG_Init(IMG_INIT_PNG);
	SDL_Surface* branchImage = IMG_Load("Branch.png");
	if (branchImage == nullptr) {
		std::cerr << "Image not found" << std::endl;
		return false;
	}

	Vec3 worldCoordsFromScreenCoords;
	
	worldCoordsFromScreenCoords.x = xAxis /
		static_cast<float>(w) * static_cast<float>(birdImage->w);
	worldCoordsFromScreenCoords.y = yAxis /
		static_cast<float>(h) * static_cast<float>(birdImage->h);
	worldCoordsFromScreenCoords.z = 0.0f;

	Flappy->setImage(birdImage);
	Flappy->setImageSizeWorldCoords(worldCoordsFromScreenCoords);


	worldCoordsFromScreenCoords.x = xAxis /
		static_cast<float>(w) * static_cast<float>(branchImage->w);
	worldCoordsFromScreenCoords.y = yAxis /
		static_cast<float>(h) * static_cast<float>(branchImage->h);
	worldCoordsFromScreenCoords.z = 0.0f;


	Branch->setImage(branchImage);
	Branch->setImageSizeWorldCoords(worldCoordsFromScreenCoords);

	

	return true;
}

void Scene1::OnDestroy() {}

void Scene1::Update(const float deltaTime) {

	Flappy->Windforce(Vec3(-30.0f, 0.0f, 0.0f));
	Flappy->DragForce(Vec3(0.2f, 0.0f, 0.0f));
	Flappy->Update(deltaTime);
}
void Scene1::HandleEvents(const SDL_Event& sdlEvent) {
	
}

void Scene1::Render() {
	Vec3 screenCoords;
	SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0, 0, 0));

	SDL_Rect square;

	
	screenCoords = projectionMatrix * Flappy->getPos();
	square.x = static_cast<int>(screenCoords.x);
	square.y = static_cast<int>(screenCoords.y);
	square.w = Flappy->getImage()->w;
	square.h = Flappy->getImage()->h;
	SDL_BlitSurface(Flappy->getImage(), nullptr, screenSurface, &square);


	SDL_Rect squareForBranch;
	screenCoords = projectionMatrix * Branch->getPos();
	squareForBranch.x = 20; // just a random number to make bird and branch closer.
	squareForBranch.y = static_cast<int>(screenCoords.y - Branch->getImage()->h);

	squareForBranch.w = Branch->getImage()->w;
	squareForBranch.h = Branch->getImage()->h;
	
	SDL_BlitSurface(Branch->getImage(), nullptr, screenSurface, &squareForBranch);


	
	SDL_UpdateWindowSurface(window);
}