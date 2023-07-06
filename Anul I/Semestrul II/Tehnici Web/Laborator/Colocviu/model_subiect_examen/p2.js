window.onload = function() {
    const data = new Date();
    let minutes = data.getMinutes();
    var n = Math.max(10, minutes);

    var clase = ["c1", "c2", "c3", "c4", "c5"];

    for (let i = 0; i < n; i ++) {
        var p = document.createElement("p");
        p.innerHTML = "Anamaria";
        var rand = Math.floor(Math.random() * (6 - 1) + 1);
        p.classList.add(clase[rand]);
        document.body.appendChild(p);
    }

    var para = document.querySelectorAll("p");
    for (let i = 0; i < para.length; i ++) {
        para[i].onclick = function(event) {
            let clasa = para[i].className;
            for (let j = 0; j < para.length; j ++) {
                if (i != j && clasa == para[j].className) {
                    para[j].style.display = "none";
                }
            }
            event.stopPropagation();
        }
    }

    document.onclick = function(event) {
        var clickY = event.clientY;
        alert(clickY);
    }
}