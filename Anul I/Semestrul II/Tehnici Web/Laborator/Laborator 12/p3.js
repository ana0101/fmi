window.onload = function() {
    var nr_apasare = 0;
    var nr_sterse = 0;

    document.onkeydown = function(event) {
        if (event.key == 's' && nr_apasare == 0) {
            nr_apasare ++;
            var nr = document.getElementById("numar").value;
            var para = document.getElementsByTagName("p");

            setInterval(function() {
                var ok = 0;
                for (let i = 0; i < para.length && ok == 0; i ++) {
                    var nr_cuv = para[i].innerHTML.split(' ').length;
                    if (nr_cuv > nr) {
                        ok = 1;
                        para[i].remove();
                        nr_sterse ++;
                        localStorage.setItem("sterse", JSON.stringify(nr_sterse));
                    }
                }
            }, 1000);
        }
    }
}