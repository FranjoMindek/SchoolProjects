//Utility methods
class Utils {
    //Method to generate and store (to local  storagE) dummy highscore data
    static setDummyHighscores() {
      if (!localStorage.getItem("highscores")) {
        let dummyHighscores = [{highscore: 50, username: "Mate"}, {highscore: 30, username: "Ivo"}, {highscore: 20, username: "Ivan"}];
        localStorage.setItem("highscores", JSON.stringify(dummyHighscores));
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

//High Score access and storage
class HighScoreManager {
  static getHighScores() {
    const highscores = localStorage.getItem("highscores");
    if (!highscores) {
      throw new Error("Highscores not set!")
    }
    return JSON.parse(highscores);
  }
  //Add new score for user (and remove old one), and sort the scores for the list
  static updateHighScore(score, user) {
    const highscores = HighScoreManager.getHighScores();
    let foundEntry = highscores.findIndex(oneEntry => oneEntry.username == user);
    if(foundEntry != -1){  highscores.splice(foundEntry, 1)};
    highscores.push({ highscore: score, username: user });
    highscores.sort(function(a,b) {return b.highscore - a.highscore});
    localStorage.setItem("highscores", JSON.stringify(highscores));
  }
}

//The main class for the CookieClicker game v1
class CookieGame {
  cookieCount = 0;
  gameIntervalTimer = null;
  updateTimerUI = null;
  updateHighScoreListUI = null;
  resetGameUI = null;
  //Constructor received methods that will be triggered to update UI 
  constructor(updateTimerUI, updateHighScoreListUI, resetGameUI){
    this.updateTimerUI = updateTimerUI;
    this.updateHighScoreListUI = updateHighScoreListUI;
    this.resetGameUI = resetGameUI;
  }
  //Starts the game and initiates the countdown timer (1 sec)
  startGame(duration) {
    let countdownDuration = duration;
    this.updateTimerUI(Utils.formatTime(countdownDuration));
    this.cookieCount = 0;
    //Defines the main timer for 1 second countdown
    this.gameIntervalTimer = setInterval(() => {
      countdownDuration--;
      if (countdownDuration < 0) {
        const username = prompt(`Your score was: ${this.cookieCount}. Please enter your username.`);
        countdownDuration = duration;
        HighScoreManager.updateHighScore(this.cookieCount, username);
        this.updateHighScoreListUI();
        this.resetGame(duration);
      }
      this.updateTimerUI(Utils.formatTime(countdownDuration));
    }, 1000);
  }
  //Resets game to the initial state
  resetGame(duration) {
    if (!gameStarted) {
      return
    }
    let timer = duration;
    this.updateTimerUI(Utils.formatTime(timer));
    clearInterval(this.gameIntervalTimer);
    this.cookieCount = 0;
    this.resetGameUI();
  }
}

function updateHighScoreListUI() {
  let highscoreList = document.querySelector(".highscore--list");
  if (!highscoreList) {
    throw new Error("Cannot find highscore list!");
  }
  // Clears the list
  while(highscoreList.firstChild) {
    highscoreList.firstChild.remove();
  }
  const highscores = HighScoreManager.getHighScores();
  highscores.forEach(score => {
    let listItem = document.createElement("li");
    listItem.textContent = `${score.username}: ${score.highscore}`;
    highscoreList.appendChild(listItem);
  });
}

function resetGameUI() {
  gameStarted = false;
  cookieCountDisplay.textContent = 0;
  btnStart.textContent = "START";
}

let cookie = document.getElementById("img--cookie");
let cookieCountDisplay = document.querySelector("#click-count");
let btnStart = document.querySelector(".btn--start");
let timer = document.getElementById('timer');

let gameStarted = false;

if (!cookie || !cookieCountDisplay || !btnStart || !timer) {
  alert("A critical error occured. UI was not loaded!");
} else {
  Utils.setDummyHighscores();
  const cookieGame = new CookieGame(
    (timeString) => timer.innerText = timeString, 
    updateHighScoreListUI, 
    resetGameUI);

  cookie.onclick = () => {
    cookieCountDisplay.textContent = ++cookieGame.cookieCount;
  };
  btnStart.onclick = () => {
    const tenSeconds = 10;
    if (!gameStarted) {
      cookieGame.startGame(tenSeconds);        
      btnStart.textContent = "RESET";
      gameStarted = true;
      cookieCountDisplay.textContent = 0;
    } else {
      cookieGame.resetGame(tenSeconds);
    }
  };
  updateHighScoreListUI();
}
