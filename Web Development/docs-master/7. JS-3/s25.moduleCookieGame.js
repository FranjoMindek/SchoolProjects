//IMPORTANT: Run example with LiveServer - install from extensions
import { HighScoreManager } from './s25.moduleHighScore.js';
import { Utils } from './s25.moduleUtils.js';

//The main class for the CookieClicker game v1
export class CookieGame {
  gameStarted = false;
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
    this.gameStarted = true;
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
    if (!this.gameStarted) {
      return
    }
    this.gameStarted = false;
    let timer = duration;
    this.updateTimerUI(Utils.formatTime(timer));
    clearInterval(this.gameIntervalTimer);
    this.cookieCount = 0;
    this.resetGameUI();
  }
}
