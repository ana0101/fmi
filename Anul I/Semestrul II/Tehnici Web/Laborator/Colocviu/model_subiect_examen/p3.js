window.onload = function() {
    if (localStorage.getItem("culoare") != null) {
        document.getElementById("data").style.color = localStorage.getItem("culoare");
    }

    var data = new Date();
    document.getElementById("data").value = data;

    var nr = 0;
    var select = document.getElementsByTagName("select")[0];

    var interval = setInterval(function() {
        document.getElementById("data").style.color = select.options[nr].value;
        document.getElementsByTagName("select").value = document.getElementById("data").style.color;
        nr ++;
        if (nr == 3)
            nr = 0;
    }, 3000);

    document.addEventListener("keydown", (e) => {
        if (e.key == 's') {
            clearInterval(interval);
            localStorage.setItem("culoare", document.getElementById("data").style.color);
        }
    });
}
