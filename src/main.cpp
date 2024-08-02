#include "../include/Sculptor.hpp"

int main() {
  
  Sculptor semaforo(34, 14, 10);


  //BOX
    semaforo.setColor(1.0, 1.0, 1.0, 1.0);
    semaforo.putBox(0, 33, 0, 13, 0, 9);
    semaforo.cutBox(1,32,1,12,1,9);

  //RED
    semaforo.setColor(1.0, 0.0, 0.0, 1.0);
    semaforo.putBox(2, 11, 2, 11, 0, 9);
    semaforo.cutBox(3,10,3,10,1,9);

  //YELLOW
    semaforo.setColor(1.0, 1.0, 0.0, 1.0);
    semaforo.putBox(12, 21, 2, 11, 0, 9);
    semaforo.cutBox(13,20,3,10,1,9);

  //GREEN
    semaforo.setColor(0.0, 1.0, 0.0, 1.0);
    semaforo.putBox(22, 31, 2, 11, 0, 9);
    semaforo.cutBox(23,30,3,10,1,9);


  
    semaforo.writeOFF("semaforo.off");

  return 0;
}

