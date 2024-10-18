#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
using namespace std;
using namespace sf;
using namespace sfp;
int main()
{

	RenderWindow window(VideoMode(800, 600), "Bounce");
	World world(Vector2f(0, 1));

	PhysicsCircle ball;
	ball.setCenter(Vector2f(200, 100));
	ball.setRadius(20);
	ball.applyImpulse(Vector2f(0.1, 0.1));
	world.AddPhysicsBody(ball);
	int thudCount(1);
	int bangCount(1);

	PhysicsRectangle floor;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);
	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};
	PhysicsRectangle roof;
	roof.setSize(Vector2f(800, 20));
	roof.setCenter(Vector2f(400, 0));
	roof.setStatic(true);
	world.AddPhysicsBody(roof);
	roof.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};
	PhysicsRectangle wallL;
	wallL.setSize(Vector2f(60, 800));
	wallL.setCenter(Vector2f(0, 400));
	wallL.setStatic(true);
	world.AddPhysicsBody(wallL);
	wallL.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};
	PhysicsRectangle wallR;
	wallR.setSize(Vector2f(60, 800));
	wallR.setCenter(Vector2f(800, 400));
	wallR.setStatic(true);
	world.AddPhysicsBody(wallR);
	wallR.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};
	PhysicsRectangle obstacle;
	obstacle.setSize(Vector2f(100, 100));
	obstacle.setCenter(Vector2f(400, 300));
	obstacle.setStatic(true);
	world.AddPhysicsBody(obstacle);
	obstacle.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
		cout << "bang " << bangCount << endl;
		bangCount++;
		};
	Clock clock;
	Time lastTime(clock.getElapsedTime());
	while (true) {

		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());
		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}
		if (bangCount >= 4) {
			window.close();
		}
		window.clear(Color(0, 0, 0));
		window.draw(ball);
		window.draw(floor);
		window.draw(roof);
		window.draw(wallL);
		window.draw(wallR);
		window.draw(obstacle);
		window.display();
	}
}
