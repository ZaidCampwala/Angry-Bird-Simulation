#include "Body.h"

Body::Body(){
	pos.x = 2;
	pos.y =5; /// meters
	pos.z = 0.0f;


	vel.x = 30 * sin(27);
	vel.y = 0; /// meters/sec
	vel.z = 0.0f;

	accel.x = 0.0f;
	accel.y = -9.80f; /// meters/sec/sec
	accel.z = 0.0f;

	c.x = 0.2f;////Drage force 
	WF.x = -30;////Windforce   /// Newtons

	mass = 2.0f; /// kg


	image = nullptr;
}

Body::Body(Vec3 pos_, Vec3 vel_, Vec3 accel_, float mass_){
	pos.x = pos_.x;
	pos.y = pos_.y;
	pos.z = pos_.z;
	vel = vel_;
	accel = accel_;
	mass = mass_;
}

Body::~Body(){

}

void Body::ApplyForce(Vec3 force_) {
	accel.x = force_.x / mass;
	accel.y = force_.y / mass;
	accel.z = force_.z / mass;
}

void Body::DragForce(Vec3 Dforce_) {
	c.x = -Dforce_.x * vel.x;
	c.y = -Dforce_.y * vel.y;
	c.z = -Dforce_.z * vel.z;
}

void Body::Windforce(Vec3 Windforce) {
	WF.x = vel.x - Windforce.x ;
	WF.y = vel.y - Windforce.y;
	WF.z = vel.z - Windforce.z;
}
void Body::Update(float deltaTime){
	pos.x += vel.x * deltaTime + 0.5f * accel.x * deltaTime * deltaTime;
	pos.y += vel.y * deltaTime + 0.5f * accel.y * deltaTime * deltaTime;
	pos.z += vel.z * deltaTime + 0.5f * accel.z * deltaTime * deltaTime;

	vel.x += accel.x * deltaTime - (WF.x + c.x) / mass * deltaTime;
	vel.y += accel.y * deltaTime - (WF.y + c.y) / mass * deltaTime;
	vel.z += accel.z * deltaTime - (WF.z + c.z) / mass * deltaTime;


	if (pos.y < 2.0f) {
		// this is just to stop the bird.
		vel.x = 0;
		vel.y = 0;
		vel.z = 0;
		accel.x = 0;
		accel.y = 0;
		accel.z = 0;
	}

}

void Body::HandleEvents(const SDL_Event& sdlEvent) {
}
