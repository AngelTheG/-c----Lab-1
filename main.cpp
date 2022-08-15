#include <iostream>
using namespace std;


// Objeto Estudiante
class Estudiante{
    private:
        string nombre;
        int edad;

    public:
        // Constructor
        Estudiante(string nombre, int edad){
            this -> nombre = nombre;
            this -> edad = edad;
        }
        // Constructor VACÍO
        Estudiante(){
            this -> nombre = "";
            this -> edad = 0;
        }
        
        //              Nombre del Estudiante
        // Setter
        void setNombre(string nombre){
            this -> nombre = nombre;
        }

        // Getter
        string getNombre(){
            return nombre;
        }

        //              Edad del Estudiante
        // Setter
        void setEdad(int edad){
            this -> edad = edad;
        }

        // Getter
        int getEdad(){
            return edad;
        }
};


// Nodos de la Lista
class NodoEstudiante{
    private:
        Estudiante estudiante;
        NodoEstudiante *vecino;

    public:
        // Constructor
        NodoEstudiante(Estudiante nuevo){
            this -> estudiante.setNombre(nuevo.getNombre());
            this -> estudiante.setEdad(nuevo.getEdad());

            this -> vecino = NULL;
        }

        // Constructor VACÍO
        NodoEstudiante(){
            this -> vecino = NULL;
        }

        // Setter Vecino
        void setVecino(NodoEstudiante *vecino_nuevo){
            this -> vecino = vecino_nuevo;
        }

        // Getter Vecino
        NodoEstudiante *getVecino(){
            return(this->vecino);
        }

        // Getter Estudiante
        Estudiante *getEstudiante(){
            return(&this->estudiante);
        }

}; 


// Objeto Lista
class ListaEstudiantes{
    private:
        NodoEstudiante *primero, *ultimo;

    public:
        // Constructor
        ListaEstudiantes(){
            primero = ultimo = NULL;
        }

        // Añadir Nodo
        void insertarNodo(NodoEstudiante *nuevo){
            // Si no hay Estudiantes, el nuevo es el primero y el último
            if (ultimo == NULL){
                primero = ultimo = nuevo;
            }
            
            // pero, Si hay Estudiantes...
            else{
                // El vecino del último pasa a ser el nuevo y...
                ultimo->setVecino(nuevo);

                // el nuevo pasa a ser el último
                ultimo = nuevo;
            }
        }

        // Buscar Estudiante
        bool buscarEstudiante(string nombre){
            // Si hay Estudiantes...
            if (ultimo != NULL){
                NodoEstudiante *objetivo;

                // Se toma el primero...
                objetivo = primero;

                while(true){
                    Estudiante *estudianteObjetivo;
                    estudianteObjetivo = objetivo->getEstudiante();

                    // y si el nombre coincide...
                    if (estudianteObjetivo->getNombre() == nombre){

                        // Se rompe el ciclo y se retorna una señal positiva
                        return true;
                        break;
                    }

                    // pero si no coincide...
                    else {
                        //y es el último...
                        if (objetivo == ultimo){
                            // Se rompe el ciclo y se retorna una señal negativa
                            return false;
                            break;
                        }
                        // y no es el último...
                        else {
                            // Se toma el siguiente estudiante, se repite el ciclo...
                            objetivo = objetivo->getVecino();
                        }
                    }
                }
            }
        }

        // Insertar Nodo en primer lugar
        void insertarPrimero(NodoEstudiante *primeroNuevo){
            // Si ya existe un primer estudiante, entonces...
            if (primero != NULL){
                // Al primeroNuevo se le asigna el primero como vecino y...
                primeroNuevo->setVecino(primero);

                // El primer lugar se le asigna al nuevo
                this -> primero = primeroNuevo;
            }
            // Si no hay un primer estudiante, entonces
            else {
                // Se inserta como si fuese el primero en ser ingresafo a la lista
                primero = ultimo = primeroNuevo;
            }
        }

        // Quitar Primer Nodo
        void quitarPrimero(){
            // Si la lista no está vacía...
            if (primero!=NULL){
                // Identificar el primero actual...
                NodoEstudiante *primeroActual = this->primero;

                // Se le asigna el primer lugar al vecino del primero...
                this->primero = this->primero->getVecino();

                // Solución de ERROR extraño, preguntar al profesor.
                primeroActual->setVecino(nullptr);

                // y se borra el primero Original
                delete primeroActual;
            }
            // Si la lista está vacía...
            else {
                cout <<"La lista de estudiantes está vacía, no se puede borrar al primero" <<endl;
            }
        }   

        // Quitar Ultimo Nodo
        void quitarUltimo(){
            // Si la lista no está vacía...
            if (primero!=NULL){
                // Se identifica el primero...
                NodoEstudiante *actual = this->primero;

                // Se crea un Nodo vacío para guardar el penútlimo
                NodoEstudiante *penultimo = nullptr;

                while (true){
                    // si la lista no tiene sólo 1 Nodo...
                    if (primero!=ultimo){
                        //se guarda el actual como penultimo...
                        penultimo = actual;
                        
                        // y el actual pasa al siguiente Nodo (Así el penultimo esta siempre un Nodo por detrás)
                        actual = actual->getVecino();

                        // si el Nodo actual coincide con último...
                        if (actual==ultimo){
                            // Se le quita el vecino al penúltimo...
                            penultimo->setVecino(nullptr);

                            // Se borra el ultimo...
                            delete actual;

                            // El penúltimo pasa a ser el último y se rompe el ciclo...
                            this->ultimo = penultimo;
                            break;
                        }
                    } 
                    // si la lista tiene un sólo Nodo...
                    else {
                        //Se borra el primero y se rompe el ciclo
                        this->quitarPrimero();
                        break;
                    }
                }
            }
            else {
                cout <<"La lista de estudiantes está vacía, no se puede borrar al último" <<endl;
            }
        }

        // Imprimir Lista
        void mostrarLista(){

            NodoEstudiante *recorrer;
            recorrer = primero;

            // Marcar Nuevo Registro de datos
            cout << "-----------------------------------"<<endl;

            // Mientras recorrer no esté vacío, o sea hayan Nodos en la Lista
            while(recorrer!=NULL){
                
                Estudiante *estudiante;
                estudiante = recorrer -> getEstudiante();
                
                // Impresión de datos del estudiante                           
                cout <<"Estudiante " << estudiante->getNombre()  << endl;
                cout <<"-- Edad: " << estudiante->getEdad() << endl;
                
                // El nuevo estudiante a "recorrer" es el vecino del estudiante actual
                recorrer = recorrer -> getVecino();
                
           }
           cout << "-----------------------------------"<<endl;
        }
};


//           MAIN
int main(){    
    ListaEstudiantes lista;

    // Creación de Estudiante
    Estudiante p("Mario", 20);
    NodoEstudiante *nuevo= new NodoEstudiante(p);

    lista.insertarNodo(nuevo);

    // Creación de Estudiante
    Estudiante q("Giusseppe", 30);
    NodoEstudiante *nuevo2= new NodoEstudiante(q);

    lista.insertarNodo(nuevo2);

    // Creación de Estudiante
    Estudiante r("Vicente", 20);
    NodoEstudiante *nuevo3= new NodoEstudiante(r);

    lista.insertarNodo(nuevo3);

    // Creación de Estudiante
    Estudiante s("Natanael", 20);
    NodoEstudiante *nuevo4= new NodoEstudiante(s);

    lista.insertarNodo(nuevo4);

    //      Lista básica creada en el orden Mario - Giussepe - Vicente - Natanael

    lista.mostrarLista();

    //      Busqueda de Felipe en la lista
    string busqueda = "Felipe";
    bool resultado = lista.buscarEstudiante(busqueda);
    
    cout <<"La busqueda de " << busqueda <<" resultó en: "<< resultado <<endl;
    
    //      Ingreso de nuevo primero
    Estudiante t("Felipe", 20);
    NodoEstudiante *nuevo5= new NodoEstudiante(t);

    // Agregarlo como primer lugar
    //lista.insertarNodo(nuevo5);
    lista.insertarPrimero(nuevo5);

    //      Lista básica modificada, nuevo orden: Felipe - Mario - Giussepe - Vicente - Natanael
    lista.mostrarLista();

    //      Busqueda nuevamente de Felipe en la lista
    bool resultado2 = lista.buscarEstudiante(busqueda);
    cout <<"La busqueda de " << busqueda <<" resultó en: "<< resultado2 <<endl;

    //      Quitar el primer lugar
    lista.quitarPrimero();

    //      Lista básica modificada, nuevo orden: Mario - Giussepe - Vicente - Natanael
    lista.mostrarLista();

    //      Quitar Último lugar
    lista.quitarPrimero();

    //      Lista básica modificada, nuevo orden: Mario - Giussepe - Vicente
    lista.mostrarLista();

    return 0;
}