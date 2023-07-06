window.onload = blog;

function blog() {
    var buton = document.querySelector("button");
    buton.onclick = postare;
}

function postare() {
    var t = document.getElementById("titlu").value;
    var c = document.getElementById("post").value;
    var articol = document.createElement("article");
    document.getElementById("postari").appendChild(articol);
    articol.className = "post";

    var titlu = document.createElement("h3");
    titlu.innerHTML = t;
    articol.appendChild(titlu);

    var continut = document.createElement("p");
    continut.innerHTML = c;
    articol.appendChild(continut);

    date = new Date();
    var year = date.getFullYear();
    var month = date.getMonth() + 1;
    var day = date.getDate();
    var dateString = day + '-' + month + '-' + year;
    titlu.innerHTML = titlu.innerHTML + ' ' + dateString;

    articol.ondblclick = function() {
        articol.remove();
    }
}