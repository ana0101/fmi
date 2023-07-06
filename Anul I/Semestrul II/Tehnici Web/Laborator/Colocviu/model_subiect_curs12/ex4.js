var express = require("express");
var app = express();
app.use(express.static(__dirname));
app.use(express.urlencoded({extended:true}));

app.post("/ex4", function(req, res) {
    var obiecte = [
    {nume:"agenda", greutate:"0.5"}, 
    {nume:"telefon", greutate:"1"}, 
    {nume:"rucsac", greutate:"2.3"}, 
    {nume:"caiet", greutate:"0.8"},
    {nume:"carte", greutate:"1"}, 
    {nume:"tobe", greutate:"4"}];

    var g = req.body.input;
    // console.log(g);
    res.write("<html><ul>")
    for (let o of obiecte) {
        if (o.nume.includes('t') && o.greutate <= g) {
            res.write("<li>" + o.nume + "</li>");
        }
    }
    res.write("</ul></html>");
});

app.listen(4000, function() {
    console.log("a pornit");
});