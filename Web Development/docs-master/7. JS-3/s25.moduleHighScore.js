//IMPORTANT: Run example with LiveServer - install from extensions
//High Score access and storage
export class HighScoreManager {
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
