#include "Geode/binding/PauseLayer.hpp"
#include "Geode/ui/Popup.hpp"
#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/PauseLayer.hpp>
class $modify(MyPauseLayer, PauseLayer) {
	bool override = false;
	void onQuit(cocos2d::CCObject* sender) {
		if (!Mod::get()->getSettingValue<bool>("enabled") || override) {
			PauseLayer::onQuit(sender);
			return;
		}
		geode::createQuickPopup("Exit?", "Are you sure you want to exit the level?", "No", "Yes", [this, sender](auto, bool btn2){
			if (!btn2) {
				return; // don't exit!
			}
			this->override = true; // avoids stack overflows :DDD
			this->onQuit(sender);
			this->override = false;
		});
	}
};
