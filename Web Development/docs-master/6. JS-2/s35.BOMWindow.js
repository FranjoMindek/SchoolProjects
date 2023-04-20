const newWindow = window.open('https://www.fer.unizg.hr/');

newWindow.blur();
newWindow.focus();

newWindow.moveTo(200, 300);
newWindow.resizeTo(200, 200);

newWindow.close();
