window.onload = f;

function f() {
    for (var i = 0; i < 10; i ++) {
        var d = document.createElement("div");
        d.classList.add("dreptunghi");
        document.body.appendChild(d);
    }

    var elem = document.querySelectorAll("div");

    var inalt = [0,0,0,0,0,0,0,0,0,0];
    for (let i = 0; i < 10; i ++) {
        inalt[i] = parseInt(getComputedStyle(elem[i]).height);
    }
    
    for (let i = 0; i < 10; i ++) {
        elem[i].onclick = function() {
            var h = parseInt(getComputedStyle(elem[i]).height) + 10;
            var h1 = h + "px";
            elem[i].style.height = h + "px";
        }
    }

    document.querySelector("body").onclick = function(event) {
        if (event.target.tagName != "DIV") {
            for (let i = 0; i < 10; i ++) {
                elem[i].style.height = inalt[i] + "px";
            }
        }
    }
}