from datetime import datetime
from threading import * 
import random
import time

#maxima cantidad de jugadores
max_jug = 120
#locks
lock_estand = Lock() 
lock_vs= Lock() 
lock_rapida = Lock() 
lock_xmas = Lock()
lock_salida = Lock()
lock_lobby = Lock() 


#declaraciones semaforos
stand_cola = Semaphore(7)
stand_juego = Semaphore(15)

vs_cola = Semaphore(4)
vs_juego = Semaphore(2)

rapida_cola = Semaphore(8)
rapida_juego = Semaphore(10)

xmas_cola = Semaphore(10)
xmas_juego = Semaphore(12)


#listas de threads
thread_list = []


#clase de contadores de semaforos, para asegurarnos que se utilizan de manera segura
class ThreadSafeCounter():
    # constructor
    def __init__(self, vaor =0):
        self._counter = vaor
        # inicializacion lock
        self._lock = Lock()
    def value(self):
        #acceder al valor del contador
        with self._lock:
            return self._counter
    def increment(self):
        #aumentar el valor del contador
        with self._lock:
            self._counter +=1
    def decrement(self):
        #disminuir el valor del contador
        with self._lock:
            self._counter -=1
    def reset(self):
        #resetear el valor del contador a 0
        with self._lock:
            self._counter = 0

#contadores de threads en la cola
contador_stand = ThreadSafeCounter()
contador_vs = ThreadSafeCounter()
contador_rapida = ThreadSafeCounter()
contador_xmas = ThreadSafeCounter()

#contadores de threads totales por juego (cola + lobby)
estandar_totales= ThreadSafeCounter(120)
vs_totales = ThreadSafeCounter(120)
xmas_totales = ThreadSafeCounter(120)
rapida_totales = ThreadSafeCounter(120)

#listas de tiempos
tiempo_ingreso = list("0"*max_jug)
tiempo_ingreso_partida = list("0"*max_jug)
tiempo_salida= list("0"*max_jug)
tiempo_ingreso_lobby =list("0"*max_jug)


'''
    Se hizo una función distinta por cada modo de juego, y dado que la estructura que siguen es similar, este comentario explicará
    su funcionamiento.
    Por cada juego, hay un lock para proteger la cola de espera, y el juegador entra si es que el lock está libre. Si logra entrar,
    se marca el tiempo, y lo mismo para entrar al juego. 
    Luego, mientras no se llegue a la cantidad de jugadores, no se puede entrar al juego. Cuando llega a la cantidad necesaria, entran
    y esperan el tiempo necesario. Después, cuando salen disminuye el contador de la cola, se marca el tiempo de salida y luego se escribe en 
    el archivo de salida. 
'''

def Estandar(i):
    global contador_stand
    flag = False
    stand_cola.acquire() 
    tiempo_ingreso[i] = datetime.now().strftime("%H:%M:%S.%f")
    stand_juego.acquire() 
    tiempo_ingreso_partida[i] = datetime.now().strftime("%H:%M:%S.%f")
    stand_cola.release() 
    contador_stand.increment() 
    while(contador_stand.value() < 14): 
        if estandar_totales.value() < 15:
            flag = True
        if(flag):
            break
    time.sleep(7) 
    contador_stand.decrement()
    escritura(lock_estand, "PartidaEstandar" , [str(i), tiempo_ingreso[i], tiempo_ingreso_partida[i]])
    stand_juego.release()
    tiempo_salida[i] = datetime.now().strftime("%H:%M:%S.%f")
    escritura(lock_salida, "Salida",[str(i), tiempo_salida[i]])
    estandar_totales.decrement()

def Versus(i):
    global contador_vs
    flag = False
    vs_cola.acquire()
    tiempo_ingreso[i] = datetime.now().strftime("%H:%M:%S.%f")
    vs_juego.acquire()
    tiempo_ingreso_partida[i] = datetime.now().strftime("%H:%M:%S.%f")
    vs_cola.release()
    contador_vs.increment() 

    while(contador_vs.value() <1):
        if vs_totales.value() < 2:
            flag = True
        if(flag):
            break
    time.sleep(3)
    contador_vs.decrement()
    escritura(lock_estand, "PartidaVersus" , [str(i), tiempo_ingreso[i], tiempo_ingreso_partida[i]])
    vs_juego.release()
    tiempo_salida[i] = datetime.now().strftime("%H:%M:%S.%f")
    escritura(lock_salida, "Salida",[str(i), tiempo_salida[i]])
    vs_totales.decrement()

def Rapida(i):
    global contador_rapida
    flag = False
    rapida_cola.acquire() 
    tiempo_ingreso[i] = datetime.now().strftime("%H:%M:%S.%f")
    rapida_juego.acquire() 
    tiempo_ingreso_partida[i] = datetime.now().strftime("%H:%M:%S.%f")
    rapida_cola.release() 
    contador_rapida.increment() 
    while(contador_rapida.value() < 9): 
        if rapida_totales.value() < 10:
            flag = True
        if(flag):
            break
    time.sleep(6) 
    contador_rapida.decrement()
    rapida_juego.release()
    escritura(lock_estand, "PartidaRapida" , [str(i), tiempo_ingreso[i], tiempo_ingreso_partida[i]])
    tiempo_salida[i] = datetime.now().strftime("%H:%M:%S.%f")
    escritura(lock_salida, "Salida",[str(i), tiempo_salida[i]])
    rapida_totales.decrement()

def Xmas(i):
    global contador_xmas
    flag = False
    xmas_cola.acquire() 
    tiempo_ingreso[i] = datetime.now().strftime("%H:%M:%S.%f")
    xmas_juego.acquire() 
    tiempo_ingreso_partida[i] = datetime.now().strftime("%H:%M:%S.%f")
    xmas_cola.release()
    contador_xmas.increment() 
    while(contador_xmas.value() < 11): 
        if xmas_totales.value() < 12:
            flag = True
        if(flag):
            break
    time.sleep(5)
    contador_xmas.decrement()
    escritura(lock_estand, "PartidaEspecialNavidad" , [str(i), tiempo_ingreso[i], tiempo_ingreso_partida[i]])
    xmas_juego.release()
    tiempo_salida[i] = datetime.now().strftime("%H:%M:%S.%f")
    escritura(lock_salida, "Salida",[str(i), tiempo_salida[i]])
    xmas_totales.decrement()

def lobby(i,playing):
    tiempo_ingreso_lobby[i] = datetime.now().strftime("%H:%M:%S.%f")
    if playing == 1:
        vs_totales.decrement()
        rapida_totales.decrement()
        xmas_totales.decrement()
        partida = "Partida Estandar"
        Estandar(i)
    elif playing ==2:
        estandar_totales.decrement()
        rapida_totales.decrement()
        xmas_totales.decrement()
        partida = "Partida Versus"
        Versus(i)
    elif playing ==3:
        estandar_totales.decrement()
        vs_totales.decrement()
        xmas_totales.decrement()
        partida = "Partida Rapida"
        Rapida(i)
    elif playing ==4:
        estandar_totales.decrement()
        rapida_totales.decrement()
        vs_totales.decrement()
        partida = "Partida Especial Navidad"
        Xmas(i)

    escritura(lock_lobby, "Lobby", [str(i),tiempo_ingreso_lobby[i],partida,tiempo_ingreso[i]])

'''
Funcion para escibir en los archivos correspondientes (los archivos también están protegidos por locks)
'''
def escritura(lock, tipoescritura, textos):
    lock.acquire()
    tex = ""
    for texto in textos:
        tex += texto+", "
    txt = f"jugador {tex}\n"
    file = open(f"{tipoescritura}.txt", "a")
    file.write(txt)
    file.close()
    lock.release()

for i in ["Lobby","Salida","PartidaEspecialNavidad","PartidaRapida","PartidaVersus","PartidaEstandar"]:
    file = open(f"{i}.txt", "w")
    file.close()

for i in range(max_jug):
    local_random = random.Random()
    local_random.seed(i)
    playing= local_random.randint(1,4)
    thread_list.append(Thread(target = lobby, args = (i,playing)))
    
for eachthread in thread_list:
    eachthread.start()
for eachthread in thread_list:
    eachthread.join()

   