window.onload = f;

function f() {
    var par = document.querySelectorAll("p");

    if (localStorage != null) {
        alert(localStorage.getItem("index"));
        for (let i = 0; i < par.length; i ++) {
            if (JSON.stringify(i) != localStorage.getItem("index"))
                par[i].style.color = "black";
        }
    }
    else {
        localStorage.clear();
    }

    for (let i = 0; i < par.length; i ++) {
        par[i].onclick = function() {
            this.style.color = "red";
            localStorage.setItem("index", JSON.stringify(i));
        }
    }
}