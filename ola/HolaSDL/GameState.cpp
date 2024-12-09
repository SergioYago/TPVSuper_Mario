#include "GameState.h"
#include "Game.h"
void GameState::update() {
	for (auto elem : gameObj) {
		elem->update();
	}
}

void GameState::render() {
	for (GameObject* elem : gameObj) {
		elem->render();
	}

}

void GameState::handleEvent(const SDL_Event e) {
	for (EventHandler* elem : eventObj) {
		elem->handleEvent(e);
	}
}
