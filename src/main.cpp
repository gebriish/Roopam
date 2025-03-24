#include <cstdio>
#include <core/project.hpp>

#include <renderer/shader.hpp>
#include <renderer/quad_batch.hpp>
#include <core/vmath.hpp>

#include <iostream>

class MyProject : public Rpm::ProjectBase 
{
public:
	MyProject()
	: Rpm::ProjectBase(640, 480)
	{}


private:
	void onUpdate(float deltaTime) override {
	}

	void onCommand(const std::string& command) override {
		if(command == "run") 
			this->onRun();
	}

	void onRun() {
	}

};


int main() {
	MyProject proj;
	proj.start();
}
