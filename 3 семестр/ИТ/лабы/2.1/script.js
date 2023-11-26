function imageSwap(){
    var firstPic = document.getElementById("first");
        secondPic = document.getElementById("second");
        firstSrc = firstPic.src;
        secondSrc = secondPic.src;
        firstPic.src = secondSrc;
        secondPic.src = firstSrc;
}