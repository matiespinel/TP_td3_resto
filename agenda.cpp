#include "agenda.h"
#include <algorithm>
#include <iostream> //ACORDARSE DE ELIMINARLO

using namespace std; //ACORDARSE DE ELIMINARLO


Agenda::Agenda() {
    _cant_reservas = 0;

}

const list<Reserva>& Agenda::reservas() const {
    return _reservas; // O(1)
} // O(1)
/**
     * Método utilizado para registrar una nueva reserva en la agenda.
     *
     * Complejidad esperada: O(log(D) + C), donde:
     *   - D es la máxima cantidad de días distintos con reservas
     *   - C es la máxima cantidad de clientes distintos
     */
void Agenda::registrar_reserva(Reserva r) {
    bool cliente_encontrado = false;
    
    _reservas.push_back(r); //O(1) amortizado 
    _deque_reservas.push_back(r); // O(1) 
    _cant_reservas++;//O(1)
    //O(3) = O(1)
    timestamp dia = principio_del_dia(r.fecha_hora); //O(1)
    _reservas_por_dia[dia].first++; // O(log(D)) operacion de mapa
    _reservas_por_dia[dia].second.push_back(r); // O(log(D)) para acceder al día, luego O(1) amortizado 
    //O(2log(D)) + O(4)

    if(!_frecuencia_clientes.empty()){ // O(1)
        int mayor = _frecuencia_clientes[_frecuencia_clientes.size()-1].second;// O(1)
        int pos = _frecuencia_clientes.size()-1;// O(1)
        //O(2log(D)) + O(7)
        for(int i = _frecuencia_clientes.size()-1; i > -1; i--){  //O(C) 
            if(_frecuencia_clientes[i].second < mayor){ // O(1)
                mayor = _frecuencia_clientes[i].second;// O(1)
                pos = i;// O(1)
            }

            if(_frecuencia_clientes[i].first == r.cliente) {// O(1)
                _frecuencia_clientes[i].second += 1;// O(1)

                if(_frecuencia_clientes[i].second > mayor && i > pos){// O(1)
                    swap(_frecuencia_clientes[i], _frecuencia_clientes[pos]);// O(1)
                }

                cliente_encontrado = true;// O(1)
            }        
        } //O(C) + //O(2log(D)) + O(4)
    }
    if(!cliente_encontrado){// O(1)
        _frecuencia_clientes.push_back({r.cliente, 1});// O(1) amortizado 
    }
    //O(C) + //O(2log(D)) + O(9) = O(Log(D) + C)

}
    

int Agenda::cantidad_reservas() const {
    return _cant_reservas; // O(1)

} //O(uan)

vector<Reserva> Agenda::ultimas_reservas(int k) const { // O(k)
    /**
     * Devuelve las últimas `k` reservas registradas.
     * Si hay menos de k reservas, devuelve todas las existentes.
     *
     * Complejidad esperada: O(k)
     * 
     */
    vector<Reserva> resultado; // O(1)
    int n = _deque_reservas.size();// O(1)
    int desde = max(0, n - k); // O(1), como lo mas nuevo va atras y lo mas viejo va adelante, entonces desde es n-k para tomar las ultimas k reservas. Si hay menos de k, entonces desde es 0 para tomar todas las reservas.
    //O(3)
    for (int i = n - 1; i >= desde; i--) { // O(k) en total, ya que se recorre a lo sumo k elementos o menos
        resultado.push_back(_deque_reservas[i]); // O(1) amortizada 
    }
    //0(3 + k)

    return resultado; // O(k) en total
}

int Agenda::reservas_del_dia(timestamp t) const {
    timestamp inicio_dia = principio_del_dia(t); // O(1)

    auto it = _reservas_por_dia.find(inicio_dia); // log(D), iterador porque eso devuelve .find()
    
    if (it != _reservas_por_dia.end()) { //O(1)si existe es diferente del final del mapa
        return it->second.first; // ->second para el valor de la clave y .first es el int  que cuenta la cantidad de reservas en ese dia. O(1)
    }
    
    return 0; // no esta el dia O(1)
}// O(Log(D))

vector<string> Agenda::clientes_frecuentes(int k) const {
    /**
     * Devuelve los nombres de los `k` clientes que más reservas realizaron.
     * Si hay menos de k clientes distintos, devuelve todos los existentes.
     *
     * Complejidad esperada: O(k)
     */
    vector<string> resultado; // O(1)

    for(int i = 0; i < k && i < _frecuencia_clientes.size(); i++){// O(k)
        resultado.push_back(_frecuencia_clientes[i].first); // O(1) amortizado
    }

    return resultado;// O(1)
}// O(k) listoooo
