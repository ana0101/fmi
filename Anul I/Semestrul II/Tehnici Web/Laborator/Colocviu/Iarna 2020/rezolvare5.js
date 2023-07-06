// window.onload = function() {
//     document.body.addEventListener("mousemove", (e) => {
//         let x = e.clientX;
//         let y = e.clientY;

//         var divs = document.querySelectorAll("div");

//         for (let i = 0; i < divs.size(); i ++) {
//             var stil = getComputedStyle(divs[i]);
//             if (x <= parseInt(stil.left)) {
//                 divs[i].style.backgroundColor = "blue";
//             }
//             else {
//                 divs[i].backgroundColor = 'red';
//             }

//             divs[i].onmouseover = function() {
//                 this.style.backgroundColor = 'purple';
//             }
//         }
//     });
// }

window.onload = function()
{
	document.onmousemove = function()
	{
		var x = event.clientX;     
		var y = event.clientY;  
	
		var divuri = document.getElementsByTagName("div");
		for(d of divuri)
		{
			var stil = getComputedStyle(d);
			if(x <= parseInt(stil.left)) d.style.backgroundColor = "blue";
			else d.style.backgroundColor = "red";
			
			d.onmouseover = function()
			{
				this.style.backgroundColor = "purple";
			}
		}
	}
}