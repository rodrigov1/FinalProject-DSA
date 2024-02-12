#ifndef RUTA_H
#define RUTA_H

class Ruta {
  private:
	int next_dest;
	int last_dest;
	int distancia_total;

  public:
	Ruta() { ; };
	~Ruta();
	int getNext() { return next_dest; };
	int getLast() { return last_dest; };
	int getDistancia() { return distancia_total; };
	void setNext(int n) { next_dest = n; };
	void setLast(int l) { last_dest = l; };
	void setDistancia(int p) { distancia_total = p; };
};

#endif
