#ifndef AGENDA_H
#define AGENDA_H

#include <string>
#include <vector>
#include <list>
#include "lib.h"
#include <queue> // para priority_queue
#include <deque> 
#include <map> // para map
#include <stack> 

using namespace std;

class Agenda {
  public:
    /**
     * Constructor.
     */
    Agenda();

    /**
     * Lista de todas las reservas registradas.
     *
     * Complejidad: O(1), usando una referencia no modificable.
     */
    const list<Reserva>& reservas() const;
    //devuelve las reservas que se hicieron 

    /**
     * Método utilizado para registrar una nueva reserva en la agenda.
     *
     * Complejidad esperada: O(log(D) + C), donde:
     *   - D es la máxima cantidad de días distintos con reservas
     *   - C es la máxima cantidad de clientes distintos
     */
    void registrar_reserva(Reserva r);

    /**
     * Devuelve la cantidad total de reservas activas.
     *
     * Complejidad esperada: O(1)
     */
    int cantidad_reservas() const;
    //mantener un entero 

    /**
     * Devuelve las últimas `k` reservas registradas.
     * Si hay menos de k reservas, devuelve todas las existentes.
     *
     * Complejidad esperada: O(k).
     */
    vector<Reserva> ultimas_reservas(int k) const;
    //recorrer la list y ya esta. es doble enlazada. 

    /**
     * Devuelve la cantidad de reservas que hay para el día de `t`.
     *
     * Por ejemplo, si t es el 10 de enero a las 15hs, devolveremos
     * la cantidad de reservas que hay para el 10 de enero.
     *
     * Complejidad esperada: O(log(D)), donde D es la máxima cantidad
     * de días distintos con reservas
     */
    int reservas_del_dia(timestamp t) const;
    // metodo de resolucion:: arbol con orden, nodo izq mas chico y nodo dercho mas grande. encontrar un nodo en peor caso seria la altura del arbol que es Log(N)???

    /**
     * Devuelve los nombres de los `k` clientes que más reservas realizaron.
     * Si hay menos de k clientes distintos, devuelve todos los existentes.
     *
     * Complejidad esperada: O(k)
     */
    vector<string> clientes_frecuentes(int k) const;

  private:
    // =====================================================================
    // INVARIANTE DE REPRESENTACIÓN:
    //
    // TODO: Escribir acá el invariante de representación en castellano!
    //
    // Recordar que también hay que presentarlo escrito en lenguaje formal.
    //
    // =====================================================================
    // =====================================================================
    // TODO: A partir de aquí, modificar la estructura según sea necesario y
    // escribir en un comentario invariante de representación en castellano.
    // =====================================================================

    /** Listado de todas las reservas realizadas */
    list<Reserva> _reservas;
    deque<Reserva> _deque_reservas; // uso deque para poder indexar en O(1)
    int _cant_reservas; 
    //max_heap con las reservas mas nuevas y vas buscando hijos??
    priority_queue<pair<timestamp, int>, vector<pair<timestamp, int>>, greater<pair<timestamp, int>>>min_heap_reservas_por_dia; // para reservas del dia, guardo el timestamp del dia y la cantidad de reservas en ese dia. el vectro es para el contenedor del heap, el greater es para que sea un min heap.
    //estructura alternativa 
    map<timestamp, pair<int, vector<Reserva>>> _reservas_por_dia;// para reservas del dia, guardo el timestamp del dia y la cantidad de reservas en ese dia. operaciones de mapa: todas log(n)

    //mapa de cliente a cantidad de reservas para clientes frecuentes
    map<string, int> mapa_clientes_frecuentes;// operaciones de mapa: todas log(n)

    vector<pair<string, int>> _frecuencia_clientes; //Vector que almacena el cliente y la cantidad de reservas que realizó

};  

#endif 

