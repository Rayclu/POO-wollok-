import  wollok.lang.Exception



class Animals{
    var property thirst = 0
    var property isVaccinated = false
    var property mustGetSick = false
    var property energy = 100
    var property weight = 0
    method isThirsty() = thirst > 0
    method isSick() = not isVaccinated and mustGetSick

    method isHungry() = self.weight() < 400

    method vaccinate(){
        isVaccinated = true
    }
    method eat(c){
        self.weight(self.weight()+c)

    }
    method walk(d) {
        self.energy(self.energy()-d)
    }
    method drink(liters) {
        self.thirst(self.thirst()-liters)
    }
}


class Cow inherits Animals(
    weight = 50, energy = 10
){
    override method eat(c){
        super(c/2)
        thirst += 1
    }
    override method walk(d) {
        super(3*d)
    }
    override method drink(liters){
        super(liters)
        thirst = 0
        self.isThirsty()

    }
}
class PepaPig inherits Animals(
    weight = 40
) {
  override method isHungry() = weight < 200
}



class VaccinateException inherits wollok.lang.Exception {}
class Chicken inherits Animals(
    weight = 4, energy = 1, thirst = false, isVaccinated = false, mustGetSick = false
){
    override method eat(c){
        super(0)
    }
    override method isHungry() = true
    override method isThirsty() = false
    override method vaccinate(){
        try{
            throw new VaccinateException()
        }catch e : VaccinateException{
            console.println("Es una gallina, no se la puede vacunar")
        }
    }


}

const cow = new Cow()
const pepa = new PepaPig()
const chicken = new Chicken()
