const fs = require('fs');

class GlobalData {

    constructor(filename) {
        this.filename = filename
        this.data = {}
    }


    initialize(force) {
        
        let unparsed_data;
        try {
            unparsed_data = fs.readFileSync(this.filename)
        } catch(err) {
            console.log('ERROR loading global data: ' + err);
            if(force === true) {
                this.store()
                unparsed_data = "{}"
            }
            else
                throw err;
        }
        
        try {
            this.data = JSON.parse(unparsed_data);
        } catch(err) {
            console.log('ERROR parsing global data: ' + err);
            throw err;
        }
    }

    store() {
        try {
            fs.writeFileSync(this.filename, JSON.stringify(this.data));
        } catch(err) {
            console.log('ERROR saving global data: ' + err);
            throw err;
        }
    }

    get() {
        return this.data;
    }
}

module.exports = GlobalData;