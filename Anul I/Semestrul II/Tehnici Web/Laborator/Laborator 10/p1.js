var express = require("express");
var app = express();
app.use(express.static(__dirname));
app.use(express.urlencoded({extended:true}));

app.get("/p1", function(req, res) {
    var nota1 = parseInt(req.query.nota1);
    var nota2 = parseInt(req.query.nota2);
    var nume = req.query.nume;
    var medie = (nota1 + nota2) / 2;
    var mesaj = "Studentul " + nume + " a avut media " + medie;
    res.send(mesaj);
});

app.post("/p1", function(req, res) {
    res.send(req.body);
});

app.listen(3000, function() {
    console.log("a pornit");
});