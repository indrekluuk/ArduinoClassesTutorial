

#ifndef _TRAFFIC_LIGHT_H
#define _TRAFFIC_LIGHT_H

#include "Timer.h"

class TrafficLight {

  long TIMER_BLINKING_GREEN = 3000;
  long TIMER_YELLOW = 2000;

  int _greenLED;
  int _yellowLED;
  int _redLED;

  enum State {
    GREEN,
    BLINKING_GREEN,
    YELLOW,
    RED
  };

  State _currentState = GREEN;
  State _targetState = GREEN;
  Timer timer;

  

public:
  TrafficLight(int greenLED, int yellowLED, int redLED) {
    _greenLED = greenLED;
    _yellowLED = yellowLED;
    _redLED = redLED;

    pinMode(_greenLED, OUTPUT);
    pinMode(_yellowLED, OUTPUT);
    pinMode(_redLED, OUTPUT);    

    green();
  }


  void go() {
    _targetState = GREEN;
  }

  void stop() {
    _targetState = RED;
  }

  void loop() {
    if (_targetState == GREEN) {
      goToGreen();
    } else {
      goToRed();
    }
  }


private:

  void goToGreen() {
    // red
    // yellow
    // green     
    switch (_currentState) {
      case RED:
        _currentState = YELLOW;
        timer.startTimer(TIMER_YELLOW);
        break;

      case YELLOW:
        yellow();
        if (timer.isTimerReady()) {
          _currentState = GREEN;
        }
        break;

      case BLINKING_GREEN:
        _currentState = GREEN;
        break;

      case GREEN:
        green();
        break;
    }
  }


  void goToRed() {
    // green
    // blikin green
    // yellow
    // red
    switch (_currentState) {
      case GREEN:
        _currentState = BLINKING_GREEN;
        timer.startTimer(TIMER_BLINKING_GREEN);
        break;
      case BLINKING_GREEN:
        blinkGreen();
        if (timer.isTimerReady()) {
          _currentState = YELLOW;
          timer.startTimer(TIMER_YELLOW);
        }
        break;
      case YELLOW:
        yellow();
        if (timer.isTimerReady()) {
          _currentState = RED;
        }
        break;
      case RED:
        red();
        break;
    }
  }


  void blinkGreen() {
    if (millis() % 1000 > 500) {
      green();
    } else {
      off();
    }
  }

  void green() {
    digitalWrite(_greenLED, HIGH);
    digitalWrite(_yellowLED, LOW);
    digitalWrite(_redLED, LOW);
  }

  void yellow() {
    digitalWrite(_greenLED, LOW);
    digitalWrite(_yellowLED, HIGH);
    digitalWrite(_redLED, LOW);
  }

  void red() {
    digitalWrite(_greenLED, LOW);
    digitalWrite(_yellowLED, LOW);
    digitalWrite(_redLED, HIGH);
  }

  void off() {
    digitalWrite(_greenLED, LOW);
    digitalWrite(_yellowLED, LOW);
    digitalWrite(_redLED, LOW);
  }

  
  
};


#endif // _TRAFFIC_LIGHT_H

