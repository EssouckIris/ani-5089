#include <iostream>

class Accumulateur {
private:
int totalX = 0;
int totalY = 0;

public:
void evenementBrut(int deltaX, int deltaY) {
totalX += deltaX;
totalY += deltaY;
}

```
void consommerParImage() {
    std::cout << totalX << ' ' << totalY << '\n';

    totalX = 0;
    totalY = 0;
}
```

};

int main() {
Accumulateur accumulateur;

```
accumulateur.evenementBrut(3, 1);
accumulateur.evenementBrut(2, -1);
accumulateur.consommerParImage();

accumulateur.evenementBrut(-4, 2);
accumulateur.consommerParImage();

return 0;
```

}
