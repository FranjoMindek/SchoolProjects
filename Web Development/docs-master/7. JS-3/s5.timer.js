let timerFunction = () => {
    setTimeout(() => {
      console.log('Asynchronous code execution start after 5 sec');
    }, 5000);
  };
console.log('Before timerFunction call');
timerFunction();
console.log('After timerFunction call');
  