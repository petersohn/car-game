#ifndef CAR_HPP
#define CAR_HPP

#include <irrlicht/irrlicht.h>

namespace car {

class Car {
public:

	typedef irr::core::vector3df Vector3d;

	Car() = default;
	Car(const Vector3d& position);

	void setMesh(irr::scene::IMeshSceneNode *newMesh);

	void move(irr::f32 deltaSeconds);

	void setGas(irr::f32 value);
	irr::f32 getGas() const;
	void increaseGas(irr::f32 deltaSeconds);
	void decreaseGas(irr::f32 deltaSeconds);

	const Vector3d& getPosition() const;
	const Vector3d& getVelocity() const;
	irr::f32 getSpeed() const;

private:
	void updateMesh();

	irr::f32 gasLevel = 0.0;

	Vector3d position; //unit is m

	Vector3d velocity = Vector3d(10, 0, 0); //in m/s
	const irr::f32 mass = 1000.0; //in kg

	irr::scene::IMeshSceneNode *mesh;
};

}

#endif /* !CAR_HPP */
