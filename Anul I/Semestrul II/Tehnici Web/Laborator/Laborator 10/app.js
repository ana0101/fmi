var express = require("express");
var app = express();

app.get("/", function(req, res) {res.send("mesaj de la server")});

app.get(["/abc", "/xyz"], function(req, res) {
    var mesaje = ["mesaj 0", "mesaj 1", "mesaj 2", "mesaj 3"];
    var i = Math.floor(Math.random() * (4 - 0) + 0);
    var mesaj = mesaje[i];
    res.send(mesaj);
});

app.listen(4000, function(){console.log("a pornit server-ul")});