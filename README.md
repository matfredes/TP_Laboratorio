Aclaraciones por conversión automática del README.md al guardar:
-Donde aparezca un \* representa únicamente un asterísco.

Primer Módulo:
Se lee un archivo "novedades.csv" mediante el programa generador el cual contendrá:

> nombre del archivo
> tamaño del archivo (inicializado en 0)
> fecha del archivo (valor aleatorio)
> autor del archivo (valor aleatorio)

Este crea 3 archivos los cuales son:
-"novedades.dat" (bin): posee mismo contenido que "novedades.csv" pero en código binario
-"maestro.csv" (txt):

> nombre del archivo
> status del archivo (incializado con ?)
> primeras 2 lineas de contenido del archivo tratado

-"maestro.dat" (bin): posee mismo contenido que "maestro.csv" pero en código binario

Comentarios sobre el primer módulo:

> El archivo "mitp2.cpp" contiene intencionalmente un campo vacío al principio para ver el funcionamiento del "generador" ante dicha situación. En caso de encontrar las primeras lineas blancas, este recorrera el archivo hasta poder imprimir 2 lineas con contenido.
> Si bien "novedades.csv" está incializado con el tamaño del archivo en 0, al cargarlo a "novedades.dat" se actualiza en valor con el tamaño real del archivo tratado.

Segundo Modulo:

Comentarios sobre el segundo módulo:
(IMPORTANTE: el funcionamiento y o excepciones de los comandos fueron respondidos y definidos en la clase explicativa)

Se utilizaran los archivos binarios novedades.dat y maestro.dat extraídos del primer módulo para, mediante una lista de comandos definidos en la carpeta .properties, realizar acciones de alta(A),baja(D),modificación(M), consulta(?) y error (E).

Los mencionados al ser salida de un comando seran separados en 2 archivos de texto de la siguiente manera:

logger.log:
-A
-D
-M
-?

error.log:
-E

Los comandos del archivo .properties reaccionaran de la siguiente forma:

add: Primero se revisan el archivo maestro.dat,novedades.dat y nuestros comandos anteriores para corroborar que el archivo destinado a ser agregado, no esté ya agregado a mi repositorio local. En caso de realizar el comando exitosamente se guardará en logger.log "A \t archivo", de lo contrario se guardará en error.log como "E \t archivo".

del: Primero se revisan el archivo maestro.dat,novedades.dat y nuestros comandos anteriores para corroborar que el archivo destinado a ser borrado exista en mi repositorio, de ser así procederé a borrarlo. En caso de realizar el comando exitosamente se guardará en logger.log "D \t archivo", de lo contrario se guardará en error.log como "E \t archivo".

status: Mediante dicho comando se imprimirá en consola los estados,modificaciones,etc realizados hasta el momento en logger.log y a su vez se guardará en logger.log "? \t archivo", en caso de usar este comando sobre un archivo no presente en logger.log, se guardará en error.log "E \t archivo" y avisará en consola que no se halló el archivo

diff: Mediante dicho comando se imprimirán en consola las diferencias entre las propiedades de cada archivo y se guardará en logger.log como "? \t archivo1 \t archivo2", en caso de dar error imprimirá en pantalla y guardará en error.log como "E \t archivo1 \t archivo2"

revert: Mediante dicho comando se guardará en logger.log "M \t archivo" de existir el mismo en el repositorio, de no encontrarse imprimirá en consola un aviso y se guardará en error.log "E \t archivo"

info: Mediante dicho comando se imprimirá en consola "información detallada" del archivo (maestro.dat) y se guardará en logger.log como "? \t archivo", en caso de ser error se guardará en error.log "E \t archivo"

blame: Mediante dicho comando se imprimirá en pantalla el autor del archivo y lo guardará en logger.log como "? \t archivo", en caso contrario avisará por consola y guardará en error.log "E \t archivo"

cat: Mediante dicho comando se imprimirá en consola el contenido del archivo tratado y guardará en logger.log como "? \t archivo", o avisará que no lo contiene y guardará en error.log "E \t archivo". De ser un error avisará en consola y guardará en error.log "E \t archivo"

propget: Mediante dicho comando se imprimirá en consola el contenido de la propiedad elegida y se guardará en logger.log como "? \t archivo". En caso de error avisará y guardará en error.log "E \t
archivo"

propset: Mediante dicho comando se modificará/cargará la propiedad de un archivo seleccionado y se imprimirá por pantalla, junto con un guardado en logger.log "M \t archivo".En caso de error se avisará y guardará en error.log "E \t archivo"
