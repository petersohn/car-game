#ifndef CAR_HPP
#define CAR_HPP

#include <SFML/Graphics.hpp>
#include "Point.hpp"

namespace car {

class Car {
public:


	Car();
	Car(const Point& position, float direction);

	void setColor(const sf::Color& color);

	void move(float deltaSeconds);

	void setThrottle(float value);
	float getThrottle() const;
	void increaseThrottle(float deltaSeconds);
	void decreaseThrottle(float deltaSeconds);

	void setBrake(float value);
	float getBrake() const;
	void increaseBrake(float deltaSeconds);
	void decreaseBrake(float deltaSeconds);

	void setTurnLevel(float value);
	float getTurnLevel() const;
	void increaseTurnToRight(float deltaSeconds);
	void increaseTurnToLeft(float deltaSeconds);
	void dontTurn(float deltaSeconds);

	const Point& getPosition() const;
	const Point& getVelocity() const;
	const Point& getOrientation() const;
	float getSpeed() const;

	const Point& getAcceleration() const;

	const Point& getFrontLeftCorner() const;
	const Point& getFrontRightCorner() const;
	const Point& getRearLeftCorner() const;
	const Point& getRearRightCorner() const;

	float getTravelDistance() const;

	void draw(sf::RenderWindow& window) const;

private:

	void updateCorners();

	static const float cDrag;
	static const float cRollingResistance;
	static const float pEngine;
	static const float fEngineMax;
	static const float fBrake;
	static const float gravity;
	static const float transMissionEfficiency;
	static const float gearRatio;
	static const float differentialRatio;
	static const float wheelRadius;
	static const float mass;
	static const float maxTurnAngle;
	static const float turnRate;

	//CM == Center of Mass
	//CG == Center of Gravity
	static const float rearWheelCMDistance;
	static const float frontWheelCMDistance;
	static const float rearCMDistance;
	static const float frontCMDistance;
	static const float heightOfCG;
	static const float wheelBase;
	static const float carWidth;

	static const float throttleIncreaseSpeed;
	static const float throttleDecreaseSpeed;
	static const float brakeIncreaseSpeed;
	static const float brakeDecreaseSpeed;

	static const float turnSpeed;

	float throttleLevel = 0.0; // [0, 1]
	float brakeLevel = 0.0; // [0, 1]
	float turnLevel = 0.0; // [-1, 1] => [left, right]

	Point position = Point(0, 0); //unit is m

	Point velocity = Point(0, 0); //in m/s
	Point orientation = Point(1., 0.); //unit vector
	Point acceleration; //recalculated with move();

	Point frontLeftCorner; //recalculated with move()
	Point frontRightCorner; //recalculated with move()
	Point rearLeftCorner; //recalculated with move()
	Point rearRightCorner; //recalculated with move()

	float travelDistance = 0.f; //recalculated with move()

	sf::Color color = sf::Color::White;
};

}

#endif /* !CAR_HPP */
