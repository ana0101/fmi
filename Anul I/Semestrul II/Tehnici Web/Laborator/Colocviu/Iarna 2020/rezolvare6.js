window.onload = function() {
    var para = document.querySelectorAll("div+p");
    for (let p of para) {
        var bs = p.querySelectorAll("b");
        for (let b of bs) {
            var text = b.innerHTML;
            text = text.split('').reverse().join('');
            b.innerHTML = text;
        }
    }
}

window.onload = function()
{
	var elemente = document.querySelectorAll("div+p")
	for(let el of elemente)
	{
		var x = el.querySelectorAll("b");
		for(i of x) 
		{
			var text = i.innerHTML;
			var invers = " ";
			for(k=text.length-1; k>=0; k--) invers+=text[k];
			var t = document.createTextNode(invers);
			el.appendChild(t);
		}
	}
}