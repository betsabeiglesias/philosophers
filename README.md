# Philosophers

*"Nunca pensé que la filosofía llegara a ser tan letal"*

## Descripción del Proyecto

El proyecto **Philosophers** es una simulación computacional inspirada en el clásico problema de los filósofos comensales, concebido por Edsger Dijkstra. Este problema ilustra los retos fundamentales de la programación concurrente, donde múltiples procesos o hilos necesitan sincronizarse para acceder a recursos compartidos de manera segura. 

En este caso, los filósofos alternan entre tres estados posibles: pensar, comer y dormir. Para alimentarse, cada filósofo necesita tomar dos tenedores ubicados a su derecha e izquierda. Sin embargo, el número de tenedores es limitado, y su uso simultáneo por varios filósofos puede provocar condiciones de carrera, interbloqueos (*deadlocks*) o inanición (*starvation*). El objetivo del proyecto es implementar una simulación que resuelva estos problemas y garantice que todos los filósofos puedan comer periódicamente, evitando bloqueos y asegurando la coherencia del sistema.

---

## Enunciado del Problema

El entorno se define como una mesa redonda con un grupo de filósofos y un número igual de tenedores. Las reglas del problema son las siguientes:

1. Los filósofos solo pueden realizar una acción a la vez: pensar, comer o dormir.
2. Comer requiere tomar simultáneamente los dos tenedores adyacentes.
3. Tras comer, un filósofo debe dejar ambos tenedores antes de dormir y luego pensar.
4. La simulación finaliza si un filósofo muere de inanición (no come durante un tiempo específico).
5. Los filósofos no tienen comunicación entre ellos y no tienen conocimiento del estado de los demás.

El programa debe modelar este sistema respetando las restricciones temporales, evitando condiciones de carrera y asegurando que ningún filósofo quede en inanición.

---

## Problemas Teóricos a Resolver

### 1. **Condiciones de Carrera (*Race Conditions*)**
   - **Descripción:** Se producen cuando múltiples hilos acceden y modifican recursos compartidos de manera simultánea sin sincronización adecuada, generando comportamientos impredecibles.
   - **Solución:** Implementar mecanismos de sincronización como **mutex** para garantizar acceso exclusivo a los recursos compartidos (tenedores).

### 2. **Interbloqueos (*Deadlocks*)**
   - **Descripción:** Ocurren cuando dos o más hilos están bloqueados indefinidamente porque cada uno espera un recurso retenido por otro.
   - **Solución:** Diseñar un protocolo de adquisición de recursos que prevenga el bloqueo circular. Por ejemplo, imponer un orden jerárquico para la toma de los tenedores o implementar un algoritmo de detección y resolución de bloqueos.

### 3. **Inanición (*Starvation*)**
   - **Descripción:** Se da cuando un hilo nunca obtiene acceso a los recursos necesarios debido a la alta prioridad o el monopolio de otros hilos.
   - **Solución:** Garantizar que todos los filósofos tengan acceso periódico a los tenedores mediante una política de planificación justa.

### 4. **Sincronización Temporal**
   - **Descripción:** Es crucial respetar las restricciones temporales del problema, como los tiempos definidos para comer, dormir y el límite máximo de espera antes de morir.
   - **Solución:** Utilizar funciones de temporización precisas como `gettimeofday` y controlar las acciones de los filósofos mediante simulación temporal.

### 5. **Eficiencia en la Simulación**
   - **Descripción:** La simulación debe ser eficiente y manejar múltiples hilos sin generar sobrecarga innecesaria en el sistema.
   - **Solución:** Optimizar el uso de hilos y mutex para minimizar el tiempo de espera y evitar bloqueos innecesarios.

---

## Soluciones Técnicas Implementadas

1. **Creación de Hilos**: Cada filósofo se modela como un hilo independiente que interactúa con los recursos compartidos de manera sincronizada.
2. **Uso de Mutex**: Los tenedores se representan mediante mutex, que aseguran el acceso exclusivo a cada recurso durante su uso.
3. **Simulación Temporal**: Se emplean funciones de temporización para simular los estados de los filósofos y garantizar el cumplimiento de las restricciones de tiempo.
4. **Control de Estados**: Cada cambio de estado de los filósofos (tomar un tenedor, comer, dormir, pensar) se registra con marcas de tiempo para asegurar la coherencia y facilitar la depuración.
5. **Gestión de Errores**: El programa verifica y maneja casos como asignación de memoria fallida, parámetros incorrectos o bloqueos inesperados.

---

Este proyecto constituye una introducción práctica a los conceptos de concurrencia y sincronización en programación. A través de su desarrollo, se adquieren competencias clave para diseñar sistemas seguros, eficientes y libres de errores en entornos multi-hilo.

### Fuentes de Consulta

Para obtener una mejor comprensión de los conceptos tratados en este proyecto, puedes consultar la siguiente lista de reproducción:

- [Introducción a la Programación Concurrente - YouTube](https://youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&si=sfnMCYYrlP9N1hbJ)
