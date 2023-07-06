var express = require("express");
var app = express();
var formidable = require("formidable");
var fs = require("fs");
app.use(express.static(__dirname));
app.use(express.urlencoded({extended:true}));
app.set('view engine', 'ejs');

app.post("/app", function(req, res) {
    var ob;
    if (fs.existsSync("produse.json")) {
        var date = fs.readFileSync("produse.json");
        ob = JSON.parse(date);
    }
    else
        ob = [];

    var form = new formidable.IncomingForm({uploadDir: "poze", keepExtensions: true});  
    var ob_form = {'nume':fields.nume,'cv':files.cv.path,'poza':files.poza.path};
    ob.push(ob_form);
    fs.writeFileSync("persoane.json",JSON.stringify(ob));});
    res.send("Salvat:");
});

app.listen(1000, function() {
    console.log("a pornit");
});