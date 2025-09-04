import  wollok.lang.Exception

class VaccinateException inherits wollok.lang.Exception {}


class Animals{
    var property farm = []
    var property thirst = 0
    var property isVaccinated = false
    var property mustGetSick = false
    var property energy = 100
    var property weight = 0
    var XeY = [0,0] 

    method isThirsty() = thirst > 0

    method isSick() = not isVaccinated and mustGetSick

    method isHungry() = self.weight() < 400

    method vaccinate(){
        isVaccinated = true
        return
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

    method appear() {
        var partner = []
        const getCandidate = { => self.farm()[0.randomUpTo(self.farm().length())].times(2)}
        partner = getCandidate()
        if(partner[0].kindName() == partner[1].kindName()){
            return 1
        }

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
        weight-=1
        thirst = 0
        self.isThirsty()
    }
    override method vaccinate() {
        try{
            if(!isVaccinated){
                isVaccinated = true
                return
            }
            throw new VaccinateException()
        }catch e : VaccinateException{
            console.println("Err: La vaca ya está vacunada. No se ha podido vacunar")
        }


    }
}
class PepaPig inherits Animals(
    weight = 50
) {
  override method eat(){}
  override method isHungry() = weight < 200

}



class Chicken inherits Animals(
    weight = 4, energy = 1, thirst = false, isVaccinated = false, mustGetSick = false
){
    override method eat(c){
        super(c)
    }
    override method isHungry() = true
    override method isThirsty() = false
    override method vaccinate(){
        try{
            throw new VaccinateException()
            return
        }catch e : VaccinateException{
            console.println("Es una gallina, no se la puede vacunar")
        }
    }


}

const cow = new Cow()
const pepa = new PepaPig()
const chicken = new Chicken()


/*
Enfermar
AdministrarAnimales
Morir
x y*/