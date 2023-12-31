#ifndef BODY_H
#define BODY_H

#include "Vector.h"
#include <SDL_image.h>
using namespace MATH;

class Body {
private:
	Vec3 pos;
	Vec3 vel;
	Vec3 accel;
	float mass;
	Vec3 c;
	Vec3 WF;
	
	SDL_Surface* image;
	Vec3 imageSizeWorldCoords;

public:
	Body();
	Body(Vec3 pos_, Vec3 vel_, Vec3 accel_, float mass_);

	~Body();
	void Update(float deltaTime);
	void ApplyForce(Vec3 force_);
	void DragForce(Vec3 Dforce_);
	void Windforce(Vec3 Windforce);
	void HandleEvents(const SDL_Event& sdlEvent);

	Vec3 getPos() { return pos; }
	void setImage(SDL_Surface* image_) { image = image_; }
	SDL_Surface* getImage() { return image; }
	void setImageSizeWorldCoords(Vec3 imageSizeWorldCoords_) { 
		imageSizeWorldCoords.x = imageSizeWorldCoords_.x;
		imageSizeWorldCoords.y = imageSizeWorldCoords_.y;
		imageSizeWorldCoords.z = imageSizeWorldCoords_.z;
	}
	Vec3 getImageSizeWorldCoords(){ return  imageSizeWorldCoords; }
};

#endif
