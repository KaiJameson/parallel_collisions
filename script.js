let canvas = null;
let context = null;
let prevTime = null;
let sats = null;

let file = null;
let reader = null;

const delay = ms => new Promise(res => setTimeout(res, ms));

function initialize(input) {
    let file = input.files[0];
    let reader = new FileReader();
    reader.readAsText(file);
    reader.onload = function() {
        sats = JSON.parse(reader.result);
        sats = sats.sats;
        run();
    }
}

const run = async() => {
    canvas = document.getElementById('canvas');
    context = canvas.getContext('2d');
    
    prevTime = performance.now();
	
    // draw the sats
    for (let i = 0; i < sats.length; i++) {
        await delay(500);
        let cycle = sats[i];

        // clear canvas and draw earth
        context.clearRect(0, 0, canvas.width, canvas.height);
        context.beginPath();
        context.arc(500, 500, 60, 0, 2*Math.PI);

        // draw all satellites
        for (let j = 0; j < cycle.length; ++j) {
            let sat = cycle[j];
            let x = sat[0] + 500;
            x += (sat[0] < 0 ? -60 : 60);
            let y = sat[1] + 500;
            y += (sat[1] < 0 ? -60 : 60);
            let r = sat[2]/5;
            context.moveTo(x+r, y);
            context.arc(x, y, r, 0, 2*Math.PI);
        }
        context.lineWidth = 1;
        context.stroke();
    }
    //context.strokeStyle = 'rgb(255, 255, 255)';
}
