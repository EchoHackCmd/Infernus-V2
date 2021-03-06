#include "Module.h"

class LocalPlayer* Module::Player = nullptr;

Module::Module(std::string name, std::string category, std::string description, uint64_t key) {
	this->name = std::move(name);
	this->category = std::move(category);
	this->description = std::move(description);
	this->key = key;
}

void Module::onBaseTick() {
	this->Player = Minecraft::ClientInstance()->LocalPlayer();
	onLoop();
	if (wasEnabled != isEnabled) {
		if (isEnabled) {
			onEnable();
			closing = false; /*Arraylist stuff*/
		}
		else {
			onDisable();
			closing = true; /*Arraylist stuff*/
		}
		Animating = true; /*Arraylist stuff*/
		wasEnabled = isEnabled;
		Minecraft::ClientInstance()->clientMessage(this->name + " " + std::string(isEnabled ? "Enabled" : "Disabled"));
		ClientManager::UpdateModuleData(this);
	}
	if (isEnabled) onTick();
}

void Command::respond(std::string output) {
	Minecraft::ClientInstance()->clientMessage(std::move(output));
}