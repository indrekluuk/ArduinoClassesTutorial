
#ifndef _BUTTON_H_
#define _BUTTON_H_


class Button {

int _buttonPin;

public:
  Button(int buttonPin) {
    _buttonPin = buttonPin;
    pinMode(_buttonPin, INPUT_PULLUP);
  }

  bool isPressed() {
    return !digitalRead(_buttonPin);
  }
  
};

#endif // _BUTTON_H_

