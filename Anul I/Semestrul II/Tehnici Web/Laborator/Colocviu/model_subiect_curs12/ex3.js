window.onload = function() {
    if (localStorage.getItem("culoare") != null) {
        document.body.style.backgroundColor = localStorage.getItem("culoare");
    }

    var nr_apasare = 0;
    document.body.addEventListener("keydown", (e) => {
        var ok = 0;
        var nr = e.key;
        for (var i = 0; i < 9; i ++) {
            if (nr == i)
                ok = 1;
        }

        if(ok == 1) {
            var butoane = document.querySelectorAll("button");
            var culoare = document.getElementById("culoare").value;
            localStorage.setItem("culoare", culoare);

            if (parseInt(nr_apasare) % 2 == 0) {
                localStorage.setItem("numar", nr);
                for (let i = 0; i < butoane.length; i ++) {
                    setTimeout(function() {
                        if (parseInt(i) % 2 == nr % 2) {
                            butoane[i].style.backgroundColor = culoare;
                        }
                    }, 500 * i);
                }
            }
            else {
                var numar = localStorage.getItem("numar");
                for (let i = 0; i < butoane.length; i ++) {
                    if (parseInt(i) % 2 != parseInt(numar) % 2) {
                        butoane[i].remove();
                    }
                }
            }

            nr_apasare = nr_apasare + 1;
        }
    });
}