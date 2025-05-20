import wollok.vm.*
object pepita {
  var energia = 100

  method comer(comida) {
    energia += comida.energia()
  }
  method estaCansada() = energia < 40 
}

object comida {
    const valorEnergetico = 10
    method energia() = valorEnergetico
    
}