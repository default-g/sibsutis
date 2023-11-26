let delay = 300;
i = 1;
timer = null;

function animate(){
        document.getElementById('santa').src = 's' + i + '.gif';
        i++;
        if(i > 12) i = 1;
} 

function santaStart() {
    if(!timer){
    timer = setInterval('animate();', delay);
    }
}

function santaStop() {
    clearTimeout(timer);
    timer = null;
}

function speedDown(){
    delay = delay + 100;
    santaStop();
    santaStart();
}

function speedUp(){
    delay = delay - 100;
    if(delay < 100) delay = 100;
    santaStop();
    santaStart();
}

