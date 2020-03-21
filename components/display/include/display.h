//
// Created by jadjer on 3/21/20.
//

#ifndef FROSTBIKE_ESP_COMPONENTS_DISPLAY_INCLUDE_DISPLAY_H_
#define FROSTBIKE_ESP_COMPONENTS_DISPLAY_INCLUDE_DISPLAY_H_

typedef struct {
  int a;
} display_config_t;

display_config_t *display_init(int pin_a, int pin_b);

#endif //FROSTBIKE_ESP_COMPONENTS_DISPLAY_INCLUDE_DISPLAY_H_
