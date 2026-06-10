#include "agenda.h"
#include <algorithm>

Agenda::Agenda() {}

const list<Reserva>& Agenda::reservas() const {
    return _reservas;
    
}
/**
     * Método utilizado para registrar una nueva reserva en la agenda.
     *
     * Complejidad esperada: O(log(D) + C), donde:
     *   - D es la máxima cantidad de días distintos con reservas
     *   - C es la máxima cantidad de clientes distintos
     */
void Agenda::registrar_reserva(Reserva r) {
    //_reservas.push_back(r);
    _deque_reservas.push_back(r); // O(1) 
    _cant_reservas ++;
    mapa_clientes_frecuentes[r.cliente]++; // O(log(C))
    // Actualizar heap_reservas_por_dia
    mapa_reservas_por_dia[principio_del_dia(r.fecha_hora)].first++; // O(log(D))
    mapa_reservas_por_dia[principio_del_dia(r.fecha_hora)].second.push_back(r); // O(log(D)) para acceder al día, luego O(1)

}
    

int Agenda::cantidad_reservas() const {
    // Implementación trivial O(n): recorre toda la lista
    //return _reservas.size(); pero .size() es 0(1)
    return _cant_reservas; //??

}

vector<Reserva> Agenda::ultimas_reservas(int k) const {
    /**
     * Devuelve las últimas `k` reservas registradas.
     * Si hay menos de k reservas, devuelve todas las existentes.
     *
     * Complejidad esperada: O(k)
     * 
     */
    vector<Reserva> resultado;
    int n = _deque_reservas.size();
    int desde = max(0, n - k); // como lo mas nuevo va atras y lo mas viejo va adelante, entonces desde es n-k para tomar las ultimas k reservas. Si hay menos de k, entonces desde es 0 para tomar todas las reservas.

    for (int i = n - 1; i >= desde; i--) { // O(k) en total, ya que se recorre a lo sumo k elementos o menos
        resultado.push_back(_deque_reservas[i]); // O(1) 
    }

    return resultado; // O(k) en total
    
    /*
    // Implementación trivial O(n): recorre toda la lista
    vector<Reserva> resultado;
    const list<Reserva>& todas = _reservas;

    // Tomamos las últimas k (o todas si hay menos de k)
    int total = todas.size();
    int inicio = max(0, total - k);
    int i = 0;

    for (const Reserva& r : todas) {
        if (i >= inicio) {
            resultado.push_back(r);
        }
        i++;
    }

    // Las invertimos para que queden de más reciente a más antigua
    reverse(resultado.begin(), resultado.end());

    return resultado;

    */
}

int Agenda::reservas_del_dia(timestamp t) const {
   auto it = mapa_reservas_por_dia.find(t); // log(D), iterador pq eso devuelve .find()
    if (it != mapa_reservas_por_dia.end()) { // si existe es diferente del final del mapa que es nulo (segun google)
        return it->second.first; // ->second para el valor de la clave y .first es el int  que cuenta la cantidad de reservas en ese dia 
    }
    return 0; // no esta el dia 

    /*// Implementación trivial O(n): recorre toda la lista
    timestamp inicio_dia = principio_del_dia(t);
    timestamp fin_dia = fin_del_dia(t);

    int cantidad = 0;
    for (const Reserva& r : _reservas) {
        if (r.fecha_hora >= inicio_dia && r.fecha_hora < fin_dia) {
            cantidad++;
        }
    }

    return cantidad; */
}

vector<string> Agenda::clientes_frecuentes(int k) const {
    /**
     * Devuelve los nombres de los `k` clientes que más reservas realizaron.
     * Si hay menos de k clientes distintos, devuelve todos los existentes.
     *
     * Complejidad esperada: O(k)
     */
    vector<string> resultado;
    // Busco en el mapa en base a la cantidad de reservas por cliente, y voy agregando a resultado hasta tener k clientes o no haber más clientes
    //auto it = mapa_reservas_por_dia.find(k); quizas no usar mapa y usar max heap 
    
    
    
    /*
    // Implementación trivial O(n*c): recorre todas las reservas y ordena
    // Primero contamos las reservas por cliente
    vector<pair<string, int>> conteo;

    for (const Reserva& r : _reservas) {
        bool encontrado = false;
        for (auto& p : conteo) {
            if (p.first == r.cliente) {
                p.second++;
                encontrado = true;
                break;
            }
        }
        if (!encontrado) {
            conteo.push_back({r.cliente, 1});
        }
    }

    // Ordenamos por cantidad de reservas (descendente)
    sort(conteo.begin(), conteo.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
    });

    // Tomamos los primeros k
    vector<string> resultado;
    for (int i = 0; i < k && i < (int)conteo.size(); i++) {
        resultado.push_back(conteo[i].first);
    }

    return resultado;

    */
}
