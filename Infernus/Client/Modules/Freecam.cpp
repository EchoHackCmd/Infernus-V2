#include "Freecam.h"

void Freecam::onEnable() {
	if (Player != nullptr) {
		if (savedPos == Vec3()) {
			savedPos = *Player->getPos();
		}
	}
}

void Freecam::onPacket(PacketType type, void* Packet, bool* cancel) {
	if (type == PacketType::Movement || type == PacketType::AuthInput) {
		*cancel = true;
	}
}

void Freecam::onDisable() {
	if (Player != nullptr) {
		if (savedPos != Vec3()) {
			Player->setPos(savedPos);
		}
	}
	savedPos = Vec3();
}