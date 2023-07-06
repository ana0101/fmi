window.onload = function f() {
    document.getElementById("rng").onchange = function f1() {
        var nr = document.getElementById("rng").value;
        // alert(nr);

        var divs = document.querySelectorAll("div");
        for (let i = 0; i < divs.length; i ++) {
            if (divs[i].innerHTML == nr) {
                divs[i].style.border = "2px solid green";
            }
        }
    }
}

// window.onload = function()
// {
// 	document.getElementById("rng").onchange = function()
// 	{
// 		x = this.value;
// 		elemente = document.getElementsByTagName("div");
// 		for(el of elemente)
// 			if(el.innerHTML==x) 
// 			{
// 				el.style.border = "solid green 2px";
// 			}
// 	}
// }