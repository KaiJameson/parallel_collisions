let canvas = null;
let context = null;
let prevTime = null;
let satLocations = null;

function update(elapsedTime) {
	satLocations = [];
	// get location data from file
}

function render(elapsedTime) {
    context.clearRect(0, 0, canvas.width, canvas.height);
	
	// draw earth
	context.beginPath();
	context.arc(500, 500, 60, 0, 2*Math.PI);
	context.stroke();
	
    // draw the sats
    context.beginPath();
    for (let row = 0; row < satLocations.length; row++) {
		
    }
    //context.strokeStyle = 'rgb(255, 255, 255)';
    //context.lineWidth = 6;
}

function gameLoop(time) {
    let elapsedTime = time - prevTime;
    prevTime = time;

    // processInput(elapsedTime);
    update(elapsedTime);
    render(elapsedTime);

    requestAnimationFrame(gameLoop);
}

function initialize() {
    canvas = document.getElementById('canvas');
    context = canvas.getContext('2d');
    // get file with sat data
    
    prevTime = performance.now();
    requestAnimationFrame(gameLoop);
}
