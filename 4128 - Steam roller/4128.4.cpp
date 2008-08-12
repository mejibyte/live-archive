/*
  Accepted
  Este código es de Rubén
 */
#include <stdio.h>
#include <queue>
#include <iostream>
#include <vector>

using namespace std;

struct item{
  int i, w, d;
  item(int I, int W, int D) : i(I), w(W), d(D) {}

  bool operator < (const item &that) const {
    return w > that.w;
  }
};


int main(){
  int r, c, i, j, w, C = 1;
  while (scanf("%d %d", &r, &c) && r + c){
    int start, end;
    scanf("%d %d", &i, &j); --i, --j;
    start = i*c + j;
    scanf("%d %d", &i, &j); --i, --j;
    end = i*c + j;

    //printf("Start y end son: %d %d\n", start, end);

    //g[3] contiene la lista de vecinos del nodo 3 (El primer nodo es el 0!)
    //Cada vector de vecinos tiene cuatro elementos: abajo, izquierda, arriba, derecha = 0, 1, 2, 3
    //cada vecino es una pareja de enteros donde "first" es la distancia del viaje
    //y "second" es el nodo de destino (-1 si está fuera del tablero).
    pair<int, int> g[r*c][4];

    //Inicializa el grafo con vecinos "muertos", para que después de leer el grafo no haya
    //que preocuparse por revisar cuales son vecinos válidos y cuales no.
    for (i=0; i<r*c; ++i){
      g[i][0] = g[i][1] = g[i][2] = g[i][3] = make_pair(0, -1);
    }

    //Acá leemos el grafo
    for (i = 0; i<r; ++i){
      for (j = 0; j < c - 1; ++j){ //Horizontales
	scanf("%d", &w);
	g[i*c + j][3] = make_pair(w, i*c + j + 1);
	g[i*c + j + 1][1] = make_pair(w, i*c + j);
      }

      for (j = 0; j < c && (i+1)*c + j < r*c; ++j){ //Verticales
	scanf("%d", &w);
	g[i*c + j][0] = make_pair(w, (i+1)*c + j);
	g[(i+1)*c + j][2] = make_pair(w, i*c + j);
      }
    }

    //Ya el grafo está leído.


    //Inicialización de Dijkstra
    //d[i][j] contiene la mínima distancia desde el comienzo para llegar al nodo i en la dirección j.
    // (j puede ser 0 = abajo, 1 = izquierda, 2 = arriba, 3 = derecha, 4 = cualquier dirección)
    //Inicialmente es infinito pues no hemos encontrado ningún camino todavía.
    int d[r*c][5];
    for (i=0; i<r*c; ++i)
      d[i][0] = d[i][1] = d[i][2] = d[i][3] = d[i][4] = INT_MAX;


    d[start][4] = 0;

    //Hacemos una búsqueda empezando en el nodo inicial en cualquier dirección.
    priority_queue<item> q;
    q.push(item(start, 0, 4)); //4 = any direction

    //Dijkstra
    while (!q.empty()){
      //Top.i tiene el nodo que estamos visitando, top.w la distancia en la que llegamos
      // y top.d la dirección con la que llegamos (0,1,2,3,4) (4 = cualquier dirección)
      item top = q.top(); q.pop();

      //printf("Saque item: i = %d, w = %d, d = %d\n", top.i, top.w, top.d);

      //Ya conozco una ruta mejor para llegar a top.i, no vale la pena seguir buscando por esta rama
      if (top.w > d[top.i][top.d]) continue;

      //Si llegué en cualquier dirección...
      if (top.d == 4){
	for (int dir=0; dir<4; ++dir){ //Intento ir a todos los vecinos en cualquier dirección
	  if (g[top.i][dir].first != 0){ //es un vecino válido
	    int j = g[top.i][dir].second;
	    
	    if (top.w + 2*g[top.i][dir].first < d[j][dir]){
	      d[j][dir] = top.w + 2*g[top.i][dir].first;
	      q.push(item(j, d[j][dir], dir));
	    }
	    
	    if(top.w + 2*g[top.i][dir].first < d[j][4]){
	      d[j][4] = top.w + 2*g[top.i][dir].first;
	      q.push(item(j, d[j][4], 4));
	    }
	  }
	}
      }else{ //Si llegué en una dirección específica "top.d"...
	if (g[top.i][top.d].first != 0){ //Es un vecino válido en la misma dirección
	  int j = g[top.i][top.d].second;

	  if (top.w + g[top.i][top.d].first < d[j][top.d]){
	    d[j][top.d] = top.w + g[top.i][top.d].first;
	    q.push(item(j, d[j][top.d], top.d));
	  }
	    
	  if (top.w + 2*g[top.i][top.d].first < d[j][4]){
	    d[j][4] = top.w + 2*g[top.i][top.d].first;
	    q.push(item(j, d[j][4], 4));
	      
	  }
	}
      }
      
    }

    printf("Case %d: ", C++);
    if (d[end][4] < INT_MAX)
      printf("%d", d[end][4]);
    else
      printf("Impossible");
    printf("\n");
  }
  return 0;
}
