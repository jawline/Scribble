function generateMenuItems() {
	return '<a class="header-link" href="./index.html">Home</a><b class="header-vrule"></b><a class="header-link" href="./projects.html">Projects</a><b class="header-vrule"></b><a class="header-link" href="./Scribble/index.html">Scribble</a><b class="header-vrule"></b><a class="header-link" href="./servers.html">Servers</a><b class="header-vrule"></b><a class="header-link" href="./about.html">About</a><b class="header-vrule"></b><a class="header-link" href="./contact.html">Contact</a><img src="img/logo.png" style="margin-top: 0px; float: right; margin-right: 10px;"/>';
}

function setupMenu() {

	  $("#header-content").html( generateMenuItems() );
}
