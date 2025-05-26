#include "Block.h"
#include "Texture.h"

using namespace std;

//constructor
Block::Block( Game* g, std::istream& is){
    game = g;
    char t,a;
    is >> position.x >> position.y>>t>>a;
    position.x = position.x * 32;
    position.y = position.y * 30;
    texture = game->getTexture(Game::BLOCK);
    tipo = Tipo::Vacio;
    action = Action::Nada;
    startFrame = 0;
    currentFrame = 0;
    Screenpos.x = position.x - game->getMapOffset();
    Screenpos.y = position.y;
    rect.x = position.x;
    rect.y = position.y;
    rect.w = rect.h = 32;
    if (t == 'B') {
        tipo = Tipo::Ladrillo;
        startFrame = 5;
    }
    else if (t == '0') {
        tipo = Tipo::Vacio;
        startFrame = 4;
    }
    else if (t == '?') {
        tipo = Tipo::Pregunta;
        startFrame = 0;
    }
    else if (t == 'H') {
        tipo = Tipo::Oculto;
        startFrame = -1;
    }

    if (a == 'P') {
        
        action = Action::Potenciador;
    }
    else if (a == 'C') {
        action = Action::Moneda;
    }
    

    
    
    
}

void Block::render() const{
   
    // const SDL_Rect& target, int row, int col, SDL_RendererFlip flip
    if (tipo == Tipo::Pregunta) {
        texture->renderFrame(rect, 0, startFrame + currentFrame, SDL_FLIP_NONE);
    }
    else {
        texture->renderFrame(rect, 0, startFrame, SDL_FLIP_NONE);
    }
}

void Block::update() {
    if (tipo == Tipo::Ladrillo) {
        startFrame = 5;
    }
    else if (tipo == Tipo::Vacio) {
        startFrame = 4;
    }
    else if (tipo == Tipo::Pregunta) {
        startFrame = 0;
    }
    else if (tipo == Tipo::Oculto) {
        startFrame = -1;
    }
    rect.x = position.x - game->getMapOffset();
    rect.y = position.y;
    rect.h = Game::TILE_SIDE;
    rect.w = Game::TILE_SIDE;

    if (hitAnimFrame) {
        rect.y = position.y- (Game::TILE_SIDE / 2);
        hitAnimFrame = false;
    }
    if (tipo == Tipo::Pregunta) {
        if (currentFrame >= 3) {
            currentFrame = 0;
        }
        else {
            currentFrame++;
        }
    }
}

void Block::active()
{
    if(tipo==Tipo::Ladrillo)
    {
        game->destroyBlock(this);
    }
    else {
        if (action == Action::Moneda) {
            //  game->playstate->addScore(200); si me da
        }
        else if (action == Action::Potenciador) {
            game->generateMushroom({ position.x,position.y });

        }
        action == Action::Nada;
        tipo = Tipo::Vacio;
    }
}





