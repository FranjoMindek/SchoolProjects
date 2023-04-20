class Person{
    constructor(name, hasCovid, isVaccinated) {
        this.name = name;
        this.hasCovid = hasCovid;
        this.isVaccinated = isVaccinated;
    }
}

class Doctor extends Person{
    constructor(name, hasCovid, isVaccinated, canVaccinate) {
        super(name, hasCovid, isVaccinated);
        this.canVaccinate = canVaccinate;
    }
}

class Patient extends Person{
    constructor(name, hasCovid, isVaccinated, hasAllergy){
        super(name, hasCovid, isVaccinated);
        this.hasAllergy = hasAllergy;
    }
    vaccinate(){
        if(this.hasCovid)
            throw new Error("Covid detected! Abort process!");
        if(this.isVaccinated || this.hasAllergy)
            return false;
        this.isVaccinated = true;
        return true;
    }
}

let patients = [
    new Patient("Iva", false, false, false),
    new Patient("Ana", false, false, true),
    new Patient("Jure", true, false, false)
];

let doctors = [
    new Doctor("Dr. Kuća", false, true, true),
    new Doctor("Dr. Neboder", false, false, false)
];

function vaccinateAll(){
    for(patient of patients){
        for(doctor of doctors){
            //console.log(doctor);
            if(doctor.canVaccinate && !doctor.hasCovid)
            try
            {
                let result = patient.vaccinate();
                if(result)
                    console.log("Patient: " + patient.name + " is vaccinated now!");
            }
            catch(err){
                //TODO Implement emergency process for Covid....
            }
        }
    }
}

vaccinateAll();