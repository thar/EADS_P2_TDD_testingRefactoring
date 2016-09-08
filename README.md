AnalizadorNoticiasLinux
===================


Práctica de TDD del curso EADS

----------


Compilación y testing
-------------

- El código de la práctica está escrito en c++.
- Los tests de la práctica están programados haciendo uso de las herramientas de google google-test.
- La compilación hace uso de CMake.
- La dependencia de google-test se obtiene automáticamente desde el repositorio de git de google-test, por lo que en el momento de la primera compilación será necesario que el PC pueda acceder a dicho repositorio.
> **Nota:**
> La versión mínima de CMake que permite compilar es la 3.5. Es posible que otras versiones puedan compilar el programa, pero habría que modificar el contenido de los CMakeLists.txt


####  compile.sh

El script **compile.sh** lanza la compilación del proyecto completo, dejando los resultados de la compilación en la carpeta **build**

####  test.sh

El script **test.sh** entra en la carpeta **build/tests/** y lanza el binario **AnalizadorTests** que lanza todos los unit tests de la aplicación.
Los resultados en formato XML de la ejecución de los tests quedan en el fichero **build/tests/XML_Report.xml**
> **Nota:**
> Antes de lanzar este script es necesario que se haya ejecutado el script **compile.sh**

####  compileAndTest.sh

El script **compileAndTest.sh** lanza de forma sucesiva los scripts **compile.sh** y **test.sh**

### Compilar y testear con Docker
Para simplificar la compilación y ejecución de los tests se ha preparado una imagen Docker.
La imagen Docker está disponible en el [Docker hub](https://hub.docker.com/r/thar/cmake-compiler-alpine) y es creada con el Dockerfile del repositorio de git [cmake-compiler-alpine](https://github.com/thar/cmake-compiler-alpine).
Para lanzar la compilación y los tests hay que ejecutar el siguiente comando desde la carpeta del proyecto.
```
docker run -v $PWD:/app/ thar/cmake-compiler-alpine ./compileAndTest.sh
```

