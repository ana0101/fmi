window.onload = imagini;

function imagini() {
    window.setTimeout(over, 20000); 
    for (var i = 0; i < 20; i++) {
        var imagine = document.createElement("img");
        imagine.src = "sad.png";
        document.getElementById("container").appendChild(imagine);
        imagine.onclick = schimbare;
    }
    document.querySelector("#game p").style.visibility = "visible";
}

function schimbare() {
    if (this.src.slice(-7) == "sad.png") {
        this.src = "happy.png";
        document.getElementById("scor").innerHTML = parseInt(document.getElementById("scor").innerHTML) + 1;
    }
}

function over() {
    document.querySelector("h1").innerHTML = "Jocul s-a terminat!";
    document.getElementById("container").remove();
}