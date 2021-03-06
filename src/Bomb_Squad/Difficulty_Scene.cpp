#include <avr/pgmspace.h>

#include "Difficulty_Scene.h"
#include "Colors.h"
#include "Display.h"
#include "Pins.h"
#include "Globals.h"
#include "Image.h"

#define NEXT_LEVEL SceneID_Game

void DifficultyScene::Bootstrap() {

  _option = g_difficulty;

  ImageUtil::Draw(_screen, 2, 9, 16);
  ImageUtil::Draw(_screen, 3, 94, 54);
  ImageUtil::Draw(_screen, 4, 70, 72);
  ImageUtil::Draw(_screen, 5, 92, 90);
  ImageUtil::Draw(_screen, 6, 17, 57);
}

void DifficultyScene::HandleFrame(unsigned char frame) {

  if(_option != _last_option) {
    _screen->drawChar(OPTION_X, _option_locations[_last_option],
                      '<', COLOR_BG, COLOR_BG, FONT_SIZE_LARGE);

    _last_option = _option;

    _screen->drawChar(OPTION_X, _option_locations[_option],
                      '<', COLOR_GREEN, COLOR_BG, FONT_SIZE_LARGE);
  }

  AnimateParticles(frame);
}

SceneID DifficultyScene::HandleInput() {

  JoystickDirection one_direction = get_joystick_vertical_direction();

  if(one_direction != _last_direction) {
    if(one_direction == JS_Up) {
      _option--;

      _last_direction = one_direction;

      if(_option < 0)
        _option = 2;
    } else if(one_direction == JS_Down) {
      _option++;

      _last_direction = one_direction;

      if(_option > 2)
        _option = 0;
    } else {

      _last_direction = one_direction;
    }
  }

  if(digitalRead(BUTTON_PIN) == BUTTON_DOWN) {
    g_difficulty = _option;
    return NEXT_LEVEL;
  }


  return SceneID_Difficulty;
}

void DifficultyScene::AnimateParticles(unsigned char frame) {

  if(frame % (FPS / 5) == 0) {
    for(unsigned char i = 0; i < PARTICLE_COUNT; i++) {
      _screen->drawPixel(FLAME_X + PARTICLE_INDEX(_x, i),
                         FLAME_Y + PARTICLE_INDEX(_y, i), COLOR_BG);

      _x = PARTICLE_SET(_x, i, random(FLAME_MAX_X));
      _y = PARTICLE_SET(_y, i, random(FLAME_MAX_Y));

      _screen->drawPixel(FLAME_X + PARTICLE_INDEX(_x, i),
                         FLAME_Y + PARTICLE_INDEX(_y, i), RGB(242, 50, 18));
    }
  }
}
