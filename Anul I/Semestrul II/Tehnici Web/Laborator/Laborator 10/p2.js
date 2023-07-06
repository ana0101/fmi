var express = require("express");
var app = express();
app.use(express.static(__dirname));
app.use(express.urlencoded({extended:true}));

app.post("/p2", function(req, res) {
    var dictionar = [
        { cuvant: "carte", engleza: "book", franceza: "livre" },
        { cuvant: "floare", engleza: "flower", franceza: "fleur" },
        { cuvant: "tablou", engleza: "picture", franceza: "photo" },
        { cuvant: "film", engleza: "movie", franceza: "film" }];

    var cuv = req.body.cuvant;
    var limba = req.body.limba;

    var traducere = "Nu exista";
    for (let d of dictionar) {
        if (d.cuvant == cuv) {
            traducere = d[limba];
        }
    }

    res.send(traducere);
});

app.listen(4000, function() {
    console.log("a pornit");
});