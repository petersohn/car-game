#ifndef CAR_HPP
#define CAR_HPP

#include <irrlicht/irrlicht.h>

namespace car {

class Car {
public:

	typedef irr::core::vector3df Vector3d;

	Car() = default;
	Car(const Vector3d& position);

	void setMesh(irr::scene::ISceneNode *newMesh);

	void move(irr::f32 deltaSeconds);

	void setThrottle(irr::f32 value);
	irr::f32 getThrottle() const;
	void increaseThrottle(irr::f32 deltaSeconds);
	void decreaseThrottle(irr::f32 deltaSeconds);

	void setBrake(irr::f32 value);
	irr::f32 getBrake() const;
	void increaseBrake(irr::f32 deltaSeconds);
	void decreaseBrake(irr::f32 deltaSeconds);

	const Vector3d& getPosition() const;
	const Vector3d& getVelocity() const;
	irr::f32 getSpeed() const;

	const Vector3d& getAcceleration() const;

private:
	void updateMesh();

	irr::f32 throttleLevel = 0.0;
	irr::f32 brakeLevel = 0.0;

	Vector3d position; //unit is m

	Vector3d velocity = Vector3d(0, 0, 0); //in m/s
	Vector3d orientation = Vector3d(0, 0, -1); //unit vector
	Vector3d acceleration; //recalculated with move();

	irr::scene::ISceneNode *mesh;
};

}

#endif /* !CAR_HPP */
