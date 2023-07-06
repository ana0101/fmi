window.onload = nume_jucator;

function nume_jucator() {
    var nume = prompt("Numele vostru: ");
    document.querySelector(".message").innerHTML += " " + nume;
    start_joc(nume);
}

function start_joc(nume, nrIncercari) {
    var nr = Math.floor(Math.random() * 20) + 1;
    alert(nr);
    var buton = document.getElementById("check");
    buton.onclick = function() {verificare(nr, nume);}
}

function verificare(nr, nume) {
    var nr2 = document.getElementById("guess").value;
    if(parseInt(document.getElementsByClassName("score")[0].innerHTML) > 1) {
        if (parseInt(nr2) == nr) {
            document.querySelector("body").style.backgroundColor = "red";
            document.querySelector(".message").innerHTML = "Ati ghicit numarul!";
            document.querySelector(".number").innerHTML = nr;
            var para = document.createElement("p");
            document.getElementById("jucatori").appendChild(para);
            para.innerHTML = "Jucatorul " + nume + " a castigat jocul cu scorul " + document.querySelector(".score").innerHTML;
        }
        else {
            if (parseInt(nr2) < nr) {
                document.querySelector(".message").innerHTML = "Numarul este prea mic, mai incercati!";
            }
            else {
                document.querySelector(".message").innerHTML = "Numarul este prea mare, mai incercati!";
            }
    
            document.querySelector(".score").innerHTML = parseInt(document.querySelector(".score").innerHTML) - 1;
            document.querySelector(".hightscore").innerHTML = parseInt(document.querySelector(".hightscore").innerHTML) + 1;
        }
    }
    else {
        document.querySelector(".message").innerHTML = "Ati pierdut jocul!";
        document.getElementById("check").disabled = true;
    }
}