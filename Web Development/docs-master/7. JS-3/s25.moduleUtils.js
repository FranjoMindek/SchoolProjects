//IMPORTANT: Run example with LiveServer - install from extensions
//Utility methods
export class Utils {
    //Method to generate and store (to local  storagE) dummy highscore data
    static async setDummyHighscores() {
      if (!localStorage.getItem("highscores")) {
        let highScorePromise = await fetch("s25.initialHighScores.json");
        if (!highScorePromise.ok) { throw new Error("Cannot load json file"); } 
        else { var jsonContents = await highScorePromise.json();}        
        localStorage.setItem("highscores", JSON.stringify(jsonContents));
      }
    }    
    //Time string formatting helper methods
    static formatTwoDigits(number) {
      return number < 10 ? "0" + number : number;
    }
    static formatTime(time) {
      const minutes = Utils.formatTwoDigits(parseInt(time / 60, 10));
      const seconds = Utils.formatTwoDigits(parseInt(time % 60, 10));
      return minutes + ":" + seconds;
  }
}

