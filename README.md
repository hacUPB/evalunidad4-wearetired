# evalunidad4-wearetired
evalunidad4-wearetired created by GitHub Classroom

## PROBLEMA PRODUCTOR-CONSUMIDOR
### DIVISIÓN ECONÓMICA GUBERNAMENTAL

Se inicializa un buffer en un hilo que creará estructuras de datos asimilando personas con: "nombre", "sexo", "edad" e "ingreso mensual". Este vendría funcionando como el productor.
Se inicializa otro hilo en el que se reciben los datos en un buffer y se comprobaría la información que entrega la "persona"; pueden ocurrir 4 casos:
1. Si el ingreso mensual es mayor a 30.000.000 COP se considera como rango 3.
2. Si el ingreso mensual está entre 10.000.000 COP y 29.999.999 COP se considera como rango 2.
3. Si el ingreso mensual está entre 2.000.000 COP y 9.999.999 COP se considera como rango 1.
4. Si el ingreso mensual es menor a 2.000.000 COP se entrará en proceso de purga: en donde se eliminará toda la información de la "persona".




