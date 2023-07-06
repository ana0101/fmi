var express = require("express");
var app = express();
app.use(express.static(__dirname));
app.use(express.urlencoded({extended:true}));

app.post("/p4", function(req, res) {
    var orase=[ { nume:"Aa", populatie:14000, capitala:true }, 
     { nume:"Bb", populatie:7000, capitala:false },
     { nume:"Cc", populatie:19000, capitala:false }, 
     { nume:"Dd", populatie:5000, capitala:false }, 
     { nume:"Ee", populatie:8000, capitala:true }, 
     { nume:"Ff", populatie:12000, capitala:false }, 
     { nume:"Gg", populatie:20000, capitala:true } ];

    var marime = req.body.marime;
    var capit = req.body.capit;
    console.log(marime);
    console.log(capit);

    res.write("<html><body><ol>");

    for (let o of orase) {
        if (marime == 'mic') {
            if (o.populatie < 10000) {
                if (capit == 'capitala') {
                    if (o.capitala == true) {
                        res.write("<li>" + o.nume + "</li>");
                    }
                }
                else {
                    if (o.capitala == false) {
                        res.write("<li>" + o.nume + "</li>");
                    }
                }
            }
        }
        else {
            if (o.populatie > 10000) {
                if (capit == 'capitala') {
                    if (o.capitala == true) {
                        res.write("<li>" + o.nume + "</li>");
                    }
                }
                else {
                    if (o.capitala == false) {
                        res.write("<li>" + o.nume + "</li>");
                    }
                }
            }
        }
    }

    res.write("</ol></body></html>");
    res.end();
});

app.listen(4000, function() {
    console.log("a pornit");
});