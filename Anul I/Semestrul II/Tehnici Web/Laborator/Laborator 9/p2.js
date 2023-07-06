window.onload = f;

function f() {
    var par = document.getElementById("salut");
    par.onclick = function(){
        par.innerHTML = "Hello!";
        localStorage.setItem("cheie", "Hello");
    }

    if (!localStorage.getItem("cheie")) {
        localStorage.setItem("cheie", "Hello");
    }
    else {
        localStorage.setItem("cheie", localStorage.getItem("cheie") + "o");
        par.innerHTML = localStorage.getItem("cheie") + "!";
    }
}