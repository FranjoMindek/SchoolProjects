const os = require('os');
const moment = require('moment');
const chalk = require('chalk');

const getUserName = () => {
    return os.userInfo().username;
}
const getHostName = () => {
    return os.hostname;
}

const getCurrentTimestamp = () => {
    return moment().format("HH:mm");
}

const fancyLog = (msg) => {
    console.log(
        chalk.bgYellow.blue(getCurrentTimestamp()) +
        ' (' + chalk.blueBright(getUserName()) +
        '@' + chalk.magentaBright(getHostName()) +
        '): ' + chalk.greenBright(msg)
    );
}

module.exports = {
    log: fancyLog
};