class Rotor {
  public:
    Rotor(byte inPinA, byte inPinB);
    int getValue();
    bool checkState();
    void setOnChangeCallback(void (*_callBackPointer)(int));
   private:
    byte _inPinA, _inPinB;
    int _currentVal, _offSet; // offset needs to be signed
    byte _lastA, _lastB;
    void updateLastState(byte a, byte b);
    void (*_onChangeCallBack)(int);
};

Rotor::Rotor(byte inPinA, byte inPinB){
  _inPinA = inPinA;
  _inPinB = inPinB;
  pinMode(_inPinA, INPUT);
  pinMode(_inPinB, INPUT);
  _currentVal = 0;
  _offSet = 0;
  updateLastState(digitalRead(_inPinA), digitalRead(_inPinB));
}

void Rotor::updateLastState(byte a, byte b){
  _lastA = a;
  _lastB = b;
}

bool Rotor::checkState(){
  byte a = digitalRead(_inPinA);
  byte b = digitalRead(_inPinB);
  if(_lastA != a || _lastB != b){
    if(a == b){
      _currentVal += _offSet;
      if(_onChangeCallBack != NULL){
        (*_onChangeCallBack)(_offSet);
      }
      _offSet = 0;
    } else {
      _offSet = _lastA != a ? 1: -1;
    }
    updateLastState(a, b);
    return a == b;
  }
  return false;
}

int Rotor::getValue(){
  return _currentVal;
}

void Rotor::setOnChangeCallback(void (*handler)(int)){
  _onChangeCallBack = handler;
}
