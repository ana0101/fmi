var express = require("express");
var app = express();
var fs = require("fs");
app.use(express.static(__dirname));
app.use(express.urlencoded({extended:true}));

app.post("/p3", function(req, res) {
    var tip = req.body.tip;
    var cuv = req.body.cuvant;
    console.log(tip + " " + cuv);
    fs.readFile("persoane.json", function(err, date) {
        if (err)
            throw err;
        var persoane = JSON.parse(date);
        res.write("<html><body><ol>");
        for (var p of persoane) {
            if (p[tip] == cuv) {
                res.write("<li>" + p.nume + " " + p.prenume + "</li>");
            }
        }
        res.write("</ol></body></html>");
        res.end();
    })
});

app.listen(4000, function() {
    console.log("a pornit");
});