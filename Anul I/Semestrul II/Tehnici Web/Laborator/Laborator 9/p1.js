window.onload = f;

function f() {
    var x = document.getElementById("i1");
    var y = document.getElementById("i2");
    var s = document.getElementById("op");
    var div = document.getElementById("operatii");

    s.onchange = function() {
        var r;
        if (s.value == '+') {
            r = parseInt(x.value) + parseInt(y.value);
        }
        if (s.value == '-') {
            r = parseInt(x.value) - parseInt(y.value);
        }
        if (s.value == '*') {
            r = parseInt(x.value) * parseInt(y.value);
        }

        var para = document.createElement("p");
        para.innerHTML = x.value + ' ' + s.value + ' ' + y.value + ' = ' + r;
        div.appendChild(para);
    }
}