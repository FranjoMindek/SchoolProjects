//IMPORTANT: Run example with LiveServer - install from extensions
import { CookieGame } from './s25.moduleCookieGame.js';
import { HighScoreManager } from './s25.moduleHighScore.js';
import { Utils } from './s25.moduleUtils.js';

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
  cookieCountDisplay.textContent = 0;
  btnStart.textContent = "START";
}

let cookie = document.getElementById("img--cookie");
let cookieCountDisplay = document.querySelector("#click-count");
let btnStart = document.querySelector(".btn--start");
let timer = document.getElementById('timer');

if (!cookie || !cookieCountDisplay || !btnStart || !timer) {
  alert("A critical error occured. UI was not loaded!");
} else {
  Utils.setDummyHighscores()
  .then(() => {
    const cookieGame = new CookieGame(
      (timeString) => timer.innerText = timeString, 
      updateHighScoreListUI, 
      resetGameUI);
  
    cookie.onclick = () => {
      cookieCountDisplay.textContent = ++cookieGame.cookieCount;
    };
    btnStart.onclick = () => {
      const tenSeconds = 10;
      if (!cookieGame.gameStarted) {
        cookieGame.startGame(tenSeconds);        
        btnStart.textContent = "RESET";
        cookieCountDisplay.textContent = 0;
      } else {
        cookieGame.resetGame(tenSeconds);
      }
    };
    updateHighScoreListUI();
  })
  .catch(err => {
    console.log("Cannot load dummy highscores JSON file!");
    throw err;
  });
}
