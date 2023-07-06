var express = require("express");
var app = express();
app.use(express.static(__dirname));
app.use(express.urlencoded({extended:true}));

app.post("/p4", function(req, res) {
    var persoane=[
    {nume:"Ion", sex:"m", varsta:3},
    {nume:"Oana", sex:"f", varsta:23},
    {nume:"Daria",sex:"f", varsta:10}, 
    {nume:"Mihai", sex:"m", varsta:19}, 
    {nume:"Gabriel", sex:"m", varsta:22}, 
    {nume:"Simona", sex:"f", varsta:11}, 
    {nume:"Bogdan", sex:"m", varsta:28}];

    var nume = req.body.nume;
    var mesaj = "Nu exista numele cautat";

    for (let p of persoane) {
        if (p.nume == nume) {
            if (p.sex == "f") {
                mesaj = "fata, ";
            }
            else {
                mesaj = "baiat, ";
            }

            if (p.varsta < 18) {
                mesaj = mesaj + "e minor";
            }
            else {
                mesaj = mesaj + "nu e minor";
            }
        }
    }

    res.write("<html><body><h3>");
    res.write(mesaj);
    res.write("</h3></body></html>");
    res.end();
});

app.listen(4000, function() {
    console.log("a pornit");
});