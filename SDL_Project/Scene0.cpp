#include "Scene0.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Randomizer.h"
#include <iostream>

Scene0::Scene0(SDL_Window* sdlWindow_){
	Randomizer r;
	window = sdlWindow_;
	
	
	for(int i = 0; i < NUM_BALLS; ++i){
		
		ballArray[i] = new Body(Vec3(r.rand(0.0f, 26.0f), r.rand(0.0f, 15.0f),0.0f),
							    Vec3(r.rand(1.0f, 10.f), 0.0f, 0.0f), 
								Vec3(0.0f, -9.8f, 0.0f), 1.0f);
	}
}

Scene0::~Scene0(){
	for(int i = 0; i < NUM_BALLS; ++i){
		delete ballArray[i];
	}
}

bool Scene0::OnCreate() {
	int w, h;
	float xAxis = 30.0f;
	float yAxis = 15.0f;
	SDL_GetWindowSize(window,&w,&h);
	
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	
	IMG_Init(IMG_INIT_PNG);
	SDL_Surface* ballImage = IMG_Load("ball.png");
	if(ballImage == nullptr){
		std::cerr << "Can't open the image" << std::endl;
		return false;
	} else {
		
		Vec3 worldCoordsFromScreenCoords;
		worldCoordsFromScreenCoords.x = xAxis / static_cast<float>(w) * static_cast<float>(ballImage->w);
		worldCoordsFromScreenCoords.y = yAxis / static_cast<float>(h) * static_cast<float>(ballImage->h);
		worldCoordsFromScreenCoords.z = 0.0f;

		for(int i = 0; i < NUM_BALLS; i++){
			ballArray[i]->setImage(ballImage);
			ballArray[i]->setImageSizeWorldCoords(worldCoordsFromScreenCoords);
		}
		
	}
	return true;
}

void Scene0::OnDestroy() {}

void Scene0::Update(const float deltaTime) {
	for(int i = 0; i < NUM_BALLS; i = i + 1){
		ballArray[i]->Update(deltaTime);
	}
}


void Scene0::HandleEvents(const SDL_Event& sdlEvent){
	for(int i = 0; i< NUM_BALLS; i++){
		ballArray[i]->HandleEvents(sdlEvent);
	}
}


void Scene0::Render() {
	SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0, 0, 0));
	SDL_Rect square;
	Vec3 screenCoords;

	for(int i = 0; i < NUM_BALLS; ++i){
		screenCoords = projectionMatrix * ballArray[i]->getPos();
		square.x = static_cast<int>(screenCoords.x);
		square.y = static_cast<int>(screenCoords.y);
		square.w = ballArray[i]->getImage()->w;
		square.h = ballArray[i]->getImage()->h;
		SDL_BlitSurface(ballArray[i]->getImage(),nullptr,screenSurface,&square);
	}
	SDL_UpdateWindowSurface(window);
}