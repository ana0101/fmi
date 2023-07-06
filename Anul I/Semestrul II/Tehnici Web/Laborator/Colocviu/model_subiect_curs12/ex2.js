window.onload = function() {
    const n = Math.floor(Math.random() * (11 - 5) + 5);
    // alert(n);
    for (let i = 0; i < n; i++) {
        var div = document.createElement("div");
        div.classList.add("patrat");
        document.body.appendChild(div);
    }

    var divs = document.querySelectorAll("div");
    for (let i = 0; i < divs.length; i++) {
        divs[i].onclick = function(event) {
            var st = divs[i].offsetLeft;
            divs[i].style.position = "relative"; 
            divs[i].style.left = (st + 10) + "px";
            event.stopPropagation();
        }
    }

    document.body.onclick = function(event) {
        var clickX = event.clientX;
        var clickY = event.clientY;

        const rand = Math.floor(Math.random() * (11 - 5) + 5);
        divs[rand].style.position = "absolute";
        divs[rand].style.left = clickX + "px";
        divs[rand].style.top = clickY + "px";
    }
}
