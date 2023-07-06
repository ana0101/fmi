function f1() {
    var carti = [{titlu: "Matilda", pagini: 256}, {titlu: "Little Women", pagini: 569}, {titlu: "Hobbit", pagini:300},
        {titlu: "Mandrie si prejudecata", pagini: 450}, {titlu: "Muntele vrajit", pagini: 150}];
    var n = prompt("Introduceti un numar");

    var v = [];
    for (var c of carti) {
        if (c.pagini >= parseInt(n))
            v.push(c.titlu);
    }
    alert(v + "\nnr: " + v.length);
}

function f2() {
    var citate = ["Citat 0", "Citat 1", "Citat 2", "Citat 3", "Citat 4"];
    var nr = Math.floor(Math.random() * 5);
    var ob = document.getElementById("citat");
    ob.innerHTML = citate[nr];
}

function f3() {
    var nume = prompt("Introduceti un nume");
    var ob = document.getElementById("bine_ati_venit");
    ob.innerHTML = "Bine ati venit " + nume.toUpperCase() + "!";
}

function f4() {
    var imagini = document.querySelectorAll("#container_galerie img");
    for (imagine of imagini) {
        imagine.src = "https://cdn4.libris.ro/img/pozeprod/59/1002/D5/25875927.jpg";
        imagine.alt = "carte interesanta";
    }
}

function f5() {
    var figcap = document.querySelectorAll("#container_galerie figcaption");
    for (var i = 0; i < figcap.length; i++)
        figcap[i].innerHTML = "Figura " + String(i);
}

function f6() {
    var paragrafe = document.querySelectorAll("p");
    for (p of paragrafe)
        p.innerHTML = p.innerHTML.toUpperCase();
}

function adauga(info) {
    var articole = document.querySelectorAll("article");
    for (art of articole) {
        var para = document.createElement("p");
        para.innerHTML = info;
        para.className = "stil";
        art.appendChild(para);
    }
}

adauga("info");